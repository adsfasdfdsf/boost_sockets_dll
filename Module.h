#pragma once
#include "fwd.h"
#ifdef CSTMODULE_EXPORT
#ifdef _WIN32
#define CSTMODULE_API declspec(dllexport)
#else
#define CSTMODULE_API __attribute ((visibility ("default")))
#endif
#else
#ifdef _WIN32
#define CSTMODULE_API declspec(dllimport)
#else
#define CSTMODULE_API __attribute ((visibility ("default")))
#endif
#endif
CSTMODULE_API IProvider& GetProvider();