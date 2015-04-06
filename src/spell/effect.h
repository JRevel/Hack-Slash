#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED
#include <map>
#include <string>
#include "../util/vec.h"
#include "../world/world.h"

using namespace std;

class LivingEntity;

class EffectData
{
private:
    map<string, int> m_ints;
    map<string, float> m_floats;
    map<string, vec2> m_vecs;
    map<string, LivingEntity*> m_entities;

public:
    EffectData();
    EffectData(const EffectData &data);
    bool hasEntity(string name) const;
    bool hasInt(string name) const;
    bool hasFloat(string name) const;
    bool hasVec(string name) const;

    int getInt(string name) const;
    float getFloat(string name) const;
    vec2 getVec(string name) const;
    LivingEntity* getEntity(string name) const;

    void setInt(string name, int val);
    void setFloat(string name, float val);
    void setVec(string name, vec2 val);
    void setEntity(string name, LivingEntity* val);
};

class Effect
{
protected:
    EffectData m_parentData;
    bool m_started;
public:
    Effect(EffectData parentData);
    virtual EffectData getData() const = 0;
    virtual void update(World &world) = 0;
    virtual bool isOver() const = 0;
    bool isStarted() const;
    void start();
};

class Spell
{
public:
    virtual Effect* cast(EffectData data) const = 0;
    virtual float getRange() const = 0;
};

class PointSpell : public Spell{};

class EntitySpell : public PointSpell{};

class DamageSpell : public EntitySpell
{
private:
    int m_damage;
public:
    DamageSpell(int damage);
    virtual Effect* cast(EffectData data) const;
    virtual float getRange() const;
};

class DamageEffect : public Effect
{
private:
    LivingEntity* m_target;
    int m_damage;
    vec2 m_dir;
public:
    DamageEffect(EffectData data, int damage);
    virtual void update(World &world);
    virtual bool isOver() const;
    virtual EffectData getData() const;
};

class AttackSpell : public Spell
{
private:
    float m_range;
    Spell *m_spell;
public:
    AttackSpell(Spell *spell, float range);
    virtual Effect* cast(EffectData data) const;
    virtual float getRange() const;
};

class AttackEffect : public Effect
{
private:
    LivingEntity* m_target;
    Spell* m_spell;
    vec2 m_dir;
public:
    AttackEffect(EffectData data, Spell *spell);
    virtual void update(World &world);
    virtual bool isOver() const;
    virtual EffectData getData() const;
};

class ProjectileSpell : public Spell
{
private:
    float m_speed, m_r;
    int m_duration;
    Spell* m_spell;

public:
    ProjectileSpell(float speed, float r, int duration, Spell *spell);
    virtual Effect* cast(EffectData data) const;
    virtual float getRange() const;
};

class ProjectileEffect : public Effect
{
private:
    vec2 m_pos, m_speed;
    float m_r;
    int m_duration;
    Spell* m_spell;
    LivingEntity *m_ignore;

public:
    ProjectileEffect(EffectData data, float speed, float r, int duration, Spell* spell);
    virtual void update(World &world);
    virtual bool isOver() const;
    virtual EffectData getData() const;
};

class SplitSpell : public Spell
{
private:
    int m_count;
    float m_angle;
    Spell* m_spell;

public:
    SplitSpell(int count, float angle, Spell *spell);
    virtual Effect* cast(EffectData data) const;
    virtual float getRange() const;
};

class SplitEffect : public Effect
{
private:
    vec2 m_pos, m_dir;
    int m_count;
    float m_angle;
    Spell *m_spell;

public:
    SplitEffect(EffectData data, int count, float angle, Spell *spell);
    virtual void update(World &world);
    virtual bool isOver() const;
    virtual EffectData getData() const;
};

class RotationSpell : public Spell
{
private:
    float m_rotSpeed;
    int m_duration, m_interval;
    Spell* m_spell;

public:
    RotationSpell(float rotSpeed, int duration, int interval, Spell *spell);
    virtual Effect* cast(EffectData data) const;
    virtual float getRange() const;
};

class RotationEffect : public Effect
{
private:
    vec2 m_pos, m_dir;
    float m_rotSpeed;
    int m_duration, m_interval, m_time;
    Spell* m_spell;

public:
    RotationEffect(EffectData data, float rotSpeed, int duration, int interval, Spell *spelll);
    virtual void update(World &world);
    virtual bool isOver() const;
    virtual EffectData getData() const;
};

class ZoneSpell : public Spell
{
private:
    float m_range;
    Spell *m_spell;
public:
    ZoneSpell(float range, Spell *spell);
    virtual Effect* cast(EffectData data) const;
    virtual float getRange() const;
};

class ZoneEffect : public Effect
{
private:
    vec2 m_pos;
    float m_range;
    Spell* m_spell;

public:
    ZoneEffect(EffectData data, float range, Spell *spell);
    virtual void update(World &world);
    virtual bool isOver() const;
    virtual EffectData getData() const;
};

#endif // EFFECT_H_INCLUDED
