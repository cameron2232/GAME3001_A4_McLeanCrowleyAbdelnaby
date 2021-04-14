#include "Enemy.h"

#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"

Enemy::Enemy() : m_maxSpeed(10.0f), m_currentAnimationState(ENEMY_IDLE)
{
	TextureManager::Instance()->loadSpriteSheet("../Assets/sprites/EnemyGuard.txt", "../Assets/sprites/EnemyGuard.png", "GuardSheet");

//	auto size = TextureManager::Instance()->getTextureSize("ship");
	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("GuardSheet"));
	
	setWidth(25);
	setHeight(40);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SHIP);

	setCurrentHeading(0.0f); // current facing angle
	setCurrentDirection(glm::vec2(1.0f, 0.0f)); // facing right
	m_turnRate = 5.0f; // 5 degrees per frame
	m_accelerationRate = 1.0f;
	m_maxSpeed = 3.0f;
	
	setLOSDistance(400.0f); // 5 ppf x 80 feet
	setLOSColour(glm::vec4(1, 0, 0, 1));
	setHasLOS(false);
	setDetectionDistance(200.0f);
	setDetectionColor(glm::vec4(0, 0, 1, 1));
	setHasDetection(false);
	setHealth(3);
	setHealthPostion(getTransform()->position - glm::vec2(40.0f, 25.0f));
	setAnimationState(ENEMY_IDLE);

	m_buildAnimations();
}


Enemy::~Enemy()
= default;

void Enemy::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the ship
	switch(m_currentAnimationState)
	{
	case ENEMY_IDLE:
		TextureManager::Instance()->playAnimation("GuardSheet", getAnimation("idle"), x, y, 0.10f, getCurrentHeading() + 80.0f, 255, false);
		break;
		
	case ENEMY_RUN:
		TextureManager::Instance()->playAnimation("GuardSheet", getAnimation("run"), x, y, 0.10f, getCurrentHeading() + 80.0f, 255, false);
		break;

	case ENEMY_DAMAGE:
		TextureManager::Instance()->playAnimation("GuardSheet", getAnimation("damage"), x, y, 0.10f, getCurrentHeading() + 80.0f, 255, false);
		break;

	case ENEMY_DEATH:
		TextureManager::Instance()->playAnimation("GuardSheet", getAnimation("death"), x, y, 0.10f, getCurrentHeading() + 80.0f, 255, false);
		break;
	}

	// draw LOS
	if (getDebugState())
	{
		Util::DrawLine(glm::vec2(getTransform()->position.x + getWidth() / 2, getTransform()->position.y + getHeight() / 2),
			(glm::vec2(getTransform()->position.x + getWidth() / 2, getTransform()->position.y + getHeight() / 2)) + getCurrentDirection() * getLOSDistance(), getLOSColour());

		// draw detection radius
		Util::DrawCircle(glm::vec2(getTransform()->position.x + getWidth() / 2, getTransform()->position.y + getHeight() / 2), getDetectionDistance(), getDetectionColor());
	}

	drawHeath();
}


void Enemy::update()
{
	//move();
	m_checkBounds();
	glm::vec2 m_targetDistance = glm::vec2(abs(getTransform()->position.x - getTargetPosition().x), abs( getTransform()->position.y - getTargetPosition().y));
	float magnitudeDistance = sqrt((m_targetDistance.x * m_targetDistance.x) + (m_targetDistance.y * m_targetDistance.y));
	setHealthPostion(getTransform()->position - glm::vec2(40.0f, 25.0f));
}

void Enemy::clean()
{
}

void Enemy::turnRight()
{
	setCurrentHeading(getCurrentHeading() + m_turnRate);
	if (getCurrentHeading() >= 360)
	{
		setCurrentHeading(getCurrentHeading() - 360.0f);;
	}
}

void Enemy::turnLeft()
{
	setCurrentHeading(getCurrentHeading() - m_turnRate);
	if (getCurrentHeading() < 0)
	{
		setCurrentHeading(getCurrentHeading() + 360.0f);
	}
}

void Enemy::moveForward()
{
	getRigidBody()->velocity = getCurrentDirection() * m_maxSpeed;
}

void Enemy::moveBack()
{
	getRigidBody()->velocity = getCurrentDirection() * -m_maxSpeed;
}

void Enemy::move()
{
	//getTransform()->position += getRigidBody()->velocity;
	//getRigidBody()->velocity *= 0.9f;
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	m_targetDirection = getTargetPosition() - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getCurrentDirection(), m_targetDirection);

	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setCurrentHeading(getCurrentHeading() + m_turnRate);
		}
		else if (target_rotation < 0.0f)
		{
			setCurrentHeading(getCurrentHeading() - m_turnRate);
		}
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

Animation& Enemy::getAnimation(const std::string& name)
{
	return m_pAnimations[name];
}

void Enemy::setSpriteSheet(SpriteSheet* sprite_sheet)
{
	m_EnemyAnimation = sprite_sheet;
}

void Enemy::setAnimation(const Animation& animation)
{
	if (!m_animationsExists(animation.name))
	{
		m_pAnimations[animation.name] = animation;
	}
}

void Enemy::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-idle-1"));
	idleAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-idle-2"));
	idleAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-idle-3"));
	idleAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-idle-4"));

	setAnimation(idleAnimation);
	
	Animation runAnimation = Animation();

	runAnimation.name = "run";
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-walking-1"));
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-walking-2"));
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-walking-3"));
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-walking-4"));
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-walking-5"));
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-walking-6"));
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-walking-7"));
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-walking-8"));

	setAnimation(runAnimation);

	Animation damageAnimation = Animation();

	damageAnimation.name = "damage";
	damageAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-damage-1"));
	damageAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-damage-2"));
	damageAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-damage-3"));
	damageAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-damage-4"));

	setAnimation(damageAnimation);

	Animation deathAnimation = Animation();

	deathAnimation.name = "death";
	deathAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-death-1"));
	deathAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-death-2"));
	deathAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-death-3"));
	deathAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-death-4"));

	setAnimation(deathAnimation);
}

bool Enemy::m_animationsExists(const std::string& id)
{
	return m_pAnimations.find(id) != m_pAnimations.end();
}

void Enemy::m_checkBounds()
{

	if (getTransform()->position.x + getWidth() > Config::SCREEN_WIDTH)
	{
		getTransform()->position = glm::vec2(800.0f - getWidth(), getTransform()->position.y);
	}

	if (getTransform()->position.x < 0)
	{
		getTransform()->position = glm::vec2(0.0f, getTransform()->position.y);
	}

	if (getTransform()->position.y + getHeight() > Config::SCREEN_HEIGHT)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 600.0f - getHeight());
	}

	if (getTransform()->position.y < 0)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 0.0f);
	}

}

void Enemy::m_reset()
{
	getRigidBody()->isColliding = false;
	const int halfWidth = getWidth() * 0.5f;
	const auto xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	const auto yComponent = -getHeight();
	getTransform()->position = glm::vec2(xComponent, yComponent);
}

