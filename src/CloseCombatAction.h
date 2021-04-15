#pragma once
#ifndef __CLOSE_COMBAT_ACTION__
#define __CLOSE_COMBAT_ACTION__
#include "ActionNode.h"

class CloseCombatAction : public ActionNode
{
public:
	CloseCombatAction();
	virtual ~CloseCombatAction();

	virtual void Action(Agent* m_agent) override;
};

#endif
