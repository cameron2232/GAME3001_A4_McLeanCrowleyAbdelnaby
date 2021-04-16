#include "Agent.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"

Agent::Agent() 
{
	m_agentHealth = new Health();
}

Agent::~Agent() = default;

bool Agent::getXMoving() const
{
	return m_isXMoving;
}

bool Agent::getYMoving() const
{
	return m_isYMoving;
}

AgentType Agent::getAgentType() const
{
	return m_Type;
}

void Agent::setAgentType(AgentType type)
{
	m_Type = type;
}

void Agent::setXMoving(bool state)
{
	m_isXMoving = state;
}

void Agent::setYMoving(bool state)
{
	m_isYMoving = state;
}

bool Agent::getMoving() const
{
	return m_isMoving;
}

void Agent::setMoving(bool state)
{
	m_isMoving = state;
}

bool Agent::getDebugState() const
{
	return m_DebugEnabled;
}

void Agent::setDebug(bool state)
{
	m_DebugEnabled = state;
}

void Agent::setHealth(int health)
{
		m_agentHealth->setHealthCount(health);
}

int Agent::getHealth()
{
	return m_agentHealth->getHealthCount();
}

bool Agent::getCloseCombat() const
{
	return m_CloseCombatRange;
}

bool Agent::getHealthState() const
{
	return m_HealthState;
}

bool Agent::getRangedAttackState() const //bool for in attack range
{
	return m_RangedAttack;
}

bool Agent::getInRange() const //bool for if too close
{
	return m_inRangeDistance;
}

void Agent::setInrange(bool state)
{
	m_inRangeDistance = state;
	std::cout << m_inRangeDistance << std::endl;
	m_minFireDistanceColour = (m_inRangeDistance) ? glm::vec4(0, 1, 0, 1) : glm::vec4(0, 0, 1, 1);
}

void Agent::SetHitTimer(int timer)
{
	m_RecentlyHitTimer = timer;
}

int Agent::getHitTimer()
{
	return m_RecentlyHitTimer;
}

bool Agent::getBehindCoverState() const
{
	return m_isBehindCover;
}

bool Agent::getHitState() const
{
	return m_isRecentlyHit;
}

void Agent::setCloseCombat(bool state)
{
	m_CloseCombatRange = state;
}

void Agent::setHealthState(bool state)
{
	m_HealthState = state;
}

void Agent::setRangedAttackState(bool state)
{
	m_RangedAttack = state;
}

void Agent::setBehindCoverState(bool state)
{
	m_isBehindCover = state;
}

void Agent::setHitState(bool state)
{
	m_isRecentlyHit = state;
}

void Agent::setHealthPostion(glm::vec2 postion)
{
	m_agentHealth->getTransform()->position = postion;
}

void Agent::drawHeath()
{
	if (m_agentHealth != nullptr)
	{
		m_agentHealth->draw();
		//std::cout << std::endl << "yes" << std::endl;
	}
}

void Agent::setFireDistance(int distance)
{
	m_fireDistance = distance;
}

int Agent::getFireDistance()
{
	return m_fireDistance;
}

void Agent::setFireDetectionColour(glm::vec4 colour)
{
	m_FireDistanceColour = colour;
}

void Agent::setIsInFireDetection(bool state)
{
	m_isInFireDistance = state;
	m_FireDistanceColour = (m_isInFireDistance) ? glm::vec4(0, 1, 0, 1) : glm::vec4(0, 0, 1, 1);
}

bool Agent::getisInFireDistance()
{
	return m_isInFireDistance;
}

glm::vec4 Agent::getFireDetectionColour()
{
	return m_FireDistanceColour;
}

void Agent::setMinFireDistance(int distance)
{
	m_MinFireDistance = distance;
}

int Agent::getMinFireDistance()
{
	return m_MinFireDistance;
}

void Agent::setminFireDistanceColour(glm::vec4 colour)
{
	m_minFireDistanceColour = colour;
}

glm::vec4 Agent::getMinFireDistancecolour()
{
	return m_minFireDistanceColour;
}

void Agent::move()
{
}

glm::vec2 Agent::getTargetPosition() const
{
	return m_targetPosition;
}

glm::vec2 Agent::getCurrentDirection() const
{
	return m_currentDirection;
}

float Agent::getLOSDistance() const
{
	return m_LOSDistance;
}

bool Agent::hasLOS() const
{
	return m_hasLOS;
}

float Agent::getCurrentHeading() const
{
	return m_currentHeading;
}

glm::vec4 Agent::getLOSColour() const
{
	return m_LOSColour;
}

float Agent::getDetectionDistance() const
{
	return m_DetectionDistance;
}

bool Agent::hasDetection() const
{
	return m_hasDetection;
}

glm::vec4 Agent::getDetectionColor() const
{
	return m_DetectionColour;
}

void Agent::setLOSDistance(const float distance)
{
	m_LOSDistance = distance;
}

void Agent::setHasLOS(const bool state)
{
	m_hasLOS = state;
	m_LOSColour = (m_hasLOS) ? glm::vec4(0, 1, 0, 1) : glm::vec4(1, 0, 0, 1);
}

void Agent::setCurrentHeading(const float heading)
{
	m_currentHeading = heading;
	m_changeDirection();
}

void Agent::setTargetPosition(glm::vec2 newPosition)
{
	m_targetPosition = newPosition;

}

void Agent::setCurrentDirection(glm::vec2 newDirection)
{
	m_currentDirection = newDirection;
}

void Agent::setLOSColour(glm::vec4 colour)
{
	m_LOSColour = colour;
}

void Agent::setDetectionDistance(float distance)
{
	m_DetectionDistance = distance;
}

void Agent::setHasDetection(bool state)
{
	m_hasDetection = state;
	m_DetectionColour = (m_hasDetection) ? glm::vec4(0, 1, 0, 1) : glm::vec4(0, 0, 1, 1);
}

void Agent::setDetectionColor(glm::vec4 colour)
{
	m_DetectionColour = colour;
}

void Agent::m_changeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);

	glm::vec2 size = TextureManager::Instance()->getTextureSize("ship");
}

