#pragma once
#ifndef __BEHIND_COVER_CONDITION__
#define __BEHIND_COVER_CONDITION__
#include "ConditionNode.h"

class BehindCoverCondition : public ConditionNode
{
public:
	BehindCoverCondition(bool behindCover = false);
	virtual ~BehindCoverCondition();

	void setBehindCover(bool state);

	virtual bool Condition() override;
private:
	bool m_behindCover;
};


#endif
