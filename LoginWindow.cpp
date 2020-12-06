#include "stdafx.h"
#include "LoginWindow.h"
#include "../NetTask/PicTransTask.h"
#include "MsgBox/DuiCloseMessageBox.h"
#include "../build/version.h"
#include "../baseclass/urlencode.h"
#include "../baseclass/RsaEncrypt.h"
#include "RsaPublic.h"
#include "./NetTask/PicTransTask.h"
#include "AccListMgr.h"
// http://weijian-api-qadrm.mtq.tvm.cn/api/user/login
//{"type":"password", "username" : "tvm", "password" : "8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92"}

#include <string>

#pragma warning( disable: 4996 ) //eg. warning C4996: 'strcpy': This function or variable may be unsafe

CLoginWindow::CLoginWindow(void)
    : m_bIsCancel(false)
{
	m_pCloseBtn = NULL;

	m_pEditAcc = NULL;
	m_pEditPwd = NULL;
	
	m_pLogin = NULL;
}

CLoginWindow::~CLoginWindow(void)
{
}

void CLoginWindow::InitWindow()
{
	m_pCloseBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"closebtn"));
	m_pEditAcc = static_cast<CEditUI*>(m_PaintManager.FindControl(L"EditAcc"));
	m_pEditPwd = static_cast<CEditUI*>(m_PaintManager.FindControl(L"EditPassword"));
	m_pLogin = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"loading"));
    
	m_pBtnRegister = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"BtnRegister")); 
  
	m_pAccCombox = static_cast<CComboBoxUI*>(m_PaintManager.FindControl(L"acccombox"));

	 //��������հ׵�����ҳ�棬����ֻ��Ϊ�˱ܿ�cef����֪©��
    //����cef��©�����������£�
    //cef�ڲ��и�FontFamilyCache��Դ�����κ�һ��Profile(webrequest�����һ�����࣬��webҳ�������������ͬ)�����һ��loadurlʱ��������shutshowʱ���٣�ҵ����Ϊ�������Ѵ����������������Profile�����֮ΪProfile��C
    //FontFamilyCache�ڹ��캯���л���Profile��C����ָ���ַΪkeyֵ��������Ϊӳ���ŵ�content::NotificationService��������
    //�κ�һ��Profile��������ʱ��������������ͨ��thisָ���ַ���ҵ�FontFamilyCache���󣬲�����Observe֪ͨ��һ�������ֻ��Profile��C���ҵ�FontFamilyCache�������ֻ֪ͨ�ᴥ��һ�Σ������ڶ��α�������쳣
    //������һ���������Profile��C���ٺ󣬺���������Profile����ʹ����Profile��C�ͷų������ڴ��ַ������������ΪProfile��T��
    //����Profile��T������ʱ������ͨ��thisָ���ַ�ٴ��ҵ�FontFamilyCache���󣬲����ٴδ���Observe֪ͨ��������������ӿհ�ҳ����Ϊ�˹���������
    //��ԭ���ǣ�
    //�ڳ����������ÿհ�ҳȥ��������FontFamilyCache��Դ��֮��פ�����ڣ�ֱ���رճ�������٣�����һ���͹����FontFamilyCache��Observe��δ�������

	//HICON h = ::LoadIcon(m_PaintManager.GetInstance(), MAKEINTRESOURCE(IDI_SACMAIN));

	SetIcon(IDI_ICON1);

	SetWindowTextW(m_hWnd, App_Name);
}


LRESULT CLoginWindow::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	return __super::OnSysCommand(uMsg, wParam, lParam, bHandled);
}

LRESULT CLoginWindow::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (uMsg == WM_LBUTTONDBLCLK || uMsg ==  WM_NCLBUTTONDBLCLK)
	{
		bHandled = true;
		return 0;
	}
	return 0;
}


DuiLib::CDuiString CLoginWindow::GetSkinFolder()
{
	return L"skin\\";
}

DuiLib::CDuiString CLoginWindow::GetSkinFile()
{
	return L"login.xml";
}

DuiLib::UILIB_RESOURCETYPE CLoginWindow::GetResourceType() const
{
	return UILIB_FILE;
}

