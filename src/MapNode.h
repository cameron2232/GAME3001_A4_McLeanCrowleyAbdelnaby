#pragma once
#ifndef __MAP_NODE__
#define __MAP_NODE__
#include "Agent.h"
#include "DisplayObject.h"
#include "TextureManager.h"

class Node : public Agent
{
public:
	Node(int x, int y);
	
	~Node();

	void draw() override;
	void update() override;
	void clean() override;
};

#endif 
