#pragma once
#ifndef __SHIP__
#define __SHIP__

#include "Agent.h"
#include "TextureManager.h"
#include "PlayerAnimationState.h"
#include <glm/vec4.hpp>

#include "Sprite.h"


class Ship final : public Agent
{
public:
	Ship();
	~Ship();

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

	// setters
	void setMaxSpeed(float newSpeed);

	void setAnimationState(PlayerAnimationState new_state);
	PlayerAnimationState getAnimationState();
	Animation& getAnimation(const std::string& name);
	void setSpriteSheet(SpriteSheet* sprite_sheet);
	void setAnimation(const Animation& animation);

private:
	void m_buildAnimations();
	void m_checkBounds();
	void m_reset();

	bool m_animationsExists(const std::string& id);
	SpriteSheet* m_CharacterAnimation;
	PlayerAnimationState m_currentAnimationState;
	// steering behaviours
	float m_maxSpeed;
	float m_turnRate;

	std::unordered_map<std::string, Animation> m_pAnimations;
};


#endif /* defined (__SHIP__) */

