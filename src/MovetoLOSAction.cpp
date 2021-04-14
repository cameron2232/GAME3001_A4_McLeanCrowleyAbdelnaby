#include "MoveToLOSAction.h"
#include <iostream>

MoveToLOSAction::MoveToLOSAction()
{
	name = "Move to LOS Action";
}

MoveToLOSAction::~MoveToLOSAction() = default;

void MoveToLOSAction::Action(Agent* m_agent)
{
	std::cout << "Performing Move To LOS Action" << std::endl;
}
