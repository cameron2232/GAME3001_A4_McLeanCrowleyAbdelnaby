#pragma once
#ifndef __WAIT_BEHIND_COVER_ACTION__
#define __WAIT_BEHIND_COVER_ACTION__
#include "ActionNode.h"


class WaitBehindCoverAction : public ActionNode
{
public:
	WaitBehindCoverAction();
	virtual ~WaitBehindCoverAction();

	virtual void Action(Agent* m_agent) override;
};

#endif