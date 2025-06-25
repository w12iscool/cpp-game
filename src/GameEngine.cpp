#include <iostream>
#include <string>


#include "GameEngine.h"

namespace Timer
{
	typedef struct
	{
		float Lifetime;
	}Timer;

	// start or restart a timer with a specific lifetime
	void StartTimer(Timer* timer, float lifetime)
	{
		if (timer != NULL)
			timer->Lifetime = lifetime;
	}

	// update a timer with the current frame time
	void UpdateTimer(Timer* timer)
	{
		// subtract this frame from the timer if it's not allready expired
		if (timer != NULL && timer->Lifetime > 0)
			timer->Lifetime -= GetFrameTime();
	}

	// check if a timer is done.
	bool TimerDone(Timer* timer)
	{
		if (timer != NULL)
			return timer->Lifetime <= 0;

		return false;
	}
}

void GameEngine::startUp()  
{  
	m_difficulty = 2;
   plr.setPos(Vector2{200, 200});  
   enemy.setRandomPos();  
   coin.setRandomPos();
   enemies.reserve(MAX_ENEMIES);
   healer.setRandomPos();
   speeder.setRandomPos();
   plr.createSaveFolder();
   plr.getFileHighScore();
   plr.getFileHighScoreEasy();
   plr.getFileHighScoreHard();
   plr.readFromSaveFile();
   plr.readFromSaveFile1();
   plr.readFromSaveFile3();

   // unfortunately hard-coded to set the default difficulty to normal upon startup cuz im lazy :(
   plr.setVelocity(NORMAL_PLAYER_SPEED);
   enemy.setVelocity(NORMAL_ENEMY_SPEED);
   for (auto& ene : enemies)
   {
	   ene.setVelocity(NORMAL_ENEMY_SPEED);
   }
}

float speedLife = 10.0f;

Timer::Timer speedTimer = { 0 };

bool speedActivated{ false };

