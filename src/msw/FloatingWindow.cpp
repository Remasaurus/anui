#include <anui/FloatingWindow.h>
#include <string_view>
#include <anui/msw/Windows.h>
#include <anui/msw/windef.h>

#define WND(hwnd) static_cast<HWND>(hwnd)
#define INSTANCE(instance) static_cast<HINSTANCE>(instance)

using namespace anui;

// WindowClass
FloatingWindow::WindowClass FloatingWindow::WindowClass::s_WndClass;

FloatingWindow::WindowClass::WindowClass() {
    m_Instance = GetModuleHandle(0);

    WNDCLASSEX wndClass = {};
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.lpszClassName = getName();
    wndClass.lpfnWndProc = 
        reinterpret_cast<WNDPROC>(FloatingWindow::handleMsgThunk); // Practically casts to the same type
    
    wndClass.hInstance = INSTANCE(m_Instance);
    wndClass.style = CS_OWNDC;
    wndClass.cbWndExtra = sizeof(void*);

    RegisterClassEx(&wndClass);
}

FloatingWindow::WindowClass::~WindowClass() {
    UnregisterClass(getName(), static_cast<::HINSTANCE>(m_Instance));
}


// Floating Window

FloatingWindow::MSWFloatingWindow(WindowProps props) {

    // windowrect
    RECT wr{};
    wr.left = 0;
    wr.right = 100;
    wr.top = 0;
    wr.bottom = 100;

    AdjustWindowRectEx(&wr, WS_OVERLAPPEDWINDOW, false, 0);
    auto m_Width = wr.right - wr.left;
    auto m_Height = wr.bottom - wr.top;

    m_Wnd = CreateWindowEx(
        0,                              // Optional window styles.
        WindowClass::getName(),         // Window class
        props.label.data(),            // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        wr.left, wr.top, m_Width, m_Height,

        NULL,       // Parent window    
        NULL,       // Menu
        static_cast<HINSTANCE>(WindowClass::getInstance()),   // Instance handle
        this        // Additional application data
    );

    ShowWindow(WND(m_Wnd), SW_SHOW);
}





// WIN32 MESSAGES


anuiLRESULT FloatingWindow::handleMsgSetup(anuiHWND hwnd,
    anuiUINT msg, anuiWPARAM wParam, anuiLPARAM lParam) {
    FloatingWindow* ptr = reinterpret_cast<FloatingWindow*>(GetWindowLongPtr(WND(hwnd), 0));

    return ptr->handleMsg(hwnd, msg, wParam, lParam);
}



anuiLRESULT FloatingWindow::handleMsgThunk(anuiHWND hwnd,
    anuiUINT msg, anuiWPARAM wParam, anuiLPARAM lParam) {

    switch (msg) {
    case WM_NCCREATE: {
        const CREATESTRUCT* const create = reinterpret_cast<CREATESTRUCT*>(lParam);
        if (create->lpCreateParams) {
            FloatingWindow* const wnd = static_cast<FloatingWindow*>(create->lpCreateParams);
            SetWindowLongPtr(WND(hwnd), 0, reinterpret_cast<LONG_PTR>(wnd));
            SetWindowLongPtr(WND(hwnd),
                GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(FloatingWindow::handleMsgSetup));

            return wnd->handleMsg(hwnd, msg, wParam, lParam);
        }
    }
    }

    return DefWindowProc(WND(hwnd), msg, wParam, lParam);

}


