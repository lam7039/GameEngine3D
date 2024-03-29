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
	/// A type which you can pass to indicate what type of filtering you want to use.
	///
	enum TextureFilterType
	{
		TEXF_NONE = 0,					// filtering disabled (valid for mip filter only)
		TEXF_POINT = 1,					// nearest
		TEXF_LINEAR = 2,				// linear interpolation
		TEXF_ANISOTROPIC = 3,			// anisotropic
		TEXF_PYRAMIDALQUAD = 6,			// 4-sample tent
		TEXF_GAUSSIANQUAD = 7,			// 4-sample gaussian
	};

	///
	/// A type which you can pass to indicate what type of sampling you want to use.
	///
	enum SamplerStateType {
		SAMP_ADDRESSU = 1,
		SAMP_ADDRESSV = 2,
		SAMP_ADDRESSW = 3,
		SAMP_BORDERCOLOR = 4,
		SAMP_MAGFILTER = 5,
		SAMP_MINFILTER = 6,
		SAMP_MIPFILTER = 7,
		SAMP_MIPMAPLODBIAS = 8,
		SAMP_MAXMIPLEVEL = 9,
		SAMP_MAXANISOTROPY = 10,
		SAMP_SRGBTEXTURE = 11,
		SAMP_ELEMENTINDEX = 12,
		SAMP_DMAPOFFSET = 13,
	};

	///
	/// A type which you can pass to indicate what primitive type you want to use.
	///
	enum PrimitiveType {
		PT_POINTLIST = 1,
		PT_LINELIST = 2,
		PT_LINESTRIP = 3,
		PT_TRIANGLELIST = 4,
		PT_TRIANGLESTRIP = 5,
		PT_TRIANGLEFAN = 6,
	};

	enum CullMode {
		CULL_NONE = 1,
		CULL_CW = 2,
		CULL_CCW = 3,
	};

	enum FillMode {
		FM_POINT = 1,
		FM_WIREFRAME = 2,
		FM_SOLID = 3,
	};

	///
	/// With this interface you can create your own renderer if you'd like.
	///
	class AbstractRenderer {
	public:
		///
		/// For initializing a renderer.
		///
		virtual void Create(HWND hWnd, int width, int height, bool windowed, CullMode cullMode, bool lighting, bool zenable, FillMode fillMode, bool clipping) = 0;
		///
		/// For updating with the created renderer.
		///
		virtual void Update(float delta) = 0;
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
		/// Set the vertex type.
		///
		virtual void SetFVF(bool coords, bool diffuse, bool specular, bool texture) = 0;
		///
		/// Set the sampler stage state value.
		///
		virtual void SetSamplerState(int sampler, SamplerStateType samplerStateType, TextureFilterType textureFilterType) = 0;
		///
		/// Set the texture to the given buffer.
		///
		virtual void SetTexture(int stage, const std::string &bufferName, int index) = 0;
		///
		/// Set the material to the given buffer.
		///
		virtual void SetMaterial(const std::string &bufferName, int index) = 0;
		///
		/// Bind a vertex buffer to a device data stream.
		///
		virtual void SetStreamSource(unsigned int streamNumber, const std::string &bufferName, unsigned int offsetInBytes, unsigned int stride = NULL) = 0;
		///
		/// Draw the buffer, if you draw a vertexbuffer you can set a PrimitiveType.
		///
		virtual void Draw(const std::string &bufferName, PrimitiveType primitiveType = PT_TRIANGLELIST) = 0;
		///
		/// Clear the target and/or z-buffer.
		///
		virtual void Clear(bool target, bool zBuffer) = 0;
		///
		/// Set the target swapchain which to render to, sets index automatically in Present() by default.
		///
		virtual void SetRenderTarget(int index = -1) = 0;
		///
		/// Set the world transformations.
		///
		virtual void SetTransform(Vector3f position, Vector3f scale, Vector3f rotation) = 0;
		///
		/// Begin the scene on which to draw.
		///
		virtual void BeginScene() = 0;
		///
		/// End the scene on which to draw.
		///
		virtual void EndScene() = 0;
		///
		/// Present the current swapchain, by default it sets it and changes the current swapchain.
		///
		virtual void Present(int index = -1) = 0;
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