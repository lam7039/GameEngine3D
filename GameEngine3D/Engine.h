#ifndef ENGINE_H
#define ENGINE_H

#include <Windows.h>
#include <string>
#include "std.h"

SE_BEGIN_NAMESPACE

SE_API void StartEngine(HINSTANCE hInstance, int nCmdShow, std::string title);

SE_END_NAMESPACE

#endif