#pragma once
#ifndef __ENEMY__
#define __ENEMY__

#include "Agent.h"
#include "TextureManager.h"
#include "PlayerAnimationState.h"
#include <glm/vec4.hpp>


#include "DecisionTree.h"
#include "Sprite.h"

class Enemy: public Agent
{
public:
	Enemy();
	~Enemy();

	// Inherited via Agent
	void draw() override = 0;
	void update() override = 0;
	void clean() override = 0;
	virtual void m_buildAnimations() = 0;

	// Movement
	void turnRight();
	void turnLeft();
	void moveForward();
	void moveBack();
	void move() override;
	void rotate();
	void flee();
	virtual void Attack();

	// getters
	float getMaxSpeed() const;
	float getTargetDistance() const;
	bool getHasDetected() const;

	// setters
	void setMaxSpeed(float newSpeed);
	void setHasDetected(bool state);

	//Animations
	void setAnimationState(PlayerAnimationState new_state);
	PlayerAnimationState getAnimationState();
	Animation& getAnimation(const std::string& name);
	void setSpriteSheet(SpriteSheet* sprite_sheet);
	void setAnimation(const Animation& animation);

	void setPatrol(int s, int e);
	void setPatrolCurrent(int c);

	int getPatrolS();
	int getPatrolE();
	int getPatrolCurrent();
	
	void m_checkBounds();
	void m_reset();

	SDL_FRect* getHitBox();

	//Animations
	bool m_animationsExists(const std::string& id);
	SpriteSheet* m_EnemyAnimation;
	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;

	// steering behaviours
	float m_maxSpeed;
	float m_turnRate;
	glm::vec2 m_targetDirection;
	float m_magnitudeDistance;
	float m_accelerationRate;
	bool hasDetected;
	SDL_FRect* Hitbox;

	int deathCooldown;
	int patrolStart, patrolEnd, patrolCurrent, attackCooldown;

	//Decision Tree
	DecisionTree* decisionTree;
	DecisionTree* getDecisionTree();
	
};


#endif /* defined (__R_ENEMY__) */
