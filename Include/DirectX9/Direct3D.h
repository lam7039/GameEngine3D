#ifndef DIRECT3D_H
#define DIRECT3D_H

#include "std.h"
#include "Camera.h"
#include <d3dx9.h>

namespace se {

	class Direct3D {
	public:
		void Init(HWND hWnd);
		void Update(float delta);
		void Render();
		void Destroy();
		static LPDIRECT3DDEVICE9 GetDevice();
	private:
		//Devices
		LPDIRECT3D9 m_d3d;
		static LPDIRECT3DDEVICE9 m_device;

		//World (have to do this somewhere else)
		D3DXMATRIX m_matRotate;
		D3DXMATRIX m_matTranslate;
		Camera m_camera;
	};

}

#endif