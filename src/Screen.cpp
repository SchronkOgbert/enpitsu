#include "enpitsu/objects/Screen.h"
#include "GLFW/glfw3.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/objects/Object.h"
#include "enpitsu/helpers/InputEvents.h"
#include "enpitsu/objects/Camera3D.h"
#include "enpitsu/objects/Object3D.h"
#include "enpitsu/objects/Camera2D.h"
#include "glm/gtx/transform.hpp"
#include <utility>

using enpitsu::Object;

enpitsu::Screen::Screen
        (const Vector2 &size,
         const bool &fullScreen
        ) : size(size), fullScreen(fullScreen)
{
    this->window = nullptr;
    this->name = "Window";
    this->objects = std::make_unique<std::list<std::unique_ptr<Object>>>();
    this->objectsQueue = std::make_unique<std::queue<std::unique_ptr<Object>>>();
    this->destroyQueue = std::make_unique<std::vector<Object *>>();
    this->callableEvents = std::make_unique<std::vector<InputEvents *>>();
    this->shouldDestroy = false;
    this->cam3DMatrix = std::vector<GLfloat>(16);
    this->cam2DMatrix = std::vector<GLfloat>(16);
    this->setCam3DMatrix(glm::value_ptr(glm::mat4(1)));
    this->setCam2DMatrix(glm::value_ptr(glm::translate(glm::mat4(1), Vector3(0, 0, 1280))));
    if (glfwInit() == GLFW_FALSE)
    {
        glfwTerminate();
        throw BadInitException();
    }
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::verbose, &consoleAppender);
}

enpitsu::Screen::~Screen()
{
    for (auto &obj: *objects)
    {
        obj->onDestroy();
    }
    if (window)
    {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void enpitsu::Screen::start()
{
    if (!camera3D)
    {
        PLOG_WARNING << "This screen has no camera3D";
    }
    if(!camera2D)
    {
        PLOGW << "This screen has no camera2D";
    }
    this->init();

    this->callInit(); //call this after the init actually runs the code and adds the objects

    before = std::chrono::system_clock::now();
    now = before;
    std::chrono::duration<float> delta{};
    while (!shouldDestroy)
    {
        now = std::chrono::system_clock::now();
        delta = now - before;
        this->tick(delta.count());
        before = now;
    }
}

void enpitsu::Screen::createGLFWWindow()
{
    window = glfwCreateWindow(
            static_cast<int>(size.x),
            static_cast<int>(size.y),
            name.c_str(),
            nullptr,
            nullptr
    );
    if (!window)
    {
        throw BadWindow();
    }
    glfwMakeContextCurrent(window);
    if (glfwRawMouseMotionSupported())
    {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    } else
    {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
        PLOGW << "Raw mouse motion not supported";
    }
}

void enpitsu::Screen::callTick(const float &delta)
{
    for (auto &obj: *objects)
    {
        obj->callTick(delta);
    }
    updateCamera3D = false;
    updateCamera2D = false;
    if (camera3D)
    {
        camera3D->callTick(delta);
    }
    if (camera2D)
    {
        camera2D->callTick(delta);
    }
    moveObjectsFromQueue();
}

void enpitsu::Screen::setGLFWHints()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_DEFAULT_MAJOT_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_DEFAULT_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, OPENGL_DEFAULT_PROFILE);
}

void enpitsu::Screen::tick(const float &delta)
{
    if (glfwWindowShouldClose(window))
    {
        this->destroy();
        return;
    }
    updateScreenDefaults();
    this->callTick(delta);
    glfwPollEvents();
    std::jthread destroyer([this]
                           {
                               this->destroyObjectsFromQueue();
                           }); // this may not actually be needed
    glfwSwapBuffers(this->window);
}

