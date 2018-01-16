#include "DirectX9\DirectXSkybox.h"

namespace se {

	void Skybox::Create() {
		m_logger.SelectLogger("engine.log");
		if (FAILED(D3DXCreateBox(Direct3D::GetDevice(), 100, 100, 100, &m_mesh, 0))) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed to create a sphere for skybox");
			return;
		}
		D3DXCreateCubeTextureFromFile(Direct3D::GetDevice(), "Assets\\Islands.dds", &m_map);
		if (FAILED(D3DXCreateCubeTextureFromFile(Direct3D::GetDevice(), "Assets\\Islands.dds", &m_map))) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed to create a cubetexture for skybox");
			return;
		}
		//TODO: make skybox work
		Direct3D::GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		Direct3D::GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		Direct3D::GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		Direct3D::GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		Direct3D::GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		Direct3D::GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		Direct3D::GetDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
		Direct3D::GetDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	}

	void Skybox::Load() {

	}

	void Skybox::Process() {

		Direct3D::GetDevice()->SetTexture(0, m_map);
		m_mesh->DrawSubset(0);


		//D3DXMATRIX matProjSave;
		//D3DXMATRIX matViewSave;
		//Direct3D::GetDevice()->GetTransform(D3DTS_VIEW, &matViewSave);
		//Direct3D::GetDevice()->GetTransform(D3DTS_PROJECTION, &matProjSave);

		//LPDIRECT3DSURFACE9 pBackBuffer;
		//LPDIRECT3DSURFACE9 pZBuffer;
		//Direct3D::GetDevice()->GetRenderTarget(0, &pBackBuffer);
		//Direct3D::GetDevice()->GetDepthStencilSurface(&pZBuffer);

		//D3DXMATRIX matProj;
		//D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 2, 1.0f, 0.5f, 1000.0f);
		//Direct3D::GetDevice()->SetTransform(D3DTS_PROJECTION, &matProj);


		//for (DWORD i = 0; i < 6; i++) {
		//	LPDIRECT3DSURFACE9 pFace;
		//	m_map->GetCubeMapSurface((D3DCUBEMAP_FACES)i, 0, &pFace);
		//	Direct3D::GetDevice()->SetRenderTarget(0, pFace);
		//	Direct3D::GetDevice()->SetRenderTarget(1, pZBuffer);

		//	pFace->Release();
		//}

		//Direct3D::GetDevice()->SetRenderTarget(1, pBackBuffer);
		//Direct3D::GetDevice()->SetRenderTarget(0, pZBuffer);

		//pBackBuffer->Release();
		//pZBuffer->Release();
	}

	void Skybox::Release() {
		//m_map->Release();
	}

}