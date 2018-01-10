#include "DirectX9\DirectXTerrain.h"
#include <iostream>

namespace se {

	struct Vertex {
		float x, y, z;
		float tu, tv;
	};

	void Terrain::Create() {
		int errorcode = m_bitmap.LoadBMP("Assets\\Naamloos2.bmp");
		std::cout << "bitmap load error: " << errorcode << std::endl;

		//const int width = 4;
		//const int height = 3;
		m_width = m_bitmap.GetWidth();
		m_height = m_bitmap.GetHeight();
		std::cout << "width: " << m_width << " height: " << m_height << std::endl;
		m_transform.posX = 10.0f;
		m_transform.posY = -5.0f;
		m_transform.posZ = 2.0f;


		m_transform.rotX = 0.0f;
		m_transform.rotY = 0.0f;
		m_transform.rotZ = 0.0f;

		unsigned char *HeightData = m_bitmap.GetPixels();

		std::cout << "heightData in pixels: " << (float)HeightData[0 * m_height + 12] << std::endl;

		//float HeightData[width][height];
		//HeightData[0][0] = 0; //Bottom-right
		//HeightData[1][0] = 0;
		//HeightData[2][0] = 0;
		//HeightData[3][0] = 0; //Bottom-left

		//HeightData[0][1] = 1;
		//HeightData[1][1] = 0;
		//HeightData[2][1] = 2;
		//HeightData[3][1] = 2;

		//HeightData[0][2] = 2; //Top-right
		//HeightData[1][2] = 2;
		//HeightData[2][2] = 4;
		//HeightData[3][2] = 2; //Top-left

		//float HeightData[width * height];
		//HeightData[0] = 0; //Bottom-right
		//HeightData[1] = 0;
		//HeightData[2] = 0;
		//HeightData[3] = 0; //Bottom-left

		//HeightData[4] = 1;
		//HeightData[5] = 0;
		//HeightData[6] = 2;
		//HeightData[7] = 2;

		//HeightData[8] = 2; //Top-right
		//HeightData[9] = 2;
		//HeightData[10] = 4;
		//HeightData[11] = 2; //Top-left

		//float tu = 0.0f;
		//float tv = 0.0f;

		const int squareVertCount = 6;
		unsigned long vertCount = m_width * m_height * squareVertCount;
		Vertex *vertices = new Vertex[vertCount];
		//Vertex vertices[(width * height * squareVertCount)];
		//TODO: look at a better way to render heightmap with indices
		for (int x = 0; x < m_width - 1; x++) {
			for (int z = 0; z < m_height - 1; z++) {
				//Without indices
				int i = x + z * m_width;
				float topLeft =		static_cast<float>(HeightData[x + z * m_width]);
				float topRight =	static_cast<float>(HeightData[(x + 1) + z * m_width]);
				float bottomLeft =	static_cast<float>(HeightData[x + (z + 1) * m_width]);
				float bottomRight = static_cast<float>(HeightData[(x + 1) + (z + 1) * m_width]);

				//std::cout << topLeft << ", " << topRight << std::endl;
				//std::cout << bottomLeft << ", " << bottomRight << std::endl;

				vertices[i * squareVertCount] =		{ static_cast<float>(-x),		topLeft,		-static_cast<float>(z),		0.0f, 0.0f };	//Topleft
				vertices[i * squareVertCount + 1] = { static_cast<float>(-(x + 1)),	topRight,		-static_cast<float>(z),		1.0f, 0.0f };	//Topright
				vertices[i * squareVertCount + 2] = { static_cast<float>(-x),		bottomLeft,		-static_cast<float>(z + 1),	0.0f, 1.0f };	//Bottomleft

				vertices[i * squareVertCount + 3] = { static_cast<float>(-x),		bottomLeft,		-static_cast<float>(z + 1),	0.0f, 1.0f };	//Bottomleft
				vertices[i * squareVertCount + 4] = { static_cast<float>(-(x + 1)),	topRight,		-static_cast<float>(z),		1.0f, 0.0f };	//Topright
				vertices[i * squareVertCount + 5] = { static_cast<float>(-(x + 1)),	bottomRight,	-static_cast<float>(z + 1),	1.0f, 1.0f };	//BottomRight

				//HeightData[x][y],
				//HeightData[x + 1][y],
				//HeightData[x][y + 1],

				//HeightData[x][y + 1],
				//HeightData[x + 1][y],
				//HeightData[x + 1][y + 1],


				//With indices but flips the textures because of:
				//00,10,00,10
				//01,11,01,11
				//00,10,00,10

				//if (x % 2 == 0 && y % 2 == 0) {
				//	tu = 0.0f;
				//	tv = 0.0f;
				//}
				//if (x % 2 != 0 && y % 2 == 0) {
				//	tu = 1.0f;
				//	tv = 0.0f;
				//}
				//if (x % 2 == 0 && y % 2 != 0) {
				//	tu = 0.0f;
				//	tv = 1.0f;
				//}
				//if (x % 2 != 0 && y % 2 != 0) {
				//	tu = 1.0f;
				//	tv = 1.0f;
				//}
				//vertices[y * width + x] = { static_cast<float>(-x), static_cast<float>(y), HeightData[x][y], tu, tv };
			}
		}

		////Attempt to stretch the texture all over the terrain
		////Top-left
		//vertices[0].tu = 0.0f;
		//vertices[0].tv = 0.0f;
		////Top-right
		//vertices[width - 1].tu = 1.0f;
		//vertices[width - 1].tv = 0.0f;
		////Bottom-left
		//vertices[(width * height - 1) - width].tu = 0.0f;
		//vertices[(width * height - 1) - width].tv = 1.0f;
		////Bottom-right
		//vertices[width * height - 1].tu = 1.0f;
		//vertices[width * height - 1].tv = 1.0f;

		int byteCount = vertCount * sizeof(Vertex);

		if (FAILED(Direct3D::GetDevice()->CreateVertexBuffer(byteCount, 0, D3DFVF_XYZ | D3DFVF_TEX1, D3DPOOL_MANAGED, &m_vertexBuffer, NULL))) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed create vertex buffer");
			return;
		}

