#ifndef DIRECT3D_H
#define DIRECT3D_H

#include "std.h"
#include "Object.h"
#include <d3dx9.h>

SE_BEGIN_NAMESPACE

class Direct3D {
public:
	Direct3D(HWND hWnd);
	~Direct3D();
	void Update(float delta);
	void Render();
private:
	LPDIRECT3D9 m_d3d;
	LPDIRECT3DDEVICE9 m_device;
	D3DXMATRIX m_matRotate;
	D3DXMATRIX m_matTranslate;
	//Mesh *m_currentMesh;
};

SE_END_NAMESPACE

#endif