#include "Terrain.h"

namespace se {

	struct Vertex {
		float x, y, z;
		DWORD color;
	};

	const int WIDTH = 4;
	const int HEIGHT = 3;

	Terrain::Terrain(LPDIRECT3DDEVICE9 device) {
		m_device = device;

		float HeightData[WIDTH][HEIGHT];
		HeightData[0][0] = 0;
		HeightData[1][0] = 0;
		HeightData[2][0] = 0;
		HeightData[3][0] = 0;

		HeightData[0][1] = 1;
		HeightData[1][1] = 0;
		HeightData[2][1] = 2;
		HeightData[3][1] = 2;

		HeightData[0][2] = 2;
		HeightData[1][2] = 2;
		HeightData[2][2] = 4;
		HeightData[3][2] = 2;

		Vertex Vertices[WIDTH * HEIGHT];
		for (int x = 0; x < WIDTH; x++) {
			for (int y = 0; y < HEIGHT; y++) {
				Vertices[y * WIDTH + x].x = -x;
				Vertices[y * WIDTH + x].y = y;
				Vertices[y * WIDTH + x].z = HeightData[x][y];
				Vertices[y * WIDTH + x].color = 0xffffffff;
			}
		}
		m_device->CreateVertexBuffer(WIDTH * HEIGHT * sizeof(Vertex), 0, D3DFVF_XYZ | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &m_vertexBuffer, NULL);

		VOID* pVertices;
		m_vertexBuffer->Lock(0, WIDTH * HEIGHT * sizeof(Vertex), (void**)&pVertices, 0);
		memcpy(pVertices, &Vertices, WIDTH * HEIGHT * sizeof(Vertex));
		m_vertexBuffer->Unlock();

		short Indices[(WIDTH - 1) * (HEIGHT - 1) * 6];
		for (int x = 0; x < WIDTH - 1; x++) {
			for (int y = 0; y < HEIGHT - 1; y++) {
				Indices[(x + y * (WIDTH - 1)) * 6 + 2] = x + y * WIDTH;
				Indices[(x + y * (WIDTH - 1)) * 6 + 1] = (x + 1) + y * WIDTH;
				Indices[(x + y * (WIDTH - 1)) * 6] = (x + 1) + (y + 1) * WIDTH;

				Indices[(x + y * (WIDTH - 1)) * 6 + 3] = (x + 1) + (y + 1) * WIDTH;
				Indices[(x + y * (WIDTH - 1)) * 6 + 4] = x + y * WIDTH;
				Indices[(x + y * (WIDTH - 1)) * 6 + 5] = x + (y + 1) * WIDTH;
			}
		}
		m_device->CreateIndexBuffer((WIDTH - 1) * (HEIGHT - 1) * 6 * sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_indexBuffer, NULL);

		VOID* pIndices;
		m_indexBuffer->Lock(0, (WIDTH - 1) * (HEIGHT - 1) * 6 * sizeof(short), (void**)&pIndices, 0);
		memcpy(pIndices, &Indices, (WIDTH - 1) * (HEIGHT - 1) * 6 * sizeof(short));
		m_indexBuffer->Unlock();
	}

	void Terrain::Render() {
		m_device->SetStreamSource(0, m_vertexBuffer, 0, sizeof(Vertex));
		m_device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		m_device->SetIndices(m_indexBuffer);
		m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, WIDTH * HEIGHT, 0, (WIDTH - 1) * (HEIGHT - 1) * 2);
	}

}
