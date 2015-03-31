#include <SDL2/SDL.h>
#include <iostream>

#include "../../util/vec.h"
#include "player.h"

Player::Player(vec2 pos, float r, float speed, int PVs, float range) : LivingEntity(pos, r, PVs, range), m_speed(speed), m_target(NULL)
{

}

void Player::draw(Screen &screen) const
{
    screen.drawCircle(m_pos, m_r, Color(0, 0, 0));
    screen.drawCircle(m_pos, m_r+m_range, Color(0, 255, 0, 25));
}

void Player::update(World &world)
{
    if(m_target == NULL)
        return;

    if(m_target->isAtRange())
    {
        m_target->targetReached(world);
        delete m_target;
        m_target = NULL;
    }
    else
    {
        vec2 dest = m_target->getTargetPos();
        if((dest-m_pos).length() < m_speed)
            move(dest-m_pos);
        else
            move((dest-m_pos).getVectWithLength(m_speed));
    }
}

void Player::setTarget(Target *target)
{
    delete m_target;
    m_target = target;
}

bool Player::isDead() const
{
    return false;
}
