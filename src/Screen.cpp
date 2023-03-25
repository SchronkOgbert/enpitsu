#include "objects/Screen.h"
#include "objects/Object.h"
#include "helpers/InputEvents.h"
#include "objects/Camera3D.h"

bool enpitsu::Screen::exists = false;

using enpitsu::Object;

enpitsu::Screen::Screen
        (const Vector2 &size,
         const bool &fullScreen
        ) : size(size), fullScreen(fullScreen)
{
    if (exists)
    {
        throw BadProcessCreation();
    }
    exists = true;
    this->window = nullptr;
    this->name = "Window";
    this->objects = std::make_unique<std::list<std::unique_ptr<Object>>>();
    this->destroyQueue = std::make_unique<std::vector<Object *>>();
    this->shouldDestroy = false;
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
    if (!camera)
    {
        PLOG_WARNING << "This screen has no camera";
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
    }
}

void enpitsu::Screen::callTick(const float &delta)
{
    for (auto &obj: *objects)
    {
        obj->callTick(delta);
    }
    if (camera)
    {
        camera->callTick(delta);
    }
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
                        });
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
        auto *pos = &(obj->cursorPos);
        glfwGetCursorPos(glfwWindow, &(pos->x), &(pos->y));
//        println(pos->first, ' ', pos->second);
        pos->y = obj->getSize().y - pos->y;
        obj->callMouseEvents(button, action, mods, obj->cursorPos);
    });
    glfwSetErrorCallback([](int errorCode, const char *description)
                         {
                             std::cerr << description;
                             exit(errorCode);
                         });

    //load opengl
//    glewExperimental = true;
    glewInit();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void enpitsu::Screen::destroy()
{
    this->shouldDestroy = true;
}

void enpitsu::Screen::callInit()
{
    PLOGI << "Calling init for " << objects->size() << " objects";
    for (auto &obj: *objects)
    {
        obj->callInit();
    }
    if (camera)
    {
        PLOGI << "Calling init for camera";
        camera->callInit();
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
            PLOGE << "Event not implemented";
        }
    }
}

void enpitsu::Screen::sendPress(KeyEvent event) const
{
    for (auto &obj: *objects)
    {
        obj->callKeyPressed(event);
    }
    if (camera)
    {
        camera->callKeyPressed(event);
    }
}

void enpitsu::Screen::sendRelease(const KeyEvent &event)
{
    for (auto &obj: *objects)
    {
        obj->callKeyReleased(event);
    }
    if (camera)
    {
        camera->callKeyReleased(event);
    }
}

void enpitsu::Screen::updateScreenDefaults()
{
    checkDepth ? glClear(GL_COLOR_BUFFER_BIT) :
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    for (auto &obj: *objects)
    {
        action ? obj->callMousePressed(event) : obj->callMouseReleased(event);
    }
    if (camera)
    {
        action ? camera->callMousePressed(event) : camera->callMouseReleased(event);
    }
}

void enpitsu::Screen::enableCursor(const bool &enable)
{
    glfwSetInputMode(window, GLFW_CURSOR, enable ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

inline const enpitsu::Vector2 &enpitsu::Screen::getSize() const
{
    return size;
}

void enpitsu::Screen::setSize(const Vector2 &size)
{
    this->size = size;
    glfwSetWindowSize(window, size.x, size.y);
}

inline const enpitsu::Camera3D *enpitsu::Screen::getCamera3D() const
{
    return this->camera.get();
}

void enpitsu::Screen::setCamera3D(enpitsu::Camera3D *camera3D)
{
    this->camera = std::unique_ptr<Camera3D>(camera3D);
}

void enpitsu::Screen::showCursor(const bool &show)
{
    glfwSetInputMode(window, GLFW_CURSOR, show ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void enpitsu::Screen::removeObjectNow(Object *obj)
{
    bool success = false;
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

