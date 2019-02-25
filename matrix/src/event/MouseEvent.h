#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "matrix/src/Core.h"
#include "matrix/src/event/Event.h"

namespace Matrix {

    class MATRIX_API MouseEvent : public Event {
    public:
        MouseEvent() {}
        ~MouseEvent() {}

        void printEventType() const override;
    protected:
        int m_KeyCode;
        int m_X, m_Y;
    private:
        EventType event = e_DefaultMouse;
    };

    class MATRIX_API MouseButtonPressed : public MouseEvent {
    public:
        MouseButtonPressed(int button)
            : m_KeyCode(button) {}
        ~MouseButtonPressed() {}

        void printEventType() const override;
    private:
        EventType event = e_MouseButtonPressed;
        int m_KeyCode;
    };

    class MATRIX_API MouseButtonReleased : public MouseEvent {
    public:
        MouseButtonReleased(int button)
            : m_KeyCode(button) {}
        ~MouseButtonReleased() {}

        void printEventType() const override;
    private:
        EventType event = e_MouseButtonReleased;
        int m_KeyCode;
    };

    class MouseMoved : public MouseEvent {
    public:
        MouseMoved(int x, int y)
            : m_X(x), m_Y(y) {}
        ~MouseMoved() {}

        void printEventType() const override;
    private:
        EventType event = e_MouseMoved;
        int m_X;
        int m_Y;
    };
}

#endif // MOUSEEVENT_H