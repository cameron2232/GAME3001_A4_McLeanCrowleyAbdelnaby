#include "Enemy.h"

#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"

Enemy::Enemy() : m_maxSpeed(10.0f), m_currentAnimationState(ENEMY_IDLE)
{
	
}


Enemy::~Enemy()
= default;

void Enemy::turnRight()
{
	setCurrentHeading(getCurrentHeading() + m_turnRate);
	if (getCurrentHeading() >= 360)
		setCurrentHeading(getCurrentHeading() - 360.0f);;
}

void Enemy::turnLeft()
{
	setCurrentHeading(getCurrentHeading() - m_turnRate);
	if (getCurrentHeading() < 0)
		setCurrentHeading(getCurrentHeading() + 360.0f);
}

void Enemy::moveForward()
{
	getRigidBody()->velocity = getCurrentDirection() * m_maxSpeed;
}

void Enemy::moveBack()
{
	getRigidBody()->velocity = getCurrentDirection() * -m_maxSpeed;
}

void Enemy::rotate()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	m_targetDirection = getTargetPosition() - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getCurrentDirection(), m_targetDirection);

	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
			setCurrentHeading(getCurrentHeading() + m_turnRate);
		
		else if (target_rotation < 0.0f)
			setCurrentHeading(getCurrentHeading() - m_turnRate);
	}
}

void Enemy::flee()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	m_targetDirection = getTransform()->position - getTargetPosition();

	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getCurrentDirection(), m_targetDirection);

	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
			setCurrentHeading(getCurrentHeading() + m_turnRate);
		
		else if (target_rotation < 0.0f)
			setCurrentHeading(getCurrentHeading() - m_turnRate);
	}


	getRigidBody()->acceleration = getCurrentDirection() * m_accelerationRate;
	getRigidBody()->velocity += getCurrentDirection() * (deltaTime)+0.5f * getRigidBody()->acceleration * (deltaTime);
	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);
	getTransform()->position += getRigidBody()->velocity;
}

void Enemy::move()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	m_targetDirection = getTargetPosition() - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getCurrentDirection(), m_targetDirection);

	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
			setCurrentHeading(getCurrentHeading() + m_turnRate);
		
		else if (target_rotation < 0.0f)
			setCurrentHeading(getCurrentHeading() - m_turnRate);
	}



	getRigidBody()->acceleration = getCurrentDirection() * m_accelerationRate;

	getRigidBody()->velocity += getCurrentDirection() * (deltaTime)+
		0.5f * getRigidBody()->acceleration * (deltaTime);


	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;
}

float Enemy::getTargetDistance() const
{
	return m_magnitudeDistance;
}

bool Enemy::getHasDetected() const
{
	return hasDetected;
}

void Enemy::setHasDetected(bool state)
{
	hasDetected = state;
}


float Enemy::getMaxSpeed() const
{
	return m_maxSpeed;
}

void Enemy::setMaxSpeed(const float newSpeed)
{
	m_maxSpeed = newSpeed;
}

void Enemy::setAnimationState(PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

PlayerAnimationState Enemy::getAnimationState()
{
	return m_currentAnimationState;
}

Animation& Enemy::getAnimation(const std::string & name)
{
	return m_pAnimations[name];
}

void Enemy::setSpriteSheet(SpriteSheet * sprite_sheet)
{
	m_EnemyAnimation = sprite_sheet;
}

void Enemy::setAnimation(const Animation & animation)
{
	if (!m_animationsExists(animation.name))
	{
		m_pAnimations[animation.name] = animation;
	}
}

void Enemy::setPatrol(int s, int e)
{
	patrolStart = patrolCurrent = s;
	patrolEnd = e;
}

void Enemy::setPatrolCurrent(int c)
{
	patrolCurrent = c;
}

int Enemy::getPatrolS()
{
	return patrolStart;
}

int Enemy::getPatrolE()
{
	return patrolEnd;
}

int Enemy::getPatrolCurrent()
{
	return patrolCurrent;
}

bool Enemy::m_animationsExists(const std::string & id)
{
	return m_pAnimations.find(id) != m_pAnimations.end();
}

DecisionTree* Enemy::getDecisionTree()
{
	return decisionTree;
}

void Enemy::m_reset()
{
	getRigidBody()->isColliding = false;
	const int halfWidth = getWidth() * 0.5f;
	const auto xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	const auto yComponent = -getHeight();
	getTransform()->position = glm::vec2(xComponent, yComponent);
}

SDL_FRect* Enemy::getHitBox()
{
	return Hitbox;
}

void Enemy::Attack()
{
	
}