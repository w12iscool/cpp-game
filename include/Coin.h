#pragma once

#include "raylib.h"
#include "Player.h"
#include "Constants.h"

class Coin
{
private:
	Vector2 m_pos{ 0, 0 };
	float m_radius{ 12 };
	Color m_color{ YELLOW };
public:
	// Set member function
	void setRadius(float radius);
	// Important functions
	void setRandomPos();
	void handlePlayerCollision(Player& plr);

	Vector2 getPos() const;
	float getRadius() const;
	Color getColor() const;
};