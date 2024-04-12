#include "Arrays.h"

#define ArrayImpl IntArray
#include "ArrayImpl.cpp"
#undef ArrayImpl
#define ArrayImpl FloatArray
#include "ArrayImpl.cpp"
#undef ArrayImpl
#define ArrayImpl Vec2fArray
#include "ArrayImpl.cpp"
#undef ArrayImpl
#define ArrayImpl Vec3fArray
#include "ArrayImpl.cpp"
#undef ArrayImpl
#define ArrayImpl Vec4fArray
#include "ArrayImpl.cpp"
#undef ArrayImpl