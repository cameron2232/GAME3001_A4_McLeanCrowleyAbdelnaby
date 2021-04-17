#include "CCEnemy.h"

#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"

CCEnemy::CCEnemy()
{
	m_maxSpeed = 10.0f;
	TextureManager::Instance()->loadSpriteSheet("../Assets/sprites/CCEnemyGuard.txt", "../Assets/sprites/CCEnemyGuard.png", "CCGuardSheet");

	//	auto size = TextureManager::Instance()->getTextureSize("ship");
	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("CCGuardSheet"));

	setWidth(30);
	setHeight(50);

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
	setAgentType(CLOSE_COMBAT_ENEMY);

	setFireDistance(50.0f); //Can fire in this range
	setIsInFireDetection(false);

	deathCooldown = 60;

	decisionTree = new DecisionTree();
	decisionTree->setAgent(this);
	Hitbox = new SDL_FRect({ getTransform()->position.x, getTransform()->position.y, 64.0f, 64.0f });
	m_buildAnimations();
}


CCEnemy::~CCEnemy()
= default;

void CCEnemy::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the ship
	switch (m_currentAnimationState)
	{
	case ENEMY_IDLE:
		TextureManager::Instance()->playAnimation("CCGuardSheet", getAnimation("idle"), x, y, 0.10f, getCurrentHeading() + 80.0f, 255, false, SDL_FLIP_VERTICAL);
		break;

	case ENEMY_RUN:
		TextureManager::Instance()->playAnimation("CCGuardSheet", getAnimation("run"), x, y, 0.10f, getCurrentHeading() + 80.0f, 255, false, SDL_FLIP_VERTICAL);
		break;

	case CCENEMY_ATTACK:
		TextureManager::Instance()->playAnimation("CCGuardSheet", getAnimation("damage"), x, y, 0.10f, getCurrentHeading() + 80.0f, 255, false, SDL_FLIP_VERTICAL);
		break;

	/*case ENEMY_DEATH:
		TextureManager::Instance()->playAnimation("CCGuardSheet", getAnimation("death"), x, y, 0.10f, getCurrentHeading() + 80.0f, 255, false);
		break;*/
	}

	// draw LOS
	if (getDebugState())
	{
		Util::DrawLine(glm::vec2(getTransform()->position.x + getWidth() / 2, getTransform()->position.y + getHeight() / 2),
			(glm::vec2(getTransform()->position.x + getWidth() / 2, getTransform()->position.y + getHeight() / 2)) + getCurrentDirection() * getLOSDistance(), getLOSColour());

		// draw detection radius
		Util::DrawCircle(glm::vec2(getTransform()->position.x + getWidth() / 2, getTransform()->position.y + getHeight() / 2), getDetectionDistance(), getDetectionColor());

		Util::DrawCircle(glm::vec2(getTransform()->position.x + getWidth() / 2, getTransform()->position.y + getHeight() / 2), 50, getDetectionColor());
	}

	drawHeath();
}


void CCEnemy::update()
{
	//move();
	//m_checkBounds();
	glm::vec2 m_targetDistance = glm::vec2(abs(getTransform()->position.x - getTargetPosition().x), abs(getTransform()->position.y - getTargetPosition().y));
	float magnitudeDistance = sqrt((m_targetDistance.x * m_targetDistance.x) + (m_targetDistance.y * m_targetDistance.y));
	setHealthPostion(getTransform()->position - glm::vec2(40.0f, 25.0f));
	Hitbox->x = getTransform()->position.x;
	Hitbox->y = getTransform()->position.y;
}

void CCEnemy::clean()
{
}

void CCEnemy::Attack()
{
	setAnimationState(CCENEMY_ATTACK);	
}

void CCEnemy::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(m_EnemyAnimation->getFrame("ccguard-idle-1"));
	idleAnimation.frames.push_back(m_EnemyAnimation->getFrame("ccguard-idle-2"));

	setAnimation(idleAnimation);

	Animation runAnimation = Animation();

	runAnimation.name = "run";
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("ccguard-walking-1"));
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("ccguard-walking-2"));
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("ccguard-walking-3"));
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("ccguard-walking-4"));
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("ccguard-walking-5"));
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("ccguard-walking-6"));
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("ccguard-walking-7"));
	runAnimation.frames.push_back(m_EnemyAnimation->getFrame("ccguard-walking-8"));

	setAnimation(runAnimation);

	Animation attackAnimation = Animation();

	attackAnimation.name = "attack";
	attackAnimation.frames.push_back(m_EnemyAnimation->getFrame("ccguard-damage-1"));
	attackAnimation.frames.push_back(m_EnemyAnimation->getFrame("ccguard-damage-2"));
	attackAnimation.frames.push_back(m_EnemyAnimation->getFrame("ccguard-damage-3"));
	attackAnimation.frames.push_back(m_EnemyAnimation->getFrame("ccguard-damage-4"));
	attackAnimation.frames.push_back(m_EnemyAnimation->getFrame("ccguard-damage-5"));

	setAnimation(attackAnimation);

	/*Animation deathAnimation = Animation();

	deathAnimation.name = "death";
	deathAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-death-1"));
	deathAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-death-2"));
	deathAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-death-3"));
	deathAnimation.frames.push_back(m_EnemyAnimation->getFrame("guard-death-4"));

	setAnimation(deathAnimation);*/
}
