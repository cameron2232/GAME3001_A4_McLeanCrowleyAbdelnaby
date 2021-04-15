#pragma once
#ifndef __ATTACK_RANGE_CONDITION__
#define __ATTACK_RANGE_CONDITION__
#include "ConditionNode.h"

class AttackRangeCondition : public ConditionNode
{
public:
	AttackRangeCondition(bool AttackRange = false);
	virtual ~AttackRangeCondition();

	void setAttackRange(bool state);

	virtual bool Condition() override;
private:
	bool m_hasAttackRange;
};


#endif
