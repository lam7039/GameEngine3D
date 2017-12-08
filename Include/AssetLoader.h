#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "std.h"
#include "DirectX9/DirectXMesh.h"

namespace se {

	class AssetLoader {
	public:
		void AddMesh(const std::string &path);
		void ReleaseMesh(const std::string &filename);
		static AssetLoader *GetInstance();
		std::map<std::string, Mesh*> AssetLoader::GetMeshes();
	private:
		static AssetLoader *m_instance;
		std::map<std::string, Mesh*> m_meshes;
		AssetLoader();
		~AssetLoader();
	};

}

#endif