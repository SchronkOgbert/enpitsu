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
#include "InputEvents.h"
#include <memory>
#include <mutex>

namespace enpitsu
{
    class Object;

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
        bool shouldDestroy;

        //control variables

        //references
        std::shared_ptr<std::list<std::shared_ptr<Object>>> objects;

        //private events
        void sendPress(KeyEvent event) const;

        void sendRelease(const KeyEvent & event);

        void updateScreenDefaults();

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

        bool addObject(std::shared_ptr<Object> obj);

        bool removeObject(std::shared_ptr<Object> obj);

        //events
        /**
         * Function that starts the screen activity\n
         * This is a blocking function, it should be placed just before the end of the program\n
         * Set all the properties of all the classes before calling this function
         */
        void start();

        /**
         * Function that calls the input events for all objects\n
         * It has to be public because of some quirks of glfw
         */
        void callKeyEvents(const int &key,
                           const int &scancode,
                           const int &action,
                           const int &mods);

    protected:

        //all the events below run sometime during the Screen::start function
        /**
         * Call init for all the objects the screen has a reference to
         */
        void callInit();

        /**
         * This function runs at the beginning of the start function\n
         * It calls Screen::setGLFWHints and Screen::createGLFWWindow
         */
        virtual void init();

        /**
         * Calls tick for all the objects the screen has a reference to
         * @param delta the time elapsed since the last tick was run
         */
        void callTick(const float &delta);

        /**
         * Override this function to define custom tick behaviour
         * @param delta the time elapsed since the last tick was run
         */
        virtual void tick(const float &delta);

        /**
         * Sets the hints for the GLFW window\n
         * Only override if you know what you're doing
         */
        virtual void setGLFWHints();

        /**
         * Creates the GLFW window\n
         * Only override if you know what you're doing
         */
        virtual void createGLFWWindow();

        /**
         * Call this function to destroy the window
         */
        virtual void destroy();
    };
}
#endif //ENPITSU_SCREEN_H
