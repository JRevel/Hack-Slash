#include <SDL2/SDL.h>

#include "direction.h"

SimpleDirection::SimpleDirection(vec2 direction) : m_direction(direction)
{

}

vec2 SimpleDirection::getDirection(vec2 pos)
{
    return m_direction.normalize();
}

TargetDirection::TargetDirection(vec2 target) : m_target(target)
{

}

vec2 TargetDirection::getDirection(vec2 pos)
{
    return (m_target-pos).normalize();
}

EntityDirection::EntityDirection(LivingEntity *target) : m_target(target)
{

}

vec2 EntityDirection::getDirection(vec2 pos)
{
    return (m_target->pos()-pos).normalize();
}
