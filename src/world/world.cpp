#include <SDL2/SDL.h>
#include <iostream>
#include "fight/projectile/projectile.h"

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

void World::update()
{
    for(int i=0; i<m_entities.size(); i++)
        m_entities[i]->wakeUp();
    for(int i=0; i<m_projectiles.size(); i++)
        m_projectiles[i]->wakeUp();

    for(int i=0; i<m_entities.size(); i++)
        m_entities[i]->update(*this);
    for(int i=0; i<m_projectiles.size(); i++)
        m_projectiles[i]->update(*this);
    m_player->update(*this);

    for(std::vector<LivingEntity*>::iterator i=m_entities.begin(); i<m_entities.end(); i++)
    {
        if((*i)->isDead())
        {
            std::cout << "!ERASE!" << std::endl;
            delete *i;
            m_entities.erase(i);
        }
    }
    for(std::vector<Projectile*>::iterator i=m_projectiles.begin(); i<m_projectiles.end(); i++)
    {
        if((*i)->isDead())
        {
            delete *i;
            m_projectiles.erase(i);
        }
    }
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
