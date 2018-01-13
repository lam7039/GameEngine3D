#ifndef RENDERER_H
#define RENDERER_H

#include "std.h"
#include <Windows.h>

namespace se {

	class AbstractRenderer {
	public:
		virtual void Create(HWND hWnd) = 0;
		virtual void Update(float delta) = 0;
		virtual void Render() = 0;
		virtual void Release() = 0;
	};

}

#endif