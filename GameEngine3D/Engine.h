#ifndef ENGINE_H
#define ENGINE_H

#include "std.h"

SE_BEGIN_NAMESPACE

SE_API void StartEngine(HINSTANCE hInstance, int nCmdShow, std::string title);
SE_API int EnterLoop(void (*start)(), void (*stop)());

SE_END_NAMESPACE

#endif