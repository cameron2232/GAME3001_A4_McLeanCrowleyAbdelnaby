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
#include "REnemy.h"
#include "CCEnemy.h"

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
	void m_DecisionMaking(Enemy* m_agent);
	void m_CheckEnemyBehindCover(Enemy* enemy);
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	glm::vec2 m_mousePosition;
	bool m_isGridEnabled;
	bool m_isPatrolling;
	void m_setUIScore();
	Target* m_pTarget;
	Ship* m_pShip;
	std::vector<Obstacle*> m_pObstacle;
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
	
	void m_CheckEnemyHealth(Enemy* enemy);
	void m_CheckCloseCombatRange(Enemy* enemy);
	void m_CheckEnemyFireDetection(Enemy* enemy);
	void m_CheckNodeLOS(Node* node);
	bool m_CheckNodeEnemyLOS(Node* node, Agent* enemy);
	void m_CheckBehindCover(Enemy* enemy);
	void m_CheckTooClose(Enemy* enemy);
	void m_RespawnEnemy(int numb);

	int cooldown = 20;
	//DecisionTree* decisionTree;
	const float m_playerSpeed = 5.0f;
	MeleeAttack* m_meleeActtack;
	int meleeCoolDown = 30;
	std::vector<Bullet*> m_pPlayerBullets;
	std::vector<Bullet*> m_pEnemyBullets;
	int currentMapNode;
	int m_enemysKilled = 0;
	Label* m_UIScore;
	Label* instructions;
	int deathCooldown = 60;
	int damageCooldown = 60;
	int meleeDamageCooldown = 60;
	int footstepCooldown = 60;
	int pfootstep = 0;
	int EnemyFireCoolDown = 20;
	int CCEnemyAttackCoolDown = 5;
};



#endif /* defined (__PLAY_SCENE__) */
