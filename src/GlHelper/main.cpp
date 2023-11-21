#include "WglContextManager.h"

int main(int argc, char** argv){

    int w = 800, h = 600;
    void* buffer;
    GlHelper::WglContextManager::CreateByBitmap(&buffer, w, h, 3, 3, true);
    // HWND wnd;
    // HGLRC glrc = GlHelper::WglContextManager::CreateByHwnd(wnd, 3, 3, true);
    
    return 0;
}