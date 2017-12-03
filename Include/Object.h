#ifndef OBJECT_H
#define OBJECT_H

#include "std.h"
#include "Mesh.h"
//#include "Vector3.h"

SE_BEGIN_NAMESPACE

class Object {
	//TODO: init should go in protected for so you can only initialize when inheriting
public:
	Object();
	SE_API void Init(const std::string &filename);
	void SetRotation(float x, float y, float z);
	void SetPosition(float x, float y, float z);
	virtual void Update(float delta);
	virtual void Render();
	std::string GetFilename();
protected:
	std::string m_filename;
	//Vector3<float> m_position;
	//Vector3<float> m_rotation;
	float m_posX;
	float m_posY;
	float m_posZ;
	float m_rotX;
	float m_rotY;
	float m_rotZ;
	Mesh *m_mesh;
private:
	D3DXMATRIX m_matRotate;
	D3DXMATRIX m_matTranslate;
};

SE_END_NAMESPACE

#endif