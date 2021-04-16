#pragma once
#ifndef __RANGE_DISTANCE_CONDITION__
#define __RANGE_DISTANCE_CONDITION__
#include "ConditionNode.h"

class TooCloseCondition : public ConditionNode
{
public:
	TooCloseCondition(bool range = false);
	virtual ~TooCloseCondition();

	void setRangeDistance(bool state);

	virtual bool Condition() override;
private:
	bool m_inRange;
};


#endif#pragma once
