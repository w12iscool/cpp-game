#pragma once

#include <vector>

#include "raylib.h"
#include "Constants.h"
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"

class GameEngine
{
private:
	Player plr;
	Coin coin;
	Enemy enemy;
	bool m_isInMenue{ true };
public:
	void startUp();
	void update();
	void render();
	void shutdown();
};