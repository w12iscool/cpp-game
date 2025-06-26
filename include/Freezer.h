#pragma once

#include "raylib.h"
#include "Player.h"
#include "Random.h"
#include "Constants.h"

class Freezer
{
private:
	Vector2 m_pos{ 0, 0 };
	float m_radius{ 0 };
	Color m_color{ SKYBLUE };
	bool m_canFreeze{ false };
public:
	// Set member functions
	void setRandomPos();

	// Important member functions
	void handleSpawning(Player& plr);
	bool handleCollisions(Player& plr);
	void drawIfFrozen();

	// Get member functions
	Vector2 getPos();
	float getRadius();
	Color getColor();
};