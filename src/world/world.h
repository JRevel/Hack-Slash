#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include "entity.h"
#include "player/player.h"

class Player;
class Projectile;

class World
{
private:
    std::vector<LivingEntity*> m_entities;
    std::vector<Projectile*> m_projectiles;
    Player *m_player;
    std::vector<TimedEffect*> m_liveEffects;

public:
    World(Player *player);
    ~World();
    void addEntity(LivingEntity *entity);
    void addProjectile(Projectile *proj);
    void update();
    void draw(Screen &screen) const;
    Player& getPlayer() const;
    std::vector<LivingEntity*> getEntitiesNear(vec2 pos);
    void addEffect(TimedEffect *effect);

    LivingEntity *getEntityAt(vec2 pos) const;
};

#endif // WORLD_H_INCLUDED
