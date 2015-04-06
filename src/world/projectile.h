#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include "entity.h"


class Projectile : public Entity
{
private:
    vec2 m_pos, m_speed;
    float m_r;
    int m_duration, m_time;
    Spell* m_spell;
    bool m_isDead;
    LivingEntity *m_ignore;

public:
    Projectile(vec2 pos, vec2 speed, float r, int duration, Spell* spell, LivingEntity *ignore = NULL);
    ~Projectile();
    virtual void update(World &world);
    virtual void draw(Screen &screen) const;
    virtual bool isDead() const;
    void onCollision(World &world, LivingEntity *entity);
};

#endif // PROJECTILE_H_INCLUDED
