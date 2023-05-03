#ifndef ENPITSU_OBJECT_H
#define ENPITSU_OBJECT_H

#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/helpers/defines.h"
#include "enpitsu/helpers/InputEvents.h"
#include "enpitsu/helpers/Exception.h"

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

        virtual ~Object();

        void destroy();

        [[nodiscard]] bool isDestroyed() const { return queueDestroy; }

    protected:
        //events
        virtual void screenSizeChanged(const Vector2& newSize);

        virtual void tick(const float &delta);

        virtual void init();

        /**
         * Specify what the object should do before getting destroyed
         */
        virtual void onDestroy();

        [[nodiscard]] bool shouldUpdateCamera3D() const;

        [[nodiscard]] bool shouldUpdateCamera2D() const;
    };
}


#endif //ENPITSU_OBJECT_H
