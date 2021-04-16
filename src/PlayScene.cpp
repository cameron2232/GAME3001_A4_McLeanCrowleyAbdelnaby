#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include <sstream>
#include <iomanip>
// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("Background",
		0, getTransform()->position.y, 0, 255, false);
	
	for (int i = 0; i < m_pPlayerBullets.size(); i++)
	{
		addChild(m_pPlayerBullets[i]);
	}
	for (int i = 0; i < m_pEnemyBullets.size(); i++)
	{
		addChild(m_pEnemyBullets[i]);
	}


	drawDisplayList();

	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);

	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();	
	}
}

void PlayScene::update()
{
	decisionTree->MakeDecision();
	if (m_pEnemy[0]->getHealth() == 1)
	{
		m_pEnemy[0]->setHealthState(true);
	}
	//std::cout << m_pPlayerBullets.size() << std::endl;
	EnemyFireCoolDown--;
	meleeCoolDown--;
	m_setUIScore();
	CollisionsUpdate();
	updateDisplayList();
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i] != nullptr)
		{
			m_DecisionMaking(m_pEnemy[i]);
		}
	}

	//m_DecisionMaking();
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_CheckShipLOS(m_pEnemy[i]);
		m_CheckShipDetection(m_pEnemy[i]);
		m_CheckEnemyDetection(m_pEnemy[i]);
		m_CheckEnemyLOS(m_pEnemy[i]);
		m_CheckEnemyFireDetection(m_pEnemy[i]);
		m_CheckEnemyBehindCover(m_pEnemy[i]);
	}

	if (m_getPatrolMode())
	{
		footstepCooldown--;
		if(footstepCooldown <= 0)
		{
			footstepCooldown = 60;
			SoundManager::Instance().playSound("EWalk", 0, 2);
		}
		//decisionTree->Update();
		for (int i = 0; i < m_pEnemy.size(); i++)
		{
			if (m_pEnemy[i]->getAnimationState() != ENEMY_DAMAGE && m_pEnemy[i]->getAnimationState() != ENEMY_DEATH)
				m_pEnemy[i]->setAnimationState(ENEMY_RUN);
		}
		
	}
	else
	{
		for (int i = 0; i < m_pEnemy.size(); i++)
		{
			if (m_pEnemy[i]->getAnimationState() != ENEMY_DAMAGE && m_pEnemy[i]->getAnimationState() != ENEMY_DEATH)
				m_pEnemy[i]->setAnimationState(ENEMY_IDLE);
		}
	}

	if(m_meleeActtack != nullptr)
		m_meleeActtack->getTransform()->position = m_pShip->getTransform()->position - glm::vec2(-10.0f, 10.f);
	//for (int i = 0; i < m_pPlayerBullets.size(); i++)
	//{
	//	m_pPlayerBullets[i]->setRotation(m_pShip->getCurrentHeading());
	//}
	m_meleeActtack->setDirection(m_pShip->getCurrentHeading() + 90);


	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (CollisionManager::AABBCheck(m_pEnemy[i], m_pNode[currentMapNode]))
		{
			if (currentMapNode == 19)
				currentMapNode = 0;
			else
			{
				currentMapNode++;
			}
			m_pEnemy[i]->setTargetPosition(glm::vec2(m_pNode[currentMapNode]->getTransform()->position.x - (m_pNode[currentMapNode]->getWidth() / 2),
				m_pNode[currentMapNode]->getTransform()->position.y - (m_pNode[currentMapNode]->getHeight() / 2)));
		}
	}

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i]->getHealth() == 0)
		{
			m_pEnemy[i]->setAnimationState(ENEMY_DEATH);
			m_setPatrolMode(false);
			
			break;
		}
	}
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i]->getAnimationState() == ENEMY_DEATH)
		{
			deathCooldown--;
		}
		if(deathCooldown <= 0)
		{
			m_enemysKilled++;
			SoundManager::Instance().playSound("Death", 0, -1);
			deathCooldown = 60;
			removeChild(m_pEnemy[i]);
			m_pEnemy[i] = nullptr;
			m_pEnemy.erase(m_pEnemy.begin() + i);
			m_pEnemy.shrink_to_fit();
			break;
		}
	}

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i]->getAnimationState() == ENEMY_DAMAGE)
		{
			damageCooldown--;
		}

		if(damageCooldown <= 0)
		{
			damageCooldown = 60;
			m_pEnemy[i]->setAnimationState(ENEMY_IDLE);
		}
	}

	if (m_pShip->getAnimationState() == PLAYER_IDLE && m_pShip->getMoving() == true)
	{
		
		m_pShip->setAnimationState(PLAYER_RUN);
	}
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	cooldown--;
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_H))
	{
		if (cooldown <= -20)
		{
			m_pShip->setDebug(!m_pShip->getDebugState());
			for (auto node : m_pNode)
				node->setDebug(!node->getDebugState());
			for (int i = 0; i < m_pEnemy.size(); i++)
			{
				m_pEnemy[i]->setDebug(!m_pEnemy[i]->getDebugState());
			}

			for (auto obstacle : m_pObstacle)
			{
				obstacle->setDebug(!obstacle->getDebug());
			}
			cooldown = 20;
		}
	}
	
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_M))
	{
		if (cooldown <= -20)
		{
			if(m_pShip->getHealth() != 3)
				m_pShip->setHealth(m_pShip->getHealth() + 1);
			std::cout << m_pShip->getHealth() << std::endl;
			cooldown = 20;
		}
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_K))
	{
		if (cooldown <= -20)
		{
			for (int i = 0; i < m_pEnemy.size(); i++)
			{
				if (m_pEnemy[i]->getHealth() != 0)
					m_pEnemy[i]->setHealth(m_pEnemy[i]->getHealth() - 1);
				std::cout << m_pEnemy[i]->getHealth() << std::endl;
				m_pEnemy[i]->setAnimationState(ENEMY_DAMAGE);
			}
			cooldown = 20;
		}
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_G))
	{
		if (cooldown <= -20)
		{
			m_pShip->setHealth(m_pShip->getHealth() - 1);
			std::cout << m_pShip->getHealth() << std::endl;
			cooldown = 20;
		}
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_P))
	{
		if (cooldown <= -20)
		{
			m_setPatrolMode(!m_getPatrolMode());
			if (m_getPatrolMode())
			{

				for (int i = 0; i < m_pEnemy.size(); i++)
				{

					m_pEnemy[i]->setAnimationState(ENEMY_RUN);
				}

			}
			else
			{
				for (int i = 0; i < m_pEnemy.size(); i++)
					m_pEnemy[i]->setAnimationState(ENEMY_IDLE);
			}
			cooldown = 20;
		}
	}
	
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_W) || EventManager::Instance().isKeyDown(SDL_SCANCODE_S) 
		|| EventManager::Instance().isKeyDown(SDL_SCANCODE_A) || EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		pfootstep--;
		if(pfootstep <= 0)
		{
			pfootstep = 30;
			SoundManager::Instance().playSound("PWalk", 0, 1);
		}
		if(m_pShip->getAnimationState() != PLAYER_SHOOT && m_pShip->getAnimationState() != PLAYER_MELEE)
			m_pShip->setAnimationState(PLAYER_RUN);
		m_pShip->setMoving(true);
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			m_pShip->setYMoving(true);
			m_pShip->setCurrentDirection(glm::vec2(m_pShip->getCurrentDirection().x, -1.0f));
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			m_pShip->setYMoving(true);
			m_pShip->setCurrentDirection(glm::vec2(m_pShip->getCurrentDirection().x, 1.0f));
		}
		else
		{
			m_pShip->setYMoving(false);
		}
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pShip->setXMoving(true);
			m_pShip->setCurrentDirection(glm::vec2(-1.0f, m_pShip->getCurrentDirection().y));
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pShip->setXMoving(true);
			m_pShip->setCurrentDirection(glm::vec2(1.0f, m_pShip->getCurrentDirection().y));
		}
		else
		{
			if(m_pShip->getAnimationState() == PLAYER_RUN)
				m_pShip->setAnimationState(PLAYER_IDLE);
			m_pShip->setXMoving(false);
		}

	}

	else
	{
		if (m_pShip->getAnimationState() != PLAYER_SHOOT && m_pShip->getAnimationState() != PLAYER_MELEE)
			m_pShip->setAnimationState(PLAYER_IDLE);
		m_pShip->setMoving(false);
	}

	if (EventManager::Instance().getMouseButton(1))
	{
		if(meleeCoolDown <= 0)
		{
			m_pShip->setAnimationState(PLAYER_MELEE);
			addChild(m_meleeActtack);
			m_meleeActtack->setEnabled(true);
			meleeCoolDown = 30;
		}
	}
	else
	{
		m_meleeActtack->setEnabled(false);
		m_pShip->setAnimationState(PLAYER_IDLE);
	}
	if(cooldown <= 0 && m_pShip->getMoving() == false && m_pShip->getAnimationState() != PLAYER_MELEE)
	{
		m_pShip->setAnimationState(PLAYER_IDLE);
	}
	if (EventManager::Instance().getMouseButton(2))
	{
		if (cooldown <= -20)
		{
			m_pShip->setAnimationState(PLAYER_SHOOT);
			m_pPlayerBullets.push_back(new Bullet(m_pShip->getTransform()->position.x + m_pShip->getWidth() / 2, m_pShip->getTransform()->position.y + m_pShip->getHeight() / 2, m_pShip->getCurrentHeading()));
			m_pPlayerBullets[m_pPlayerBullets.size() - 1]->setRotation(m_pShip->getCurrentHeading());
			SoundManager::Instance().playSound("Fire", 0, -1);
			cooldown = 20;
		}
		
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	TextureManager::Instance()->load("../Assets/textures/BackgroundFramework_1.png", "Background");
	const SDL_Color colour = { 0, 255, 0, 255 };
	m_UIScore = new Label("--", "Consolas", 20, colour, glm::vec2(625.0f, 15.0f));
	m_UIScore->setParent(this);
	addChild(m_UIScore);





	instructions = new Label("--", "Consolas", 15, colour, glm::vec2(550.0f, 585.0f));
	instructions->setParent(this);
	addChild(instructions);

	std::stringstream stream;

	stream << "(P - Enemy patrol)" << " (H - Debug view)"<< " (W,A,S,D - Moves player)";
	const std::string Score_string = stream.str();
	instructions->setText(Score_string);


	// add the ship to the scene as a start point
	m_pShip = new Ship();
	m_pShip->getTransform()->position = glm::vec2(50.0f, 550.0f);
	addChild(m_pShip, 2);


	// add the Obstacle to the scene as a start point
	m_pObstacle[0] = new Obstacle(268, 241, 79.0f, 79.0f); //top left obstacle
	addChild(m_pObstacle[0]);

	// add the Obstacle to the scene as a start point
	m_pObstacle[1] = new Obstacle(134, 47, 0, 441);
	addChild(m_pObstacle[1]);

	// add the Obstacle to the scene as a start point
	m_pObstacle[2] = new Obstacle(61, 160, 229, 440);
	addChild(m_pObstacle[2]);

	m_pObstacle[3] = new Obstacle(192, 178, 536, 292);
	addChild(m_pObstacle[3]);

	m_pObstacle[4] = new Obstacle(249, 59, 503, 52);
	addChild(m_pObstacle[4]);
	
	// added the target to the scene a goal

	m_pNode.push_back(new Node(40, 20)); //Top Nodes
	m_pNode.push_back(new Node(110, 20));
	m_pNode.push_back(new Node(170, 20));
	m_pNode.push_back(new Node(230, 20));
	m_pNode.push_back(new Node(290, 20));
	m_pNode.push_back(new Node(365, 20));
	m_pNode.push_back(new Node(365, 100)); //Right Nodes
	m_pNode.push_back(new Node(365, 160));
	m_pNode.push_back(new Node(365, 220));
	m_pNode.push_back(new Node(365, 280));
	m_pNode.push_back(new Node(365, 360));
	m_pNode.push_back(new Node(290, 360)); //Bottom Nodes
	m_pNode.push_back(new Node(230, 360));
	m_pNode.push_back(new Node(170, 360));
	m_pNode.push_back(new Node(110, 360));
	m_pNode.push_back(new Node(40, 340));
	m_pNode.push_back(new Node(40, 280)); //Left Nodes
	m_pNode.push_back(new Node(40, 220));
	m_pNode.push_back(new Node(40, 160));
	m_pNode.push_back(new Node(40, 100));

	m_pNode.push_back(new Node(143, 414));
	m_pNode.push_back(new Node(143, 454));
	m_pNode.push_back(new Node(143, 494));
	m_pNode.push_back(new Node(103, 414));
	m_pNode.push_back(new Node(63, 414));
	m_pNode.push_back(new Node(23, 414));
	m_pNode.push_back(new Node(103, 494));
	m_pNode.push_back(new Node(63, 494));
	m_pNode.push_back(new Node(23, 494));

	m_pNode.push_back(new Node(200, 410));
	m_pNode.push_back(new Node(250, 410));
	m_pNode.push_back(new Node(300, 410));
	m_pNode.push_back(new Node(200, 450));
	m_pNode.push_back(new Node(200, 490));
	m_pNode.push_back(new Node(200, 530));
	m_pNode.push_back(new Node(200, 570));
	m_pNode.push_back(new Node(300, 450));
	m_pNode.push_back(new Node(300, 490));
	m_pNode.push_back(new Node(300, 530));
	m_pNode.push_back(new Node(300, 570));

	m_pNode.push_back(new Node(500, 500));
	m_pNode.push_back(new Node(560, 500));
	m_pNode.push_back(new Node(640, 500));
	m_pNode.push_back(new Node(700, 500));
	m_pNode.push_back(new Node(750, 500));
	m_pNode.push_back(new Node(750, 440));
	m_pNode.push_back(new Node(750, 380));
	m_pNode.push_back(new Node(750, 320));
	m_pNode.push_back(new Node(750, 260));
	m_pNode.push_back(new Node(700, 260));
	m_pNode.push_back(new Node(640, 260));
	m_pNode.push_back(new Node(560, 260));
	m_pNode.push_back(new Node(500, 260));
	m_pNode.push_back(new Node(500, 440));
	m_pNode.push_back(new Node(500, 380));
	m_pNode.push_back(new Node(500, 320));

	m_pNode.push_back(new Node(480, 20));
	m_pNode.push_back(new Node(540, 20));
	m_pNode.push_back(new Node(600, 20));
	m_pNode.push_back(new Node(660, 20));
	m_pNode.push_back(new Node(720, 20));
	m_pNode.push_back(new Node(760, 20));
	m_pNode.push_back(new Node(760, 120));
	m_pNode.push_back(new Node(760, 70));
	m_pNode.push_back(new Node(760, 120));
	m_pNode.push_back(new Node(480, 120));
	m_pNode.push_back(new Node(540, 120));
	m_pNode.push_back(new Node(600, 120));
	m_pNode.push_back(new Node(660, 120));
	m_pNode.push_back(new Node(720, 120));
	m_pNode.push_back(new Node(480, 70));




	for (auto node : m_pNode)
		addChild(node);

	m_pEnemy.push_back(new REnemy());
	//m_pEnemy.push_back(new CCEnemy());
	m_pEnemy[0]->getTransform()->position = glm::vec2(10.0f, 15.0f);
	m_pEnemy[0]->setTargetPosition(m_pNode[0]->getTransform()->position);
	addChild(m_pEnemy[0]);

	//m_pEnemy[1]->getTransform()->position = glm::vec2(100.0f, 15.0f);
	//m_pEnemy[1]->setTargetPosition(m_pNode[5]->getTransform()->position);
	//addChild(m_pEnemy[1]);
	// Create Decision Tree
	decisionTree = new DecisionTree();

	decisionTree->setAgent(m_pEnemy[0]);


	decisionTree->Display();


	m_meleeActtack = new MeleeAttack(m_pShip->getCurrentHeading());


	std::cout << "------------------------" << std::endl;
	std::cout << decisionTree->MakeDecision() << std::endl;
	std::cout << "------------------------\n" << std::endl;

	SoundManager::Instance().load("../Assets/audio/bgmusic.mp3", "BGMusic", SOUND_MUSIC);
	SoundManager::Instance().load("../Assets/audio/death.wav", "Death", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/fire.wav", "Fire", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/pwalk.wav", "PWalk", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/ewalk.wav", "EWalk", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/hitsound.wav", "Hit", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/meleehit.wav", "Melee", SOUND_SFX);

	SoundManager::Instance().allocateChannels(16);

	SoundManager::Instance().playMusic("BGMusic", -1, 0);
	SoundManager::Instance().setMusicVolume(10);
	SoundManager::Instance().setSoundVolume(10);
}

void PlayScene::CollisionsUpdate()
{
	for (auto& obj : m_pObstacle)
	{
		if (CollisionManager::AABBCheck(m_pShip, obj))
		{
			//std::cout << m_pShip->getTransform()->position.x - m_playerSpeed << std::endl;
			if (int(m_pShip->getTransform()->position.x + m_pShip->getWidth() - m_pShip->getRigidBody()->velocity.x) <= (obj->getTransform()->position.x))
			{
				m_pShip->getTransform()->position.x -= m_playerSpeed * 2;
			}
			else if (int(m_pShip->getTransform()->position.x - m_pShip->getRigidBody()->velocity.x) >= (obj->getTransform()->position.x + obj->getWidth()))
			{
				m_pShip->getTransform()->position.x += m_playerSpeed * 2;
			}
			else if ((m_pShip->getTransform()->position.y + m_pShip->getHeight() - m_playerSpeed) <= (obj->getTransform()->position.y))
			{
				m_pShip->getTransform()->position.y -= m_playerSpeed * 2;
			}
			else if ((m_pShip->getTransform()->position.y + m_playerSpeed) >= (obj->getTransform()->position.y + obj->getHeight()))
			{
				m_pShip->getTransform()->position.y += m_playerSpeed * 2;
			}
		}
	}

	for (auto& obj : m_pObstacle)
	{
		for (int i = 0; i < m_pEnemy.size(); i++)
		{
			if (CollisionManager::AABBCheck(m_pEnemy[i], obj))
			{
				//std::cout << m_pShip->getTransform()->position.x - m_playerSpeed << std::endl;
				if (int(m_pEnemy[i]->getTransform()->position.x + m_pEnemy[i]->getWidth() - m_pEnemy[i]->getRigidBody()->velocity.x) <= (obj->getTransform()->position.x))
				{
					m_pEnemy[i]->getTransform()->position.x -= m_playerSpeed * 2;
				}
				else if (int(m_pEnemy[i]->getTransform()->position.x - m_pEnemy[i]->getRigidBody()->velocity.x) >= (obj->getTransform()->position.x + obj->getWidth()))
				{
					m_pEnemy[i]->getTransform()->position.x += m_playerSpeed * 2;
				}
				else if ((m_pEnemy[i]->getTransform()->position.y + m_pEnemy[i]->getHeight() - m_playerSpeed) <= (obj->getTransform()->position.y))
				{
					m_pEnemy[i]->getTransform()->position.y -= m_playerSpeed * 2;
				}
				else if ((m_pEnemy[i]->getTransform()->position.y + m_playerSpeed) >= (obj->getTransform()->position.y + obj->getHeight()))
				{
					m_pEnemy[i]->getTransform()->position.y += m_playerSpeed * 2;
				}
			}
		}
		
	}
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i]->getTargetDistance() < 50)
			m_pEnemy[i]->setMaxSpeed(1.0f);

		else m_pEnemy[i]->setMaxSpeed(3.0f);
	}


	for (int i = 0; i < m_pPlayerBullets.size(); i++)
	{
		if (m_pPlayerBullets[i] != nullptr)
		{
			if (m_pPlayerBullets[i]->getTransform()->position.x >= 900)
			{
				removeChild(m_pPlayerBullets[i]);
				m_pPlayerBullets[i] = nullptr;
				m_pPlayerBullets.erase(m_pPlayerBullets.begin() + i);
				m_pPlayerBullets.shrink_to_fit();
				break;
			}
			if (m_pPlayerBullets[i]->getTransform()->position.x <= -100)
			{
				removeChild(m_pPlayerBullets[i]);
				m_pPlayerBullets[i] = nullptr;
				m_pPlayerBullets.erase(m_pPlayerBullets.begin() + i);
				m_pPlayerBullets.shrink_to_fit();
				break;
			}
			if (m_pPlayerBullets[i]->getTransform()->position.y <= -100)
			{
				removeChild(m_pPlayerBullets[i]);
				m_pPlayerBullets[i] = nullptr;
				m_pPlayerBullets.erase(m_pPlayerBullets.begin() + i);
				m_pPlayerBullets.shrink_to_fit();
				break;
			}
			if (m_pPlayerBullets[i]->getTransform()->position.y >= 700)
			{
				removeChild(m_pPlayerBullets[i]);
				m_pPlayerBullets[i] = nullptr;
				m_pPlayerBullets.erase(m_pPlayerBullets.begin() + i);
				m_pPlayerBullets.shrink_to_fit();
				break;
			}

			for(int i = 0; i < m_pPlayerBullets.size(); i++)
			{
				for (int j = 0; j < m_pEnemy.size(); j++)
				{
					if (CollisionManager::AABBCheck(m_pPlayerBullets[i], m_pEnemy[j]))
					{
						SoundManager::Instance().playSound("Hit", 0, -1);
						damageCooldown = 60;
						m_pEnemy[j]->setAnimationState(ENEMY_DAMAGE);
						m_pEnemy[j]->setHealth(m_pEnemy[j]->getHealth() - 1);
					}
				}

			}
			for(auto obstacle : m_pObstacle)
			{
				if(CollisionManager::AABBCheck(m_pPlayerBullets[i], obstacle))
				{
					removeChild(m_pPlayerBullets[i]);
					m_pPlayerBullets[i] = nullptr;
					m_pPlayerBullets.erase(m_pPlayerBullets.begin() + i);
					m_pPlayerBullets.shrink_to_fit();
					break;
				}
			}
		}
	}
	if (m_meleeActtack->isEnabled())
	{
		for (int i = 0; i < m_pEnemy.size(); i++)
		{
			if (CollisionManager::AABBCheck(m_meleeActtack, m_pEnemy[i]))
			{
				m_pEnemy[i]->setAnimationState(ENEMY_DAMAGE);
				SoundManager::Instance().playSound("Melee", 0, -1);
				m_pEnemy[i]->setHealth(m_pEnemy[i]->getHealth() - 1);
			}
		}
	}

	for (int i = 0; i < m_pEnemyBullets.size(); i++)
	{
		if (m_pEnemyBullets[i] != nullptr)
		{
			if (m_pEnemyBullets[i]->getTransform()->position.x >= 900)
			{
				removeChild(m_pEnemyBullets[i]);
				m_pEnemyBullets[i] = nullptr;
				m_pEnemyBullets.erase(m_pEnemyBullets.begin() + i);
				m_pEnemyBullets.shrink_to_fit();
				break;
			}
			if (m_pEnemyBullets[i]->getTransform()->position.x <= -100)
			{
				removeChild(m_pEnemyBullets[i]);
				m_pEnemyBullets[i] = nullptr;
				m_pEnemyBullets.erase(m_pEnemyBullets.begin() + i);
				m_pEnemyBullets.shrink_to_fit();
				break;
			}
			if (m_pEnemyBullets[i]->getTransform()->position.y <= -100)
			{
				removeChild(m_pEnemyBullets[i]);
				m_pEnemyBullets[i] = nullptr;
				m_pEnemyBullets.erase(m_pEnemyBullets.begin() + i);
				m_pEnemyBullets.shrink_to_fit();
				break;
			}
			if (m_pEnemyBullets[i]->getTransform()->position.y >= 700)
			{
				removeChild(m_pEnemyBullets[i]);
				m_pEnemyBullets[i] = nullptr;
				m_pEnemyBullets.erase(m_pEnemyBullets.begin() + i);
				m_pEnemyBullets.shrink_to_fit();
				break;
			}

			for (int i = 0; i < m_pEnemyBullets.size(); i++)
			{

				if (CollisionManager::AABBCheck(m_pEnemyBullets[i],m_pShip))
				{
					m_pShip->setAnimationState(ENEMY_DAMAGE);
					m_pShip->setHealth(m_pShip->getHealth() - 1);
				}


			}
			for (auto obstacle : m_pObstacle)
			{
				if (CollisionManager::AABBCheck(m_pEnemyBullets[i], obstacle))
				{
					removeChild(m_pEnemyBullets[i]);
					m_pEnemyBullets[i] = nullptr;
					m_pEnemyBullets.erase(m_pEnemyBullets.begin() + i);
					m_pEnemyBullets.shrink_to_fit();
					break;
				}
			}
		}
	}
}

