#pragma once
#ifndef __MOVE_BEHIND_COVER_ACTION__
#define __MOVE_BEHIND_COVER_ACTION__
#include "ActionNode.h"


class MoveBehindCoverAction : public ActionNode
{
public:
	MoveBehindCoverAction();
	virtual ~MoveBehindCoverAction();

	virtual void Action(Agent* m_agent) override;
};

#endif