void GameEngine::update()
{

	// Handle enemy movement and collision
	enemy.movementHandler(plr);
	enemy.damagePlayer(plr);
	for (auto& ene : enemies)
	{
		ene.movementHandler(plr);
		ene.damagePlayer(plr);
	}

	// Handle plr movement
	plr.handleMovement();

	// Handle death checking
	plr.checkIfDead();

	// Coin handling
	coin.handlePlayerCollision(plr);

	// High score checking
	plr.handleHighScore(m_difficulty);

	// Previous Score Checking For More Enemies
	enemy.addEnemy(enemies, plr, m_difficulty);

	// Healer spawning and score checking
	healer.handleSpawning(plr);

	// Healer collision checking
	healer.handleCollision(plr);

	// Speeder spawning and score checking
	speeder.handleSpawning(plr);

	// Speeder collision checking

	if (speeder.handleCollision(plr) && !speedActivated)
	{
		Timer::StartTimer(&speedTimer, speedLife);
		plr.setVelocity(plr.getSpeededVelocity(m_difficulty));
		speedActivated = true;
	}

	if (speedActivated)
	{
		Timer::UpdateTimer(&speedTimer);

		if (Timer::TimerDone(&speedTimer))
		{
			plr.setVelocity(plr.getUnspeededVelocity(m_difficulty));
			speedActivated = false;
		}
	}

	// Increases damage by 1 each time the plr earns 100 coins
	enemy.handleScoreHundred(plr);
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
		for (auto& ene : enemies)
		{
			DrawCircle(ene.getPos().x, ene.getPos().y, ene.getRadius(), ene.getColor());
		}

		// Draw plr health bar
		plr.drawHealthBar();

		// Draw coin
		DrawCircle(coin.getPos().x, coin.getPos().y, coin.getRadius(), coin.getColor());

		// Draw healer
		DrawCircle(healer.getPos().x, healer.getPos().y, healer.getRadius(), GREEN);

		// Draw Speeder
		DrawCircle(speeder.getPos().x, speeder.getPos().y, speeder.getRadius(), BLUE);

		// Draw score
		plr.drawScore();

		// Draw dmg multiplier
		enemy.drawDmgMultiplier();

		// Draw high score
		plr.drawHighScore(m_difficulty);

		if (speedActivated)
		{
			speeder.drawIfSpeeded();
		}
	}
	// Death message
	if (plr.getDead() && m_isInMenue == false && m_isInDifficulty == false)
	{
		plr.saveHighScore(m_difficulty);
		enemy.setSwitch(false);
		plr.setScore(0);
		int screenWidth = 800;
		int screenHeight = 400;

		const char* text = "You died. Press enter to try again!";
		std::string highScoreText1 = "You had a high score of: ";
		std::string highScoreText2;

		switch (m_difficulty)
		{
		case 1:
			highScoreText2 = std::to_string(plr.getHighScoreEasy());
			break;
		case 2:
			highScoreText2 = std::to_string(plr.getHighScore());
			break;
		case 3:
			highScoreText2 = std::to_string(plr.getHighScoreHard());
			break;
		default:
			highScoreText2 = std::to_string(plr.getHighScore());
			break;
		}

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
			for (auto& ene : enemies)
			{
				ene.setSwitch(true);
				ene.setRandomPos();
			}
			coin.setRandomPos();
			plr.setDead(false);
		}

		if (IsKeyPressed(KEY_BACKSPACE))
		{
			enemy.setSwitch(false);
			for (auto& ene : enemies)
			{
				ene.setSwitch(false);
			}
			m_isInMenue = true;

		}
	}

	if (m_isInMenue && m_isInDifficulty == false)
	{
		enemy.setSwitch(false);
		for (auto& ene : enemies)
		{
			ene.setSwitch(false);
		}

		ClearBackground(RAYWHITE);
		int screenWidth = 800;
		int screenHeight = 400;
		const char* text = "Press enter to play!";
		int fontSize = 35;
		int textWidth = MeasureText(text, fontSize);
		int posX = (screenWidth - textWidth) / 2;
		int posY = (screenHeight - fontSize) / 2 + fontSize;  // Adjust Y so baseline looks centered
		DrawText(text, posX, posY, fontSize, BLACK);
		DrawText("Press M to switch difficulties!", (screenWidth - MeasureText("Press M to switch difficulties!", 20)) / 2, posY + 35, 20, BLACK);

		DrawText("Goal Busters", (screenWidth - MeasureText("Goal Busters", 60)) / 2, posY - 70, 60, BLUE);

		if (IsKeyPressed(KEY_ENTER))
		{
			plr.setDead(false);
			plr.setHealth(plr.getMaxHealth());
			plr.setRandomPos();
			enemy.setRandomPos();
			coin.setRandomPos();
			enemy.setSwitch(true);
			for (auto& ene : enemies)
			{
				ene.setRandomPos();
				ene.setSwitch(true);
			}

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
		const char* text = "Welcome to the difficulty select menu!";
		int fontSize = 20;
		int textWidth = MeasureText(text, fontSize);
		int posX = (screenWidth - textWidth) / 2;
		int posY = (screenHeight - fontSize) / 2 + fontSize;
		DrawText(text, posX, posY - 170, fontSize, BLACK);
		DrawText("1 - Easy", (screenWidth - MeasureText("1 - Easy", 30)) / 2, posY - 130, 30, GREEN);
		DrawText("2 - Normal", (screenWidth - MeasureText("2 - Normal", 30)) / 2, posY - 90, 30, BLACK);
		DrawText("3 - Hard", (screenWidth - MeasureText("3 - Hard", 30)) / 2, posY - 50, 30, RED);
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
			diffColor = BLACK;
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
		DrawText("Press backspace to go back", (screenWidth - MeasureText("Press backspace to go back", 30)) / 2, posY1 + 70, 30, BLACK);
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
			for (auto& ene : enemies)
			{
				ene.setVelocity(EASY_ENEMY_SPEED);
			}
			break;
		case 2:
			plr.setVelocity(NORMAL_PLAYER_SPEED);
			enemy.setVelocity(NORMAL_ENEMY_SPEED);
			for (auto& ene : enemies)
			{
				ene.setVelocity(NORMAL_ENEMY_SPEED);
			}
			break;
		case 3:
			plr.setVelocity(HARD_PLAYER_SPEED);
			enemy.setVelocity(HARD_ENEMY_SPEED);
			for (auto& ene : enemies)
			{
				ene.setVelocity(HARD_ENEMY_SPEED);
			}
			break;
		default:
			plr.setVelocity(NORMAL_PLAYER_SPEED);
			enemy.setVelocity(NORMAL_ENEMY_SPEED);
			for (auto& ene : enemies)
			{
				ene.setVelocity(NORMAL_ENEMY_SPEED);
			}
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
	plr.saveHighScore(m_difficulty);
}
