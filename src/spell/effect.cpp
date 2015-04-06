#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

#include "effect.h"
#include "../world/entity.h"
#include "../world/projectile.h"

EffectData::EffectData()
{

}

EffectData::EffectData(const EffectData &data) : m_ints(data.m_ints), m_floats(data.m_floats), m_vecs(data.m_vecs), m_entities(data.m_entities)
{

}

bool EffectData::hasEntity(string name) const
{
    return m_entities.find(name) != m_entities.end();
}

bool EffectData::hasInt(string name) const
{
    return m_ints.find(name) != m_ints.end();
}

bool EffectData::hasFloat(string name) const
{
    return m_floats.find(name) != m_floats.end();
}

bool EffectData::hasVec(string name) const
{
    return m_vecs.find(name) != m_vecs.end();
}

int EffectData::getInt(string name) const
{
    std::cout << name << std::endl;
    return m_ints.at(name);
}

float EffectData::getFloat(string name) const
{
    std::cout << name << std::endl;
    return m_floats.at(name);
}

vec2 EffectData::getVec(string name) const
{
    std::cout << name << std::endl;
    return m_vecs.at(name);
}

LivingEntity* EffectData::getEntity(string name) const
{
    std::cout << name << std::endl;
    return m_entities.at(name);
}

void EffectData::setInt(string name, int val)
{
    m_ints[name] = val;
}

void EffectData::setFloat(string name, float val)
{
    std::cout << name << std::endl;
    m_floats[name] = val;
}

void EffectData::setVec(string name, vec2 val)
{
    std::cout << name << std::endl;
    m_vecs[name] = val;
}

void EffectData::setEntity(string name, LivingEntity *val)
{
    std::cout << name << std::endl;
    m_entities[name] = val;
}

Effect::Effect(EffectData parentData) : m_started(false), m_parentData(parentData)
{

}

bool Effect::isStarted() const
{
    return m_started;
}

void Effect::start()
{
    m_started = true;
}

DamageSpell::DamageSpell(int damage) : m_damage(damage)
{

}

Effect* DamageSpell::cast(EffectData data) const
{
    return new DamageEffect(data, m_damage);
}

float DamageSpell::getRange() const
{
    return 0;
}

DamageEffect::DamageEffect(EffectData data, int damage) : Effect(data), m_damage(damage), m_target(data.getEntity("target"))
{

}

void DamageEffect::update(World &world)
{
    m_target->damage(m_damage);
}

EffectData DamageEffect::getData() const
{
    EffectData data;
    data.setEntity("target", m_target);
    data.setVec("pos", m_target->pos());
    data.setVec("targetPos", m_target->pos());
    data.setVec("dir", m_dir);
}

bool DamageEffect::isOver() const
{
    return true;
}

AttackSpell::AttackSpell(Spell *spell, float range) : m_spell(spell), m_range(range)
{

}

Effect* AttackSpell::cast(EffectData data) const
{
    return new AttackEffect(data, m_spell);
}

float AttackSpell::getRange() const
{
    return m_range;
}


AttackEffect::AttackEffect(EffectData data, Spell *spell) : Effect(data), m_spell(spell)
{

}

void AttackEffect::update(World &world)
{
    world.addEffect(m_spell->cast(getData()));
}

bool AttackEffect::isOver() const
{
    return true;
}

EffectData AttackEffect::getData() const
{
    return m_parentData;
}

ProjectileSpell::ProjectileSpell(float speed, float r, int duration, Spell *spell) : m_speed(speed), m_r(r), m_duration(duration), m_spell(spell)
{

}

Effect* ProjectileSpell::cast(EffectData data) const
{
    return new ProjectileEffect(data, m_speed, m_r, m_duration, m_spell);
}

float ProjectileSpell::getRange() const
{
    return m_speed*m_duration*0.7f;
}

ProjectileEffect::ProjectileEffect(EffectData data, float speed, float r, int duration, Spell* spell) : Effect(data), m_pos(data.getVec("pos")), m_speed(data.getVec("dir").getVectWithLength(speed)), m_ignore(NULL), m_r(r), m_duration(duration), m_spell(spell)
{
    if(data.hasEntity("ignore"))
        m_ignore = data.getEntity("ignore");
}

