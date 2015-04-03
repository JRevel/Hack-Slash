#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "../draw/screen.h"

class World;

class Entity
{
private:
    bool m_sleeping;
public:
    Entity();
    virtual void update(World &world) = 0;
    virtual void draw(Screen &screen) const = 0;
    virtual bool isDead() const = 0;
    void wakeUp();
    bool isSleeping() const;
};

class LivingEntity : public Entity
{
protected:
    vec2 m_pos;
    float m_r, m_range;
    int m_PVs;

public:
    LivingEntity(vec2 pos, float r, int PVs, float range);
    void move(vec2 dir);
    void damage(int damage);
    virtual bool isDead() const;

    vec2 pos() const;
    float r() const;
    float getRange() const;
};

#include "world.h"

#endif // ENTITY_H_INCLUDED
