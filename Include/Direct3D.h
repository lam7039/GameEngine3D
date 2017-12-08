#ifndef DIRECT3D_H
#define DIRECT3D_H

#include "std.h"
#include "Camera.h"
#include "Mesh.h"
#include <d3dx9.h>

namespace se {

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
		Camera m_camera;
	};

}

#endif