#include "MeleeAttack.h"
#include "TextureManager.h"
#include "Util.h"

MeleeAttack::MeleeAttack(float r):m_direction(r)
{
	TextureManager::Instance()->load("../Assets/textures/knife.png", "knife");
	auto size = TextureManager::Instance()->getTextureSize("knife");
	//getTransform()->position = glm::vec2(300.0f, 300.0f);
	setWidth(size.x);
	setHeight(size.y);
}

MeleeAttack::~MeleeAttack()
= default;

void MeleeAttack::draw()
{
	//TextureManager::Instance()->draw("knife", getTransform()->position.x, getTransform()->position.y, m_direction, 255, false);
}

void MeleeAttack::update()
{
}

void MeleeAttack::clean()
{
}

void MeleeAttack::setDirection(float direction)
{
	m_direction = direction;
}
