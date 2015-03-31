#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include "entity.h"

class Monster : public LivingEntity
{
private:
    float m_speed, m_detectRange;
public:
    Monster(vec2 pos, float size, float speed, float detectRange, int PVs, float range);
    virtual void update(World &world);
    virtual void draw(Screen &screen) const;
};

#endif // MONSTER_H_INCLUDED
