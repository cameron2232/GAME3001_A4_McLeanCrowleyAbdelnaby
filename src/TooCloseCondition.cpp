#include "TooCloseCondition.h"

TooCloseCondition::TooCloseCondition(bool range)
{
	setRangeDistance(range);
	name = "Range Distance Condition";
}

TooCloseCondition::~TooCloseCondition() = default;

void TooCloseCondition::setRangeDistance(bool state)
{
	data = m_inRange = state;
}

bool TooCloseCondition::Condition()
{
	return m_inRange;
}
