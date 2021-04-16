#pragma once
#ifndef __AGENT__
#define __AGENT__

#include "DisplayObject.h"
#include "Health.h"
#include "EventManager.h"
#include "AgentType.h"
#include <glm/vec4.hpp>

class Agent : public DisplayObject
{
public:
	Agent();
	~Agent();

	// Inherited via GameObject
	void draw() override = 0;
	void update() override = 0;
	void clean() override = 0;

	virtual void move();

	// getters
	glm::vec2 getTargetPosition() const;
	glm::vec2 getCurrentDirection() const;

	float getLOSDistance() const;
	bool hasLOS() const;
	float getCurrentHeading() const;
	glm::vec4 getLOSColour() const;
	float getDetectionDistance() const;
	bool hasDetection() const;
	glm::vec4 getDetectionColor() const;
	bool getDebugState() const;
	bool getMoving() const;
	bool getXMoving() const;
	bool getYMoving() const;
	AgentType getAgentType() const;
	int getHealth();
	bool getCloseCombat() const;
	bool getHealthState() const;
	bool getRangedAttackState() const;
	bool getInRange() const;
	bool getBehindCoverState() const;
	bool getHitState() const;

	// setters
	void setTargetPosition(glm::vec2 newPosition);
	void setCurrentDirection(glm::vec2 newDirection);
	void setLOSDistance(float distance);
	void setHasLOS(bool state);
	void setCurrentHeading(float heading);
	void setLOSColour(glm::vec4 colour);
	void setDetectionDistance(float distance);
	void setHasDetection(bool state);
	void setDetectionColor(glm::vec4 colour);
	void setDebug(bool state);
	void setHealth(int health);
	void setMoving(bool state);
	void setXMoving(bool state);
	void setYMoving(bool state);
	void setHealthPostion(glm::vec2 postion);
	void drawHeath();
	void setAgentType(AgentType type);
	void setCloseCombat(bool state);
	void setHealthState(bool state);
	void setRangedAttackState(bool state);
	void setBehindCoverState(bool state);
	void setHitState(bool state);
	void setInrange(bool state);


	void setFireDistance(int distance);
	int getFireDistance();
	void setFireDetectionColour(glm::vec4 colour);
	void setIsInFireDetection(bool state);
	bool getisInFireDistance();
	glm::vec4 getFireDetectionColour();
private:
	void m_changeDirection();
	float m_currentHeading;
	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;
	Health* m_agentHealth;
	AgentType m_Type;
	// LOS
	float m_LOSDistance;
	bool m_hasLOS;
	bool m_CloseCombatRange;
	bool m_HealthState;
	bool m_RangedAttack;
	bool m_inRangeDistance;
	bool m_isBehindCover;
	bool m_isRecentlyHit;
	glm::vec4 m_LOSColour;

	//Detection Radius
	float m_DetectionDistance;
	bool m_hasDetection;
	glm::vec4 m_DetectionColour;

	int m_fireDistance;
	bool m_isInFireDistance;
	glm::vec4 m_FireDistanceColour;

	//Debug
	bool m_DebugEnabled;
	bool m_isMoving;
	bool m_isXMoving;
	bool m_isYMoving;
};


#endif