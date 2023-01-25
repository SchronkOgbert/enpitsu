//
// Created by weekendUM on 1/25/2023.
//

#ifndef ENPITSU_INPUTEVENTS_H
#define ENPITSU_INPUTEVENTS_H

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

    MouseEvent(const MouseEvent::Event &event, const float &scrollValue = 0) :
            event(event),
            scrollValue(scrollValue)
    {}
};

struct KeyEvent
{
    enum Event
    {
        KEY_Q,
        KEY_W,
        KEY_E,
        KEY_R,
        KEY_T,
        KEY_Y,
        KEY_U,
        KEY_I,
        KEY_O,
        KEY_P,
        KEY_A,
        KEY_S,
        KEY_D,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_Z,
        KEY_X,
        KEY_C,
        KEY_V,
        KEY_B,
        KEY_N,
        KEY_M,
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

    KeyEvent(const KeyEvent::Event &event) : event(event)
    {}
};

class InputEvents
{
public:
    virtual void OnMouseClick(const MouseEvent &event) = 0;

    virtual void OnKeyClicked(const KeyEvent &event) = 0;

    virtual void OnKeyPressed(const KeyEvent &event) = 0;

    virtual void OnKeyReleased(const KeyEvent &event) = 0;
};

#endif //ENPITSU_INPUTEVENTS_H
