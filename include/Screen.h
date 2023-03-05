#ifndef ENPITSU_SCREEN_H
#define ENPITSU_SCREEN_H

#include "defines.h" // this contains pretty much every import the project needs from std and 3rd party libraries

#include "Exception.h"
#include "GeometryEssentials.h"
#include "InputEvents.h"

namespace enpitsu
{
    class Object;

    class Camera3D;

    template<class Object>
    concept objectType =
    requires(Object t)
    {
        { t.callInit() };
    };

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

    class BadObjectAdd : public Exception
    {
    public:
        BadObjectAdd() : Exception("The object you are trying to add is nullptr.")
        {}
    };

    class BadObjectRemove : public Exception
    {
    public:
        explicit BadObjectRemove(void *obj) : Exception("Could not remove object. "
                                                        "Are you sure you added it using Screen::addObject?")
        {
            std::cerr << "object " << obj << '\n';
        }
    };

    class Screen
    {
        static bool exists;

        friend class Object;

        friend class Camera3D;

        //props
        Vector2 size;
        bool fullScreen;
        GLFWwindow *window;
        std::string name;
        bool shouldDestroy;
        Vector2 cursorPos;
        std::unique_ptr<Camera3D> camera;

        //control variables
        std::chrono::time_point<std::chrono::system_clock> before;
        std::chrono::time_point<std::chrono::system_clock> now;

        //references
        std::unique_ptr<std::list<std::unique_ptr<Object>>> objects;

        //private events
        void sendPress(KeyEvent event) const;

        void sendRelease(const KeyEvent &event);

        void updateScreenDefaults();

        void removeObject(Object *obj);



    public:
        Screen() = delete;

        // default constructor
        explicit Screen
                (
                        const Vector2 &size,
                        const bool &fullScreen = false
                );

        //move constructor
        explicit Screen
                (
                        const Vector2 &&size, // TODO change this to Vector2
                        const bool &&fullScreen = false
                ) : Screen(size, fullScreen)
        {}

        //destructor
        virtual ~Screen();

        template<objectType type>
        type *addObject(type *obj)
        {
            if (!obj) throw BadObjectAdd();
            PLOGD << "Add object " << obj << " to screen";
            objects->emplace_back(obj);
            obj->callInit();
            PLOGD << "There are " << objects->size() << " objects after this operation";
            return obj;
        }

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

        void callMouseEvents(const int &button,
                             const int &action,
                             const int &mods,
                             const Vector2 &pos);

        void enableCursor(const bool &enable);

        void showCursor(const bool &show);

        /**
         * get the window size
         * @return std::pair of <int, int>, first is width, second is height
         */
        [[nodiscard]] const Vector2 & getSize() const;

        void setSize(const Vector2 &size);

        [[nodiscard]] const Camera3D* getCamera3D() const;

        void setCamera3D(Camera3D* camera3D);

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
