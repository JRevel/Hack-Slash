#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include "entity.h"
#include "player.h"
#include "../spell/effect.h"

class Player;
class Projectile;
class Effect;

class World
{
private:
    std::vector<LivingEntity*> m_entities;
    std::vector<Projectile*> m_projectiles;
    std::vector<Effect*> m_effects;
    Player *m_player;

public:
    World(Player *player);
    ~World();
    void addEntity(LivingEntity *entity);
    void addProjectile(Projectile *proj);
    void addEffect(Effect* effect);
    void update();
    void draw(Screen &screen) const;
    Player& getPlayer() const;
    std::vector<LivingEntity*> getEntitiesNear(vec2 pos);

    LivingEntity *getEntityAt(vec2 pos) const;
};

#endif // WORLD_H_INCLUDED
