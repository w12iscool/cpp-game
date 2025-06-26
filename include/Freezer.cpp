#include "Freezer.h"

void Freezer::setRandomPos()
{
	m_pos.x = Random::get(20, SCREEN_WIDTH - 20);
	m_pos.y = Random::get(20, SCREEN_HEIGHT - 20);
}

void Freezer::handleSpawning(Player& plr)
{
	if (plr.getScore() == plr.getPreviousFreezerScore() + 65)
	{
		m_canFreeze = true;
		plr.setPreviousFreezerScore();
		m_radius = 20;
	}

	if (plr.getDead())
	{
		m_canFreeze = false;
		m_radius = false;
		plr.clearPreviousFreezerScore();
	}

}

bool Freezer::handleCollisions(Player& plr)
{
	if (CheckCollisionCircles(plr.getPos(), plr.getRadius(), m_pos, m_radius) && m_canFreeze)
	{
		m_radius = 0;
		m_pos.x = Random::get(20, SCREEN_WIDTH - 20);
		m_pos.y = Random::get(20, SCREEN_HEIGHT - 20);
		m_canFreeze = false;

		return true;
	}
	return false;
}

void Freezer::drawIfFrozen()
{
	DrawText("Enemies Frozen!", 10, 70, 20, SKYBLUE);
}

Vector2 Freezer::getPos()
{
	return m_pos;
}

float Freezer::getRadius()
{
	return m_radius;
}

Color Freezer::getColor()
{
	return SKYBLUE;
}

