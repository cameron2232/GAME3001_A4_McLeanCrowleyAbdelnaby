#include "Health.h"
#include "TextureManager.h"

Health::Health()
{
	TextureManager::Instance()->load("../Assets/textures/Heart.png", "heart");
	auto size = TextureManager::Instance()->getTextureSize("heart");
	getTransform()->position = glm::vec2(300.0f, 300.0f);
	setWidth(size.x);
	setHeight(size.y);
}

Health::~Health()
= default;
void Health::draw()
{
	auto offSet = 5;
	if (m_healthCount >= 1)
		TextureManager::Instance()->draw("heart", getTransform()->position.x - offSet, getTransform()->position.y, 0, 255, false);
	if (m_healthCount >= 2)
		TextureManager::Instance()->draw("heart", getTransform()->position.x + getWidth() , getTransform()->position.y, 0, 255, false);
	if (m_healthCount == 3)
		TextureManager::Instance()->draw("heart", getTransform()->position.x + (getWidth() * 2) + offSet, getTransform()->position.y, 0, 255, false);
}

void Health::update()
{
}

void Health::clean()
{
}

int Health::getHealthCount()
{
	return m_healthCount;
}

void Health::setHealthCount(int health)
{
	m_healthCount = health;
}
