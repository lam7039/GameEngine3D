#pragma once

#ifdef GAMEENGINE3D_EXPORTS
# define SE_API __declspec(dllexport)
#else
# define SE_API __declspec(dllimport)
#endif

#include <string>

#define BEGIN_NAMESPACE			namespace se {
#define END_NAMESPACE			}

