#pragma once
#include "raylib.h"
#include "Random.h"
#include "Constants.h"
#include "Player.h"
#include <iostream>

class Healer
{
private:
	Vector2 m_pos{ 0, 0 };
	float m_radius{ 0 };
	Color m_color{ GREEN };
	bool m_canHeal{ false };
public:
	// Set member functions
	void setRandomPos();

	// Important functions
	void handleSpawning(Player& plr);
	void handleCollision(Player& plr);

	// Get member functions
	Vector2 getPos() const;
	float getRadius() const;
	Color getColor() const;
};