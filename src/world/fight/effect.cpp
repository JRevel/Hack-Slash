#include <SDL2/SDL.h>
#include <iostream>

#include "effect.h"
#include "node.h"
#include <cmath>

Effect::Effect() : m_parent(NULL)
{

}

Effect::~Effect()
{
    for(std::map<std::string, Node<int>*>::iterator it = m_intOut.begin(); it != m_intOut.end(); it++)
        delete it->second;
    for(std::map<std::string, Node<float>*>::iterator it = m_floatOut.begin(); it != m_floatOut.end(); it++)
        delete it->second;
    for(std::map<std::string, Node<vec2>*>::iterator it = m_vecOut.begin(); it != m_vecOut.end(); it++)
        delete it->second;
    for(std::map<std::string, Node<Effect*>*>::iterator it = m_effectOut.begin(); it != m_effectOut.end(); it++)
        delete it->second;
    for(std::map<std::string, Node<std::string>*>::iterator it = m_strOut.begin(); it != m_strOut.end(); it++)
        delete it->second;
    for(std::map<std::string, NodeRef<int>*>::iterator it = m_intIn.begin(); it != m_intIn.end(); it++)
        delete it->second;
    for(std::map<std::string, NodeRef<float>*>::iterator it = m_floatIn.begin(); it != m_floatIn.end(); it++)
        delete it->second;
    for(std::map<std::string, NodeRef<vec2>*>::iterator it = m_vecIn.begin(); it != m_vecIn.end(); it++)
        delete it->second;
    for(std::map<std::string, NodeRef<Effect*>*>::iterator it = m_effectIn.begin(); it != m_effectIn.end(); it++)
        delete it->second;
    for(std::map<std::string, NodeRef<std::string>*>::iterator it = m_strIn.begin(); it != m_strIn.end(); it++)
        delete it->second;
}

void Effect::floatOut(std::string name, float val) {m_floatOut[name] = new Node<float>(val);}
void Effect::intOut(std::string name, int val) {m_intOut[name] = new Node<int>(val);}
void Effect::vecOut(std::string name, vec2 val) {m_vecOut[name] = new Node<vec2>(val);}
void Effect::strOut(std::string name, string val) {m_strOut[name] = new Node<std::string>(val);}
void Effect::effectOut(std::string name, Effect* val) {m_effectOut[name] = new Node<Effect*>(val);}
void Effect::entityOut(std::string name, LivingEntity* val) {m_entityOut[name] = new Node<LivingEntity*>(val);}

void Effect::floatIn(std::string name) {m_floatIn[name] = new NodeRef<float>();}
void Effect::intIn(std::string name) {m_intIn[name] = new NodeRef<int>();}
void Effect::vecIn(std::string name) {m_vecIn[name] = new NodeRef<vec2>();}
void Effect::strIn(std::string name) {m_strIn[name] = new NodeRef<std::string>();}
void Effect::effectIn(std::string name) {m_effectIn[name] = new NodeRef<Effect*>();}
void Effect::entityIn(std::string name) {m_entityIn[name] = new NodeRef<LivingEntity*>();}

Node<float>*  Effect::getFloatOut(string name)
{
    if(m_floatOut[name] != NULL)
        return m_floatOut[name];
    if(m_parent != NULL)
        return m_parent->getFloatOut(name);
    return NULL;
}

Node<int>* Effect::getIntOut(string name)
{
    if(m_intOut[name] != NULL)
        return m_intOut[name];
    if(m_parent != NULL)
        return m_parent->getIntOut(name);
    return NULL;
}

Node<vec2>* Effect::getVecOut(string name)
{
    if(m_vecOut[name] != NULL)
        return m_vecOut[name];
    if(m_parent != NULL)
        return m_parent->getVecOut(name);
    return NULL;
}

Node<string>* Effect::getStrOut(string name)
{
    if(m_strOut[name] != NULL)
        return m_strOut[name];
    if(m_parent != NULL)
        return m_parent->getStrOut(name);
    return NULL;
}

Node<Effect*>* Effect::getEffectOut(string name)
{
    if(m_effectOut[name] != NULL)
        return m_effectOut[name];
    if(m_parent != NULL)
        return m_parent->getEffectOut(name);
    return NULL;
}

