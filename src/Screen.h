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

    class BadProcessCreation : public Exception
    {
    public:
        BadProcessCreation() : Exception("A screen already exists in this process. "
                                         "If you want to create multiple screens please create multiple processes")
        {}
    };

    class Screen
    {
        static bool exists;
    public:
        Screen() = delete;

        // default constructor
        explicit Screen
                (
                        const std::tuple<int, int> &size,
                        const bool &fullScreen = false
                );

        //move constructor
        explicit Screen
                (
                        const std::tuple<int, int> &&size,
                        const bool &&fullScreen = false
                ) : Screen(size, fullScreen)
        {}

        //destructor
        virtual ~Screen();

        //events
        void start();

        virtual void init();
        virtual void tick();
        virtual void stop();
    };
}
#endif //ENPITSU_SCREEN_H
