#include "ship.h"


#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"

Ship::Ship() : m_maxSpeed(10.0f), m_currentAnimationState(PLAYER_IDLE)
{
	//TextureManager::Instance()->load("../Assets/textures/ship3.png","ship");
	TextureManager::Instance()->loadSpriteSheet("../Assets/sprites/CharacterSheet.txt", "../Assets/sprites/CharacterSheet.png", "CharacterSheet");


	//auto size = TextureManager::Instance()->getTextureSize("ship");
	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("CharacterSheet"));

	setWidth(40);
	setHeight(40);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SHIP);
	
	setCurrentHeading(0.0f); // current facing angle
	setCurrentDirection(glm::vec2(1.0f, 0.0f)); // facing right
	m_turnRate = 5.0f; // 5 degrees per frame

	setMaxSpeed(5.0f);
	setLOSDistance(400.0f); // 5 ppf x 80 feet
	setLOSColour(glm::vec4(1, 0, 0, 1));
	setHasLOS(false);
	setDetectionDistance(60.0f);
	setDetectionColor(glm::vec4(0, 0, 1, 1));
	setHasDetection(false);
	setDebug(false);
	setHealth(3);
	setHealthPostion(getTransform()->position - glm::vec2(40.0f, 25.0f));
	setAnimationState(PLAYER_IDLE);

	m_buildAnimations();
	//getHealth()->getTransform()->position = getTransform()->position + glm::vec2(0.0f, 25.0f);
}


Ship::~Ship()
= default;

void Ship::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the ship
	//TextureManager::Instance()->draw("ship", x, y, getCurrentHeading(), 255, false);

	switch(m_currentAnimationState)
	{
	case PLAYER_IDLE:
		TextureManager::Instance()->playAnimation("CharacterSheet", getAnimation("idle"), x, y, 0.10f, getCurrentHeading(), 255, false);
		break;
	case PLAYER_RUN:
		TextureManager::Instance()->playAnimation("CharacterSheet", getAnimation("run"), x, y, 0.10f, getCurrentHeading(), 255, false);
		break;
	case PLAYER_SHOOT:
		TextureManager::Instance()->playAnimation("CharacterSheet", getAnimation("shoot"), x, y, 0.10f, getCurrentHeading(), 255, false);
		break;
	case PLAYER_MELEE:
		TextureManager::Instance()->playAnimation("CharacterSheet", getAnimation("melee"), x, y, 0.10f, getCurrentHeading(), 255, false);
		break;
	}


	if (getDebugState())
	{
		//Draw LOS
		Util::DrawLine(glm::vec2(getTransform()->position.x + getWidth() / 2, getTransform()->position.y + getHeight() / 2),
			(glm::vec2(getTransform()->position.x + getWidth() / 2, getTransform()->position.y + getHeight() / 2)) + getCurrentDirection() * getLOSDistance(), getLOSColour());
		
		// draw detection radius
		Util::DrawCircle(glm::vec2(getTransform()->position.x + getWidth() / 2, getTransform()->position.y + getHeight() / 2), getDetectionDistance(), getDetectionColor());
	}
	drawHeath();
}


void Ship::update()
{
	
	if(getMoving())
		move();
	m_checkBounds();
	setHealthPostion(getTransform()->position - glm::vec2(40.0f, 25.0f));
	auto angle = (atan2(EventManager::Instance().getMousePosition().y - getTransform()->position.y, EventManager::Instance().getMousePosition().x - getTransform()->position.x)
		* 180.00 / 3.1415926);
	setCurrentHeading(angle);
}

void Ship::clean()
{
}

void Ship::turnRight()
{
	setCurrentHeading(getCurrentHeading() + m_turnRate );
	if (getCurrentHeading() >= 360) 
	{
		setCurrentHeading(getCurrentHeading() - 360.0f);;
	}
}

void Ship::turnLeft()
{
	setCurrentHeading(getCurrentHeading() - m_turnRate);
	if (getCurrentHeading() < 0)
	{
		setCurrentHeading(getCurrentHeading() + 360.0f);
	}
}

void Ship::moveForward()
{
	getRigidBody()->velocity = getCurrentDirection() * m_maxSpeed;
}

void Ship::moveBack()
{
	getRigidBody()->velocity = getCurrentDirection() * -m_maxSpeed;
}

void Ship::move()
{
	/*getTransform()->position += getRigidBody()->velocity;
	getRigidBody()->velocity *= 0.9f;*/
	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, getMaxSpeed());
	if(getXMoving())
	{
		getRigidBody()->velocity.x = getCurrentDirection().x * m_maxSpeed;
		getTransform()->position.x += getRigidBody()->velocity.x;

	}
	if(getYMoving())
	{

		getRigidBody()->velocity.y = getCurrentDirection().y * m_maxSpeed;
		getTransform()->position.y += getRigidBody()->velocity.y;
	}

}

float Ship::getMaxSpeed() const
{
	return m_maxSpeed;
}

void Ship::setMaxSpeed(const float newSpeed)
{
	m_maxSpeed = newSpeed;
}

void Ship::setAnimationState(PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

PlayerAnimationState Ship::getAnimationState()
{
	return m_currentAnimationState;
}

void Ship::setSpriteSheet(SpriteSheet* sprite_sheet)
{
	m_CharacterAnimation = sprite_sheet;
}

void Ship::setAnimation(const Animation& animation)
{
	if (!m_animationsExists(animation.name))
	{
		m_pAnimations[animation.name] = animation;
	}
}

bool Ship::m_animationsExists(const std::string& id)
{
	return m_pAnimations.find(id) != m_pAnimations.end();
}

Animation& Ship::getAnimation(const std::string& name)
{
	return m_pAnimations[name];
}

void Ship::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-idle-1"));
	idleAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-idle-2"));
	idleAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-idle-3"));
	idleAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-idle-4"));

	setAnimation(idleAnimation);

	Animation shootAnimation = Animation();

	shootAnimation.name = "shoot";
	shootAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-shoot-1"));
	shootAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-shoot-2"));
	shootAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-shoot-3"));
	shootAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-shoot-4"));

	setAnimation(shootAnimation);

	Animation meleeAnimation = Animation();

	meleeAnimation.name = "melee";
	meleeAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-melee-1"));
	meleeAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-melee-2"));
	meleeAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-melee-3"));
	meleeAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-melee-4"));
	meleeAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-melee-5"));

	setAnimation(meleeAnimation);

	Animation runAnimation = Animation();

	runAnimation.name = "run";
	runAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-run-1"));
	runAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-run-2"));
	runAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-run-3"));
	runAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-run-4"));
	runAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-run-5"));
	runAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-run-6"));
	runAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-run-7"));
	runAnimation.frames.push_back(m_CharacterAnimation->getFrame("character-run-8"));

	setAnimation(runAnimation);
}

void Ship::m_checkBounds()
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

void Ship::m_reset()
{
	getRigidBody()->isColliding = false;
	const int halfWidth = getWidth() * 0.5f;
	const auto xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	const auto yComponent = -getHeight();
	getTransform()->position = glm::vec2(xComponent, yComponent);
}

