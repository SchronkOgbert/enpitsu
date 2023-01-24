//
// Created by weekendUM on 1/23/2023.
//
#include <tuple>
#include <iostream>
#include "Screen.h"

int enpitsu::Screen::screenCount = 0;

enpitsu::Screen::Screen
        (const std::tuple<int, int> &size,
         const bool &fullScreen,
         const std::function<bool()> &customInit
        )
{
    //initialize glfw
    if(!screenCount)
    {
        if(glfwInit() == GLFW_FALSE)
        {
            glfwTerminate();
            throw BadInitException();
        }
    }
    screenCount++;

    //custom initialize functionality
    if(!customInit())
    {
        glfwTerminate();
        throw BadCustomInitException();
    }

    std::cout << "Created screen of size: " << std::get<0>(size) << 'x' << std::get<1>(size) << '\n';
}

enpitsu::Screen::~Screen()
{
    screenCount--;
    if(!screenCount)
    {
        glfwTerminate();
    }
}

