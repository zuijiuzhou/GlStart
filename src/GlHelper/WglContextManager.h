#pragma once
#include <Windows.h>

namespace GlHelper
{
    class WglContextManager
    {
    public:
        static HGLRC CreateByHwnd(
            HWND hWnd,
            int major, int minor, int core);

        static HGLRC CreateByBitmap(void** color_buffer, int width, int height, int major, int minor, int core);
    };
}
