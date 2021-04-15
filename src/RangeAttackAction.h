#pragma once
#ifndef __RANGED_ATTACK_ACTION__
#define __RANGED_ATTACK_ACTION__
#include "ActionNode.h"

class RangedAttackAction : public ActionNode
{
public:
	RangedAttackAction();
	virtual ~RangedAttackAction();

	virtual void Action(Agent* m_agent) override;
};

#endif