#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include "../../entity.h"

class Projectile : public Entity
{
private:
    vec2 m_pos, m_speed;
    float m_r;
    int m_duration, m_time, m_damage;

public:
    Projectile(vec2 pos, vec2 speed, float r, int duration, int damage);
    virtual void update(World &world);
    virtual void draw(Screen &screen) const;
    virtual bool isDead() const;
};

#endif // PROJECTILE_H_INCLUDED
