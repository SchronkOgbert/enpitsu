//
// Created by weekendUM on 1/23/2023.
//
#include <tuple>
#include <iostream>
#include "Screen.h"

bool enpitsu::Screen::exists = false;

enpitsu::Screen::Screen
        (const std::tuple<int, int> &size,
         const bool &fullScreen
        )
{
    if(exists)
    {
        throw BadProcessCreation();
    }
    exists = true;
    this->size = size;
    this->fullScreen = fullScreen;
    if(glfwInit() == GLFW_FALSE)
    {
        glfwTerminate();
        throw BadInitException();
    }

    std::cout << "Created screen of size: " << std::get<0>(size) << 'x' << std::get<1>(size) << '\n';
}

enpitsu::Screen::~Screen()
{
    std::cout << "Screen::~Screen\n";
    glfwTerminate();
}

void enpitsu::Screen::start()
{
    this->init();
    this->callTick();
}

void enpitsu::Screen::init()
{
    std::cout << "Screen::init\n";
}

void enpitsu::Screen::callTick()
{
    std::cout << "Screen::callTick\n";
}

void enpitsu::Screen::stop()
{
    std::cout << "Screen::stop\n";
}

