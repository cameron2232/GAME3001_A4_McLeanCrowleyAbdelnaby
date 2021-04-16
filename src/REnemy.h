#pragma once
#ifndef __R_ENEMY__
#define __R_ENEMY__

#include "Agent.h"
#include "TextureManager.h"
#include "PlayerAnimationState.h"
#include <glm/vec4.hpp>


#include "Enemy.h"
#include "Sprite.h"

class REnemy final : public Enemy
{
public:
	REnemy();
	~REnemy();

	// Inherited via Agent
	void draw() override;
	void update() override;
	void clean() override;
	void Attack();

private:
	//Animations
	void m_buildAnimations() override;
};


#endif /* defined (__R_ENEMY__) */