#include "MapNode.h"

Node::Node(int x, int y)
{
	TextureManager::Instance()->load("../Assets/textures/Node.png", "node");
	auto size = TextureManager::Instance()->getTextureSize("node");
	setWidth(size.x);
	setHeight(size.y);
	
	getTransform()->position = glm::vec2(x, y);

	setType(NODE);
	getRigidBody()->isColliding = false;
}

Node::~Node() = default;

void Node::draw()
{
	if(getDebugState())
	{
		TextureManager::Instance()->draw("node",
			getTransform()->position.x, getTransform()->position.y, 0, 255, false);
	}
	
}

void Node::update()
{
}

void Node::clean()
{
}
