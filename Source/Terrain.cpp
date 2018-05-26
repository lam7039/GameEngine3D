#include "Terrain.h"

namespace se {

	Terrain::Terrain(AbstractRenderer *renderer, const std::string &assetName, const std::string &heightMap, const std::string &texture) : AbstractAsset(renderer, assetName) {
		m_logger.SelectLogger("engine.log");
		if (m_bitmap.LoadBMP(heightMap) > 0) {
			m_logger.Log(ERRORTYPE_ERROR, __FILE__, __LINE__, "Failed to load the bitmap");
			return;
		}
		unsigned char *heightData = m_bitmap.GetData();

		const int squareVertCount = 6;
		m_size = m_bitmap.GetSize();
		m_size.z = squareVertCount;

		unsigned long vertCount = m_size.x * m_size.y * squareVertCount;
		Vertex *vertices = new Vertex[vertCount];

		for (int x = 0; x < m_size.x - 1; x++) {
			for (int z = 0; z < m_size.y - 1; z++) {
				int i = x + z * m_size.x;
				float topLeft = static_cast<float>(heightData[x + z * m_size.x]) / 10;
				float topRight = static_cast<float>(heightData[(x + 1) + z * m_size.x]) / 10;
				float bottomLeft = static_cast<float>(heightData[x + (z + 1) * m_size.x]) / 10;
				float bottomRight = static_cast<float>(heightData[(x + 1) + (z + 1) * m_size.x]) / 10;

				if (topLeft != bottomRight) {
					vertices[i * squareVertCount + 0] = { static_cast<float>(x + 1),	topRight,		static_cast<float>(z),		1.0f, 0.0f };	//Topright
					vertices[i * squareVertCount + 1] = { static_cast<float>(x),		topLeft,		static_cast<float>(z),		0.0f, 0.0f };	//Topleft
					vertices[i * squareVertCount + 2] = { static_cast<float>(x + 1),	bottomRight,	static_cast<float>(z + 1),	1.0f, 1.0f };	//BottomRight

					vertices[i * squareVertCount + 3] = { static_cast<float>(x + 1),	bottomRight,	static_cast<float>(z + 1),	1.0f, 1.0f };	//BottomRight
					vertices[i * squareVertCount + 4] = { static_cast<float>(x),		topLeft,		static_cast<float>(z),		0.0f, 0.0f };	//Topleft
					vertices[i * squareVertCount + 5] = { static_cast<float>(x),		bottomLeft,		static_cast<float>(z + 1),	0.0f, 1.0f };	//Bottomleft
				}
				else {
					vertices[i * squareVertCount + 0] = { static_cast<float>(x),		topLeft,		static_cast<float>(z),		0.0f, 0.0f };	//Topleft
					vertices[i * squareVertCount + 1] = { static_cast<float>(x),		bottomLeft,		static_cast<float>(z + 1),	0.0f, 1.0f };	//Bottomleft
					vertices[i * squareVertCount + 2] = { static_cast<float>(x + 1),	topRight,		static_cast<float>(z),		1.0f, 0.0f };	//Topright

					vertices[i * squareVertCount + 3] = { static_cast<float>(x + 1),	topRight,		static_cast<float>(z),		1.0f, 0.0f };	//Topright
					vertices[i * squareVertCount + 4] = { static_cast<float>(x),		bottomLeft,		static_cast<float>(z + 1),	0.0f, 1.0f };	//Bottomleft
					vertices[i * squareVertCount + 5] = { static_cast<float>(x + 1),	bottomRight,	static_cast<float>(z + 1),	1.0f, 1.0f };	//BottomRight
				}
			}
		}

		m_renderer->CreateVertexBuffer(m_assetName, RENDERTYPE_TERRAIN, vertices, &m_size);
		m_renderer->InitializeTextureArray(m_assetName, 1);
		m_renderer->CreateTexture(m_assetName, texture, 0);

		delete[] vertices;
		vertices = NULL;
	}

	void Terrain::Render() {
		m_renderer->SetSamplerState(0, SAMP_MAGFILTER, TEXF_LINEAR);
		m_renderer->SetSamplerState(0, SAMP_MINFILTER, TEXF_LINEAR);
		m_renderer->SetFVF(true, false, false, true);
		m_renderer->SetStreamSource(0, m_assetName, 0);
		m_renderer->SetTexture(0, m_assetName, 0);
		m_renderer->DrawPrimitive(m_assetName, PT_TRIANGLELIST);
	}

	void Terrain::Release() {
		m_renderer->Release(m_assetName);
	}
}