void ProjectileEffect::update(World &world)
{
    world.addProjectile(new Projectile(m_pos, m_speed, m_r, m_duration, m_spell, m_ignore));
}

bool ProjectileEffect::isOver() const
{
    return true;
}

EffectData ProjectileEffect::getData() const
{
    return m_parentData;
}

SplitSpell::SplitSpell(int count, float angle, Spell *spell) : m_count(count), m_angle(angle), m_spell(spell)
{

}

Effect* SplitSpell::cast(EffectData data) const
{
    return new SplitEffect(data, m_count, m_angle, m_spell);
}

float SplitSpell::getRange() const
{
    return m_spell->getRange();
}

SplitEffect::SplitEffect(EffectData data, int count, float angle, Spell *spell) : Effect(data), m_pos(data.getVec("pos")), m_dir(data.getVec("dir")), m_count(count), m_angle(angle), m_spell(spell)
{

}

void SplitEffect::update(World &world)
{
    EffectData data = m_parentData;
    data.setVec("pos", m_pos);
    data.setVec("targetPos", m_pos);
    for(int i=0; i<m_count; i++)
    {
        float angle = m_angle/(m_count-1)*i-m_angle/2 + m_dir.angle();
        data.setVec("dir", vec2(cos(angle), sin(angle)));

        world.addEffect(m_spell->cast(data));
    }
}

bool SplitEffect::isOver() const
{

}

EffectData SplitEffect::getData() const
{
    return m_parentData;
}

RotationSpell::RotationSpell(float rotSpeed, int duration, int interval, Spell *spell) : m_rotSpeed(rotSpeed), m_duration(duration), m_interval(interval), m_spell(spell)
{

}

Effect* RotationSpell::cast(EffectData data) const
{
    return new RotationEffect(data, m_rotSpeed, m_duration, m_interval, m_spell);
}

float RotationSpell::getRange() const
{
    return m_spell->getRange();
}

RotationEffect::RotationEffect(EffectData data, float rotSpeed, int duration, int interval, Spell *spell) : Effect(data), m_pos(data.getVec("pos")), m_dir(data.getVec("dir")), m_rotSpeed(rotSpeed), m_time(0), m_duration(duration), m_interval(interval), m_spell(spell)
{

}

void RotationEffect::update(World &world)
{
    m_time++;
    if(m_time%m_interval == 0)
    {
        EffectData data = m_parentData;
        data.setVec("pos", m_pos);
        data.setVec("targetPos", m_pos);
        float angle = m_dir.angle()+m_rotSpeed*m_time;
        std::cout << angle/M_PI*180 << std::endl;
        data.setVec("dir", vec2(cos(angle), sin(angle)));
        world.addEffect(m_spell->cast(data));
    }
}

bool RotationEffect::isOver() const
{
    return m_time >= m_duration;
}

EffectData RotationEffect::getData() const
{
    return m_parentData;
}


ZoneSpell::ZoneSpell(float range, Spell *spell) : m_range(range), m_spell(spell)
{

}

Effect* ZoneSpell::cast(EffectData data) const
{
    return new ZoneEffect(data, m_range, m_spell);
}

float ZoneSpell::getRange() const
{
    return m_range;
}

ZoneEffect::ZoneEffect(EffectData data, float range, Spell *spell) : Effect(data), m_range(range), m_pos(data.getVec("targetPos")), m_spell(spell)
{

}

void ZoneEffect::update(World &world)
{
    std::vector<LivingEntity*> entities = world.getEntitiesNear(m_pos);
    for(int i=0; i<entities.size(); i++)
    {
        if((entities[i]->pos()-m_pos).length() < m_range+entities[i]->r())
        {
            EffectData data(m_parentData);
            data.setVec("pos", m_pos);
            data.setVec("targetPos", entities[i]->pos());
            data.setVec("dir", entities[i]->pos()-m_pos);
            data.setEntity("target", entities[i]);
            data.setEntity("ignore", entities[i]);
            world.addEffect(m_spell->cast(data));
        }
    }
}

bool ZoneEffect::isOver() const
{
    return true;
}

EffectData ZoneEffect::getData() const
{
    return m_parentData;
}
