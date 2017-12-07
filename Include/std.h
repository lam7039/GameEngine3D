#pragma once

#ifdef _WIN32 || __CYGWIN__
# define SE_EXPORT __declspec(dllexport)
# define SE_IMPORT __declspec(dllimport)
#else
# if __GNUC__ >= 4
#  define SE_EXPORT __attribute__ ((visibility ("default")))
#  define SE_IMPORT __attribute__ ((visibility ("default")))
# else
#  define SE_EXPORT
#  define SE_IMPORT
# endif
#endif

#ifdef GameEngine3D_EXPORTS
# define SE_API SE_EXPORT
#else
# define SE_API SE_IMPORT
# endif

#include <string>
#include <functional>
#include <map>
#include <vector>

#define SE_BEGIN_NAMESPACE namespace se {
#define SE_END_NAMESPACE }