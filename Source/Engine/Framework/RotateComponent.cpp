#include "RotateComponent.h"

bool nc::RotateComponent::Initialize()
{
	return false;
}

void nc::RotateComponent::Update(float dt)
{
	//m_owner->transform.euler += euler * dt;

	//glm::quat rotation = EulerToQuaternion(euler * dt);
	//m_owner->transform.rotation = m_owner->transform.rotation * rotation;
}

void nc::RotateComponent::ProcessGui()
{
}
