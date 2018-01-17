#include "DirectX9\DirectXSkybox.h"

namespace se {

	struct Vertex {
		float x;
		float y;
		float z;
		float tu;
		float tv;
	};

	Skybox::Skybox() {
		m_transform.scaleX = 100;
		m_transform.scaleY = 100;
		m_transform.scaleZ = 100;
	}

	void Skybox::Create(Transform3f transform, const std::string &src) {
		m_logger.SelectLogger("engine.log");
		//TODO: use the transform (initial position and scale) for the skybox
		m_faceCount = 6;
		const int squareVertCount = 6;

		float posX = 1.0f / 4.0f;
		float posY = 1.0f / 3.0f;
		Vertex vertices[] = {
			// Front Face
			{ 0.0f, 0.0f, 0.0f,			posX, posY },					//Topleft
			{ 100.0f, 0.0f, 0.0f,		posX * 2, posY },				//Topright
			{ 0.0f, -100.0f, 0.0f,		posX, posY * 2 },				//Bottomleft
			{ 0.0f, -100.0f, 0.0f,		posX, posY * 2 },				//Bottomleft
			{ 100.0f, 0.0f, 0.0f,		posX * 2, posY },				//Topright
			{ 100.0f, -100.0f, 0.0f,		posX * 2, posY * 2 },		//Bottomright

			// Bottom Face
			{ 0.0f, -100.0f, 0.0f,		posX, posY * 2 },				//Topleft
			{ 100.0f, -100.0f, 0.0f,		posX * 2, posY * 2 },		//Topright
			{ 0.0f, -100.0f, -100.0f,		posX, posY * 3 },	 		//Bottomleft
			{ 0.0f, -100.0f, -100.0f,		posX, posY * 3 },	 		//Bottomleft
			{ 100.0f, -100.0f, 0.0f,		posX * 2, posY * 2 },		//Topright
			{ 100.0f, -100.0f, -100.0f,	posX * 2, posY * 3 },			//Bottomright

			// Back Face
			{ 100.0f, 0.0f, -100.0f,		posX * 3, posY },			//Topleft
			{ 0.0f, 0.0f, -100.0f,		posX * 4, posY },				//Topright
			{ 100.0f, -100.0f, -100.0f,	posX * 3, posY * 2 },			//Bottomleft
			{ 100.0f, -100.0f, -100.0f,	posX * 3, posY * 2 },			//Bottomleft
			{ 0.0f, 0.0f, -100.0f,		posX * 4, posY },				//Topright
			{ 0.0f, -100.0f, -100.0f,		posX * 4, posY * 2 },		//Bottomright

			// Top Face
			{ 0.0f, 0.0f, 0.0f,			posX, posY },					//Topleft
			{ 0.0f, 0.0f, -100.0f,		posX, 0.0f },					//Bottomleft
			{ 100.0f, 0.0f, 0.0f,		posX * 2, posY },				//Topright
			{ 100.0f, 0.0f, 0.0f,		posX * 2, posY },				//Topright
			{ 0.0f, 0.0f, -100.0f,		posX, 0.0f },					//Bottomleft
			{ 100.0f, 0.0f, -100.0f,		posX * 2, 0.0f },			//Bottomright

			// Left Face
			{ 0.0f, 0.0f, -100.0f,		0.0f, posY },					//Topleft
			{ 0.0f, 0.0f, 0.0f,			posX, posY },					//Topright
			{ 0.0f, -100.0f, -100.0f,		0.0f, posY * 2 },			//Bottomleft
			{ 0.0f, -100.0f, -100.0f,		0.0f, posY * 2 },			//Bottomleft
			{ 0.0f, 0.0f, 0.0f,			posX, posY },					//Topright
			{ 0.0f, -100.0f, 0.0f,		posX, posY * 2 },				//Bottomright

			// Right Face
			{ 100.0f, 0.0f, 0.0f,		posX * 2, posY },				//Topleft
			{ 100.0f, 0.0f, -100.0f,		posX * 3, posY },			//Topright
			{ 100.0f, -100.0f, 0.0f,		posX * 2, posY * 2 },		//Bottomleft
			{ 100.0f, -100.0f, 0.0f,		posX * 2, posY * 2 },		//Bottomleft
			{ 100.0f, 0.0f, -100.0f,		posX * 3, posY },			//Topright
			{ 100.0f, -100.0f, -100.0f,	posX * 3, posY * 2 },			//Bottomright
		};

		int byteCount = m_faceCount * squareVertCount * sizeof(Vertex);

		if (FAILED(Direct3D::GetDevice()->CreateVertexBuffer(byteCount, 0, D3DFVF_XYZ | D3DFVF_TEX1, D3DPOOL_MANAGED, &m_vertexBuffer, NULL))) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed create vertex buffer");
			return;
		}

		VOID* pVertices;
		m_vertexBuffer->Lock(0, byteCount, (void**)&pVertices, 0);
		memcpy(pVertices, &vertices, byteCount);
		m_vertexBuffer->Unlock();

		if (FAILED(D3DXCreateTextureFromFile(Direct3D::GetDevice(), src.c_str(), &m_texture))) {
			m_logger.Log(2, __FILE__, __LINE__, ("Could not find texture map path: " + src).c_str());
			return;
		}
	}

	void Skybox::Process() {

		D3DXMatrixRotationYawPitchRoll(&m_matRotate, m_transform.rotX, m_transform.rotY, m_transform.rotZ);
		D3DXMatrixTranslation(&m_matTranslate, m_transform.posX, m_transform.posY, m_transform.posZ);
		Direct3D::GetDevice()->SetTransform(D3DTS_WORLD, &(m_matRotate * m_matTranslate));
		Direct3D::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
		Direct3D::GetDevice()->SetStreamSource(0, m_vertexBuffer, 0, sizeof(Vertex));

		Direct3D::GetDevice()->SetTexture(0, m_texture);
		Direct3D::GetDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_faceCount * 2);

		//Direct3D::GetDevice()->SetTexture(0, m_map);
		//m_mesh->DrawSubset(0);

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
		m_texture->Release();
		m_vertexBuffer->Release();
	}

	void Skybox::SetPosition(float x, float y, float z) {
		m_transform.posX = x;
		m_transform.posY = y;
		m_transform.posZ = z;
	}

	void Skybox::SetRotation(float x, float y, float z) {
		m_transform.rotX = x;
		m_transform.rotY = y;
		m_transform.rotZ = z;
	}

	void Skybox::SetScale(float x, float y, float z) {
		m_transform.scaleX = x;
		m_transform.scaleY = y;
		m_transform.scaleZ = z;
	}

}