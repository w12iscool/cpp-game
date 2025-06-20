#pragma once

#include <vector>

#include "raylib.h"
#include "Constants.h"
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
#include <vector>

class GameEngine
{
private:
	Player plr;
	Coin coin;
	Enemy enemy;
	std::vector<Enemy> enemies;
	bool m_isInMenue{ true };
	bool m_isInDifficulty{ false };
	int m_difficulty{ 1 };
public:
	void startUp();
	void update();
	void render();
	void shutdown();
};