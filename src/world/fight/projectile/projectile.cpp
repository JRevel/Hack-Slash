#include <SDL2/SDL.h>

#include "projectile.h"

Projectile::Projectile(vec2 pos, vec2 speed, float r, int duration, int damage) : m_pos(pos), m_speed(speed), m_duration(duration), m_r(r), m_damage(damage), m_time(0)
{

}

void Projectile::update(World &world)
{
    m_pos += m_speed;
    m_time++;
}

bool Projectile::isDead() const
{
    return m_time >= m_duration;
}

void Projectile::draw(Screen &screen) const
{
    screen.drawCircle(m_pos, m_r, Color(0, 0, 255));
}
