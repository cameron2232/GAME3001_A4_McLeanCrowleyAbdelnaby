#pragma once
#ifndef __ATTACK_ACTION__
#define __ATTACK_ACTION__
#include "ActionNode.h"

class RangeAttackAction : public ActionNode
{
public:
	RangeAttackAction();
	virtual ~RangeAttackAction();

	virtual void Action(Agent* m_agent) override;
};

#endif
