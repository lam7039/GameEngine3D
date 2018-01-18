#include "DirectX9\DirectXSkybox.h"

namespace se {

	struct Vertex {
		float x;
		float y;
		float z;
		float tu;
		float tv;
	};

	Skybox::Skybox(LPDIRECT3DDEVICE9 device) {
		m_device = device;
	}

	void Skybox::Create(Transform3f transform, const std::string &src) {
		m_logger.SelectLogger("engine.log");

		m_faceCount = 6;
		const int squareVertCount = 6;
		
		float posX = (1.0f / 4.0f);
		float posY = (1.0f / 3.0f);

		Vertex vertices[] = {
			// Front Face
			{ transform.posX, transform.posY, transform.posZ,																posX * 1, posY * 1 },	//Topleft
			{ transform.posX + transform.scaleX, transform.posY, transform.posZ,											posX * 2, posY * 1 },	//Topright
			{ transform.posX, transform.posY - transform.scaleY, transform.posZ,											posX * 1, posY * 2 },	//Bottomleft
			{ transform.posX, transform.posY - transform.scaleY, transform.posZ,											posX * 1, posY * 2 },	//Bottomleft
			{ transform.posX + transform.scaleX, transform.posY, transform.posZ,											posX * 2, posY * 1 },	//Topright
			{ transform.posX + transform.scaleX, transform.posY - transform.scaleY, transform.posZ,							posX * 2, posY * 2 },	//Bottomright

			// Bottom Face
			{ transform.posX, transform.posY - transform.scaleY, transform.posZ,											posX * 1, posY * 2 },	//Topleft
			{ transform.posX + transform.scaleX, transform.posY - transform.scaleY, transform.posZ,							posX * 2, posY * 2 },	//Topright
			{ transform.posX, transform.posY - transform.scaleY, transform.posZ - transform.scaleZ,							posX * 1, 1.0f },		//Bottomleft
			{ transform.posX, transform.posY - transform.scaleY, transform.posZ - transform.scaleZ,							posX * 1, 1.0f },		//Bottomleft
			{ transform.posX + transform.scaleX, transform.posY - transform.scaleY, transform.posZ,							posX * 2, posY * 2 },	//Topright
			{ transform.posX + transform.scaleX, transform.posY - transform.scaleY, transform.posZ - transform.scaleZ,		posX * 2, 1.0f },		//Bottomright

			// Back Face
			{ transform.posX + transform.scaleX, transform.posY, transform.posZ - transform.scaleZ,							posX * 3, posY * 1 },	//Topleft
			{ transform.posX, transform.posY, transform.posZ - transform.scaleZ,											1.0f, posY * 1 },		//Topright
			{ transform.posX + transform.scaleX, transform.posY - transform.scaleY, transform.posZ - transform.scaleZ,		posX * 3, posY * 2 },	//Bottomleft
			{ transform.posX + transform.scaleX, transform.posY - transform.scaleY, transform.posZ - transform.scaleZ,		posX * 3, posY * 2 },	//Bottomleft
			{ transform.posX, transform.posY, transform.posZ - transform.scaleZ,											1.0f, posY * 1 },		//Topright
			{ transform.posX, transform.posY - transform.scaleY, transform.posZ - transform.scaleZ,							1.0f, posY * 2 },		//Bottomright

			// Top Face
			{ transform.posX, transform.posY, transform.posZ - transform.scaleZ,											posX * 1, 0.0f },		//Topleft
			{ transform.posX + transform.scaleX, transform.posY, transform.posZ - transform.scaleZ,							posX * 2, 0.0f },		//Topright
			{ transform.posX, transform.posY, transform.posZ,																posX * 1, posY * 1 },	//Bottomleft
			{ transform.posX, transform.posY, transform.posZ,																posX * 1, posY * 1 },	//Bottomleft
			{ transform.posX + transform.scaleX, transform.posY, transform.posZ - transform.scaleZ,							posX * 2, 0.0f },		//Topright
			{ transform.posX + transform.scaleX, transform.posY, transform.posZ,											posX * 2, posY * 1 },	//Bottomright

			// Left Face
			{ transform.posX , transform.posY, transform.posZ - transform.scaleZ,											0.0f, posY * 1 },		//Topleft
			{ transform.posX, transform.posY, transform.posZ,																posX * 1, posY * 1 },	//Topright
			{ transform.posX, transform.posY - transform.scaleY, transform.posZ - transform.scaleZ,							0.0f, posY * 2 },		//Bottomleft
			{ transform.posX, transform.posY - transform.scaleY, transform.posZ - transform.scaleZ,							0.0f, posY * 2 },		//Bottomleft
			{ transform.posX, transform.posY, transform.posZ,																posX * 1, posY * 1 },	//Topright
			{ transform.posX, transform.posY - transform.scaleY, transform.posZ,											posX * 1, posY * 2 },	//Bottomright

			// Right Face
			{ transform.posX + transform.scaleX, transform.posY, transform.posZ,											posX * 2, posY * 1 },	//Topleft
			{ transform.posX + transform.scaleX, transform.posY, transform.posZ - transform.scaleZ,							posX * 3, posY * 1 },	//Topright
			{ transform.posX + transform.scaleX, transform.posY - transform.scaleY, transform.posZ,							posX * 2, posY * 2 },	//Bottomleft
			{ transform.posX + transform.scaleX, transform.posY - transform.scaleY, transform.posZ,							posX * 2, posY * 2 },	//Bottomleft
			{ transform.posX + transform.scaleX, transform.posY, transform.posZ - transform.scaleZ,							posX * 3, posY * 1 },	//Topright
			{ transform.posX + transform.scaleX, transform.posY - transform.scaleY, transform.posZ - transform.scaleZ,		posX * 3, posY * 2 },	//Bottomright
		};
		m_transform = transform;
		int byteCount = m_faceCount * squareVertCount * sizeof(Vertex);

		if (FAILED(m_device->CreateVertexBuffer(byteCount, 0, D3DFVF_XYZ | D3DFVF_TEX1, D3DPOOL_MANAGED, &m_vertexBuffer, NULL))) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed create vertex buffer");
			return;
		}

		VOID* pVertices;
		m_vertexBuffer->Lock(0, byteCount, (void**)&pVertices, 0);
		memcpy(pVertices, &vertices, byteCount);
		m_vertexBuffer->Unlock();

		if (FAILED(D3DXCreateTextureFromFile(m_device, src.c_str(), &m_texture))) {
			m_logger.Log(2, __FILE__, __LINE__, ("Could not find texture map path: " + src).c_str());
			return;
		}
	}

	void Skybox::Process() {
		D3DXMatrixRotationYawPitchRoll(&m_matRotate, m_transform.rotX, m_transform.rotY, m_transform.rotZ);
		D3DXMatrixTranslation(&m_matTranslate, m_transform.posX, m_transform.posY, m_transform.posZ);
		m_device->SetTransform(D3DTS_WORLD, &(m_matRotate * m_matTranslate));
		m_device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
		m_device->SetStreamSource(0, m_vertexBuffer, 0, sizeof(Vertex));
		m_device->SetTexture(0, m_texture);
		m_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		m_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		m_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		m_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		m_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
		m_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_faceCount * 2);
	}

	void Skybox::Release() {
		m_texture->Release();
		m_vertexBuffer->Release();
	}

}