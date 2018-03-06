#ifndef RENDERER_H
#define RENDERER_H

#include <Windows.h>
#include <string>
#include "Vector3.h"

namespace se {

	///
	/// A vertex you can use to create an array to pass to CreateVertexBuffer.
	///
	struct Vertex {
		float x;
		float y;
		float z;
		float tu;
		float tv;
	};

	///
	/// A type which you can pass to indicate what type of rendering you want to use.
	///
	enum RenderType {
		RENDERTYPE_MESH,
		RENDERTYPE_TERRAIN,
		RENDERTYPE_SKYBOX
	};

	///
	/// With this interface you can create your own renderer if you'd like.
	///
	class AbstractRenderer {
	public:
		///
		/// For initializing a renderer.
		///
		virtual void Create(int width, int height) = 0;
		///
		/// For updating with the created renderer.
		///
		virtual void Update(float delta) = 0;
		///
		/// For rendering with the created renderer.
		///
		virtual void Render(const std::string &bufferName) = 0;
		///
		/// For processing other data like setting the transformations to a device.
		///
		virtual void Process() = 0;
		///
		/// For releasing whatever needs releasing.
		///
		virtual void Release() = 0;
		///
		/// For releasing a single thing of whatever needs releasing.
		///
		virtual void Release(const std::string &bufferName) = 0;
		///
		/// Initialize an array for creating a texture with CreateTexture to a given buffer.
		///
		virtual void InitializeTextureArray(const std::string &bufferName, int size) = 0;
		///
		/// Create a buffer with a given vertices array, you can differentiate with RenderType, size is there for primitivecount.
		///
		virtual void CreateVertexBuffer(const std::string &bufferName, RenderType type, Vertex *vertices, Vector3i *size = nullptr) = 0;
		///
		/// Create a texture to the given buffer, the texture array of the given buffer needs to be initialized with InitializeTextureArray.
		///
		virtual void CreateTexture(const std::string &bufferName, const std::string &path, int id) = 0;
		///
		/// Create a mesh with a pipeline.
		///
		virtual void CreateMesh(const std::string &bufferName, const std::string &path) = 0;
		///
		/// Set the position and rotation for the screen view.
		///
		virtual void SetViewTransform(Vector3f position, Vector3f rotation) = 0;
		///
		/// Get the current axes of the view.
		///
		virtual Vector3f GetViewAxes() = 0;
	};

}

#endif