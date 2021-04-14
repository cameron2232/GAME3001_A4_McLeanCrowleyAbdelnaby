#include "DecisionTree.h"
#include <iostream>

#include "AttackAction.h"
#include "MoveToLOSAction.h"
#include "MoveToPlayerAction.h"
#include "PatrolAction.h"

DecisionTree::DecisionTree()
{
	m_buildTree();
}

DecisionTree::~DecisionTree() = default;

Agent* DecisionTree::getAgent() const
{
	return m_agent;
}

void DecisionTree::setAgent(Agent * agent)
{
	m_agent = agent;
}

TreeNode* DecisionTree::getCurrentNode() const
{
	return m_currentNode;
}

void DecisionTree::setCurrentNode(TreeNode* node)
{
	m_currentNode = node;
}

TreeNode* DecisionTree::AddNode(TreeNode * parent, TreeNode * child_node, const TreeNodeType type)
{
	switch (type)
	{
	case LEFT_TREE_NODE:
		parent->Left = child_node;
		break;
	case RIGHT_TREE_NODE:
		parent->Right = child_node;
		break;
	}

	child_node->Parent = parent; // Backwards Traversal

	return child_node;
}

void DecisionTree::Display()
{
	for (auto* node : m_treeNodeList)
	{
		std::cout << node->name << std::endl;
	}
}

void DecisionTree::Update()
{
	m_LOSNode->setLOS(m_agent->hasLOS());

	if(getCurrentNode() == m_treeNodeList[3])
	{
		m_CurrentAction = new PatrolAction;
		m_CurrentAction->Action(getAgent());
	}
	
}

// In-order Traversal
std::string DecisionTree::MakeDecision()
{
	Update();

	auto currentNode = m_treeNodeList[0]; 

	while (!currentNode->isLeaf)
	{
		currentNode = (currentNode->data) ? (currentNode->Right) : (currentNode->Left);
	}

	setCurrentNode(currentNode);
	return currentNode->name;
}

void DecisionTree::m_buildTree()
{
	m_LOSNode = new LOSCondition();
	m_treeNodeList.push_back(m_LOSNode); // Node 0

	m_RadiusNode = new RadiusCondition();
	AddNode(m_LOSNode, m_RadiusNode, LEFT_TREE_NODE);
	m_treeNodeList.push_back(m_RadiusNode); // Node 1

	m_CloseCombatNode = new CloseCombatCondition();
	AddNode(m_LOSNode, m_CloseCombatNode, RIGHT_TREE_NODE);
	m_treeNodeList.push_back(m_CloseCombatNode); // Node 2

	TreeNode* patrolNode = AddNode(m_RadiusNode, new PatrolAction(), LEFT_TREE_NODE);
	m_treeNodeList.push_back(patrolNode); // Node 3

	TreeNode* moveToLOSNode = AddNode(m_RadiusNode, new MoveToLOSAction(), RIGHT_TREE_NODE);
	m_treeNodeList.push_back(moveToLOSNode); // Node 4

	TreeNode* moveToPlayerNode = AddNode(m_CloseCombatNode, new MoveToPlayerAction(), LEFT_TREE_NODE);
	m_treeNodeList.push_back(moveToPlayerNode); // Node 5

	TreeNode* attackNode = AddNode(m_CloseCombatNode, new AttackAction(), RIGHT_TREE_NODE);
	m_treeNodeList.push_back(attackNode); // Node 6
}
