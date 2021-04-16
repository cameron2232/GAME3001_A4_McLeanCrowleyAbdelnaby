#include "WaitBehindCoverAction.h"
#include <iostream>

WaitBehindCoverAction::WaitBehindCoverAction()
{
	name = "Wait Behind Cover Action";
}

WaitBehindCoverAction::~WaitBehindCoverAction()
= default;

void WaitBehindCoverAction::Action(Agent* m_agent)
{
	std::cout << "Performing Wait Behind Cover Action" << std::endl;
}