anuiLRESULT FloatingWindow::handleMsg(anuiHWND hwnd,
    anuiUINT msg, anuiWPARAM wParam, anuiLPARAM lParam) {

    return DefWindowProc(WND(hwnd), msg, wParam, lParam);

    switch (msg) {
        /*
    case WM_WINDOWPOSCHANGED: {
        WINDOWPOS* data = reinterpret_cast<WINDOWPOS*>(lParam);
        if (!(data->flags & SWP_NOMOVE)) {
            m_X = data->x;
            m_Y = data->y;
        }
        if (!(data->flags & SWP_NOSIZE)) {
            m_Width = data->cx;
            m_Height = data->cy;
        }
        break;
    }
    case WM_DESTROY: {
        if (wglGetCurrentContext() == m_GLRC) {
            wglMakeCurrent(NULL, NULL);
        }
        wglDeleteContext(m_GLRC);
        ReleaseDC(m_WND, m_DC);
        m_Closed = true;
        PostQuitMessage(0);
        return 0;
    }
    }

    if (!m_EventCallback) return DefWindowProc(hwnd, msg, wParam, lParam);

    switch (msg) {
        // Application events
    case WM_WINDOWPOSCHANGED: {
        WINDOWPOS* data = reinterpret_cast<WINDOWPOS*>(lParam);
        if (!(data->flags & SWP_NOMOVE)) {
            m_EventCallback(WindowMoveEvent(m_X, m_Y));
        }
        if (!(data->flags & SWP_NOSIZE)) {
            m_EventCallback(WindowResizeEvent(m_Width, m_Height));
        }
        return 0;
    }
    case WM_CLOSE: {
        m_EventCallback(WindowCloseEvent());
        return 0;
    }
    case WM_SETFOCUS: {
        m_EventCallback(WindowFocusEvent());
        return 0;
    }

    case WM_KILLFOCUS: {
        m_EventCallback(WindowLostFocusEvent());
        return 0;
    }

                     // Keyboard events
    case WM_KEYDOWN: {
        WORD keyFlags = HIWORD(lParam);
        m_EventCallback(KeyDownEvent(wParam, (keyFlags & KF_REPEAT) == KF_REPEAT, LOWORD(lParam)));
        return 0;
    }
    case WM_CHAR: {
        WORD keyFlags = HIWORD(lParam);
        m_EventCallback(CharEvent(wParam, (keyFlags & KF_REPEAT) == KF_REPEAT, LOWORD(lParam)));
        return 0;
    }
    case WM_KEYUP: {
        WORD keyFlags = HIWORD(lParam);
        m_EventCallback(KeyUpEvent(wParam));
        return 0;
    }

                 // Mouse events
                 // Mouse move
    case WM_MOUSEMOVE: {
        m_EventCallback(MouseMoveEvent(LOWORD(lParam), HIWORD(lParam)));
        return 0;
    }
                     // MouseButtonDown
    case WM_LBUTTONDOWN: {
        SetCapture(hwnd);
        m_EventCallback(MouseButtonDownEvent(1, LOWORD(lParam), HIWORD(lParam)));
        return 0;
    }
    case WM_RBUTTONDOWN: {
        m_EventCallback(MouseButtonDownEvent(2, LOWORD(lParam), HIWORD(lParam)));
        return 0;
    }
    case WM_MBUTTONDOWN: {
        m_EventCallback(MouseButtonDownEvent(3, LOWORD(lParam), HIWORD(lParam)));
        return 0;
    }
    case WM_XBUTTONDOWN: {
        m_EventCallback(MouseButtonDownEvent(3 + HIWORD(wParam), LOWORD(lParam), HIWORD(lParam)));
        return 0;
    }

                       // MouseButtonUp
    case WM_LBUTTONUP: {
        ReleaseCapture();
        m_EventCallback(MouseButtonUpEvent(1, LOWORD(lParam), HIWORD(lParam)));
        return 0;
    }
    case WM_RBUTTONUP: {
        m_EventCallback(MouseButtonUpEvent(2, LOWORD(lParam), HIWORD(lParam)));
        return 0;
    }
    case WM_MBUTTONUP: {
        m_EventCallback(MouseButtonUpEvent(3, LOWORD(lParam), HIWORD(lParam)));
        return 0;
    }
    case WM_XBUTTONUP: {
        m_EventCallback(MouseButtonUpEvent(3 + HIWORD(wParam), LOWORD(lParam), HIWORD(lParam)));
        return 0;
    }

                     // Scroll
    case WM_MOUSEWHEEL: {
        m_EventCallback(MouseScrollEvent(0, GET_WHEEL_DELTA_WPARAM(wParam),
            LOWORD(lParam) - m_X, HIWORD(lParam) - m_Y));
        return 0;
    }
    case WM_MOUSEHWHEEL: {
        m_EventCallback(MouseScrollEvent(GET_WHEEL_DELTA_WPARAM(wParam), 0,
            LOWORD(lParam) - m_X, HIWORD(lParam) - m_Y));
        return 0;
    }
    */

    default:
        return DefWindowProc(WND(hwnd), msg, wParam, lParam);
    }
}