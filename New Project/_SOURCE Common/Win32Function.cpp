#include "../_SOURCE Common/Win32Functions.h"

LRESULT CALLBACK WindowProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            } break;
    }
    return DefWindowProc (hWnd, message, wParam, lParam);
}//if the message is WM_DESTROY, quit the window