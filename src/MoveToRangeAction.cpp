#include "MoveToRangeAction.h"

#include <iostream>

MoveToRangeAction::MoveToRangeAction()
{
	name = "Move To Range Action";
}

void MoveToRangeAction::Action(Agent* m_agent)
{
	std::cout << "Performing Move To Range Action" << std::endl;
}
