#include "DirectX9\DirectXTerrain.h"

namespace se {

	struct Vertex {
		float x;
		float y;
		float z;
		float tu;
		float tv;
	};

	Terrain::Terrain(LPDIRECT3DDEVICE9 device) {
		m_device = device;
	}

	void Terrain::Create(const std::string &heightMap, const std::string &texture, Transform3f &transform) {
		m_logger.SelectLogger("engine.log");
		if (m_bitmap.LoadBMP("Assets\\" + heightMap) > 0) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed to load the bitmap");
			return;
		}
		m_width = m_bitmap.GetWidth();
		m_height = m_bitmap.GetHeight();

		m_transform = transform;

		unsigned char *HeightData = m_bitmap.GetData();

		const int squareVertCount = 6;
		unsigned long vertCount = m_width * m_height * squareVertCount;
		Vertex *vertices = new Vertex[vertCount];

		for (int x = 0; x < m_width - 1; x++) {
			for (int z = 0; z < m_height - 1; z++) {
				int i = x + z * m_width;
				float topLeft = static_cast<float>(HeightData[x + z * m_width]) / 10;
				float topRight = static_cast<float>(HeightData[(x + 1) + z * m_width]) / 10;
				float bottomLeft = static_cast<float>(HeightData[x + (z + 1) * m_width]) / 10;
				float bottomRight = static_cast<float>(HeightData[(x + 1) + (z + 1) * m_width]) / 10;

				vertices[i * squareVertCount] = {	  static_cast<float>(x),		topLeft,		-static_cast<float>(z),		0.0f, 0.0f };	//Topleft
				vertices[i * squareVertCount + 1] = { static_cast<float>((x + 1)),	topRight,		-static_cast<float>(z),		1.0f, 0.0f };	//Topright
				vertices[i * squareVertCount + 2] = { static_cast<float>(x),		bottomLeft,		-static_cast<float>(z + 1),	0.0f, 1.0f };	//Bottomleft

				vertices[i * squareVertCount + 3] = { static_cast<float>(x),		bottomLeft,		-static_cast<float>(z + 1),	0.0f, 1.0f };	//Bottomleft
				vertices[i * squareVertCount + 4] = { static_cast<float>((x + 1)),	topRight,		-static_cast<float>(z),		1.0f, 0.0f };	//Topright
				vertices[i * squareVertCount + 5] = { static_cast<float>((x + 1)),	bottomRight,	-static_cast<float>(z + 1),	1.0f, 1.0f };	//BottomRight
			}
		}

		int byteCount = vertCount * sizeof(Vertex);

		if (FAILED(m_device->CreateVertexBuffer(byteCount, 0, D3DFVF_XYZ | D3DFVF_TEX1, D3DPOOL_MANAGED, &m_vertexBuffer, NULL))) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed create vertex buffer");
			return;
		}

		VOID* pVertices;
		m_vertexBuffer->Lock(0, byteCount, (void**)&pVertices, 0);
		memcpy(pVertices, &*vertices, byteCount);
		m_vertexBuffer->Unlock();

		delete[] vertices;
		vertices = NULL;

		if (FAILED(D3DXCreateTextureFromFile(m_device, ("Assets\\" + texture).c_str(), &m_texture))) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed to load texture for terrain");
			return;
		}
		m_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		m_device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	}

	void Terrain::Process() {
		D3DXMatrixRotationYawPitchRoll(&m_matRotate, m_transform.rotX, m_transform.rotY, m_transform.rotZ);
		D3DXMatrixTranslation(&m_matTranslate, m_transform.posX, m_transform.posY, m_transform.posZ);
		m_device->SetTransform(D3DTS_WORLD, &(m_matRotate * m_matTranslate));
		m_device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
		m_device->SetStreamSource(0, m_vertexBuffer, 0, sizeof(Vertex));
		m_device->SetTexture(0, m_texture);
		m_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		m_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		m_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		m_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_width * m_height * 2);
	}

	void Terrain::Release() {
		m_texture->Release();
		m_vertexBuffer->Release();
	}
}