bool CLoginWindow::CheckAccPW()
{
    CString strPW = m_pEditPwd->GetText();
    CString strAcc = m_pEditAcc->GetText();
    strAcc.Trim();
    if (strPW.IsEmpty() || strAcc.IsEmpty())
    {
        CDuiString str;
        CPaintManagerUI::GetLangText(L"#TIP_USERACOUNT_EMPTY", str);
        ShowTip(str);
        return false;
    }

    return true;
}

void CLoginWindow::ExitSAC()
{
	ShowWindow(false);
	PostQuitMessage(0);
}

void CLoginWindow::Notify(TNotifyUI& msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (msg.pSender == m_pCloseBtn)
		{
			ShowWindow(false);
			PostQuitMessage(0);
		}
		else if (msg.pSender == m_pLogin )
		{
			//OnButtonLogin();
			ShowWindow(false);
			if (NULL == m_pMainWindow)
			{
				m_pMainWindow = new CMainframe;
				m_pMainWindow->Create(NULL, L"mainframe", UI_WNDSTYLE_FRAME, 0L);
			}

			m_pMainWindow->ShowWindow(true);
			m_pMainWindow->CenterWindow();
			if (NULL == m_pRoom)
			{
				m_pRoom = new CRoomWindow;
				m_pRoom->Create(NULL, L"roomwindow", UI_WNDSTYLE_FRAME, 0L);
			}

			m_pRoom->ShowWindow(true);
			m_pRoom->CenterWindow();
		}
        else if (msg.pSender == m_pBtnRegister)
        {
             ::ShellExecute(NULL, L"open", RegisterURL, NULL, NULL, SW_SHOWNORMAL);
        }
	}
}

void CLoginWindow::OnButtonLogin()
{
	if (!CheckAccPW())
		return;
	
	CString strAcc = m_pEditAcc->GetText();
	CString strPwd = m_pEditPwd->GetText();

	LoginWithUserNamePwd( strAcc, strPwd, MSG_LOGIN_THIRDPART_HTTP );
}

void CLoginWindow::ShowTip(LPCWSTR lpText, bool bErr)
{
	::MessageBox(m_hWnd, lpText, L"��ʾ", MB_OK);
}

void CLoginWindow::LoginFail(LPCWSTR lpcontect)
{
	ShowTip(lpcontect);
}

void CLoginWindow::checkUpdate()
{
	//CString token = LoginUserDataMgr().GetInstance()->GetToken();
	//CUTFString utfToken((LPCTSTR)token);

	//string strHeader = "Authorization: Bearer ";
	//strHeader += utfToken.UTF8();
	string accept = "accept: application/json";
	std::list<std::string> header;
	//header.push_back(strHeader);
	header.push_back(accept);

	CString strurl;
	strurl.Format(L"%s?version=%s", checkUpdateURL, VERSION_WSTRING_BUILD);
	
	//strurl.Format(L"%s?version=1.01.0.04", checkUpdateURL);

	CHttpGetHeaderTask::ReqHttp(strurl.GetBuffer(), m_hWnd, MSG_CheckUpdate, header);
}

DuiLib::CDuiString CLoginWindow::GetZIPFileName() const
{
	return L"UISkin.zip";
}

void CLoginWindow::LoginWithUserNamePwd(LPCWSTR lpacc, LPCWSTR lppw, int nCallBackMsg)
{
	if ( lstrcmpW(lpacc, L"") == 0 || lstrcmpW(lppw, L"") == 0 )
	{
		lpacc = m_pEditAcc->GetText();
		lppw = m_pEditPwd->GetText();
	}

	CUTFString utfAcc((LPCTSTR)lpacc);
	CUTFString utfPwd((LPCTSTR)lppw);

	CStringA strSecretKey = utfPwd.UTF8();

	char buf[2];
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, strSecretKey, strSecretKey.GetLength());
	SHA256_Final(hash, &sha256);
	
	std::string strStr = strSecretKey.GetString();

	std::string NewString;
