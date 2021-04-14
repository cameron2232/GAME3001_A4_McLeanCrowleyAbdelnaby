#pragma once
#ifndef __ATTACK_ACTION__
#define __ATTACK_ACTION__
#include "ActionNode.h"

class AttackAction : public ActionNode
{
public:
	AttackAction();
	virtual ~AttackAction();

	virtual void Action(Agent* m_agent) override;
};

#endif