Node<LivingEntity*>* Effect::getEntityOut(string name)
{
    if(m_entityOut[name] != NULL)
        return m_entityOut[name];
    if(m_parent != NULL)
        return m_parent->getEntityOut(name);
    return NULL;
}

NodeRef<float>&  Effect::getFloatIn(string name) {return *m_floatIn[name];}
NodeRef<int>& Effect::getIntIn(string name) {return *m_intIn[name];}
NodeRef<vec2>& Effect::getVecIn(string name) {return *m_vecIn[name];}
NodeRef<string>& Effect::getStrIn(string name) {return *m_strIn[name];}
NodeRef<Effect*>& Effect::getEffectIn(string name) {return *m_effectIn[name];}
NodeRef<LivingEntity*>& Effect::getEntityIn(string name) {return *m_entityIn[name];}

bool Effect::hasFloatOut(string name) const {return m_floatOut.find(name) != m_floatOut.end();}
bool Effect::hasIntOut(string name) const {return m_intOut.find(name) != m_intOut.end();}
bool Effect::hasVecOut(string name) const {return m_vecOut.find(name) != m_vecOut.end();}
bool Effect::hasStrOut(string name) const {return m_strOut.find(name) != m_strOut.end();}
bool Effect::hasEntitytOut(string name) const {return m_entityOut.find(name) != m_entityOut.end();}
bool Effect::hasEffectOut(string name) const {return m_effectOut.find(name) != m_effectOut.end();}

void Effect::setParent(Effect *parent)
{
    m_parent = parent;
}

/**
    * Cast :
    * IN :
    * - range float
    * OUT :
    * - pos vec2
    * - dir vec2
    * - target entity
**/

CastEffect::CastEffect(LivingEntity &caster, Effect *effect, LivingEntity *target) : m_effect(effect)
{
    vecOut("pos", caster.pos());
    vecOut("dir", target->pos()-caster.pos());
    entityOut("target", target);

    floatIn("range");
    effect->connectTo(this);
    getFloatIn("range") >> *effect->getFloatOut("range");

    floatOut("range", max(m_floatIn["range"]->getNode()->getValue(), caster.getRange()));
}

CastEffect::CastEffect(LivingEntity &caster, Effect *effect, vec2 target) : m_effect(effect)
{
    vecOut("pos", caster.pos());
    vecOut("dir", target);

    floatIn("range");
    effect->connectTo(this);
    getEffectIn("range") >> *effect->getEffectOut("range");

    floatOut("range", max(m_floatIn["range"]->getValue(), caster.getRange()));
}

CastEffect::~CastEffect()
{

}

void CastEffect::connectTo(Effect *parent)
{
    setParent(parent);
}

void CastEffect::applyEffect(World &world)
{
    m_effect->applyEffect(world);
}

DamageEffect::DamageEffect(int damage) : m_damage(damage)
{
    entityIn("target");
    floatOut("range", 0);
}

DamageEffect::~DamageEffect()
{

}

void DamageEffect::applyEffect(World &world)
{
    m_entityIn["target"]->getNode()->getValue()->damage(m_damage);
}

void DamageEffect::connectTo(Effect *parent)
{
    setParent(parent);
    getEntityIn("target") >> *parent->getEntityOut("target");
}

ProjectileEffect::ProjectileEffect(Effect *effect, float speed, int duration, int damage) : m_effect(effect), m_speed(speed), m_duration(duration), m_damage(damage)
{
    vecIn("pos");
    vecIn("dir");
    entityIn("ignore");
    vecOut("pos");
    vecOut("dir");
    floatOut("range", m_speed*duration*0.7f);
}

ProjectileEffect::~ProjectileEffect()
{

}

void ProjectileEffect::applyEffect(World &world)
{
    vec2 pos = getVecIn("pos").getValue(),
        dir = getVecIn("dir").getValue().getVectWithLength(m_speed);
    NodeRef<LivingEntity*> node = getEntityIn("ignore");
    world.addProjectile(new Projectile(pos, dir, 5, m_duration, m_effect, node.getNode() == NULL ? NULL : node.getValue()));
}

