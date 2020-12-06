/************************************************************************/
/* Cef3 Window manager							                        */
/* author : Qiuyoukun							                        */
/* date : 2019-08-01							                        */
/************************************************************************/
#pragma once

class CCefContainerWnd;

class CCefUIBase : public CControlUI, public IBrowserEvent
{
protected:
    static CString MakeSafeJSString(LPCWSTR szStr);

public:
    CCefUIBase();
    virtual ~CCefUIBase();

    void AttachContainer(CCefContainerWnd * pContainer);
    virtual bool CreateBrowser(LPCTSTR szName = NULL, LPRECT rcBrowser = NULL, LPCWSTR lpcookiepath = NULL, LPCWSTR lpcookieServer = NULL, LPCWSTR lpdomain = NULL );
    virtual bool CloseBrowser();
    const HWND GetBrowserHWND() const;
	bool CloseBrowserOther();
    bool IsCalledClose() { return m_bCalledClose; };

	void GetCookie(LPCTSTR lpurl, LPCTSTR strcookiepath);

protected:
    void NotifyCreated();
    void NotifyClosed();

protected:
    HWND m_hBrowerWnd;
    CComPtr<ICefBrowser> m_spCefWebBrowser;
    DWORD	m_nTimeCreate;
    __int64	m_nLoadSize;

private:
    CCefContainerWnd * m_pContainer;
    bool m_bCalledClose;
};
    
class CCefContainerWnd : public WindowImplBase
{
public:
    CCefContainerWnd(bool bAutoDelete = true);
    virtual ~CCefContainerWnd();

	virtual void OnCefCreated(CCefUIBase * pCef);
    //���Ϊ�Ӵ��ڵĻ���ֻ�и��������ٺ�Żᴥ������Ϣ
    virtual void OnCefClosed(CCefUIBase * pCef);
    //���ڹر�
    virtual bool IsClosing();
    //��ȫ�رգ��رճɹ�����лص�֪ͨ
    virtual void SafeClose(std::function<void()> funClosed);
    
    void AddCef(CCefUIBase * pCef);
    bool RemoveCef(CCefUIBase * pCef, bool bEnumChild = false);
    //������ĸ��ӹ�ϵ�����߼����ӹ�ϵ���䴰�ڲ��޸��ӹ�����������ڴ��ڸ��ӹ�ϵ����bRealChild����Ϊtrue
    void AddChildCefContainer(CCefContainerWnd* pChild, bool bRealChild = false);
    void RemoveChildCefContainer(CCefContainerWnd* pChild);

    void WaitLastMessageLoop(int iCount, int iDelay);

    // override WindowImplBase
    virtual LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) override;
    virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)override;
    virtual void OnFinalMessage(HWND hWnd)override;
    virtual CControlUI* CreateControl(LPCTSTR pstrClass)override;
protected:
    virtual void DoClose() {};
    virtual void OnChildClosed(CCefContainerWnd* pChild, bool bReal);

private:
    void _SetFather(CCefContainerWnd* pFather, bool bReal = false);
    bool _EnumAndCloseCef(bool bEnumChild = false);
    CCefUIBase * _EnumUnCloseCef(bool bEnumChild = false);
    CCefUIBase * _GetUnCloseCef();
    bool _IsRealFather(CCefContainerWnd* pFather);
    void _TryFinalClose();

private:
    enum SafeCloseStep
    {
        sc_nomal = 0,
        sc_doClose,
        sc_closing,
    };

private:
    friend class CCefWndWrapManager;
    std::vector<CCefUIBase*> m_vCefList;
    std::vector<CCefContainerWnd*> m_vChilds;
    bool m_bFatherReal;             //�游����
    bool m_bAutoDelete;
    CCefContainerWnd * m_pFather;
    std::function<void()> m_funClosed;

protected:
    SafeCloseStep m_eCloseStep;
};

class CCefWndWrapManager
{
public:
    CCefWndWrapManager(void);
	virtual ~CCefWndWrapManager(void);

    static void Init();
    static void UnInit();

    static void AddItem(CCefContainerWnd * pItem, bool bAsyn = true);
    static void RemoveItem(CCefContainerWnd * pItem, bool bAsyn = true);

private:
    static LRESULT __stdcall _MsgWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static const HWND _CreateWnd(const WNDPROC pfnWndProc, void * pData, const wchar_t * pwszWndName = NULL, const wchar_t * pwszClassName = NULL);
    static void _AddItem(CCefContainerWnd * pItem);
    static void _RemoveItem(CCefContainerWnd * pItem);

private:
    static HWND m_hMgrWnd;
    static std::vector<CCefContainerWnd*> m_vWrapList;
};