void PlayScene::m_DecisionMaking(Enemy* m_agent)
{
	if (m_agent == nullptr)
	{
		return;
	}
	else if (decisionTree->getCurrentNode()->name == "Patrol Action")
	{
		m_agent->move();
	}
	else if (decisionTree->getCurrentNode()->name == "Move To Player Action")
	{
		m_agent->move();
		m_agent->setTargetPosition(m_pShip->getTransform()->position);
	}
	else if (decisionTree->getCurrentNode()->name == "Ranged Attack Action")
	{
		if (EnemyFireCoolDown <= -20)
		{
			m_pEnemyBullets.push_back(new Bullet(m_agent->getTransform()->position.x + m_agent->getWidth() / 2, m_agent->getTransform()->position.y + m_agent->getHeight() / 2, m_agent->getCurrentHeading()));
			m_pEnemyBullets[m_pEnemyBullets.size() - 1]->setRotation(m_agent->getCurrentHeading());
			std::cout << "YESSSSSS" << std::endl;
			EnemyFireCoolDown = 20;
		}
	}
	else if (decisionTree->getCurrentNode()->name == "Move to LOS Action")
	{
		m_agent->rotate();
		m_agent->setTargetPosition(m_pShip->getTransform()->position);
	}
	else if (decisionTree->getCurrentNode()->name == "Flee Action")
	{
		m_agent->flee();
		m_agent->setTargetPosition(m_pShip->getTransform()->position);
	}
}

