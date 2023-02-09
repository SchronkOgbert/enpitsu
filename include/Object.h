//
// Created by weekendUM on 1/24/2023.
//

#ifndef ENPITSU_OBJECT_H
#define ENPITSU_OBJECT_H

#include "defines.h"
#include "InputEvents.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Exception.h"

namespace enpitsu
{
    class BadGLObject : public Exception
    {
    public:
        BadGLObject() : Exception("Either the vao, vertexPosition or ebo could not be initialized")
        {}
    };

    class InputEvents;
    class Object
    {
        friend class Screen;
        InputEvents* eventHandler{nullptr};
    protected:
        Screen* screen;
    public:
        explicit Object(Screen *screen);

        void callTick(const float &delta);

        void callInit();

        void callKeyPressed(const KeyEvent & event);

        void callKeyReleased(const KeyEvent &event);

        void callMousePressed(const MouseEvent &event);

        void callMouseReleased(const MouseEvent &event);

        virtual ~Object();

        void destroy();

    protected:
        //events
        virtual void tick(const float &delta);

        virtual void init();

        /**
         * Specify what the object should do before getting destroyed
         */
        virtual void onDestroy();

        virtual void draw() = 0;
    };
}


#endif //ENPITSU_OBJECT_H
