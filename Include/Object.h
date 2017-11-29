#ifndef OBJECT_H
#define OBJECT_H

#include "std.h"
#include "Mesh.h"

SE_BEGIN_NAMESPACE

class Object {
public:
	Object();
	void ChangePosition(float x, float y, float z);
protected:
	float m_posX;
	float m_posY;
	float m_posZ;
	Mesh m_mesh;
};

SE_END_NAMESPACE

#endif