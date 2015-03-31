#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED

#include "../entity.h"
#include "direction.h"
#include "projectile/projectile.h"

class World;

class Effect
{
protected:
    Effect *m_parent;
public:
    Effect();
    ~Effect();
    void setParent(Effect *effect);
    virtual void applyEffect(World &world, Direction &target) = 0;
    virtual float getRange() const = 0;
    virtual vec2 getPos() const = 0;
};

class CastEffect : public Effect
{
private:
    Effect *m_child;
    LivingEntity &m_caster;

public:
    CastEffect(LivingEntity &caster, Effect *child);
    ~CastEffect();
    virtual void applyEffect(World &world, Direction &target);
    virtual float getRange() const;
    virtual vec2 getPos() const;
};

class ProjectileEffect : public Effect
{
private:
    Effect *m_effect;
    float m_speed;
    int m_duration, m_damage;
public:
    ProjectileEffect(Effect *effect, float speed, int duration, int damage);
    ~ProjectileEffect();
    virtual void applyEffect(World &world, Direction &target);
    virtual float getRange() const;
    virtual vec2 getPos() const;
};

#endif // EFFECT_H_INCLUDED
