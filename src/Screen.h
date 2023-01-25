//
// Created by weekendUM on 1/23/2023.
//

#ifndef ENPITSU_SCREEN_H
#define ENPITSU_SCREEN_H

#include "defines.h"

#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Exception.h"
#include <string>
#include "Object.h"
#include <memory>

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

    class BadWindow : public Exception
    {
    public:
        BadWindow() : Exception("Could not create a window. Are the window hints valid?")
        {}
    };

    class Screen
    {
        static bool exists;

        //props
        std::tuple<int, int> size;
        bool fullScreen;
        GLFWwindow *window;
        std::string name;

        //references
        std::shared_ptr<std::vector<std::shared_ptr<Object>>> objects;

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

        bool addObject(const std::shared_ptr<Object> &obj);

        bool addObject(const std::shared_ptr<Object> &&obj)
        { return addObject(obj); }

        //events
        void start();

    protected:

        virtual void callTick(float delta);

        virtual void stop();
    };
}
#endif //ENPITSU_SCREEN_H
