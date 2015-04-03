#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED

#include "../entity.h"
#include "direction.h"
#include "projectile/projectile.h"
#include <map>
#include <string>

using namespace std;

class World;

template<typename T>
class Node;

template<typename T>
class NodeRef;

class Effect
{
protected:
    map<string, Node<int>*> m_intOut;
    map<string, Node<float>*> m_floatOut;
    map<string, Node<vec2>*> m_vecOut;
    map<string, Node<Effect*>*> m_effectOut;
    map<string, Node<LivingEntity*>*> m_entityOut;
    map<string, Node<string>*> m_strOut;

    map<string, NodeRef<int>*> m_intIn;
    map<string, NodeRef<float>*> m_floatIn;
    map<string, NodeRef<vec2>*> m_vecIn;
    map<string, NodeRef<Effect*>*> m_effectIn;
    map<string, NodeRef<LivingEntity*>*> m_entityIn;
    map<string, NodeRef<string>*> m_strIn;

    Effect *m_parent;

public:
    Effect();
    ~Effect();
    virtual void connectTo(Effect *parent) = 0;
    virtual void applyEffect(World &world) = 0;

    void setParent(Effect *parent);

    void floatOut(string name, float val = 0);
    void intOut(string name, int val = 0);
    void vecOut(string name, vec2 val = vec2(0, 0));
    void strOut(string name, string val = "");
    void effectOut(string name, Effect* val = NULL);
    void entityOut(string name, LivingEntity* val = NULL);

    void floatIn(string name);
    void intIn(string name);
    void vecIn(string name);
    void strIn(string name);
    void effectIn(string name);
    void entityIn(string name);

    Node<float>* getFloatOut(string name);
    Node<int>* getIntOut(string name);
    Node<vec2>* getVecOut(string name);
    Node<string>* getStrOut(string name);
    Node<LivingEntity*>* getEntityOut(string name);
    Node<Effect*>* getEffectOut(string name);

    NodeRef<float>& getFloatIn(string name);
    NodeRef<int>& getIntIn(string name);
    NodeRef<vec2>& getVecIn(string name);
    NodeRef<string>& getStrIn(string name);
    NodeRef<LivingEntity*>& getEntityIn(string name);
    NodeRef<Effect*>& getEffectIn(string name);

    bool hasFloatOut(string name) const;
    bool hasIntOut(string name) const;
    bool hasVecOut(string name) const;
    bool hasStrOut(string name) const;
    bool hasEntitytOut(string name) const;
    bool hasEffectOut(string name) const;
};

class CastEffect : public Effect
{
private:
    Effect *m_effect;
public:
    CastEffect(LivingEntity &caster, Effect *child, LivingEntity *target);
    CastEffect(LivingEntity &caster, Effect *child, vec2 target);
    ~CastEffect();
    virtual void connectTo(Effect *parent);
    virtual void applyEffect(World &world);
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
    virtual void connectTo(Effect *parent);
    virtual void applyEffect(World &world);
};

class DamageEffect : public Effect
{
private:
    int m_damage;

public:
    DamageEffect(int damage);
    ~DamageEffect();
    virtual void connectTo(Effect *parent);
    virtual void applyEffect(World &world);
};

class EntityEffect : public Effect
{
private:
    Effect *m_effect;
    LivingEntity *m_target;

public:
    EntityEffect(Effect *effect, LivingEntity *target, vec2 dir);
    ~EntityEffect();
    virtual void applyEffect(World &world);
    virtual void connectTo(Effect *parent);
};

class DirEffect : public Effect
{
private:
    Effect *m_effect;
    LivingEntity *m_target;

public:
    DirEffect(Effect *effect, vec2 dir);
    ~DirEffect();
    virtual void applyEffect(World &world);
    virtual void connectTo(Effect *parent);
};

class SplitEffect : public Effect
{
private:
    Effect *m_effect;
    int m_count;
    float m_angle;
public:
    SplitEffect(Effect *effect, int splitCount, float angle);
    ~SplitEffect();

    virtual void applyEffect(World &world);
    virtual void connectTo(Effect *parent);
};

class MultiEffect : public Effect
{
private:
    Effect **m_effect;
    int m_count;
public:
    MultiEffect(Effect **effect, int effectCount);
    ~MultiEffect();

    virtual void applyEffect(World &world);
    virtual void connectTo(Effect *parent);
};

class TimedEffect : public Effect
{
public:
    virtual void update() = 0;
    virtual bool isOver() const = 0;
};

class CyclicEffect : public TimedEffect
{
private:
    int m_time, m_period, m_times;
    Effect *m_effect;

public:
    CyclicEffect(int period, int times);

    virtual void applyEffect(World &world);
    virtual void connectTo(Effect *parent);
    virtual void update();
    virtual bool isOver() const;
};

#endif // EFFECT_H_INCLUDED
