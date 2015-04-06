#ifndef DIRECTION_H_INCLUDED
#define DIRECTION_H_INCLUDED

#include "../util/vec.h"
#include "entity.h"

class Direction
{
public:
    virtual vec2 getDirection(vec2 pos) = 0;
};

class SimpleDirection : public Direction
{
private:
    vec2 m_direction;
public:
    SimpleDirection(vec2 direction);
    virtual vec2 getDirection(vec2 pos);
};

class TargetDirection : public Direction
{
private:
    vec2 m_target;
public:
    TargetDirection(vec2 target);
    virtual vec2 getDirection(vec2 pos);
};

class EntityDirection : public Direction
{
private:
    LivingEntity *m_target;
public:
    EntityDirection(LivingEntity *target);
    virtual vec2 getDirection(vec2 pos);
};

#endif // DIRECTION_H_INCLUDED
