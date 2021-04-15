#pragma once
#ifndef __RECENTLY_HIT_CONDITION__
#define __RECENTLY_HIT_CONDITION__
#include "ConditionNode.h"

class RecentlyHitCondition : public ConditionNode
{
public:
	RecentlyHitCondition(bool Hit = false);
	virtual ~RecentlyHitCondition();

	void setRecentlyHit(bool state);

	virtual bool Condition() override;
private:
	bool m_recentlyHit;
};


#endif

