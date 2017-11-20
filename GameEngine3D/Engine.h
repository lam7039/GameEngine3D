#ifndef ENGINE_H
#define ENGINE_H

#include "std.h"

SE_BEGIN_NAMESPACE

SE_API void StartEngine(const HINSTANCE &hInstance, const int &nCmdShow, const std::string &title);
SE_API int EnterLoop(void (*start)(), void (*stop)());
SE_API void LogDebug(const std::string& message);

SE_END_NAMESPACE

#endif