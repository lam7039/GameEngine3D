#ifndef ENGINE_H
#define ENGINE_H

#include <Windows.h>
#include <string>
#include <iostream>

#include "std.h"

SE_BEGIN_NAMESPACE

SE_API void StartEngine(HINSTANCE hInstance, int nCmdShow, std::string title);
SE_API int EnterLoop(void (*start)(), void (*stop)());

SE_END_NAMESPACE

#endif