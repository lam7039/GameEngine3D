#include "DirectX9\DirectXTerrain.h"

namespace se {

	struct Vertex {
		float x, y, z;
		float tu, tv;
	};

	const int WIDTH = 4;
	const int HEIGHT = 3;

	void Terrain::Create() {
		m_position.Set(2.0f, 5.0f, 2.0f);
		m_rotation.Set(0.0f, (D3DX_PI / 2), 0.0f);

		//positive = depth, negative = height
		float HeightData[WIDTH][HEIGHT];
		HeightData[0][0] = 0; //Top-left
		HeightData[1][0] = 0;
		HeightData[2][0] = 0;
		HeightData[3][0] = 0; //Top-right

		HeightData[0][1] = 1;
		HeightData[1][1] = 0;
		HeightData[2][1] = 2;
		HeightData[3][1] = 2;

		HeightData[0][2] = 2; //Bottom-left
		HeightData[1][2] = 2;
		HeightData[2][2] = 4;
		HeightData[3][2] = 2; //Bottom-right

		//float tu = 0.0f;
		//float tv = 0.0f;

		const int squareVertCount = 6;
		Vertex vertices[(WIDTH * HEIGHT * squareVertCount)];

		//TODO: look at a better way to render heightmap with indices
		for (int x = 0; x < WIDTH - 1; x++) {
			for (int y = 0; y < HEIGHT - 1; y++) {
				//Without indices
				int i = x + y * WIDTH;
				vertices[i * squareVertCount]		= { static_cast<float>(-x),			static_cast<float>(y),		HeightData[x][y],			0.0f, 0.0f };
				vertices[i * squareVertCount + 1]	= { static_cast<float>(-(x + 1)),	static_cast<float>(y),		HeightData[x + 1][y],		1.0f, 0.0f };
				vertices[i * squareVertCount + 2]	= { static_cast<float>(-x),			static_cast<float>(y + 1),	HeightData[x][y + 1],		0.0f, 1.0f };

				vertices[i * squareVertCount + 3]	= { static_cast<float>(-(x + 1)),	static_cast<float>(y),		HeightData[x + 1][y],		1.0f, 0.0f };
				vertices[i * squareVertCount + 4]	= { static_cast<float>(-x),			static_cast<float>(y + 1),	HeightData[x][y + 1],		0.0f, 1.0f };
				vertices[i * squareVertCount + 5]	= { static_cast<float>(-(x + 1)),	static_cast<float>(y + 1),	HeightData[x + 1][y + 1],	1.0f, 1.0f };

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
				//vertices[y * WIDTH + x] = { static_cast<float>(-x), static_cast<float>(y), HeightData[x][y], tu, tv };
			}
		}

		////Attempt to stretch the texture all over the terrain
		////Top-left
		//vertices[0].tu = 0.0f;
		//vertices[0].tv = 0.0f;
		////Top-right
		//vertices[WIDTH - 1].tu = 1.0f;
		//vertices[WIDTH - 1].tv = 0.0f;
		////Bottom-left
		//vertices[(WIDTH * HEIGHT - 1) - WIDTH].tu = 0.0f;
		//vertices[(WIDTH * HEIGHT - 1) - WIDTH].tv = 1.0f;
		////Bottom-right
		//vertices[WIDTH * HEIGHT - 1].tu = 1.0f;
		//vertices[WIDTH * HEIGHT - 1].tv = 1.0f;

		int vertCount = sizeof(vertices) / sizeof(Vertex);
		int byteCount = vertCount * sizeof(Vertex);

		if (FAILED(Direct3D::GetDevice()->CreateVertexBuffer(byteCount, 0, D3DFVF_XYZ | D3DFVF_TEX1, D3DPOOL_MANAGED, &m_vertexBuffer, NULL))) {
			//TODO: log failed to create vertex buffer
			return;
		}

		VOID* pVertices;
		m_vertexBuffer->Lock(0, byteCount, (void**)&pVertices, 0);
		memcpy(pVertices, &vertices, byteCount);
		m_vertexBuffer->Unlock();

		//short Indices[(WIDTH - 1) * (HEIGHT - 1) * squareVertCount];
		//int indicesCount = sizeof(Indices) / sizeof(short);
		//int byteCountIndices = indicesCount * sizeof(short);

		//for (int x = 0; x < WIDTH - 1; x++) {
		//	for (int y = 0; y < HEIGHT - 1; y++) {
		//		int i = (x + y * (WIDTH - 1));
		//		int topleft = x + y * WIDTH;
		//		int topright = (x + 1) + y * WIDTH;
		//		int bottomleft = x + (y + 1) * WIDTH;
		//		int bottomright = (x + 1) + (y + 1) * WIDTH;

		//		Indices[i * squareVertCount] = topleft;
		//		Indices[i * squareVertCount + 1] = topright;
		//		Indices[i * squareVertCount + 2] = bottomleft;

		//		Indices[i * squareVertCount + 3] = topright;
		//		Indices[i * squareVertCount + 4] = bottomleft;
		//		Indices[i * squareVertCount + 5] = bottomright;
		//	}
		//}
		//Direct3D::GetDevice()->CreateIndexBuffer(byteCountIndices, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_indexBuffer, NULL);

		//VOID* pIndices;
		//m_indexBuffer->Lock(0, byteCountIndices, (void**)&pIndices, 0);
		//memcpy(pIndices, &Indices, byteCountIndices);
		//m_indexBuffer->Unlock();

		if (FAILED(D3DXCreateTextureFromFile(Direct3D::GetDevice(), "Assets\\texture.jpg", &m_texture))) {
			//TODO: log failed to create texture for terrain
			MessageBox(NULL, "failed to load texture for terrain", "Meshes.exe", MB_OK);
			return;
		}
		Direct3D::GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		Direct3D::GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		Direct3D::GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	}

	void Terrain::Load() {

	}

	void Terrain::Process() {
		D3DXMatrixRotationYawPitchRoll(&m_matRotate, m_rotation.X, m_rotation.Y, m_rotation.Z);
		D3DXMatrixTranslation(&m_matTranslate, m_position.X, m_position.Y, m_position.Z);
		Direct3D::GetDevice()->SetTransform(D3DTS_WORLD, &(m_matRotate * m_matTranslate));
		Direct3D::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
		Direct3D::GetDevice()->SetStreamSource(0, m_vertexBuffer, 0, sizeof(Vertex));
		Direct3D::GetDevice()->SetTexture(0, m_texture);
		//Direct3D::GetDevice()->SetIndices(m_indexBuffer);
		//Direct3D::GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, WIDTH * HEIGHT, 0, (WIDTH - 1) * (HEIGHT - 1) * 2);
		Direct3D::GetDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, WIDTH * HEIGHT * 2);
	}

	void Terrain::Release() {
		m_texture->Release();
		//m_indexBuffer->Release();
		m_vertexBuffer->Release();
	}
}
