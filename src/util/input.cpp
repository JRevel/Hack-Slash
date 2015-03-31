#include <SDL2/SDL.h>
#include "input.h"

Input::Input() : m_time(1), m_closed(false)
{
    m_buttons = new int[10];
    for(int i=0; i<10; i++)
        m_buttons[i] = 0;
    m_keys = new int[SDL_NUM_SCANCODES];
    for(int i=0; i<SDL_NUM_SCANCODES; i++)
        m_keys[i] = 0;
}

Input::~Input()
{
    delete[] m_buttons;
    delete[] m_keys;
}

void Input::update()
{
    m_mouseMotion = vec2(0, 0);
    m_time++;
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_CLOSE)
                    m_closed = true;
                break;
            case SDL_KEYDOWN:
                m_keys[event.key.keysym.scancode] = m_time;
                break;
            case SDL_KEYUP:
                m_keys[event.key.keysym.scancode] = -m_time;
                break;
            case SDL_MOUSEMOTION:
                m_mouseMotion.x = event.motion.x;
                m_mouseMotion.y = event.motion.y;
                m_mousePos.x = event.motion.x;
                m_mousePos.y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                m_buttons[event.button.button] = m_time;
                break;
            case SDL_MOUSEBUTTONUP:
                m_buttons[event.button.button] = -m_time;
        }
    }
}

bool Input::keyPressed(int key) const
{
    return m_keys[key] == m_time;
}

bool Input::keyReleased(int key) const
{
    return m_keys[key] == -m_time;
}

bool Input::keyDown(int key) const
{
    return m_keys[key] > 0;
}

bool Input::keyUp(int key) const
{
    return m_keys[key] <= 0;
}

bool Input::isClosed() const
{
    return m_closed;
}

vec2 Input::mousePos() const
{
    return m_mousePos;
}

vec2 Input::mouseMotion() const
{
    return m_mouseMotion;
}

bool Input::isMouseMoving() const
{
    return m_mouseMotion.x != 0 || m_mouseMotion.y != 0;
}

bool Input::buttonPressed(int button) const
{
    return m_buttons[button] == m_time;
}

bool Input::buttonReleased(int button) const
{
    return m_buttons[button] == -m_time;
}

bool Input::buttonDown(int button) const
{
    return m_buttons[button] > 0;
}

bool Input::buttonUp(int button) const
{
    return m_buttons[button] <= 0;
}

void Input::setClosed(bool flag)
{
    m_closed = flag;
}
