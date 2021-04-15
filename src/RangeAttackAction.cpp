#include "RangeAttackAction.h"
#include <iostream>

RangeAttackAction::RangeAttackAction()
{
	name = "Attack Action";
}

RangeAttackAction::~RangeAttackAction() = default;

void RangeAttackAction::Action(Agent* m_agent)
{
	std::cout << "Performing Attack Action" << std::endl;
}
