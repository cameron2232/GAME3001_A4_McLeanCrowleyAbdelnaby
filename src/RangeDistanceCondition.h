#pragma once
#ifndef __RANGE_DISTANCE_CONDITION__
#define __RANGE_DISTANCE_CONDITION__
#include "ConditionNode.h"

class RangeDistanceCondition : public ConditionNode
{
public:
	RangeDistanceCondition(bool range = false);
	virtual ~RangeDistanceCondition();

	void setRangeDistance(bool state);

	virtual bool Condition() override;
private:
	bool m_inRange;
};


#endif#pragma once
