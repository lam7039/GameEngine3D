#ifndef DIRECTXSKYBOX_H
#define DIRECTXSKYBOX_H

#include "std.h"
#include "DirectX9\Direct3D.h"
#include "Skybox.h"
#include "Asset.h"
#include "Debug.h"
#include "Transform.h"

namespace se {

	class Skybox : public AbstractSkybox {
	public:
		Skybox();
		void Create(Transform3f transform, const std::string &src) override;
		void Process() override;
		void Release() override;
		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);
	private:
		//LPD3DXMESH m_mesh;
		//LPDIRECT3DCUBETEXTURE9 m_map;
		Debug m_logger;
		Transform3f m_transform;

		LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;
		LPDIRECT3DTEXTURE9 m_texture;

		int m_faceCount;

		D3DXMATRIX m_matRotate;
		D3DXMATRIX m_matTranslate;
	};

}

#endif