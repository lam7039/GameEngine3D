#pragma once

#ifdef _WIN32 || __CYGWIN__
# include <Windows.h>
#else
# ifdef __linux__
#  include <X11/Xlib.h>
# endif
#endif

#include <string>
#include <functional>
#include <map>
#include <vector>