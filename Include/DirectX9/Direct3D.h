#ifndef DIRECT3D_H
#define DIRECT3D_H

#include "std.h"
#include "Renderer.h"
#include "Debug.h"
#include <d3d9.h>
#include <d3dx9.h>

namespace se {

	///
	/// The renderer for DirectX 9
	///
	class Direct3D : public AbstractRenderer {
	public:
		void Create(HWND hWnd) override;
		void Update(float delta) override;
		void Process(HWND hWnd) override;
		void Release() override;
		LPDIRECT3DDEVICE9 GetDevice();
	private:
		Debug m_logger;
		//Devices
		LPDIRECT3D9 m_d3d;
		LPDIRECT3DDEVICE9 m_device;


		//World
		D3DXMATRIX m_scale;
		D3DXMATRIX m_matRotate;
		D3DXMATRIX m_matTranslate;
	};

}

#endif