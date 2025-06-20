#include <iostream>
#include <string>


#include "GameEngine.h"

void GameEngine::startUp()
{
	plr.setPos(Vector2{200, 200});
	enemy.setRandomPos();
	coin.setRandomPos();
}

void GameEngine::update()
{

	// Handle enemy movement and collision
	enemy.movementHandler(plr);
	enemy.damagePlayer(plr);

	// Handle plr movement
	plr.handleMovement();

	

	// Coin handling
	coin.handlePlayerCollision(plr);
	
}

void GameEngine::render()
{
	// Background
	ClearBackground(BLACK);

	// Draw player
	DrawCircle(plr.getPos().x, plr.getPos().y, plr.getRadius(), plr.getColor());

	// Draw enemy
	DrawCircle(enemy.getPos().x, enemy.getPos().y, enemy.getRadius(), enemy.getColor());

	// Draw plr health bar
	plr.drawHealthBar();

	// Draw coin
	DrawCircle(coin.getPos().x, coin.getPos().y, coin.getRadius(), coin.getColor());

	// Draw score
	plr.drawScore();


}

void GameEngine::shutdown()
{
	std::cout << "Hello world";
}
