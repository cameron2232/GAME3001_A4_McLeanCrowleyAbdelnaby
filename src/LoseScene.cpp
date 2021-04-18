#include "LoseScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

LoseScene::LoseScene()
{
	LoseScene::start();
}

LoseScene::~LoseScene()
= default;

void LoseScene::draw()
{
	drawDisplayList();
}

void LoseScene::update()
{
	updateDisplayList();
}

void LoseScene::clean()
{
	removeAllChildren();
}

void LoseScene::handleEvents()
{
	EventManager::Instance().update();

	// Button Events
	m_pRestartButton->update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
		TheGame::Instance()->quit();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
}

void LoseScene::start()
{
	const SDL_Color red = { 255, 0, 0, 255 };

	m_Lose = new Label("YOU ARE DEAD", "Dock51", 85, red, glm::vec2(400.0f, 100.0f));
	m_Lose->setParent(this);
	addChild(m_Lose);

	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/restartButton.png", "restartButton", RESTART_BUTTON);
	m_pRestartButton->getTransform()->position = glm::vec2(400.0f, 400.0f);
	m_pRestartButton->addEventListener(CLICK, [&]()-> void
		{
			m_pRestartButton->setActive(false);
			TheGame::Instance()->changeSceneState(PLAY_SCENE);
		});

	m_pRestartButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pRestartButton->setAlpha(128);
		});

	m_pRestartButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pRestartButton->setAlpha(255);
		});

	addChild(m_pRestartButton);
}