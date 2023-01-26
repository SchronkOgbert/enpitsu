//
// Created by weekendUM on 1/25/2023.
//

#ifndef ENPITSU_INPUTEVENTS_H
#define ENPITSU_INPUTEVENTS_H
namespace enpitsu
{
    struct MouseEvent
    {
        enum Event
        {
            RIGHT_MOUSE_BUTTON,
            LEFT_MOUSE_BUTTON,
            MIDDLE_MOUSE_BUTTON
        };
        MouseEvent::Event event;
        float scrollValue;

        MouseEvent() = default;

        MouseEvent(const MouseEvent::Event &event, const float &scrollValue = 0) :
                event(event),
                scrollValue(scrollValue)
        {}
    };

    struct KeyEvent
    {
        enum Event
        {
            KEY_A,
            KEY_B,
            KEY_C,
            KEY_D,
            KEY_E,
            KEY_F,
            KEY_G,
            KEY_H,
            KEY_I,
            KEY_J,
            KEY_K,
            KEY_L,
            KEY_M,
            KEY_N,
            KEY_O,
            KEY_P,
            KEY_Q,
            KEY_R,
            KEY_S,
            KEY_T,
            KEY_U,
            KEY_V,
            KEY_W,
            KEY_X,
            KEY_Y,
            KEY_Z,
            KEY_1,
            KEY_2,
            KEY_3,
            KEY_4,
            KEY_5,
            KEY_6,
            KEY_7,
            KEY_8,
            KEY_9,
            KEY_0,
            KEY_LEFT,
            KEY_RIGHT,
            KEY_UP,
            KEY_DOWN
        };
        KeyEvent::Event event;

        KeyEvent() = default;

        KeyEvent(const KeyEvent::Event &event) : event(event)
        {}
    };

    class InputEvents
    {
    public:
        virtual void OnMouseClick(const MouseEvent &event) = 0;

        virtual void OnKeyPressed(const KeyEvent &event) = 0;

        virtual void OnKeyReleased(const KeyEvent &event) = 0;
    };
}
#endif //ENPITSU_INPUTEVENTS_H