		VOID* pVertices;
		m_vertexBuffer->Lock(0, byteCount, (void**)&pVertices, 0);
		memcpy(pVertices, &*vertices, byteCount);
		m_vertexBuffer->Unlock();

		delete[] vertices;
		vertices = NULL;

		//short Indices[(width - 1) * (height - 1) * squareVertCount];
		//int indicesCount = sizeof(Indices) / sizeof(short);
		//int byteCountIndices = indicesCount * sizeof(short);

		//for (int x = 0; x < width - 1; x++) {
		//	for (int y = 0; y < height - 1; y++) {
		//		int i = (x + y * (width - 1));
		//		int topleft = x + y * width;
		//		int topright = (x + 1) + y * width;
		//		int bottomleft = x + (y + 1) * width;
		//		int bottomright = (x + 1) + (y + 1) * width;

		//		Indices[i * squareVertCount] = topleft;
		//		Indices[i * squareVertCount + 1] = topright;
		//		Indices[i * squareVertCount + 2] = bottomleft;

		//		Indices[i * squareVertCount + 3] = bottomleft;
		//		Indices[i * squareVertCount + 4] = topright;
		//		Indices[i * squareVertCount + 5] = bottomright;
		//	}
		//}
		//Direct3D::GetDevice()->CreateIndexBuffer(byteCountIndices, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_indexBuffer, NULL);

		//VOID* pIndices;
		//m_indexBuffer->Lock(0, byteCountIndices, (void**)&pIndices, 0);
		//memcpy(pIndices, &Indices, byteCountIndices);
		//m_indexBuffer->Unlock();

		if (FAILED(D3DXCreateTextureFromFile(Direct3D::GetDevice(), "Assets\\texture.jpg", &m_texture))) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed to load texture for terrain");
			return;
		}
		Direct3D::GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		Direct3D::GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		Direct3D::GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	}

	void Terrain::Load() {

	}

	void Terrain::Process() {
		D3DXMatrixRotationYawPitchRoll(&m_matRotate, m_transform.rotX, m_transform.rotY, m_transform.rotZ);
		D3DXMatrixTranslation(&m_matTranslate, m_transform.posX, m_transform.posY, m_transform.posZ);
		Direct3D::GetDevice()->SetTransform(D3DTS_WORLD, &(m_matRotate * m_matTranslate));
		Direct3D::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
		Direct3D::GetDevice()->SetStreamSource(0, m_vertexBuffer, 0, sizeof(Vertex));
		Direct3D::GetDevice()->SetTexture(0, m_texture);
		//Direct3D::GetDevice()->SetIndices(m_indexBuffer);
		//Direct3D::GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_width * m_height, 0, (m_width - 1) * (m_height - 1) * 2);
		Direct3D::GetDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_width * m_height * 2);
	}

	void Terrain::Release() {
		m_texture->Release();
		//m_indexBuffer->Release();
		m_vertexBuffer->Release();
	}
}
