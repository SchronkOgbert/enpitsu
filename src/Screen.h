//
// Created by weekendUM on 1/23/2023.
//

#ifndef ENPITSU_SCREEN_H
#define ENPITSU_SCREEN_H

#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Exception.h"
#include <string>

#ifdef _MSC_VER
#define strdup _strdup
#endif

namespace enpitsu
{

    class BadInitException : public Exception
    {
    public:
        BadInitException() : Exception("Screen could not be properly initialized")
        {}
    };

    class BadCustomInitException : public Exception
    {
    public:
        BadCustomInitException() : Exception("Your custom init function failed")
        {}
    };

    class Screen
    {
        static int screenCount;
    public:
        Screen() = delete;

        // default constructor
        explicit Screen
                (
                        const std::tuple<int, int> &size,
                        const bool &fullScreen = false,
                        const std::function<bool()> &customInit = []()
                        { return true; }
                );

        //move constructor
        explicit Screen
                (
                        const std::tuple<int, int> &&size,
                        const bool &&fullScreen = false,
                        const std::function<bool()> &&customInit = []()
                        { return true; }
                ) : Screen(size, fullScreen, customInit)
        {}

        //destructor
        ~Screen();

        void defaultInitialize();
    };
}
#endif //ENPITSU_SCREEN_H
