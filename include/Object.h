//
// Created by weekendUM on 1/24/2023.
//

#ifndef ENPITSU_OBJECT_H
#define ENPITSU_OBJECT_H

#include "defines.h"
#include "InputEvents.h"

namespace enpitsu
{
    class Screen;
    class InputEvents;
    class Object
    {
    protected:
        Screen* screen;
        InputEvents* eventHandler{nullptr};
    public:
        explicit Object(Screen *screen);

        void callTick(const float &delta);

        void callInit();

        void callKeyPressed(const KeyEvent & event);

        void callKeyReleased(const KeyEvent &event);

        void callMousePressed(const MouseEvent &event);

        void callMouseReleased(const MouseEvent &event);

        virtual ~Object();

    protected:
        //events
        virtual void tick(const float &delta);

        virtual void init();

        virtual void destroy();

        virtual void draw()
        {  };
    };
}


#endif //ENPITSU_OBJECT_H
