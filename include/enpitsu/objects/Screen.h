#ifndef ENPITSU_SCREEN_H
#define ENPITSU_SCREEN_H

#include "enpitsu/helpers/defines.h" // this contains pretty much every import the project needs from std and 3rd party libraries

#include "enpitsu/helpers/Exception.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/helpers/InputEvents.h"
#include <functional>

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
                format("Could not remove object {}. Are you sure you added it using Screen::addObject?", obj))
        {
        }
    };

    /**
     * Class that manages the window
     * This is pretty much a god class
     */
    class Screen
    {
        friend class Object;

        friend class Camera3D;

        friend class Camera2D;

        //props
        Vector2 size;
        bool fullScreen;

        // misc
        bool checkDepth{false};
        std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> windowPtr;
        GLFWwindow *window;
        std::string name;
        bool shouldDestroy;
        Vector2 cursorPos;
        std::unique_ptr<Camera3D> camera3D;
        std::unique_ptr<Camera2D> camera2D;

        //control variables
        std::chrono::time_point<std::chrono::system_clock> before;
        std::chrono::time_point<std::chrono::system_clock> now;
        bool updateCamera3D = false;
        bool updateCamera2D = false;
        Vector3 lightPosition;
        Vector4 lightColor;

        //references
        std::unique_ptr<std::queue<std::unique_ptr<Object>>> objectsQueue;
        std::unique_ptr<std::list<std::unique_ptr<Object>>> objects;
        std::unique_ptr<std::vector<Object *>> destroyQueue;
        std::unique_ptr<std::vector<InputEvents *>> callableEvents;

        // geometry
        std::vector<GLfloat> cam3DMatrix;
        std::vector<GLfloat> cam2DMatrix;

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

        void callScreenSizeChanged();

    public:
        Screen() = delete;

        static unsigned screenCount;

        /**
         * The default constructor of the class
         * @param size size in pixels(width x height)
         * @param fullScreen whether it should be fullscreen or not(this doesn't actually work yet)
         */
        explicit Screen
                (
                        const Vector2 &size,
                        const bool &fullScreen = false
                );

        //destructor
        virtual ~Screen();

        /**
         * Adds an object to the screen
         * The object shall be added using the newObject<objectType T> function, where objectType is a concept
         * @tparam type object class(must be derived from enpitsu::Object
         * @param obj an r-value unique pointer that will be stripped(returned from newObject<objectType T>)
         * @return a raw pointer to the added object, this is the only way to get its reference, it cannot be retrieved later
         */
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
         * A good practice would be to have an object derived from enpitsu::ControlObject added in the screen's init to control other objects
         */
        void start();

        void stop();

        /**
         * Function that calls the keyboard events for all objects\n
         * It has to be public because of some quirks of glfw
         */
        void callKeyEvents(const int &key,
                           const int &scancode,
                           const int &action,
                           const int &mods);

        /**
         * Function that calls the mouse events for all objects\n
         * It has to be public because of some quirks of glfw
         */
        void callMouseEvents(const int &button,
                             const int &action,
                             const int &mods,
                             const Vector2 &pos);

        /**
         * Enables or disables the cursor
         * @param enable whether it should be enabled or disabled
         */
        void enableCursor(const bool &enable);

        /**
         * Shows or hides the cursor
         * @param show whether to show or hide the cursor
         */
        void showCursor(const bool &show);

        // getters and setters

        /**
         * get the window size
         * @return std::pair of <int, int>, first is width, second is height
         */
        [[nodiscard]] const Vector2 & getSize() const { return size; }

        /**
         * set the window size
         * @param size width x height expressed as a Vector2
         */
        void setSize(const Vector2 &size);

        /**
         * gets the camera attached to the screen
         * @return raw pointer to camera
         */
        [[nodiscard]] Camera3D* getCamera3D();

        /**
         * sets the screen camera
         * @param camera3D r-value unique_ptr(will be stripped)
         */
        void setCamera3D(std::unique_ptr<Camera3D>&& camera3D);

        Camera2D* getCamera2D() { return this->camera2D.get(); }

        void setCamera2D(std::unique_ptr<Camera2D>&& camera2D);

        /**
         * adds an object that should have input events called for it
         * @param eventHandler raw pointer to object
         */
        void addEventHandler(InputEvents* eventHandler);

        /**
         * sets the background color of the whole canvas(affects 2D and 3D)
         * @param newColor
         */
        void setBackgroundColor(const Vector4& newColor);

        /**
         * gets the current mouse position on the screen
         * @return width and height expressed as Vector2
         */
        [[nodiscard]] Vector2 getMousePosition() const;

        /**
         * sets the mouse position
         * @param newPosition width and height expressed as Vector2
         */
        void setMousePosition(const Vector2& newPosition);

        /**
         * this is only useful for OpenGL math, it gets the camera matrix, which is the projection matrix multiplied by the view matrix
         * @return projection * view
         */
        [[nodiscard]] const GLfloat *getCam3DMatrix() const { return &cam3DMatrix[0]; }

        /**
         * sets the camera matrix(which should be a result of the projection matrix multiplied by the view matrix)
         * @param camMatrix glm::mat4 with the desired data
         */
        void setCam3DMatrix(const GLfloat *camMatrix);

        [[nodiscard]] const GLfloat *getCam2DMatrix() const { return &cam2DMatrix[0]; };

        void setCam2DMatrix(const GLfloat* camMatrix);

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

        [[nodiscard]] const Vector3 &getLightPosition() const;

        void setLightPosition(const Vector3 &lightPosition);

        [[nodiscard]] const Vector4 &getLightColor() const;

        void setLightColor(const Vector4 &lightColor);

        void setVSyncFrameCount(const int& frameCount);

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
