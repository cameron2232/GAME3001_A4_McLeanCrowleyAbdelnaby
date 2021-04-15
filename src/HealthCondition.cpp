#include "HealthCondition.h"

HealthCondition::HealthCondition(bool Health)
{
	setHealthCondition(Health);
	name = "Health Condition";
}

HealthCondition::~HealthCondition() = default;

void HealthCondition::setHealthCondition(bool state)
{
	data = m_Health = state;
}

bool HealthCondition::Condition()
{
	return m_Health;
}
