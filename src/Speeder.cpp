#include "Speeder.h"


void Speeder::setRandomPos()
{
	m_pos.x = Random::get(12, SCREEN_WIDTH - 12);
	m_pos.y = Random::get(12, SCREEN_HEIGHT - 12);
}

bool Speeder::handleCollision(Player& plr)
{
	if (CheckCollisionCircles(m_pos, m_radius, plr.getPos(), plr.getRadius()) && m_canSpeed)
	{
		m_radius = 0;
		m_pos.x = Random::get(12, SCREEN_WIDTH - 12);
		m_pos.y = Random::get(12, SCREEN_HEIGHT - 12);
		m_canSpeed = false;

		return true;
	}
	return false;
}

void Speeder::handleSpawning(Player& plr)
{
	if (plr.getScore() == plr.getPreviousSpeederScore() + 1)
	{
		m_canSpeed = true;
		plr.setPreviousSpeederScore();
		m_radius = 12;
		std::cout << "spawned";
	}
	if (plr.getDead())
	{
		m_canSpeed = false;
		m_radius = 0;
		plr.clearPreviousSpeederScore();
	}
}

void Speeder::drawIfSpeeded()
{

	DrawText("Speeded!", 10, 70, 20, BLUE);
}

Vector2 Speeder::getPos()
{
	return m_pos;
}

float Speeder::getRadius()
{
	return m_radius;
}

Color Speeder::getColor() const
{
	return m_color;
}
