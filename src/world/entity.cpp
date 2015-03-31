#include <SDL2/SDL.h>
#include "entity.h"

LivingEntity::LivingEntity(vec2 pos, float r, int PVs, float range) : m_pos(pos), m_r(r), m_PVs(PVs), m_range(range)
{

}

void LivingEntity::move(vec2 dir)
{
    m_pos += dir;
}

bool LivingEntity::isDead() const
{
    return m_PVs <= 0;
}

void LivingEntity::damage(int dmg)
{
    m_PVs -= dmg;
}

vec2 LivingEntity::pos() const
{
    return m_pos;
}


float LivingEntity::r() const
{
    return m_r;
}

float LivingEntity::getRange() const
{
    return m_range;
}
