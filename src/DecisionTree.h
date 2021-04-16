#pragma once
#ifndef __DECISION_TREE__
#define __DECISION_TREE__
#include "Agent.h"
#include "CloseCombatCondition.h"
#include "LOSCondition.h"
#include "RadiusCondition.h"
#include "HealthCondition.h"
#include "BehindCoverCondition.h"
#include "AttackRangeCondition.h"
#include "TooCloseCondition.h"
#include "TreeNode.h"
#include "TreeNodeType.h"
#include "PatrolAction.h"
#include "RangeAttackAction.h"
#include "MoveToLOSAction.h"
#include "MoveToPlayerAction.h"
#include "FleeAction.h"
#include "MoveBehindCoverAction.h"
#include "WaitBehindCoverAction.h"
#include "MoveToRangeAction.h"
#include "CloseCombatAction.h"
#include "RecentlyHitCondition.h"

class DecisionTree
{
public:
	DecisionTree();
	~DecisionTree();

	// Getters Setters
	Agent* getAgent() const;
	void setAgent(Agent* agent);

	TreeNode* getCurrentNode() const;
	void setCurrentNode(TreeNode* node);

	ActionNode* getCurrentAction() const;
	void setCurrentAction(ActionNode* node);

	TreeNode* AddNode(TreeNode* parent, TreeNode* child_node, TreeNodeType type);
	void Display();
	void Update();

	std::string MakeDecision();

private:
	Agent* m_agent;
	LOSCondition* m_LOSNode;
	RadiusCondition* m_RadiusNode;
	CloseCombatCondition* m_CloseCombatNode;
	HealthCondition* m_HealthNode;
	AttackRangeCondition* m_AttackRangeNode;
	TooCloseCondition* m_RangeDistanceNode;
	BehindCoverCondition* m_BehindCoverNode;
	RecentlyHitCondition* m_RecentlyHitNode;


	TreeNode* m_currentNode;
	void m_buildTree();

	std::vector<TreeNode*> m_treeNodeList;
};


#endif
