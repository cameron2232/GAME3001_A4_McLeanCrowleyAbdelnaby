#pragma once
#ifndef __HEALTH_CONDITION__
#define __HEALTH_CONDITION__
#include "ConditionNode.h"

class HealthCondition : public ConditionNode
{
public:
	HealthCondition(bool Health = false);
	virtual ~HealthCondition();

	void setHealthCondition(bool state);

	virtual bool Condition() override;
private:
	bool m_Health;
};


#endif
