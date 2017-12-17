#ifndef SKYBOX_H
#define SKYBOX_H

#include "std.h"
#include "DirectX9\Direct3D.h"
#include "Asset.h"

namespace se {

	class Skybox : public AbstractAsset {
	public:
		void Create();
		void Load();
		void Process();
		void Release();
	private:
		LPDIRECT3DCUBETEXTURE9 m_map;
		LPDIRECT3DSURFACE9 m_face;


	};

}

#endif