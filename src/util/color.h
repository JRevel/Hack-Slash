#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include <SDL2/SDL.h>

class Color
{
private:
    Uint8 m_r, m_g, m_b, m_a;

public:
    Color();
    Color(Uint32 col);
    Color(const Color &col);
    Color(int R, int G, int B, int A = 255);
    Color(float r, float g, float b, float a = 1.0f);

    int r() const;
    int g() const;
    int b() const;
    int a() const;

    Uint32 toUint() const;
};

#endif // COLOR_H_INCLUDED
