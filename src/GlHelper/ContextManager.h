#pragma once
#include <Windows.h>

class ContextManager{
public:
    static void CreateWglContextFromHwnd(
        HWND hwnd,
        bool is_core_profile
    );
};