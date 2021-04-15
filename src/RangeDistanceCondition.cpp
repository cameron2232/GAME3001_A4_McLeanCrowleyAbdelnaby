#include "RangeDistanceCondition.h"

RangeDistanceCondition::RangeDistanceCondition(bool range)
{
	setRangeDistance(range);
	name = "Range Distance Condition";
}

RangeDistanceCondition::~RangeDistanceCondition() = default;

void RangeDistanceCondition::setRangeDistance(bool state)
{
	data = m_inRange = state;
}

bool RangeDistanceCondition::Condition()
{
	return m_inRange;
}