void PlayScene::m_CheckEnemyBehindCover(Enemy* enemy)
{
}

void PlayScene::GUI_Function()
{
	//TODO: We need to deal with this
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);
	
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("GAME3001 - Lab 7", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	ImGui::Separator();
	
	if (ImGui::Button("Start"))
	{
		m_pShip->setDebug(!m_pShip->getDebugState());
		for (auto node : m_pNode)
			node->setDebug(!node->getDebugState());
		for (int i = 0; i < m_pEnemy.size(); i++)
		{
			m_pEnemy[i]->setDebug(!m_pEnemy[i]->getDebugState());
		}

		for (auto obstacle : m_pObstacle)
		{
			obstacle->setDebug(!obstacle->getDebug());
		}
	}

	ImGui::SameLine();
	
	if (ImGui::Button("Reset"))
	{
		m_pShip->getTransform()->position = glm::vec2(50.0f, 550.0f);

		if (m_pEnemy.size() == 0)
		{
			m_pEnemy.push_back(new REnemy());
			m_pEnemy[0]->getTransform()->position = glm::vec2(10.0f, 15.0f);
			m_pEnemy[0]->setTargetPosition(m_pNode[0]->getTransform()->position);
			addChild(m_pEnemy[0]);
			decisionTree->setAgent(m_pEnemy[0]);
		}
		else
		{
			m_pEnemy[0]->getTransform()->position = glm::vec2(10.0f, 15.0f);
			m_pEnemy[0]->setHealth(3);
		}
		
	}

	ImGui::Separator();

	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

void PlayScene::m_setUIScore()
{
	std::stringstream stream;

	stream << "Enemys alive:" << m_pEnemy.size() << " Enemeys killed:" << m_enemysKilled;
	const std::string Score_string = stream.str();
	m_UIScore->setText(Score_string);
}

void PlayScene::m_CheckShipLOS(DisplayObject* target_object)
{
	bool collidingObstacle;
	// if ship to target distance is less than or equal to LOS Distance
	auto ShipToTargetDistance = Util::distance(m_pShip->getTransform()->position, target_object->getTransform()->position);
	if (ShipToTargetDistance <= m_pShip->getLOSDistance())
	{
		std::vector<DisplayObject*> contactList;
		for (auto object : getDisplayList())
		{
			if (object->getType() == NODE || object->getType() == NONE || object->getType() == BULLET)
			{
				continue;
			}
			// check if object is farther than than the target
			auto ShipToObjectDistance = Util::distance(m_pShip->getTransform()->position, object->getTransform()->position);
			bool collidingObstacle = (CollisionManager::lineRectCheck(glm::vec2(m_pShip->getTransform()->position.x + getWidth() / 2, m_pShip->getTransform()->position.y + getHeight() / 2),
				(glm::vec2(m_pShip->getTransform()->position.x + getWidth() / 2, m_pShip->getTransform()->position.y + getHeight() / 2) + m_pShip->getCurrentDirection() * m_pShip->getLOSDistance()),
				object->getTransform()->position, object->getWidth(), object->getHeight()));
			
			if (ShipToObjectDistance <= ShipToTargetDistance && collidingObstacle)
			{
				if ((object->getType() != m_pShip->getType()) && (object->getType() != target_object->getType()))
				{
					contactList.push_back(object);
				}
			}
		}
		contactList.push_back(target_object); // add the target to the end of the list
		auto hasLOS = CollisionManager::LOSCheck(m_pShip->getTransform()->position,
			m_pShip->getTransform()->position + m_pShip->getCurrentDirection() * m_pShip->getLOSDistance(), contactList, target_object);

		m_pShip->setHasLOS(hasLOS);
	}
}

void PlayScene::m_CheckShipDetection(DisplayObject* target_object)
{
	// if ship to target distance is less than or equal to detection Distance
	auto ShipToTargetDistance = Util::distance(m_pShip->getTransform()->position, target_object->getTransform()->position);
	if (ShipToTargetDistance <= m_pShip->getDetectionDistance())
	{
		std::vector<DisplayObject*> contactList;
		for (auto object : getDisplayList())
		{
			// check if object is farther than than the target
			auto ShipToObjectDistance = Util::distance(m_pShip->getTransform()->position, object->getTransform()->position);

			if (ShipToObjectDistance <= ShipToTargetDistance)
			{
				if ((object->getType() != m_pShip->getType()) && (object->getType() != target_object->getType()))
				{
					contactList.push_back(object);
				}
			}
		}
		contactList.push_back(target_object); // add the target to the end of the list
		auto hasDetection = CollisionManager::detectionCheck(m_pShip->getTransform()->position, m_pShip->getDetectionDistance(), contactList, target_object);

		m_pShip->setHasDetection(hasDetection);
	}
}

void PlayScene::m_CheckEnemyDetection(Enemy* enemy)
{
	// if ship to target distance is less than or equal to detection Distance
	auto ShipToTargetDistance = Util::distance(enemy->getTransform()->position, m_pShip->getTransform()->position);
	if (ShipToTargetDistance <= enemy->getDetectionDistance())
	{
		enemy->setHasDetection(true);
	}
	else
	{
		enemy->setHasDetection(false);
	}
}

void PlayScene::m_CheckEnemyLOS(Enemy* enemy)
{
	bool collidingObstacle;
	// if ship to target distance is less than or equal to LOS Distance
	auto ShipToTargetDistance = Util::distance(enemy->getTransform()->position, m_pShip->getTransform()->position);
	if (ShipToTargetDistance <= enemy->getLOSDistance())
	{
		std::vector<DisplayObject*> contactList;
		for (auto object : getDisplayList())
		{
			if (object->getType() == NODE || object->getType() == NONE || object->getType() == BULLET)
			{
				continue;
			}
			collidingObstacle = (CollisionManager::lineRectCheck(glm::vec2(enemy->getTransform()->position.x + getWidth() / 2, enemy->getTransform()->position.y + getHeight() / 2),
				(glm::vec2(enemy->getTransform()->position.x + getWidth() / 2, enemy->getTransform()->position.y + getHeight() / 2) + enemy->getCurrentDirection() * enemy->getLOSDistance()),
				object->getTransform()->position, object->getWidth(), object->getHeight()));
			// check if object is farther than than the target
			auto ShipToObjectDistance = Util::distance(enemy->getTransform()->position, object->getTransform()->position);

			if (ShipToObjectDistance <= ShipToTargetDistance && collidingObstacle)
			{
				if ((object->getType() != enemy->getType()) && (object->getType() != m_pShip->getType()))
				{
					contactList.push_back(object);
				}
			}
		}
		contactList.push_back(m_pShip); // add the target to the end of the list
		auto hasLOS = CollisionManager::LOSCheck(enemy->getTransform()->position,
			enemy->getTransform()->position + enemy->getCurrentDirection() * enemy->getLOSDistance(), contactList, m_pShip);

		enemy->setHasLOS(hasLOS);
	}
}

void PlayScene::m_setDebugMode(bool state)
{
	m_isGridEnabled = state;
}

bool PlayScene::m_getDebugMode() const
{
	return m_isGridEnabled;
}

void PlayScene::m_setPatrolMode(bool state)
{
	m_isPatrolling = state;
}

bool PlayScene::m_getPatrolMode() const
{
	return m_isPatrolling;
}

void PlayScene::m_CheckEnemyFireDetection(Enemy* enemy)
{
	auto ShipToTargetDistance = Util::distance(enemy->getTransform()->position, m_pShip->getTransform()->position);
	if (ShipToTargetDistance <= enemy->getFireDistance())
	{
		enemy->setIsInFireDetection(true);
		enemy->setRangedAttackState(true);
	}
	else
	{
		enemy->setIsInFireDetection(false);
		enemy->setRangedAttackState(false);
	}
}
