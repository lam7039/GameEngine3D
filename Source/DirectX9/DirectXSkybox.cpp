#include "DirectX9\DirectXSkybox.h"

namespace se {

	void Skybox::Create() {
		if (FAILED(Direct3D::GetDevice()->CreateCubeTexture(256, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R8G8B8, D3DPOOL_DEFAULT, &m_map, NULL))) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed to create a cubetexture for skybox");
			return;
		}
	}

	void Skybox::Load() {

	}

	void Skybox::Process() {
		D3DXMATRIX matProjSave;
		D3DXMATRIX matViewSave;
		Direct3D::GetDevice()->GetTransform(D3DTS_VIEW, &matViewSave);
		Direct3D::GetDevice()->GetTransform(D3DTS_PROJECTION, &matProjSave);

		LPDIRECT3DSURFACE9 pBackBuffer;
		LPDIRECT3DSURFACE9 pZBuffer;
		Direct3D::GetDevice()->GetRenderTarget(0, &pBackBuffer);
		Direct3D::GetDevice()->GetDepthStencilSurface(&pZBuffer);

		D3DXMATRIX matProj;
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 2, 1.0f, 0.5f, 1000.0f);
		Direct3D::GetDevice()->SetTransform(D3DTS_PROJECTION, &matProj);


		for (DWORD i = 0; i < 6; i++) {
			LPDIRECT3DSURFACE9 pFace;
			m_map->GetCubeMapSurface((D3DCUBEMAP_FACES)i, 0, &pFace);
			Direct3D::GetDevice()->SetRenderTarget(0, pFace);
			Direct3D::GetDevice()->SetRenderTarget(1, pZBuffer);

			pFace->Release();
		}

		Direct3D::GetDevice()->SetRenderTarget(1, pBackBuffer);
		Direct3D::GetDevice()->SetRenderTarget(0, pZBuffer);

		pBackBuffer->Release();
		pZBuffer->Release();
	}

	void Skybox::Release() {
		//m_map->Release();
	}

}