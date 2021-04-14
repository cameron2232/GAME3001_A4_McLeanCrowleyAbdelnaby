#include "Bullet.h"
#include "TextureManager.h"
#include "Game.h"
Bullet::Bullet(float x, float y,float r): m_Orientation(glm::vec2(0.0f, -1.0f)), m_RotationAngle(r), m_accelerationRate(0.0f), m_MaxSpeed(2.0f)
{
	TextureManager::Instance()->load("../Assets/textures/Bullet.png", "Bullet");
	auto size = TextureManager::Instance()->getTextureSize("Bullet");

	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(x, y);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	m_MaxSpeed = 1.0f;
	getRigidBody()->isColliding = false;
	setType(BULLET);
}

Bullet::~Bullet()
= default;

void Bullet::draw()
{
	TextureManager::Instance()->draw("Bullet", getTransform()->position.x, getTransform()->position.y, m_RotationAngle, 255, false);
}

void Bullet::update()
{
	Move();
}

void Bullet::clean()
{
}

void Bullet::Move()
{
	auto deltalTime = TheGame::Instance()->getDeltaTime();
	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();
	// using the formula pf = pi + vi*t_0.5ai*t^2
	getRigidBody()->velocity += getOrientation() * (deltalTime)+0.5f * getRigidBody()->acceleration * (deltalTime);
	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_MaxSpeed);
	getTransform()->position += getRigidBody()->velocity;
}


glm::vec2 Bullet::getOrientation() const
{
	return m_Orientation;
}

void Bullet::setOrientation(glm::vec2 Orientation)
{
	m_Orientation = Orientation;
}

void Bullet::setRotation(float Angle)
{
	m_RotationAngle = Angle;
	const auto angle_in_radians = (Angle) * Util::Deg2Rad;

	const auto x = cos(angle_in_radians);
	const auto y = sin(angle_in_radians);

	// convert the angle to a normalized vector
	setOrientation(glm::vec2(x, y));
}

float Bullet::getRotation() const
{
	return m_RotationAngle;
}

float Bullet::getAccelerationRate() const
{
	return m_accelerationRate;
}

void Bullet::setAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}
