#include <SDL2/SDL.h>

#include "../util/vec.h"
#include "monster.h"

Monster::Monster(vec2 pos, float r, float speed, float detectRange, int PVs, float range) : LivingEntity(pos, r, PVs, range), m_detectRange(detectRange), m_speed(speed)
{

}

void Monster::draw(Screen &screen) const
{
    screen.drawCircle(m_pos, m_r, Color(255, 0, 0));
    screen.drawCircle(m_pos, m_r+m_range, Color(0, 255, 0, 128));
}

void Monster::update(World &world)
{
    Player &player = world.getPlayer();
    if((player.pos()-pos()).length() < m_detectRange && (player.pos()-pos()).length() > m_r+player.r()+m_range)
        move((player.pos()-pos()).getVectWithLength(m_speed));
}
