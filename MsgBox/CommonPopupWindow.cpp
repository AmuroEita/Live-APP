#include "stdafx.h"
#include "CommonPopupWindow.h"
//#include "../resource.h"

CCommonPopupWindow*CCommonPopupWindow::New()
{
    return new CCommonPopupWindow();
}
void CCommonPopupWindow::Notify(DuiLib::TNotifyUI& msg)
{
    if (on_notify)
        on_notify(msg);
}

void CCommonPopupWindow::InitWindow()
{
    //SetIcon(IDI_SETUP);
    if (on_init_window)
        on_init_window();
}
void CCommonPopupWindow::OnFinalMessage(HWND hWnd)
{
    if (on_closed)
        on_closed();
    delete this;
}

LRESULT CCommonPopupWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{    
    if (on_hanle_msg)
        bHandled = on_hanle_msg(uMsg, wParam, lParam);
    else
        bHandled = false;
    return 0;
}

void CCommonPopupWindow::SetWindowClassName(LPCWSTR lpszName)
{
    strWinClsName = lpszName;
}
void CCommonPopupWindow::SetSkinFile(LPCWSTR lpszFileName)
{
    strSkinFile = lpszFileName;
}
void CCommonPopupWindow::SetCallback(
    std::function<void(DuiLib::TNotifyUI&)> on_notify,
    std::function<void(void)> on_init_window,
    std::function<bool(UINT, WPARAM, LPARAM)> on_hanle_msg,
    std::function<void(void)> on_closed
)
{
    this->on_notify = on_notify;
    this->on_init_window = on_init_window;
    this->on_hanle_msg = on_hanle_msg;
    this->on_closed = on_closed;
}


void CCommonPopupWindow::SetCtrlEnable(LPCWSTR lpszName, bool b)
{
    auto pCtrl = FindControl<DuiLib::CControlUI>(lpszName);
    if (pCtrl)
        pCtrl->SetEnabled(b);
}
void CCommonPopupWindow::SetCtrlVisible(LPCWSTR lpszName, bool b)
{
    auto pCtrl = FindControl<DuiLib::CControlUI>(lpszName);
    if (pCtrl)
        pCtrl->SetVisible(b);
}
bool CCommonPopupWindow::GetCtrlEnable(LPCWSTR lpszName)
{
    auto pCtrl = FindControl<DuiLib::CControlUI>(lpszName);
    if (pCtrl)
        return pCtrl->IsEnabled();
    return false;
}
bool CCommonPopupWindow::GetCtrlVisible(LPCWSTR lpszName)
{
    auto pCtrl = FindControl<DuiLib::CControlUI>(lpszName);
    if (pCtrl)
        return pCtrl->IsVisible();
    return false;
}
void CCommonPopupWindow::SetCtrlAttribute(LPCWSTR lpszName, std::function<void(DuiLib::CControlUI*)> set_fun)
{
    auto pCtrl = FindControl<DuiLib::CControlUI>(lpszName);
    if (pCtrl)
        set_fun(pCtrl);
}
CCommonPopupWindow::CCommonPopupWindow():dwUserData(0)
{

}
LPCTSTR CCommonPopupWindow::GetWindowClassName() const
{
    return strWinClsName;
}

DuiLib::UILIB_RESOURCETYPE CCommonPopupWindow::GetResourceType() const
{
    return UILIB_FILE;
}
DuiLib::CDuiString CCommonPopupWindow::GetSkinFile()
{
    return (LPCTSTR)strSkinFile;
}
//LPCTSTR CCommonPopupWindow::GetResourceID() const
//{
//    return MAKEINTRESOURCE(IDR_ZIPRES);
//}
