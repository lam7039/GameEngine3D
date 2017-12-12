#include "DirectX9\DirectXTerrain.h"

namespace se {

	struct Vertex {
		float x, y, z;
		float tu, tv;
	};

	const int WIDTH = 4;
	const int HEIGHT = 3;

	Terrain::Terrain() {
		m_position.Set(2.0f, 5.0f, 2.0f);
		//m_rotation.Set(0.0f, (D3DX_PI / 2), 0.0f);

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

		Vertex Vertices[WIDTH * HEIGHT];
		for (int x = 0; x < WIDTH; x++) {
			for (int y = 0; y < HEIGHT; y++) {
				Vertices[y * WIDTH + x].x = -x;
				Vertices[y * WIDTH + x].y = y;
				Vertices[y * WIDTH + x].z = HeightData[x][y];
				//Vertices[z * WIDTH + x].color = 0xffffffff;
				//Top-left
				if (x % 2 == 0 && y % 2 == 0) {
					Vertices[y * WIDTH + x].tu = 0.0f;
					Vertices[y * WIDTH + x].tv = 0.0f;
				}
				//Top-right
				if (x % 2 != 0 && y % 2 == 0) {
					Vertices[y * WIDTH + x].tu = 1.0f;
					Vertices[y * WIDTH + x].tv = 0.0f;
				}
				//Bottom-left
				if (x % 2 == 0 && y % 2 != 0) {
					Vertices[y * WIDTH + x].tu = 0.0f;
					Vertices[y * WIDTH + x].tv = 1.0f;
				}
				//Bottom-right
				if (x % 2 != 0 && y % 2 != 0) {
					Vertices[y * WIDTH + x].tu = 1.0f;
					Vertices[y * WIDTH + x].tv = 1.0f;
				}
			}
		}

		int vertCount = sizeof(Vertices) / sizeof(Vertex);
		m_byteCount = vertCount * sizeof(Vertex);

		if (FAILED(Direct3D::GetDevice()->CreateVertexBuffer(m_byteCount, 0, D3DFVF_XYZ | D3DFVF_TEX1, D3DPOOL_MANAGED, &m_vertexBuffer, NULL))) {
			//TODO: log failed to create vertex buffer
			return;
		}

		VOID* pVertices;
		m_vertexBuffer->Lock(0, m_byteCount, (void**)&pVertices, 0);
		memcpy(pVertices, &Vertices, m_byteCount);
		m_vertexBuffer->Unlock();

		short Indices[(WIDTH - 1) * (HEIGHT - 1) * 6];
		int indicesCount = sizeof(Indices) / sizeof(short);
		int byteCount = indicesCount * sizeof(short);

		for (int x = 0; x < WIDTH - 1; x++) {
			for (int y = 0; y < HEIGHT - 1; y++) {
				Indices[(x + y * (WIDTH - 1)) * 6] = (x + 1) + (y + 1) * WIDTH;
				Indices[(x + y * (WIDTH - 1)) * 6 + 1] = (x + 1) + y * WIDTH;
				Indices[(x + y * (WIDTH - 1)) * 6 + 2] = x + y * WIDTH;

				Indices[(x + y * (WIDTH - 1)) * 6 + 3] = (x + 1) + (y + 1) * WIDTH;
				Indices[(x + y * (WIDTH - 1)) * 6 + 4] = x + y * WIDTH;
				Indices[(x + y * (WIDTH - 1)) * 6 + 5] = x + (y + 1) * WIDTH;
			}
		}
		Direct3D::GetDevice()->CreateIndexBuffer(byteCount, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_indexBuffer, NULL);

		VOID* pIndices;
		m_indexBuffer->Lock(0, byteCount, (void**)&pIndices, 0);
		memcpy(pIndices, &Indices, byteCount);
		m_indexBuffer->Unlock();

		if (FAILED(D3DXCreateTextureFromFile(Direct3D::GetDevice(), "Assets\\texture.jpg", &m_texture))) {
			//TODO log failed to create texture for terrain
			MessageBox(NULL, "failed to load texture for terrain", "Meshes.exe", MB_OK);
			return;
		}
		Direct3D::GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		Direct3D::GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		Direct3D::GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	}

	void Terrain::Render() {
		D3DXMatrixRotationYawPitchRoll(&m_matRotate, m_rotation.X, m_rotation.Y, m_rotation.Z);
		D3DXMatrixTranslation(&m_matTranslate, m_position.X, m_position.Y, m_position.Z);
		Direct3D::GetDevice()->SetTransform(D3DTS_WORLD, &(m_matRotate * m_matTranslate));
		Direct3D::GetDevice()->SetStreamSource(0, m_vertexBuffer, 0, sizeof(Vertex));
		Direct3D::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
		Direct3D::GetDevice()->SetTexture(0, m_texture);
		Direct3D::GetDevice()->SetIndices(m_indexBuffer);
		//TODO: sometimes crashes when using m_byteCount for some reason
		Direct3D::GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, WIDTH * HEIGHT, 0, (WIDTH - 1) * (HEIGHT - 1) * 2);
	}

	void Terrain::Release() {
		m_texture->Release();
		m_indexBuffer->Release();
		m_vertexBuffer->Release();
	}
}
