#ifndef INPUT_INCLUDED
#define INPUT_INCLUDED

#include "vec.h"

class Input
{
public:
    Input();
    ~Input();

    void update();

    bool keyPressed(int key) const;
    bool keyReleased(int key) const;
    bool keyDown(int key) const;
    bool keyUp(int key) const;
    bool buttonPressed(int button) const;
    bool buttonReleased(int button) const;
    bool buttonDown(int button) const;
    bool buttonUp(int button) const;
    bool charPressed() const;

    bool isClosed() const;
    bool isMouseMoving() const;

    vec2 mousePos() const;
    vec2 mouseMotion() const;

    void setClosed(bool flag);

private:

    int *m_keys, *m_buttons;
    vec2 m_mousePos, m_mouseMotion;
    bool m_closed;
    int m_time;
};

#endif
