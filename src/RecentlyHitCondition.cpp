#include "RecentlyHitCondition.h"

RecentlyHitCondition::RecentlyHitCondition(bool Hit)
{
	setRecentlyHit(Hit);
}

RecentlyHitCondition::~RecentlyHitCondition() = default;

void RecentlyHitCondition::setRecentlyHit(bool state)
{
	data = m_recentlyHit = state;
}

bool RecentlyHitCondition::Condition()
{
	return m_recentlyHit;
}
