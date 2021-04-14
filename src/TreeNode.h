#pragma once
#ifndef __TREE_NODE__
#define __TREE_NODE__
#include <string>
#include "Agent.h"

struct TreeNode
{
	TreeNode() = default;
	virtual ~TreeNode() = default;

	std::string name = "";
	bool data = false;

	TreeNode* Left = nullptr;
	TreeNode* Right = nullptr;
	TreeNode* Parent = nullptr;
	bool isLeaf = false;
};

#endif