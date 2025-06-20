#include "Player.h"
#include "Constants.h"
#include "Random.h"

// Set member functions
void Player::setPos(Vector2 pos)
{
	m_pos = pos;
}

void Player::setVelocity(float velocity)
{
	m_velocity = velocity;
}

void Player::setRadius(float radius)
{
	m_radius = radius;
}

void Player::setColor(Color color)
{
	m_color = color;
}

void Player::setDead(bool dead)
{
	m_dead = dead;
}

void Player::setHealth(float health)
{
	m_health = health;
}

void Player::setScore(int score)
{
	m_score = score;
}

// Important member functions
void Player::handleMovement()
{
	float frameTime{ GetFrameTime() };

	// Movement
	if (IsKeyDown(KEY_A))
		m_pos.x -= m_velocity * frameTime;
	if (IsKeyDown(KEY_D))
		m_pos.x += m_velocity * frameTime;
	if (IsKeyDown(KEY_W))
		m_pos.y -= m_velocity * frameTime;
	if (IsKeyDown(KEY_S))
		m_pos.y += m_velocity * frameTime;

	// Prevent the player from going out of bounds
	if (m_pos.x < 0)
		m_pos.x = 0;
	if (m_pos.x > SCREEN_WIDTH)
		m_pos.x = SCREEN_WIDTH;
	if (m_pos.y < 0)
		m_pos.y = 0;
	if (m_pos.y > SCREEN_HEIGHT)
		m_pos.y = SCREEN_HEIGHT;
}

void Player::addScore()
{
	m_score += 1;
}

void Player::takeDamage()
{
	m_health -= 1;
}

void Player::drawScore()
{
	std::string sScore = std::to_string(m_score);
	std::string temp1 = "SCORE: ";
	std::string temp2 = temp1 + sScore;
	char const* text = temp2.c_str();

	DrawText(text, 10, 10, 30, YELLOW);
}

void Player::heal()
{
	m_health += 14;
}

void Player::drawHealthBar()
{
	if (m_dead == false)
	{
		Rectangle healthBar{ Rectangle{10.0f, 370.0f, (m_health / m_maxHealth) * HEALTHBAR_WIDTH, HEALTHBAR_HEIGHT} };
		Rectangle backgroundBar{ Rectangle{10.0f, 370.0f, HEALTHBAR_WIDTH, HEALTHBAR_HEIGHT} };
		DrawRectangle(backgroundBar.x, backgroundBar.y, backgroundBar.width, backgroundBar.height, DARKGRAY);
		DrawRectangle(healthBar.x, healthBar.y, healthBar.width, healthBar.height, GREEN);

		DrawText("Health", 10, 350, 20, GREEN);
	}
	
}

void Player::checkIfDead()
{
	if (m_health <= 0)
	{
		m_dead = true;
	}
}

void Player::setRandomPos()
{
	m_pos.x = Random::get(10, SCREEN_WIDTH - 10);
	m_pos.y = Random::get(10, SCREEN_HEIGHT - 10);
}

// Get member functions
Vector2 Player::getPos() const
{
	return m_pos;
}

float Player::getVelocity() const
{
	return m_velocity;
}

float Player::getRadius() const
{
	return m_radius;
}

Color Player::getColor() const
{
	return m_color;
}

int Player::getScore() const
{
	return m_score;
}

float Player::getHealth() const
{
	return m_health;
}

const float Player::getMaxHealth() const
{
	return m_maxHealth;
}

bool Player::getDead() const
{
	return m_dead;
}

