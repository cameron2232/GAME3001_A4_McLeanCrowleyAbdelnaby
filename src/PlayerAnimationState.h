#pragma once
#ifndef __PLAYER_ANIMATION_STATE__
#define __PLAYER_ANIMATION_STATE__

enum PlayerAnimationState
{
	PLAYER_IDLE_RIGHT,
	PLAYER_IDLE_LEFT,
	PLAYER_RUN_RIGHT,
	PLAYER_RUN_LEFT,
	PLAYER_RUN_UP,
	PLAYER_RUN_DOWN,
	PLAYER_IDLE,
	PLAYER_RUN,
	PLAYER_SHOOT,
	PLAYER_MELEE,
	ENEMY_IDLE,
	ENEMY_RUN,
	ENEMY_DAMAGE,
	ENEMY_DEATH,
	NUM_OF_ANIMATION_STATES
};

#endif /* defined (__PLAYER_ANIMATION_STATE__)*/