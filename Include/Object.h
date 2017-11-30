#ifndef OBJECT_H
#define OBJECT_H

#include "std.h"
#include "Mesh.h"
#include <d3dx9.h>

SE_BEGIN_NAMESPACE

class Object {
public:
	Object(LPDIRECT3DDEVICE9 device, const std::string &meshLocation);
	void Update();
	void Render();
	void ChangePosition(float x, float y, float z);
protected:
	LPDIRECT3DDEVICE9 m_device;
	float m_posX;
	float m_posY;
	float m_posZ;
	Mesh m_mesh;
};

SE_END_NAMESPACE

#endif