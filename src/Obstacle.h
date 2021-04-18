#pragma once
#ifndef __OBSTACLE__
#define __OBSTACLE__
#include "DisplayObject.h"
#include "Renderer.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Agent.h"
#include "Health.h"

class Obstacle final : public DisplayObject
{
public:
	// constructors
	Obstacle(int x, int y, std::string File, std::string id);

	Obstacle(int w, int h, int x, int y);
	
	// destructor
	~Obstacle();
	
	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;
	int getHealth();
	void setHealth(int x);

	void setDebug(bool state);
	bool getDebug() const;
private:
	SDL_Rect Rect;
	bool DebugState;
	std::string ID;
	Health* m_pObstacleHealth;
};

#endif /* defined (__OBSTACLE__) */