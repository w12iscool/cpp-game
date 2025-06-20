#include "Coin.h"
#include "Random.h"
#include "Constants.h"

void Coin::setRadius(float radius)
{
	m_radius = radius;
}

void Coin::setRandomPos()
{
	m_pos.x = Random::get(20, SCREEN_WIDTH - m_radius);
	m_pos.y = Random::get(20, SCREEN_HEIGHT - m_radius);
}

void Coin::handlePlayerCollision(Player& plr)
{
	if (CheckCollisionCircles(m_pos, m_radius, plr.getPos(), plr.getRadius()))
	{
		plr.addScore();
		setRandomPos();
	}
}

Vector2 Coin::getPos() const
{
	return m_pos;
}

float Coin::getRadius() const
{
	return m_radius;
}

Color Coin::getColor() const
{
	return m_color;
}
