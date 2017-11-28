#ifndef DIRECT3D_H
#define DIRECT3D_H

#include "std.h"
#include "Mesh.h"
#include <d3dx9.h>

SE_BEGIN_NAMESPACE

class Direct3D {
public:
	Direct3D(HWND hWnd);
	~Direct3D();
	void Update(float delta);
	//void Render();
	LPDIRECT3DDEVICE9 GetDevice();
private:
	LPDIRECT3D9 m_d3d;
	LPDIRECT3DDEVICE9 m_device;
	//LPDIRECT3DVERTEXBUFFER9 m_vBuffer;
	//LPDIRECT3DTEXTURE9 m_texture;
};

SE_END_NAMESPACE

#endif