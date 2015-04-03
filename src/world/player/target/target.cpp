#include <SDL2/SDL.h>

#include "target.h"
#include "../../fight/effect.h"
#include "../../fight/node.h"

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

AttackTarget::AttackTarget(LivingEntity &caster, LivingEntity* target, Effect *effect) : Target(caster), m_target(target), m_effect(effect)
{

}

AttackTarget::~AttackTarget()
{
    delete m_effect;
}

vec2 AttackTarget::getTargetPos() const
{
    return m_target->pos();
}

bool AttackTarget::isAtRange() const
{
    return (m_caster.pos()-m_target->pos()).length() < m_caster.r() + m_target->r() + m_effect->getFloatOut("range")->getValue();// + m_effect->getFloat("range");
}

void AttackTarget::targetReached(World &world) const
{
    CastEffect(m_caster, m_effect, m_target).applyEffect(world);
}
