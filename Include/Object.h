#ifndef OBJECT_H
#define OBJECT_H

#include "std.h"
#include "Mesh.h"
#include <d3dx9.h>

SE_BEGIN_NAMESPACE

class Object {
public:
	Object();
	//TODO: init should go in protected for so you can only initialize when inheriting
	void Init(const std::string &filename);
	void Update(LPDIRECT3DDEVICE9 device);
	void Render();
	void ChangePosition(float x, float y, float z);
protected:
	std::string m_filename;
	float m_posX;
	float m_posY;
	float m_posZ;
	Mesh *m_mesh;
};

SE_END_NAMESPACE

#endif