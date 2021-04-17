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
	m_label = new Label("--", "Consolas", 15, colour, glm::vec2(625.0f, 15.0f));
}

Node::~Node() = default;

void Node::draw()
{
	if(getDebugState())
	{
		TextureManager::Instance()->draw("node",
			getTransform()->position.x, getTransform()->position.y, 0, 255, false);

		m_label->getTransform()->position = glm::vec2(getTransform()->position.x + getWidth()/2, getTransform()->position.y + getHeight() / 2);
		m_label->draw();
	}
	
}

void Node::update()
{
	
}

void Node::clean()
{
}

void Node::setHasLOS(bool state)
{
	m_hasLOS = state;
}

bool Node::getHasLOS()
{
	return m_hasLOS;
}

