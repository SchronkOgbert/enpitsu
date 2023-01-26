//
// Created by weekendUM on 1/23/2023.
//
#include <tuple>
#include <iostream>
#include <chrono>
#include <ctime>
#include "Screen.h"
#include "InputEvents.h"

bool enpitsu::Screen::exists = false;

enpitsu::Screen::Screen
        (const std::tuple<int, int> &size,
         const bool &fullScreen
        )
{
    if (exists)
    {
        throw BadProcessCreation();
    }
    exists = true;
    this->size = size;
    this->fullScreen = fullScreen;
    this->window = nullptr;
    this->name = "Window";
    this->objects = std::make_shared<std::vector<std::shared_ptr<Object>>>(std::vector<std::shared_ptr<Object>>());
    this->shouldDestroy = false;
    if (glfwInit() == GLFW_FALSE)
    {
        glfwTerminate();
        throw BadInitException();
    }
}

enpitsu::Screen::~Screen()
{
    if (window)
    {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void enpitsu::Screen::start()
{
    this->init();

    this->callInit(); //call this after the init actually runs the code and adds the objects

    auto before = std::chrono::system_clock::now();
    auto now = before;
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
            std::get<0>(size),
            std::get<1>(size),
            name.c_str(),
            nullptr,
            nullptr
    );
    if (!window)
    {
        throw BadWindow();
    }
    glfwMakeContextCurrent(window);
}

void enpitsu::Screen::callTick(const float &delta)
{
    for (auto &obj: *objects)
    {
        obj->callTick(delta);
    }
}

bool enpitsu::Screen::addObject(std::shared_ptr<Object> obj)
{
    std::cout << "Add object " << obj << " to screen\n";
    objects->push_back(obj);
    std::cout << "There are " << objects->size() << " objects after this operation\n";
    return true;
}

void enpitsu::Screen::setGLFWHints()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_DEFAULT_MAJOT_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_DEFAULT_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, OPENGL_DEFAULT_PROFILE);
}

void enpitsu::Screen::tick(const float &delta)
{
//    std::cout << "delta: " << delta << '\n';
    if (glfwWindowShouldClose(window))
    {
        this->destroy();
        return;
    }
    updateScreenDefaults();
    this->callTick(delta);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void enpitsu::Screen::init()
{
    this->setGLFWHints();
    this->createGLFWWindow();
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, [](GLFWwindow *windowRef, int key, int scancode, int action, int mods)
    {
        static_cast<Screen*>(glfwGetWindowUserPointer(windowRef))->callKeyEvents(
                key,
                scancode,
                action,
                mods
                );
    });
    gladLoadGL();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void enpitsu::Screen::destroy()
{
    this->shouldDestroy = true;
}

void enpitsu::Screen::callInit()
{
    std::cout << "Calling init for " << objects->size() << " objects\n";
    for (auto &obj: *objects)
    {
        obj->callInit();
    }
}

void enpitsu::Screen::callKeyEvents(const int &key,
                                    const int &scancode,
                                    const int &action,
                                    const int &mods)
{
    KeyEvent event{};
    if(key >=65 && key <= 90)
    {
        event = KeyEvent(KeyEvent::Event(key - 65));
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
            std::cerr << "Event not implemented\n";
        }
    }

}

void enpitsu::Screen::sendPress(KeyEvent event) const
{
    for(auto &obj : *objects)
    {
        obj->callKeyPressed(event);
    }
}

void enpitsu::Screen::sendRelease(const KeyEvent &event)
{
    for(auto &obj : *objects)
    {
        obj->callKeyReleased(event);
    }
}

void enpitsu::Screen::updateScreenDefaults()
{
    int x, y;
    glfwGetWindowSize(window, &x, &y);
    this->size = std::make_tuple(x, y);
    glViewport(0, 0, x, y);
    glClear(GL_COLOR_BUFFER_BIT);
}

