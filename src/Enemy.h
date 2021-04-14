#pragma once
#ifndef __ENEMY__
#define __ENEMY__

#include "Agent.h"
#include "TextureManager.h"
#include "PlayerAnimationState.h"
#include <glm/vec4.hpp>

#include "Sprite.h"

class Enemy final : public Agent
{
public:
	Enemy();
	~Enemy();

	// Inherited via Agent
	void draw() override;
	void update() override;
	void clean() override;

	// Movement
	void turnRight();
	void turnLeft();
	void moveForward();
	void moveBack();
	void move() override;

	// getters
	float getMaxSpeed() const;
	float getTargetDistance() const;

	// setters
	void setMaxSpeed(float newSpeed);

	//Animations
	void setAnimationState(PlayerAnimationState new_state);
	PlayerAnimationState getAnimationState();
	Animation& getAnimation(const std::string& name);
	void setSpriteSheet(SpriteSheet* sprite_sheet);
	void setAnimation(const Animation& animation);

private:
	void m_checkBounds();
	void m_reset();

	//Animations
	void m_buildAnimations();
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
};


#endif /* defined (__ENEMY__) */