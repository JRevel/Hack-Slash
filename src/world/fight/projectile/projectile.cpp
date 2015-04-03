#include <SDL2/SDL.h>
#include <iostream>

#include "projectile.h"
#include "../effect.h"

Projectile::Projectile(vec2 pos, vec2 speed, float r, int duration, Effect* effect, LivingEntity *ignore) : m_pos(pos), m_speed(speed), m_duration(duration), m_r(r), m_effect(effect), m_time(0), m_isDead(false), m_ignore(ignore)
{

}

Projectile::~Projectile()
{

}

void Projectile::update(World &world)
{
    if(!isSleeping())
    {
        std::vector<LivingEntity*> entities = world.getEntitiesNear(m_pos);
        for(int i=0; i<entities.size(); i++)
        {
            if(entities[i] != m_ignore && (m_pos-entities[i]->pos()).length() < m_r + entities[i]->r())
                onCollision(world, entities[i]);
        }
        m_pos += m_speed;
        m_time++;
    }
}

bool Projectile::isDead() const
{
    return m_isDead | m_time >= m_duration;
}

void Projectile::draw(Screen &screen) const
{
    screen.drawCircle(m_pos, m_r, Color(0, 0, 255));
}

void Projectile::onCollision(World &world, LivingEntity *target)
{
    Effect* effect = new EntityEffect(m_effect, target, m_speed);
    effect->applyEffect(world);
    m_isDead = true;
}
