#pragma once
#ifndef __OBSTACLE__
#define __OBSTACLE__
#include "DisplayObject.h"
#include "Renderer.h"
#include "SoundManager.h"
#include "TextureManager.h"

class Obstacle final : public DisplayObject
{
public:
	// constructors
	Obstacle();

	Obstacle(int w, int h, int x, int y);
	
	// destructor
	~Obstacle();
	
	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;

	void setDebug(bool state);
	bool getDebug() const;
private:
	SDL_Rect Rect;
	bool DebugState;
};

#endif /* defined (__OBSTACLE__) */