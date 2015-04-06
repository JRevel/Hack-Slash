#include <SDL2/SDL.h>
#include <iostream>
#include <algorithm>
#include "projectile.h"
#include "../spell/effect.h"

#include "world.h"

World::World(Player *player) : m_player(player)
{

}

World::~World()
{
    for(int i=0; i<m_entities.size(); i++)
        delete m_entities[i];
    for(int i=0; i<m_projectiles.size(); i++)
        delete m_projectiles[i];
    delete m_player;
}

void World::addEntity(LivingEntity *entity)
{
    m_entities.push_back(entity);
}

void World::addProjectile(Projectile *proj)
{
    m_projectiles.push_back(proj);
}

void World::addEffect(Effect *effect)
{
    m_effects.push_back(effect);
}

bool isOver(Effect *effect)
{
    return effect->isOver() && effect->isStarted();
}
bool isEntityDead(LivingEntity *entity)
{
    return entity->isDead() && !entity->isSleeping();
}
bool isProjectileDead(Projectile *entity)
{
    return entity->isDead() && !entity->isSleeping();
}

void World::update()
{
    for(int i=0; i<m_entities.size(); i++)
        m_entities[i]->wakeUp();
    for(int i=0; i<m_projectiles.size(); i++)
        m_projectiles[i]->wakeUp();
    for(int i=0; i<m_effects.size(); i++)
    {
        std::cout << "test" << std::endl;
        m_effects[i]->start();
    }

    for(int i=0; i<m_entities.size(); i++)
        m_entities[i]->update(*this);
    for(int i=0; i<m_projectiles.size(); i++)
        m_projectiles[i]->update(*this);
    for(int i=0; i<m_effects.size(); i++)
    {
        if(m_effects[i]->isStarted())
            m_effects[i]->update(*this);
    }
    m_player->update(*this);

    m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), isEntityDead), m_entities.end());
    m_projectiles.erase(std::remove_if(m_projectiles.begin(), m_projectiles.end(), isProjectileDead), m_projectiles.end());
    m_effects.erase(std::remove_if(m_effects.begin(), m_effects.end(), isOver), m_effects.end());
}

void World::draw(Screen &screen) const
{
    for(int i=0; i<m_entities.size(); i++)
        m_entities[i]->draw(screen);
    for(int i=0; i<m_projectiles.size(); i++)
        m_projectiles[i]->draw(screen);
    m_player->draw(screen);
}

Player& World::getPlayer() const
{
    return *m_player;
}

LivingEntity* World::getEntityAt(vec2 pos) const
{
    for(int i=0; i<m_entities.size(); i++)
    {
        if((m_entities[i]->pos()-pos).length() < m_entities[i]->r())
            return m_entities[i];
    }
    return NULL;
}

std::vector<LivingEntity*> World::getEntitiesNear(vec2 pos)
{
    return m_entities;
}
