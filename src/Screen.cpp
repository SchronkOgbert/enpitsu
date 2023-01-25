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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_DEFAULT_MAJOT_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_DEFAULT_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, OPENGL_DEFAULT_PROFILE);

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

    gladLoadGL();
    glViewport(0, 0, std::get<0>(size), std::get<1>(size));
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    auto before = std::chrono::system_clock::now();
    auto now = before;
    std::chrono::duration<float> delta{};
    while (!glfwWindowShouldClose(window))
    {
        now = std::chrono::system_clock::now();
        delta = now - before;
        this->callTick(delta.count());
        glfwPollEvents();
        before = now;
    }
}

void enpitsu::Screen::callTick(float delta)
{
    for (auto &obj: *objects)
    {
        obj->tick(delta);
    }
}

void enpitsu::Screen::stop()
{
    std::cout << "Screen::stop\n";
}

bool enpitsu::Screen::addObject(const std::shared_ptr<Object> &obj)
{
    objects->push_back(obj);
    return true;
}

