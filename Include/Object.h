#ifndef OBJECT_H
#define OBJECT_H

#include "std.h"
#include "Vector3.h"

SE_BEGIN_NAMESPACE

class SE_API Object {
public:
	Object();
	void Init(const std::string &filename);
	void SetRotation(float x, float y, float z);
	void SetPosition(float x, float y, float z);
	virtual void Update(float delta);
	virtual void Render();
	Vector3<float> GetPosition();
	Vector3<float> GetRotation();
	std::string GetFilename();
protected:
	std::string m_filenameMesh;
	Vector3<float> m_position;
	Vector3<float> m_rotation;
};

SE_END_NAMESPACE

#endif