#pragma once

#ifdef GAMEENGINE3D_EXPORTS
# define SE_API __declspec(dllexport)
#else
# define SE_API __declspec(dllimport)
#endif

#define SE_BEGIN_NAMESPACE		namespace se {
#define SE_END_NAMESPACE		}
