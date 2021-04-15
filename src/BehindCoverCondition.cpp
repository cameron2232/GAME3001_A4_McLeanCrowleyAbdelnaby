#include "BehindCoverCondition.h"

BehindCoverCondition::BehindCoverCondition(bool behindCover)
{
	setBehindCover(behindCover);
	name = "Behind Cover Condition";
}

BehindCoverCondition::~BehindCoverCondition() = default;

void BehindCoverCondition::setBehindCover(bool state)
{
	data = m_behindCover = state;
}

bool BehindCoverCondition::Condition()
{
	return m_behindCover;
}
