#include "MoveBehindCoverAction.h"

#include <iostream>

MoveBehindCoverAction::MoveBehindCoverAction()
{
	name = "Move Behind Cover Action";
}

void MoveBehindCoverAction::Action(Agent* m_agent)
{
	std::cout << "Performing Move Behind Cover Action" << std::endl;
}
