#include "MoveBehindCoverAction.h"

#include <iostream>

MoveBehindCoverAction::MoveBehindCoverAction()
{
	name = "Move Behind Cover Action";
}

MoveBehindCoverAction::~MoveBehindCoverAction()
= default;

void MoveBehindCoverAction::Action(Agent* m_agent)
{
	std::cout << "Performing Move Behind Cover Action" << std::endl;
	m_agent->move();
}
