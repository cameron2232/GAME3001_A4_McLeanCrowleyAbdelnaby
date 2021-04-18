#pragma once
#ifndef __LOSE_SCENE__
#define __LOSE_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Button.h"
#include "Sprite.h"

class LoseScene final : public Scene
{
public:
	LoseScene();
	~LoseScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	Label* m_Lose;
	Button* m_pRestartButton;
};

#endif