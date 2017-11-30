#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "std.h"
#include "Mesh.h"
#include <vector>

//TODO: use a map and call, call it in object and destroy it there too, not in the manager?
SE_BEGIN_NAMESPACE

class ResourceManager {
public:
	void Init(LPDIRECT3DDEVICE9 device);
	void AddMesh(std::string path);
	std::vector<Mesh> GetMeshes();
	void Clean();
private:
	LPDIRECT3DDEVICE9 m_device;
	std::vector<Mesh> m_meshes;
};

SE_END_NAMESPACE

#endif