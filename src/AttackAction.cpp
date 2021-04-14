#include "AttackAction.h"
#include <iostream>

AttackAction::AttackAction()
{
	name = "Attack Action";
}

AttackAction::~AttackAction() = default;

void AttackAction::Action(Agent* m_agent)
{
	std::cout << "Performing Attack Action" << std::endl;
}
