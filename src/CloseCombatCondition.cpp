#include "CloseCombatCondition.h"

CloseCombatCondition::CloseCombatCondition(bool within_combat_range)
{
	setIsWithinCombatRange(within_combat_range);
	name = "Close Combat Range Condition";
}

CloseCombatCondition::~CloseCombatCondition() = default;

void CloseCombatCondition::setIsWithinCombatRange(bool state)
{
	data = m_isWithinCombatRange = state;
}

bool CloseCombatCondition::Condition()
{
	return m_isWithinCombatRange;
}
