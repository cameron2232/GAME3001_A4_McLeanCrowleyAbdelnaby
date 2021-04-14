#include "MoveToPlayerAction.h"
#include <iostream>

MoveToPlayerAction::MoveToPlayerAction()
{
	name = "Move To Player Action";
}

MoveToPlayerAction::~MoveToPlayerAction() = default;

void MoveToPlayerAction::Action(Agent* m_agent)
{
	std::cout << "Performing Move To Player Action" << std::endl;
}