void enpitsu::Screen::init()
{
    this->setGLFWHints();
    this->createGLFWWindow();
    //set callbacks
    glfwSetWindowUserPointer(window, this); //needed for callbacks

    glfwSetKeyCallback(window, [](GLFWwindow *windowRef, int key, int scancode, int action, int mods)
    {
        static_cast<Screen *>(glfwGetWindowUserPointer(windowRef))->callKeyEvents(
                key,
                scancode,
                action,
                mods
        );
    });
    glfwSetWindowSizeCallback(window, [](GLFWwindow *glfwWindow, int width, int height)
    {
        auto *screen = static_cast<Screen *>(glfwGetWindowUserPointer(glfwWindow));
        screen->size = Vector2(width, height);
        glViewport(0, 0, width, height);
        screen->now = std::chrono::system_clock::now();
        std::chrono::duration<float> delta = screen->now - screen->before;
        screen->tick(delta.count());
        screen->before = screen->now;

    });
    glfwSetCursorPosCallback(window, [](GLFWwindow *glfwWindow, double xpos, double ypos)
    {
        static_cast<Screen *>(glfwGetWindowUserPointer(glfwWindow));
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow *glfwWindow, int button, int action, int mods)
    {
        auto obj = static_cast<Screen *>(glfwGetWindowUserPointer(glfwWindow));
        double x, y;
        glfwGetCursorPos(glfwWindow, &x, &y);
        y = obj->getSize().y - y;
        obj->cursorPos = {x, y};
        obj->callMouseEvents(button, action, mods, obj->cursorPos);
    });
    glfwSetErrorCallback([](int errorCode, const char *description)
                         {
                             std::cerr << description;
                             exit(errorCode);
                         });

    //load opengl
    glewInit();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    moveObjectsFromQueue();
}

void enpitsu::Screen::destroy()
{
    this->shouldDestroy = true;
}

void enpitsu::Screen::callInit()
{
    if (camera3D)
    {
        PLOGD << "Calling init for camera3D";
        camera3D->callInit();
    }
    if (camera2D)
    {
        camera2D->callInit();
    }
}

void enpitsu::Screen::callKeyEvents(const int &key,
                                    const int &scancode,
                                    const int &action,
                                    const int &mods)
{
    KeyEvent event{};
    if (key >= 65 && key <= 90)
    {
        event = KeyEvent(KeyEvent::Event(key - 65));
    } else if (key < 58 && key > 47)
    {
        event = KeyEvent(KeyEvent::Event(key - 22));

    } else
    {
        switch (key)
        {

        }
    }
    switch (action)
    {
        case GLFW_PRESS:
        {
            sendPress(event);
            break;
        }
        case GLFW_RELEASE:
        {
            sendRelease(event);
            break;
        }
        default:
        {
//            PLOGE << "Event not implemented";
        }
            break;
    }
}

void enpitsu::Screen::sendPress(KeyEvent event) const
{
    for (auto obj: *callableEvents)
    {
        obj->OnKeyPressed(event);
    }
}

void enpitsu::Screen::sendRelease(const KeyEvent &event)
{
    for (auto &obj: *callableEvents)
    {
        obj->OnKeyReleased(event);
    }
}

void enpitsu::Screen::updateScreenDefaults() const
{
    checkDepth ? glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) :
    glClear(GL_COLOR_BUFFER_BIT);
}

void enpitsu::Screen::removeObject(Object *obj)
{
    destroyQueue->push_back(obj);
}

void enpitsu::Screen::callMouseEvents(const int &button, const int &action, const int &mods,
                                      const Vector2 &pos)
{
    MouseEvent event{};
    event.screenPos = pos;
    switch (button)
    {
        case GLFW_MOUSE_BUTTON_LEFT:
        {
            event.button = MouseEvent::Event::LEFT_MOUSE_BUTTON;
            break;
        }
        case GLFW_MOUSE_BUTTON_RIGHT:
        {
            event.button = MouseEvent::Event::RIGHT_MOUSE_BUTTON;
            break;
        }
        case GLFW_MOUSE_BUTTON_MIDDLE:
        {
            event.button = MouseEvent::Event::MIDDLE_MOUSE_BUTTON;
            break;
        }
        default:
        {
            throw BadMouseInput();
        }
    }
    for (auto &obj: *callableEvents)
    {
        action ? obj->OnMousePressed(event) : obj->OnMouseReleased(event);
    }
}

