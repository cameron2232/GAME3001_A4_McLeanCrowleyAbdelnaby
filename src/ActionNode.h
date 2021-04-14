#pragma once
#ifndef __ACTION_NODE__
#define __ACTION_NODE__
#include "TreeNode.h"

// Interface
class ActionNode : public TreeNode
{
public:
	ActionNode() { isLeaf = true; }
	virtual ~ActionNode() = default;

	virtual void Action(Agent* m_agent) = 0;
};

#endif