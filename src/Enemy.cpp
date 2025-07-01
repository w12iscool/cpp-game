#include "Enemy.h"

void Enemy::setRandomPos()
{
	m_pos.x = Random::get(20, SCREEN_WIDTH - m_radius);
	m_pos.y = Random::get(20, SCREEN_HEIGHT - m_radius);
}

void Enemy::setSwitch(bool setBool)
{
	m_switch = setBool;
}

void Enemy::setRadius(float radius)
{
	m_radius = radius;
}

void Enemy::setVelocity(float velocity)
{
	m_velocity = velocity;
}

void Enemy::movementHandler(Player& plr)
{
	float frameTime{ GetFrameTime() };

	// Follow the plr
	if (m_switch)
	{
		if (m_pos.x > plr.getPos().x && Random::get(0, 1) == 1)
			m_pos.x -= m_velocity * frameTime;
		if (m_pos.x < plr.getPos().x && Random::get(0, 1) == 1)
			m_pos.x += m_velocity * frameTime;
		if (m_pos.y > plr.getPos().y && Random::get(0, 1) == 1)
			m_pos.y -= m_velocity * frameTime;
		if (m_pos.y < plr.getPos().y && Random::get(0, 1) == 1)
			m_pos.y += m_velocity * frameTime;
	}
	
	
	// In case the enemy somehow goes out of bounds.
	if (m_pos.x < 0)
		m_pos.x = 0;
	if (m_pos.x > SCREEN_WIDTH)
		m_pos.x = SCREEN_WIDTH;
	if (m_pos.y < 0)
		m_pos.y = 0;
	if (m_pos.y > SCREEN_HEIGHT)
		m_pos.y = SCREEN_HEIGHT;
}

void Enemy::damagePlayer(Player& plr, bool canDamage)
{
	if (CheckCollisionCircles(plr.getPos(), plr.getRadius(), m_pos, m_radius) && canDamage)
	{
		plr.takeDamage(m_dmg);
	}
}

void Enemy::addEnemy(std::vector<Enemy>& enemies, Player& plr, int difficulty)
{
	if (plr.getScore() == plr.getPreviousScore() + 10)
	{
		plr.setPreviousScore();

		Enemy copyEnemy;

		if (difficulty == 1)
			copyEnemy.setVelocity(EASY_ENEMY_SPEED);
		if (difficulty == 2)
			copyEnemy.setVelocity(NORMAL_ENEMY_SPEED);
		if (difficulty == 3)
			copyEnemy.setVelocity(HARD_ENEMY_SPEED);

		if (enemies.size() < MAX_ENEMIES)
		{
			copyEnemy.setRandomPos();
			enemies.push_back(copyEnemy);
			std::cout << enemies.size();
		}
	}
	if (plr.getDead())
	{
		enemies.clear();
		plr.clearPreviousScore();
	}
}



void Enemy::handleScoreHundred(Player& plr)
{
	if (plr.getScore() == plr.getPreviousHundredScore() + 100)
	{
		m_dmg += 1;
		m_canDrawDmgMultiplier = true;
		plr.setPreviousHundredScore();
	}

	if (plr.getDead())
	{
		m_dmg = 1;
		plr.clearPreviousHundredScore();
		m_canDrawDmgMultiplier = false;
	}
}

void Enemy::drawDmgMultiplier()
{
	if (m_canDrawDmgMultiplier)
	{
		std::string sMultiplier{ std::to_string(m_dmg) };
		std::string temp1 = "DAMAGE: ";
		std::string temp2 = "X";
		std::string temp3 = temp1 + sMultiplier + temp2;
		const char* text = temp3.c_str();
		int centeredX = ((SCREEN_WIDTH - MeasureText(text, 30)) / 2);

		DrawText(text, centeredX, 20, 30, RED);
	}
}

bool Enemy::handlePause(Player& plr, int difficulty, bool hasSpeed, bool& isPaused, bool& canDamage)
{
	if (IsKeyReleased(KEY_P))
	{
		if (isPaused == true)
		{
			m_switch = false;
			plr.setVelocity(0);
			std::cout << "paused";
			canDamage = false;
			isPaused = !isPaused;
		}
		else
		{

			m_switch = true;
			if (hasSpeed == true)
			{
				plr.setVelocity(plr.getSpeededVelocity(difficulty));
			}
			if (hasSpeed == false)
			{
				plr.setVelocity(plr.getUnspeededVelocity(difficulty));
			}
			canDamage = true;
			isPaused = !isPaused;
			std::cout << "unpaused";
		}
	}
	return isPaused;
}



Vector2 Enemy::getPos() const
{
	return m_pos;
}

float Enemy::getRadius() const
{
	return m_radius;
}

float Enemy::getVelocity() const
{
	return m_velocity;
}

Color Enemy::getColor() const
{
	return m_color;
}
