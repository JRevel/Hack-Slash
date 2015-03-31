#include <SDL2/SDL.h>

#include "effect.h"

Effect::Effect() : m_parent(NULL)
{

}

Effect::~Effect()
{

}

void Effect::setParent(Effect *parent)
{
    m_parent = parent;
}

CastEffect::CastEffect(LivingEntity &caster, Effect *child) : m_caster(caster), m_child(child)
{
    m_child->setParent(this);
}

CastEffect::~CastEffect()
{
    delete m_child;
}

void CastEffect::applyEffect(World &world, Direction &dir)
{
    m_child->applyEffect(world, dir);
}

float CastEffect::getRange() const
{
    return m_child->getRange();
}

vec2 CastEffect::getPos() const
{
    return m_caster.pos();
}

ProjectileEffect::ProjectileEffect(Effect *effect, float speed, int duration, int damage) : m_effect(effect), m_speed(speed), m_duration(duration), m_damage(damage)
{

}

ProjectileEffect::~ProjectileEffect()
{
    delete m_effect;
}

void ProjectileEffect::applyEffect(World &world, Direction &dir)
{
    vec2 pos = getPos();
    world.addProjectile(new Projectile(pos, dir.getDirection(pos)*m_speed, 5, m_duration, m_damage));
}

float ProjectileEffect::getRange() const
{
    return m_speed*m_duration*0.9;
}

vec2 ProjectileEffect::getPos() const
{
    return m_parent->getPos();
}
