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
		std::unordered_map<std::string, Mesh*> GetMeshes();
	private:
		static AssetLoader *m_instance;
		std::unordered_map<std::string, Mesh*> m_meshes;
		AssetLoader();
		~AssetLoader();
	};

}

#endif