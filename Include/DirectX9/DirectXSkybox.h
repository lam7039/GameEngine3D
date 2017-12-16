#ifndef SKYBOX_H
#define SKYBOX_H

#include "std.h"
#include "DirectX9\Direct3D.h"
#include "DirectX9\DirectXMesh.h"
#include "Asset.h"

namespace se {

	class Skybox : public AbstractAsset {
	public:
		void Create();
		void Load();
		void Process();
		void Release();
	private:
		Mesh *m_mesh;
		LPDIRECT3DTEXTURE9 m_texture;
	};

}

#endif