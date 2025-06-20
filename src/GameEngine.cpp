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
	if (plr.getDead() == false && m_isInMenue == false && m_isInDifficulty == false)
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
	if (plr.getDead() && m_isInMenue == false && m_isInDifficulty == false)
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
		DrawText("Press backspace to go back to the menu", posX, posY + 40 + 40, 20, BLACK);

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

		if (IsKeyPressed(KEY_BACKSPACE))
		{
			enemy.setSwitch(false);
			m_isInMenue = true;

		}
	}

	if (m_isInMenue && m_isInDifficulty == false)
	{
		enemy.setSwitch(false);

		ClearBackground(RAYWHITE);
		int screenWidth = 800;
		int screenHeight = 400;
		const char* text = "Welcome to the game! Press enter to play!";
		int fontSize = 35;
		int textWidth = MeasureText(text, fontSize);
		int posX = (screenWidth - textWidth) / 2;
		int posY = (screenHeight - fontSize) / 2 + fontSize;  // Adjust Y so baseline looks centered
		DrawText(text, posX, posY-15, fontSize, BLACK);
		DrawText("Press M to switch difficulties!", posX, posY + 25, 35, BLACK);

		if (IsKeyPressed(KEY_ENTER))
		{
			plr.setDead(false);
			plr.setHealth(plr.getMaxHealth());
			plr.setRandomPos();
			enemy.setRandomPos();
			coin.setRandomPos();
			enemy.setSwitch(true);

			m_isInMenue = false;
		}

		if (IsKeyPressed(KEY_M))
		{
			m_isInDifficulty = true;
			m_isInMenue = false;
		}
	}

	if (m_isInDifficulty)
	{
		ClearBackground(RAYWHITE);
		
		int screenWidth = 800;
		int screenHeight = 400;
		const char* text = "Welcome to the difficulty select menu! Press backspace to go back.";
		int fontSize = 20;
		int textWidth = MeasureText(text, fontSize);
		int posX = (screenWidth - textWidth) / 2;
		int posY = (screenHeight - fontSize) / 2 + fontSize;
		DrawText(text, posX, posY - 170, fontSize, BLACK);
		DrawText("Press: '1' for easy, '2' for normal, '3' for hard", posX, posY - 140, 20, BLACK);

		std::string sDifficulty;
		Color diffColor;
		switch (m_difficulty)
		{
		case 1:
			sDifficulty = "Easy";
			diffColor = GREEN;
			break;
		case 2:
			sDifficulty = "Normal";
			diffColor = YELLOW;
			break;
		case 3:
			sDifficulty = "Hard";
			diffColor = RED;
			break;
		default:
			sDifficulty = "Normal";
			diffColor = RED;
			break;
		}

		const char* text1 = sDifficulty.c_str();
		int fontSize1 = 60;
		int textWidth1 = MeasureText(text1, fontSize1);
		int posX1 = (screenWidth - textWidth1) / 2;
		int posY1 = (screenHeight - fontSize1) / 2 + fontSize1;
		DrawText(text1, posX1, posY1, fontSize1, diffColor);

		if (IsKeyPressed(KEY_ONE))
			m_difficulty = 1;
		if (IsKeyPressed(KEY_TWO))
			m_difficulty = 2;
		if (IsKeyPressed(KEY_THREE))
			m_difficulty = 3;

		switch (m_difficulty)
		{
		case 1:
			plr.setVelocity(EASY_PLAYER_SPEED);
			enemy.setVelocity(EASY_ENEMY_SPEED);
			break;
		case 2:
			plr.setVelocity(NORMAL_PLAYER_SPEED);
			enemy.setVelocity(NORMAL_ENEMY_SPEED);
			break;
		case 3:
			plr.setVelocity(HARD_PLAYER_SPEED);
			enemy.setVelocity(HARD_ENEMY_SPEED);
			break;
		default:
			plr.setVelocity(NORMAL_PLAYER_SPEED);
			enemy.setVelocity(NORMAL_ENEMY_SPEED);
			break;
		}

		if (IsKeyPressed(KEY_BACKSPACE))
		{
			m_isInDifficulty = false;
			m_isInMenue = true;
		}
	}
}

void GameEngine::shutdown()
{
	std::cout << "Hello world";
}
