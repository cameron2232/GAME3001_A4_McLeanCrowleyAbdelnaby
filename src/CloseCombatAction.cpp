#include "CloseCombatAction.h"

#include <iostream>

CloseCombatAction::CloseCombatAction()
{
	name = "Close Combat Action";
}

CloseCombatAction::~CloseCombatAction() = default;

void CloseCombatAction::Action(Agent* m_agent)
{
	std::cout << "Performing Close Combat Action" << std::endl;
}
