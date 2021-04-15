#include "AttackRangeCondition.h"

AttackRangeCondition::AttackRangeCondition(bool AttackRange)
{
	setAttackRange(AttackRange);
	name = "Attack Range Condition";
}

AttackRangeCondition::~AttackRangeCondition() = default;

void AttackRangeCondition::setAttackRange(bool state)
{
	data = m_hasAttackRange = state;
}

bool AttackRangeCondition::Condition()
{
	return m_hasAttackRange;
}
