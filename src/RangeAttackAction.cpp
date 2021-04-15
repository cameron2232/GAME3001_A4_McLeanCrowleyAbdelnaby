#include "RangeAttackAction.h"
#include <iostream>

RangeAttackAction::RangeAttackAction()
{
	name = "Attack Action";
}

RangedAttackAction::~RangedAttackAction()
= default;


void RangedAttackAction::Action(Agent * m_agent)
{
	std::cout << "Performing Attack Action" << std::endl;
}
