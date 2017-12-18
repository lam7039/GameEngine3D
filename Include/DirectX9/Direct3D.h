#ifndef DIRECT3D_H
#define DIRECT3D_H

#include "std.h"
#include "Transform.h"
#include "Renderer.h"
#include <d3d9.h>
#include <d3dx9.h>

namespace se {

	class Direct3D : public AbstractRenderer {
	public:
		void Create(HWND hWnd) override;
		void Render() override;
		void Release() override;
		static LPDIRECT3DDEVICE9 GetDevice();
	private:
		//Devices
		LPDIRECT3D9 m_d3d;
		static LPDIRECT3DDEVICE9 m_device;

		//World (have to do this somewhere else)
		D3DXMATRIX m_scale;
		D3DXMATRIX m_matRotate;
		D3DXMATRIX m_matTranslate;
	};

}

#endif