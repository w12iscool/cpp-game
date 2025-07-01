#pragma once

#include "raylib.h"
#include "Random.h"
#include "Constants.h"
#include "Player.h"

#include <string>

class Enemy
{
private:
	Vector2 m_pos{ 0, 0 };
	float m_radius{ 20 };
	float m_velocity{ 200.0f };
	Color m_color{ RED };
	bool m_switch{ true };
	int m_dmg{ 1 };
	bool m_canDrawDmgMultiplier{ false };
	
public:
	// The one set member function lol
	void setRandomPos();
	void setSwitch(bool setBool);
	void setRadius(float radius);
	void setVelocity(float velocity);

	// Movement, thinking, etc.
	void movementHandler(Player& plr);
	void damagePlayer(Player& plr, bool canDamage);
	void addEnemy(std::vector<Enemy>& enemies, Player& plr, int difficulty);
	void handleScoreHundred(Player& plr);
	void drawDmgMultiplier();
	void handlePause(Player& plr, int difficulty, bool hasSpeed, bool& isPaused, bool& canDamage);
	
	// Get member functions
	Vector2 getPos() const;
	float getRadius() const;
	float getVelocity() const;
	Color getColor() const;
	bool getSwitch();
};