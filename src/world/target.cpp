#include <SDL2/SDL.h>
#include <iostream>

#include "target.h"
#include "../spell/effect.h"

Target::Target(LivingEntity &caster) : m_caster(caster)
{

}

SimpleTarget::SimpleTarget(LivingEntity &caster, vec2 target) : Target(caster), m_target(target)
{

}

vec2 SimpleTarget::getTargetPos() const
{
    return m_target;
}

bool SimpleTarget::isAtRange() const
{
    return (m_caster.pos()-m_target).length() < m_caster.r();
}

void SimpleTarget::targetReached(World &world) const
{

}

AttackTarget::AttackTarget(LivingEntity &caster, LivingEntity* target, Spell *spell) : Target(caster), m_target(target), m_spell(spell)
{

}

AttackTarget::~AttackTarget()
{
    delete m_spell;
}

vec2 AttackTarget::getTargetPos() const
{
    return m_target->pos();
}

bool AttackTarget::isAtRange() const
{
    return (m_caster.pos()-m_target->pos()).length() < m_caster.r() + m_target->r() + m_spell->getRange();
}

void AttackTarget::targetReached(World &world) const
{
    EffectData data;
    data.setEntity("target", m_target);
    data.setEntity("caster", &m_caster);
    data.setVec("pos", m_caster.pos());
    data.setVec("targetPos", m_target->pos());
    data.setVec("dir", m_target->pos()-m_caster.pos());
    world.addEffect(m_spell->cast(data));
}
