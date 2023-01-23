//
// Created by weekendUM on 1/23/2023.
//
#include <tuple>
#include <iostream>
#include "Screen.h"

Screen::Screen(const std::tuple<int, int> &size, const bool &fullScreen)
{
    std::cout << "Created screen of size: " << std::get<0>(size) << 'x' << std::get<1>(size) << '\n';
}

