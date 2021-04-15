#include "RangeAttackAction.h"
#include <iostream>

RangedAttackAction::RangedAttackAction()
{
	name = "Ranged Attack Action";
}

RangedAttackAction::~RangedAttackAction() = default;

void RangedAttackAction::Action(Agent * m_agent)
{
	std::cout << "Performing Ranged Attack Action" << std::endl;
}
