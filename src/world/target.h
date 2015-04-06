#ifndef TARGET_H_INCLUDED
#define TARGET_H_INCLUDED

#include "player.h"
#include "monster.h"

class Effect;
class Spell;

class Target
{
protected:
    LivingEntity &m_caster;

public:
    Target(LivingEntity &caster);
    virtual vec2 getTargetPos() const = 0;
    virtual bool isAtRange() const = 0;
    virtual void targetReached(World &world) const = 0;
};

class SimpleTarget : public Target
{
protected:
    vec2 m_target;

public:
    SimpleTarget(LivingEntity &caster, vec2 target);
    virtual vec2 getTargetPos() const;
    virtual bool isAtRange() const;
    virtual void targetReached(World &world) const;
};

class Monster;

class AttackTarget : public Target
{
protected:
    LivingEntity *m_target;
    Spell *m_spell;

public:
    AttackTarget(LivingEntity &caster, LivingEntity *target, Spell *spell);
    ~AttackTarget();
    virtual vec2 getTargetPos() const;
    virtual bool isAtRange() const;
    virtual void targetReached(World &world) const;
};

#endif // TARGET_H_INCLUDED

