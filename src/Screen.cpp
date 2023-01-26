//
// Created by weekendUM on 1/23/2023.
//
#include <tuple>
#include <iostream>
#include <chrono>
#include <ctime>
#include "Screen.h"

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

bool enpitsu::Screen::addObject(const std::shared_ptr<Object> &obj)
{
    objects->push_back(obj);
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
    if(glfwWindowShouldClose(window))
    {
        this->destroy();
        return;
    }
    this->callTick(delta);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void enpitsu::Screen::init()
{
    this->setGLFWHints();
    this->createGLFWWindow();
    gladLoadGL();
    this->callInit();
}

void enpitsu::Screen::destroy()
{
    this->shouldDestroy = true;
}

void enpitsu::Screen::callInit()
{
    for(auto &obj : *objects)
    {
        obj->callInit();
    }
}

