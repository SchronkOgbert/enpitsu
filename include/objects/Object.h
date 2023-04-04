//
// Created by weekendUM on 1/24/2023.
//

#ifndef ENPITSU_OBJECT_H
#define ENPITSU_OBJECT_H

#include "helpers/defines.h"
#include "helpers/InputEvents.h"
#include "helpers/Exception.h"

namespace enpitsu
{
    class BadGLObject : public Exception
    {
    public:
        BadGLObject() : Exception("Either the vao, vertexPosition or ebo could not be initialized")
        {}
    };

    class InputEvents;
    class Screen;
    class Object
    {
        friend class Screen;
        InputEvents* eventHandler{nullptr};

        bool queueDestroy{false};
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

        [[nodiscard]] bool isDestroyed() const { return queueDestroy; }

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
