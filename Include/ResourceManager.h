#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "std.h"
#include "Mesh.h"
#include <d3dx9.h>
#include <vector>

SE_BEGIN_NAMESPACE

class ResourceManager {
public:
	void Init(LPDIRECT3DDEVICE9 device);
	void AddMesh(std::string path);
	void Render();
	void Clean();
private:
	LPDIRECT3DDEVICE9 m_device;
	std::vector<Mesh> m_meshes;
};

SE_END_NAMESPACE

#endif