void ProjectileEffect::connectTo(Effect *parent)
{
    setParent(parent);
    getVecIn("pos") >> *parent->getVecOut("pos");
    getVecIn("dir") >> *parent->getVecOut("dir");
    *getVecOut("dir") << getVecIn("dir").getValue();
    *getVecOut("pos") << getVecIn("pos").getValue();
    getEntityIn("ignore") >> parent->getEntityOut("ignore");
}

EntityEffect::EntityEffect(Effect *effect, LivingEntity *target, vec2 dir) : m_effect(effect)
{
    entityOut("target", target);
    entityOut("ignore", target);
    vecOut("pos", target->pos());
    vecOut("dir", dir);
    effect->connectTo(this);
}

EntityEffect::~EntityEffect()
{

}

void EntityEffect::applyEffect(World &world)
{
    m_effect->applyEffect(world);
}

void EntityEffect::connectTo(Effect *parent)
{
    setParent(parent);
}

DirEffect::DirEffect(Effect *effect, vec2 dir) : m_effect(effect)
{
    vecIn("pos");
    vecOut("pos");
    vecOut("dir", dir);
}

DirEffect::~DirEffect()
{

}

void DirEffect::applyEffect(World &world)
{;
    m_effect->applyEffect(world);
}

void DirEffect::connectTo(Effect *parent)
{
    setParent(parent);
    getVecIn("pos") >> *parent->getVecOut("pos");
    *getVecOut("pos") << getVecIn("pos").getValue();
    m_effect->connectTo(this);
}

SplitEffect::SplitEffect(Effect *effect, int splitCount, float angle) : m_effect(effect)
{
    intOut("count", splitCount);
    floatOut("angle", angle);

    vecIn("pos");
    vecIn("dir");
    floatIn("range");
    getFloatIn("range") >> *effect->getFloatOut("range");
    floatOut("range", getFloatIn("range").getValue());
}

SplitEffect::~SplitEffect()
{

}

void SplitEffect::applyEffect(World &world)
{
    float initAngle = getVecIn("dir").getValue().angle();
    float totalAngle = getFloatOut("angle")->getValue();
    int n = getIntOut("count")->getValue();
    for(int i=0; i<n; i++)
    {
        float angle = initAngle + totalAngle*i/(n-1) - totalAngle/2;
        vec2 dir = vec2(cos(angle), sin(angle));
        DirEffect effect(m_effect, dir);
        effect.connectTo(this);
        effect.applyEffect(world);
    }
}

void SplitEffect::connectTo(Effect *parent)
{
    setParent(parent);
    getVecIn("pos") >> *parent->getVecOut("pos");
    getVecIn("dir") >> *parent->getVecOut("dir");
    vecOut("pos", getVecIn("pos").getValue());
}

MultiEffect::MultiEffect(Effect **effect, int effectCount) : m_effect(effect)
{
    intOut("count", effectCount);

    vecIn("pos");
    vecIn("dir");
    floatIn("range");
    entityIn("target");
    float maxRange = 0;
    for(int i=0; i<effectCount; i++)
    {
        float range = effect[i]->getFloatOut("range")->getValue();
        if(range > maxRange)
            range = maxRange;
    }

    floatOut("range", maxRange);
}

MultiEffect::~MultiEffect()
{

}

void MultiEffect::applyEffect(World &world)
{
    int n = getIntOut("count")->getValue();
    for(int i=0; i<n; i++)
    {
        EntityEffect effect(m_effect[i], getEntityIn("target").getValue(), getVecIn("dir").getValue());
        effect.connectTo(this);
        effect.applyEffect(world);
    }
}

void MultiEffect::connectTo(Effect *parent)
{
    setParent(parent);
    getVecIn("pos") >> *parent->getVecOut("pos");
    getVecIn("dir") >> *parent->getVecOut("dir");
    getEntityIn("target") >> *parent->getEntityOut("target");
    vecOut("pos", getVecIn("pos").getValue());
}

CyclicEffect::CyclicEffect(int period, int times) : m_time(0), m_period(period), m_times(times)
{

}

void CyclicEffect::connectTo(Effect *parent)
{

}

void CyclicEffect::applyEffect(World &world)
{
    if(m_time%m_period == 0)
    {
        m_effect->applyEffect(world);
        m_times--;
    }
}

void CyclicEffect::update()
{
    m_time++;
}

bool CyclicEffect::isOver() const
{
    return m_times <= 0;
}
