#include "color.h"

Color::Color() : m_r(255), m_g(255), m_b(255), m_a(255)
{

}

Color::Color(const Color &col) : m_r(col.m_r), m_g(col.m_g), m_b(col.m_b), m_a(col.m_a)
{

}

Color::Color(int r, int g, int b, int a) : m_r(r), m_g(g), m_b(b), m_a(a)
{

}

int Color::r() const
{
    return m_r;
}

int Color::g() const
{
    return m_g;
}

int Color::b() const
{
    return m_b;
}

int Color::a() const
{
    return m_a;
}

Uint32 Color::toUint() const
{
    return (m_a << 24) + (m_r << 16) + (m_g << 8) + m_b;
}