void enpitsu::Screen::enableCursor(const bool &enable)
{
    glfwSetInputMode(window, GLFW_CURSOR, enable ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

void enpitsu::Screen::setSize(const Vector2 &size)
{
    this->size = size;
    glfwSetWindowSize(window, size.x, size.y);
}

enpitsu::Camera3D *enpitsu::Screen::getCamera3D()
{
    return this->camera3D.get();
}

void enpitsu::Screen::setCamera3D(std::unique_ptr<Camera3D> &&camera3D)
{
    this->camera3D = std::move(camera3D);
}

void enpitsu::Screen::showCursor(const bool &show)
{
    glfwSetInputMode(window, GLFW_CURSOR, show ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void enpitsu::Screen::removeObjectNow(Object *obj)
{
    bool success = false;
    std::erase(*callableEvents, dynamic_cast<InputEvents *>(obj));
    objects->remove_if([obj, &success](std::unique_ptr<Object> &el)
                       {
                           if (success) return false;
                           success = obj == el.get();
                           return obj == el.get();
                       });
    if (!success) throw BadObjectRemove(obj);
}

void enpitsu::Screen::destroyObjectsFromQueue()
{
    if (this->destroyQueue->empty()) return;
    for (auto &el: *destroyQueue)
    {
        removeObjectNow(el);
    }
    this->destroyQueue->clear();
}

inline bool enpitsu::Screen::getCheckDepth() const
{
    return checkDepth;
}

void enpitsu::Screen::setCheckDepth(bool checkDepth)
{
    checkDepth ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    this->checkDepth = checkDepth;
}

void enpitsu::Screen::addEventHandler(enpitsu::InputEvents *eventHandler)
{
    callableEvents->push_back(eventHandler);
    PLOGD << "Callables: " << callableEvents->size();
}

void enpitsu::Screen::moveObjectsFromQueue()
{
    while (!objectsQueue->empty())
    {
        PLOGD << "Adding " << objectsQueue->front().get();
        objectsQueue->front()->callInit();
        auto eventHandler = dynamic_cast<InputEvents *>(objectsQueue->front().get());
        if (eventHandler)
        {
            callableEvents->push_back(eventHandler);
        }
        objects->push_back(std::move(objectsQueue->front()));
        objectsQueue->pop();
        PLOGD << std::format("{} elements left in queue", objectsQueue->size());
    }
}

void enpitsu::Screen::setBackgroundColor(const Vector4 &newColor)
{
    glClearColor(newColor.x, newColor.y, newColor.z, newColor.a);
}

enpitsu::Vector2 enpitsu::Screen::getMousePosition() const
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return {x, y};
}

void enpitsu::Screen::setMousePosition(const enpitsu::Vector2 &newPosition)
{
    glfwSetCursorPos(window, newPosition.x, newPosition.y);
}

void enpitsu::Screen::setCam3DMatrix(const GLfloat *camMatrix)
{
    for (int i = 0; i < 16; i++)
    {
        if (this->cam3DMatrix[i] != camMatrix[i])
        {
            updateCamera3D = true;
            this->cam3DMatrix[i] = camMatrix[i];
        }
    }
}

void enpitsu::Screen::setCam2DMatrix(const GLfloat *camMatrix)
{
    for (int i = 0; i < 16; i++)
    {
        if (this->cam2DMatrix[i] != camMatrix[i])
        {
            updateCamera2D = true;
            this->cam2DMatrix[i] = camMatrix[i];
        }
    }
}

void enpitsu::Screen::setCamera2D(std::unique_ptr<Camera2D> &&camera2D)
{
    this->camera2D = std::move(camera2D);
}

