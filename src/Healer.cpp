#include "Healer.h"

void Healer::setRandomPos()
{
	m_pos.x = Random::get(12, SCREEN_WIDTH - 12);
	m_pos.y = Random::get(12, SCREEN_HEIGHT - 12);
}

void Healer::handleCollision(Player& plr)
{
	if (CheckCollisionCircles(plr.getPos(), plr.getRadius(), m_pos, m_radius) && m_canHeal)
	{
		plr.heal();
		m_radius = 0;
		m_pos.x = Random::get(12, SCREEN_WIDTH - 12);
		m_pos.y = Random::get(12, SCREEN_HEIGHT - 12);
		m_canHeal = false;
	}
}

void Healer::handleSpawning(Player& plr)
{
	if (plr.getScore() == plr.getPreviousHealerScore() + 20)
	{
		m_canHeal = true;
		plr.setPreviousHealerScore();
		m_radius = 12;
		std::cout << "spawned";
	}
	
	if (plr.getDead())
	{
		m_canHeal = false;
		plr.clearPreviousHealerScore();
	}
}

Vector2 Healer::getPos() const
{
	return m_pos;
}

float Healer::getRadius() const
{
	return m_radius;
}

Color Healer::getColor() const
{
	return m_color;
}
