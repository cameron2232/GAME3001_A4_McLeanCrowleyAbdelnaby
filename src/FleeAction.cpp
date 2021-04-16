#include "FleeAction.h"
#include <iostream>

FleeAction::FleeAction()
{
	name = "Flee Action";
}

FleeAction::~FleeAction() = default;

void FleeAction::Action(Agent * m_agent)
{
	std::cout << "Performing Flee Action" << std::endl;
	m_agent->flee();
}