#include "Obstacle.h"

Obstacle::Obstacle(int x, int y,std::string File, std::string id)
{
	ID = id;
	TextureManager::Instance()->load(File, id);

	auto size = TextureManager::Instance()->getTextureSize(id);
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(x, y);

	setType(OBSTACLE);
	getRigidBody()->isColliding = false;
	m_pObstacleHealth = new Health();
	m_pObstacleHealth->setHealthCount(3);
}

Obstacle::Obstacle(int w, int h, int x, int y)
{
	getTransform()->position = glm::vec2(x, y);

	setWidth(w);
	setHeight(h);
	setType(OBSTACLE);
	Rect.w = w;
	Rect.h = h;
	Rect.x = getTransform()->position.x;
	Rect.y = getTransform()->position.y;
	m_pObstacleHealth = new Health();
	m_pObstacleHealth->setHealthCount(-10);
}

Obstacle::~Obstacle()
= default;



void Obstacle::draw()
{
	TextureManager::Instance()->draw(ID,
		getTransform()->position.x, getTransform()->position.y, 0, 255, false);
	if(getDebug())
	{
		SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 0, 255, 0, 255);
		SDL_RenderFillRect(Renderer::Instance()->getRenderer(), &Rect);
	}
}

void Obstacle::update()
{
}

void Obstacle::clean()
{
}
int Obstacle::getHealth()
{
	return m_pObstacleHealth->getHealthCount();
}
void Obstacle::setHealth(int x)
{
	m_pObstacleHealth->setHealthCount(x);
}
bool Obstacle::getDebug() const
{
	return DebugState;
}

void Obstacle::setDebug(bool state)
{
	DebugState = state;
}
