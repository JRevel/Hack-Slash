#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "entity.h"

class Target;

class Player : public LivingEntity
{
private:
    float m_speed;
    Target* m_target;

public:
    Player(vec2 pos, float r, float speed, int PVs, float range);
    virtual void update(World &world);
    virtual void draw(Screen &screen) const;
    virtual bool isDead() const;
    void setTarget(Target* target);
};

#endif // PLAYER_H_INCLUDED