//	SHA256(reinterpret_cast<unsigned char*>(strStr.c_str()), strSecretKey.GetLength(), NewString);

	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(buf, "%02x", hash[i]);
		NewString = NewString + buf;
	}

	Json::Value root;
	SetJsonValue(root, "type", "password" );
	SetJsonValue(root, "username", utfAcc.UTF8());
	SetJsonValue(root, "password", NewString.c_str());

	CStringA strA;
	JsonWriteToStringUTF8(root, strA);

	string accept = "Content-Type: application/json";
	std::list<std::string> header;
	header.push_back(accept);

	CHttpSimplePostTask::ReqHttp(loginURl, m_hWnd, nCallBackMsg, strA.GetString(), header);
}

CControlUI* CLoginWindow::CreateControl(LPCTSTR pstrClass)
{
// 	if (_tcsicmp(pstrClass, _T("CircleImage")) == 0)
// 	{
// 		return new CCircleImageUI;
// 	}
	return __super::CreateControl(pstrClass);
}


void CLoginWindow::OnMsgReturn(TNotifyUI& msg)
{
	if (msg.pSender == m_pEditPwd)
	{
		OnButtonLogin();

        //�ӳٴ�����¼��������ǰ���������룬���س����󣬻����е���¼��״̬��Ȼ���������������ʧ�������Ե���Щͻأ
        //���������ԭ���ǣ�����һ���Ĵ����У��ᴥ������������ʧȥ���㶯����Ȼ������������༭����CEditWnd����WM_CLOSE��Ϣ���ٴ��ڣ������ٶ����첽���ӳ٣�����������������
        //����������Ϣ�첽������¼�����Ա�����������
	}
}

void CLoginWindow::OnMsgEnterTab(TNotifyUI& msg)
{
	if ((::GetKeyState(VK_SHIFT) & 0x8000) != 0)
	{
		if (msg.pSender == m_pEditAcc)
		{
			m_pEditPwd->SetFocus();
			m_pEditPwd->SetSelAll();
		}
	}
	else
	{
		if (msg.pSender == m_pEditAcc)
		{
			m_pEditPwd->SetFocus();
			m_pEditPwd->SetSelAll();
		}
	}
}

void CLoginWindow::OnFinalMessage(HWND hWnd)
{
    __super::OnFinalMessage(hWnd);
    //���������ڣ�cef��Դ���������ͷţ���Ⱦ���̲��������˳�
    //SAFE_RELEASE_WND(m_pMainWindow, true);
}

void CLoginWindow::LoadAccount()
{
	WCHAR wcPath[MAX_PATH] = { 0 };
	SHGetSpecialFolderPath(NULL, wcPath, CSIDL_APPDATA, FALSE);
    PathAppend(wcPath, PROGRAM_APPDATA_FLODER_NAME);
	PathAppend(wcPath, USER_ACC_SAVE_PATH);

	m_AccListMgr.LoadAcc(wcPath);
	
}

void CLoginWindow::SaveAccount(LPCTSTR lpAcc, LPCWSTR lppw)
{
	if (lstrcmpW(lpAcc, L"") == 0 || lstrcmpW(lppw, L"") == 0 )
	{
		return;
	}

	PACCATTI pAcc = m_AccListMgr.FindByAccount(lpAcc);
	if(NULL == pAcc)
	{ 
		pAcc = new ACCATTI();
		if (FAILED(m_AccListMgr.AddAccount(pAcc)))
		{ 
			delete pAcc;
			return;
		}
	}

	pAcc->strAcc = lpAcc;
	pAcc->strPasswd = lppw;

	WCHAR wcPath[MAX_PATH] = { 0 };
	SHGetSpecialFolderPath(NULL, wcPath, CSIDL_APPDATA, FALSE);
    PathAppend(wcPath, PROGRAM_APPDATA_FLODER_NAME);
    PathAppend(wcPath, USER_ACC_SAVE_PATH);

	m_AccListMgr.SaveAcc(wcPath);
}

std::string Byte2Hex(char* bytes, int bytelength)
{
	string str("");
	string str2(STR_FORMAT_CONST);
	for (int i = 0; i < bytelength; i++) {
		int b;
		b = 0x0f & (bytes[i] >> 4);
		char s1 = str2.at(b);
		str.append(1, str2.at(b));
		b = 0x0f & bytes[i];
		str.append(1, str2.at(b));
		char s2 = str2.at(b);
	}
	return str;
}