#ifndef ENGINE_H
#define ENGINE_H

#include <Windows.h>
#include <string>
#include "std.h"

SE_BEGIN_NAMESPACE

SE_API void StartEngine(const std::string& title, HINSTANCE hInstance, int nCmdShow, int width, int height);

SE_END_NAMESPACE

#endif