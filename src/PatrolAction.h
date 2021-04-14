#pragma once
#ifndef __PATROL_ACTION__
#define __PATROL_ACTION__
#include "ActionNode.h"


class PatrolAction : public ActionNode
{
public:
	PatrolAction();
	virtual ~PatrolAction();

	

	virtual void Action(Agent* m_agent) override;
};

#endif 
