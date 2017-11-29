#include "Object.h"

SE_BEGIN_NAMESPACE

Object::Object() {
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;
}

void Object::ChangePosition(float x, float y, float z) {
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}

SE_END_NAMESPACE