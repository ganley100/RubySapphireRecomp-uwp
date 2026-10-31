// Minimal launcher window (Win32) — builds cleanly in GitHub Actions.
// Named RubyLauncher; later can be packaged as MSIX / swapped for full UWP.
//
// Title: RubyRecomp Launcher
// Esc or close button exits.

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>

static const wchar_t kClassName[] = L"RubyLauncherClass";
static const wchar_t kTitle[] = L"RubyRecomp Launcher";

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rc;
        GetClientRect(hwnd, &rc);
        HBRUSH brush = CreateSolidBrush(RGB(26, 26, 46));
        FillRect(hdc, &rc, brush);
        DeleteObject(brush);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(255, 215, 94));
        DrawTextW(hdc, L"RubyRecomp\nUWP / Xbox launcher shell\n\n(Esc to quit)",
                  -1, &rc, DT_CENTER | DT_VCENTER | DT_WORDBREAK);
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            PostQuitMessage(0);
            return 0;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = kClassName;
    RegisterClassExW(&wc);

    HWND hwnd = CreateWindowExW(
        0, kClassName, kTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 960, 540,
        nullptr, nullptr, hInstance, nullptr);
    if (!hwnd) return 1;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return (int)msg.wParam;
}
