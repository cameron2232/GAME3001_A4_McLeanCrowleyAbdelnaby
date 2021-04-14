#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Button.h"
#include "DecisionTree.h"
#include "Label.h"
#include "Obstacle.h"
#include "ship.h"
#include "SpaceShip.h"
#include "Target.h"
#include "MapNode.h"
#include "MeleeAttack.h"
#include "Bullet.h"
#include "Enemy.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	void CollisionsUpdate();

	

private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	glm::vec2 m_mousePosition;
	bool m_isGridEnabled;
	bool m_isPatrolling;
	void m_setUIScore();
	Target* m_pTarget;
	Ship* m_pShip;
	Obstacle* m_pObstacle[5];
	std::vector<Enemy*> m_pEnemy;
	std::vector<Node*> m_pNode;
	void m_CheckShipLOS(DisplayObject* object);
	void m_CheckShipDetection(DisplayObject* object);
	void m_CheckEnemyDetection(Enemy* enemy);
	void m_CheckEnemyLOS(Enemy* enemy);
	void m_setDebugMode(bool state);
	bool m_getDebugMode() const;
	void m_setPatrolMode(bool state);
	bool m_getPatrolMode() const;
	int cooldown = 20;
	DecisionTree* decisionTree;
	const float m_playerSpeed = 5.0f;
	MeleeAttack* m_meleeActtack;
	int meleeCoolDown = 30;
	std::vector<Bullet*> m_pPlayerBullets;
	int currentMapNode;
	int m_enemysKilled = 0;
	Label* m_UIScore;
	Label* instructions;
	int deathCooldown = 60;
	int damageCooldown = 60;
	int footstepCooldown = 60;
	int pfootstep = 0;

};



#endif /* defined (__PLAY_SCENE__) */
