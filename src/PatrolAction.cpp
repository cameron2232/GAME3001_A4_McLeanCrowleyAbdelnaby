#include "PatrolAction.h"
#include <iostream>

PatrolAction::PatrolAction()
{
	name = "Patrol Action";
}

PatrolAction::~PatrolAction() = default;

void PatrolAction::Action(Agent* m_agent)
{
	//std::cout << "Performing Patrol Action" << std::endl;
	m_agent->move();
}