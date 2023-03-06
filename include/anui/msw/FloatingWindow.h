#pragma once
#include <anui/msw/windef.h>

class MSWFloatingWindow : public FloatingWindowBase {
public:
    MSWFloatingWindow(WindowProps props = WindowProps());


private:

    static anuiLRESULT handleMsgThunk(anuiHWND hwnd,
        anuiUINT msg, anuiWPARAM wParam, anuiLPARAM lParam);


    static anuiLRESULT handleMsgSetup(anuiHWND hwnd,
        anuiUINT msg, anuiWPARAM wParam, anuiLPARAM lParam);

    anuiLRESULT handleMsg(anuiHWND hwnd,
        anuiUINT msg, anuiWPARAM wParam, anuiLPARAM lParam);


    anuiHWND m_Wnd;

    class WindowClass {
    public:

        static const wchar_t* getName() { return s_ClassName; }
        static anuiHINSTANCE getInstance() { return s_WndClass.m_Instance; }

    private:
        WindowClass();
        ~WindowClass();

        anuiHINSTANCE m_Instance;
        static WindowClass s_WndClass;
        static constexpr const wchar_t* s_ClassName = L"WINDOWCLASS";
    };


};

#include <anui/msw/winundef.h>