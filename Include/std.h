#pragma once

#ifdef GameEngine3D_EXPORTS
# define SE_API __declspec(dllexport)
#else
# define SE_API __declspec(dllimport)
#endif

#include <string>
#include <functional>
#include <map>
#include <vector>

#define SE_BEGIN_NAMESPACE namespace se {
#define SE_END_NAMESPACE }