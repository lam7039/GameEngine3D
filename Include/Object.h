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
	void Update(float delta);
	void Render(LPDIRECT3DDEVICE9 device);
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
protected:
	D3DXMATRIX m_matRotate;
	D3DXMATRIX m_matTranslate;
	std::string m_filename;
	float m_posX;
	float m_posY;
	float m_posZ;
	float m_rotX;
	float m_rotY;
	float m_rotZ;
	Mesh *m_mesh;
};

SE_END_NAMESPACE

#endif