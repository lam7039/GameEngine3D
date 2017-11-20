#ifndef DIRECT3D_H
#define DIRECT3D_H

#include "std.h"
#include <d3d9.h>

SE_BEGIN_NAMESPACE

class Direct3D {
public:
	Direct3D(HWND hWnd);
	void Draw();
	~Direct3D();
private:
	LPDIRECT3D9 m_d3d;
	LPDIRECT3DDEVICE9 m_d3dDev;
	LPDIRECT3DVERTEXBUFFER9 m_vBuffer;
};

#endif

SE_END_NAMESPACE