#pragma once

#include "raylib.h"
#include "Player.h"
#include "Random.h"

class Speeder
{
private:
	Vector2 m_pos{ 0 };
	float m_radius{ 0 };
	Color m_color{ BLUE };
	bool m_canSpeed{ false };
public:
	// Set member functions
	void setRandomPos();

	// Important member functions
	bool handleCollision(Player& plr);
	void handleSpawning(Player& plr);
	void drawIfSpeeded();

	// Get member functions
	Vector2 getPos();
	float getRadius();
	Color getColor() const;
};