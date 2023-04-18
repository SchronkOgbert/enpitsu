#ifndef ENPITSU_SCREEN_H
#define ENPITSU_SCREEN_H

#include "enpitsu/helpers/defines.h" // this contains pretty much every import the project needs from std and 3rd party libraries

#include "enpitsu/helpers/Exception.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/helpers/InputEvents.h"
#include <cstring>
#include <memory>
#include <utility>
#include <vector>

namespace enpitsu
{
    class Object;

    class Camera3D;

    class InputEvents;

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
        explicit BadObjectRemove(void *obj) : Exception(
                std::format("Could not remove object {}. Are you sure you added it using Screen::addObject?", obj))
        {
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
    public:
        /**
         * check whether the depth is checked(used in 3D rendering)
         * @return value, default is false
         */
        [[nodiscard]] bool getCheckDepth() const;

        /**
         * enables or disables depth checking(used in 3D rendering)
         * @param checkDepth true for enable, false for disable, default false
         */
        void setCheckDepth(bool checkDepth);

    private:
        // misc
        bool checkDepth{false};
        GLFWwindow *window;
        std::string name;
        bool shouldDestroy;
        Vector2 cursorPos;
        std::unique_ptr<Camera3D> camera;

        //control variables
        std::chrono::time_point<std::chrono::system_clock> before;
        std::chrono::time_point<std::chrono::system_clock> now;
        bool updateCamera = false;

        //references
        std::unique_ptr<std::queue<std::unique_ptr<Object>>> objectsQueue;
        std::unique_ptr<std::list<std::unique_ptr<Object>>> objects;
        std::unique_ptr<std::vector<Object *>> destroyQueue;
        std::unique_ptr<std::vector<InputEvents *>> callableEvents;

        // geometry
        std::vector<GLfloat> camMatrix;

        //private events
        void sendPress(KeyEvent event) const;

        void sendRelease(const KeyEvent &event);

        void updateScreenDefaults() const;

        /**
         * adds the object to a destruction queue, it will get removed at the end of the frame
         * @param obj object to be removed
         */
        void removeObject(Object *obj);

        /**
         * removes an object immediately, without waiting, in exceedingly bad conditions it may cause lag spikes
         * @param obj
         */
        void removeObjectNow(Object *obj);

        void destroyObjectsFromQueue();

        void moveObjectsFromQueue();

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
                );

        //destructor
        virtual ~Screen();

        template<objectType type>
        type *addObject(std::unique_ptr<type> &&obj)
        {
            if (!obj) throw BadObjectAdd();
            PLOGD << "Add object " << obj.get() << " to screen";
            objectsQueue->push(std::move(obj));
            PLOGD << "There are " << objectsQueue->size() << " objects to be added after this operation";
            return static_cast<type*>(objectsQueue->back().get()); // after moving, obj loses its pointer
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
        [[nodiscard]] const Vector2 & getSize() const { return size; }

        void setSize(const Vector2 &size);

        [[nodiscard]] Camera3D* getCamera3D();

        void setCamera3D(std::unique_ptr<Camera3D>&& camera3D);

        void addEventHandler(InputEvents* eventHandler);

        void setBackgroundColor(const Vector4& newColor);

        [[nodiscard]] Vector2 getMousePosition() const;

        void setMousePosition(const Vector2& newPosition);

        [[nodiscard]] const GLfloat *getCamMatrix() const { return &camMatrix[0]; }

        void setCamMatrix(const GLfloat *camMatrix);

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
