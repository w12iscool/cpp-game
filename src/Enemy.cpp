#include "Enemy.h"

void Enemy::setRandomPos()
{
	m_pos.x = Random::get(10, SCREEN_WIDTH - 10);
	m_pos.y = Random::get(10, SCREEN_HEIGHT - 10);
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

void Enemy::damagePlayer(Player& plr)
{
	if (CheckCollisionCircles(plr.getPos(), plr.getRadius(), m_pos, m_radius))
	{
		plr.takeDamage();
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
