#include "Arrays.h"

#define ArrayImpl IntArray
#include "ArrayImpl.cppt"
#undef ArrayImpl
#define ArrayImpl FloatArray
#include "ArrayImpl.cppt"
#undef ArrayImpl
#define ArrayImpl Vec2fArray
#include "ArrayImpl.cppt"
#undef ArrayImpl
#define ArrayImpl Vec3fArray
#include "ArrayImpl.cppt"
#undef ArrayImpl
#define ArrayImpl Vec4fArray
#include "ArrayImpl.cppt"
#undef ArrayImpl