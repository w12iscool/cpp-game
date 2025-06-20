#pragma once
#include "raylib.h"
#include "Constants.h"
#include <string>

class Player
{
private:
	Vector2 m_pos = Vector2{ 0, 0 };
	float m_velocity{ 600.0f };
	float m_radius{ 20 };
	Color m_color{ WHITE };
	int m_score{ 0 };
	float m_health{ 70 };
	const float m_maxHealth{ 70 };
public:
	// Set member functions
	void setPos(Vector2 pos);
	void setVelocity(float velocity);
	void setRadius(float radius);
	void setColor(Color color);

	// Other important stuff i.e movement, score handling, etc.
	void handleMovement();
	void addScore();
	void takeDamage();
	void drawScore();
	void heal();
	void drawHealthBar();

	// Get member functions
	Vector2 getPos() const;
	float getVelocity() const;
	float getRadius() const;
	Color getColor() const;
	int getScore() const;
	float getHealth() const;
	const float getMaxHealth() const;
};