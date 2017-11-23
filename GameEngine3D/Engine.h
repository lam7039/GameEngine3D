#ifndef ENGINE_H
#define ENGINE_H

#include "std.h"

SE_BEGIN_NAMESPACE

SE_API void LogDebug(const std::string& message);
SE_API void StartEngine(HINSTANCE hInstance, int nCmdShow, const std::string &title);
SE_API int EnterLoop(const std::function<void()> &start, const std::function<void()> &stop);

SE_END_NAMESPACE

#endif