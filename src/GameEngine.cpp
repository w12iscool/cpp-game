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

	// Handle death checking
	plr.checkIfDead();

	// Coin handling
	coin.handlePlayerCollision(plr);

	// High score checking
	plr.handleHighScore();
	
}

void GameEngine::render()
{
	if (plr.getDead() == false)
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

		// Draw high score
		plr.drawHighScore();
	}
	// Death message
	if (plr.getDead())
	{
		enemy.setSwitch(false);

		int screenWidth = 800;
		int screenHeight = 400;

		const char* text = "You died. Press enter to try again!";
		std::string highScoreText1 = "You had a high score of: ";
		std::string highScoreText2 = std::to_string(plr.getHighScore());
		std::string highScoreText3 = highScoreText1 + highScoreText2;
		const char* highScoreText4 = highScoreText3.c_str();

		int fontSize = 30;

		// Measure text width
		int textWidth = MeasureText(text, fontSize);

		// Compute position to center
		int posX = (screenWidth - textWidth) / 2;
		int posY = (screenHeight - fontSize) / 2 + fontSize;  // Adjust Y so baseline looks centered

		ClearBackground(RAYWHITE);

		DrawText(text, posX, posY, fontSize, BLACK);
		DrawText(highScoreText4, posX, posY - 40, fontSize, BLACK);

		if (IsKeyPressed(KEY_ENTER))
		{
			plr.setHealth(plr.getMaxHealth());
			plr.setScore(0);
			plr.setRandomPos();
			enemy.setSwitch(true);
			enemy.setRandomPos();
			coin.setRandomPos();
			plr.setDead(false);
		}
	}


}

void GameEngine::shutdown()
{
	std::cout << "Hello world";
}
