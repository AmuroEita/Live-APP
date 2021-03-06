#pragma once

class CCommonPopupWindow :public DuiLib::WindowImplBase
{
public:
    static CCommonPopupWindow*New();
    //INotifyUI
public:
    virtual void Notify(DuiLib::TNotifyUI& msg);
    virtual void InitWindow();
    virtual void OnFinalMessage(HWND hWnd);
    virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, bool& /*bHandled*/);
    template<class CtrlType>
    CtrlType *FindControl(LPCWSTR lpszName)
    {
        return static_cast<CtrlType*>(m_PaintManager.FindControl(lpszName));
    }

    void SetWindowClassName(LPCWSTR lpszName);
    void SetSkinFile(LPCWSTR lpszFileName);
    void SetCallback(
        std::function<void(DuiLib::TNotifyUI&)> on_notify,
        std::function<void(void)> on_init_window,
        std::function<bool(UINT, WPARAM, LPARAM)> on_hanle_msg,
        std::function<void(void)> on_closed
    );
    void SetUserData(DWORD dwUser) { dwUserData = dwUser; }
    DWORD GetUserData() { return dwUserData; }
    
    void SetCtrlEnable(LPCWSTR lpszName, bool b);
    void SetCtrlVisible(LPCWSTR lpszName, bool b);
    bool GetCtrlEnable(LPCWSTR lpszName);
    bool GetCtrlVisible(LPCWSTR lpszName);

    void SetCtrlAttribute(LPCWSTR lpszName, std::function<void(DuiLib::CControlUI*)> set_fun);
    //CWindowWndc
protected:
    CCommonPopupWindow();
    virtual LPCTSTR GetWindowClassName() const;
    UINT GetClassStyle() const { return CS_DBLCLKS; }

    virtual DuiLib::UILIB_RESOURCETYPE GetResourceType() const;
    virtual DuiLib::CDuiString GetSkinFile();
   // virtual LPCTSTR GetResourceID() const;

private:
    CString strWinClsName;
    CString strSkinFile;
    std::function<void(DuiLib::TNotifyUI&)> on_notify;
    std::function<void(void)> on_init_window;
    std::function<bool(UINT, WPARAM, LPARAM)> on_hanle_msg;
    std::function<void(void)> on_closed;
    DWORD dwUserData;
};
