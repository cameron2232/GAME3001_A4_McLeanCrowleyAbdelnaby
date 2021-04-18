#include "RangeAttackAction.h"
#include <iostream>

RangeAttackAction::RangeAttackAction()
{
	name = "Ranged Attack Action";
}

RangeAttackAction::~RangeAttackAction()
= default;


void RangeAttackAction::Action(Agent * m_agent)
{
	std::cout << "Performing Attack Action" << std::endl;
	m_agent->rotate();
}
