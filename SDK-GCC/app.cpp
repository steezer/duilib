#include "res/targetver.h"

#define _CRT_SECURE_NO_WARNINGS
//#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "res/resource.h"
// #include "HttpClient.h"

#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "wldap32.lib")
#pragma comment (lib, "Shell32.lib")
#pragma comment (lib, "Shlwapi.lib")
#pragma comment (lib, "httpapi.lib")
#pragma comment (lib, "crypt32.lib")

#include <objbase.h>
#include <zmouse.h>
#include <exdisp.h>
#include <vector>
#include <sstream>

#include "UIlib.h"

using namespace DuiLib;

#define WM_ADDLISTITEM WM_USER + 50
/*
* 存放第二列数据
*/
std::vector<std::string> domain;
/*
* 存放第三列数据
*/
std::vector<std::string> desc;
/*
*  线程函数中传入的结构体变量，使用线程为了使界面线程立即返回，防止卡住，你们懂得。
*/
struct Prama
{
	// 窗体句柄
	HWND hWnd;

	// 列表控件
	CListUI* pList;

	// 搜索按钮
	CButtonUI* pSearch;

	// 域名
	CDuiString tDomain;
};

LPBYTE g_lpResourceZIPBuffer = NULL;

class ListMainForm : public CWindowWnd, public INotifyUI
{

private:
	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pMinBtn;
	CButtonUI* m_pLogin;
	CButtonUI* m_pRegister;

public:
	ListMainForm() {
	};

	LPCTSTR GetWindowClassName() const
	{
		return _T("ScanMainForm");
	};

	UINT GetClassStyle() const
	{
		return CS_DBLCLKS;
	};

	void OnFinalMessage(HWND /*hWnd*/)
	{
		delete this;
	};

	void Init()
	{
		m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("closebtn")));
		m_pMinBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("minbtn")));
		m_pLogin = static_cast<CButtonUI*>(m_pm.FindControl(_T("login")));
		m_pRegister = static_cast<CButtonUI*>(m_pm.FindControl(_T("register")));
	}

	void OnPrepare(TNotifyUI& msg)
	{

	}

	// void Login(const std::wstring &url, std::string &res) {
	// 	std::vector<std::wstring> headers;
	// 	headers.push_back(L"");
	// 	HttpClient httpClient(L"Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.100 Safari/537.36");
	// 	httpClient.http_get(url, headers, res);
	// }

	void Notify(TNotifyUI& msg)
	{
		if (msg.sType == _T("windowinit"))
			OnPrepare(msg);
		else if (msg.sType == _T("click"))
		{
			if (msg.pSender == m_pCloseBtn)
			{
				PostQuitMessage(0);
				return;
			}
			else if (msg.pSender == m_pMinBtn)
			{
				SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
				return;
			}
			else if (msg.pSender == m_pLogin)
			{
				CEditUI* username=static_cast<CEditUI*>(m_pm.FindControl(_T("username")));
				CEditUI* password = static_cast<CEditUI*>(m_pm.FindControl(_T("password")));
                
                //MessageBox(NULL, L(), _T("返回结果"), NULL);
                
				// std::wstring url = L"http://www.h928.com/";
				// std::string res = "";
				// this->Login(url, res);
				// std::string result= UTF8ToAnsi(res);
				// MessageBox(NULL, result.c_str(), _T("返回结果"), NULL);
			}
			else if (msg.pSender == m_pRegister)
			{

			}

		}
	}

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
		::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		m_pm.Init(m_hWnd);
		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(_T("login.xml"), (UINT)0, NULL, &m_pm);
		ASSERT(pRoot && "Failed to parse XML");
		m_pm.AttachDialog(pRoot);
		m_pm.AddNotifier(this);
		Init();
		return 0;
	}

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		::PostQuitMessage(0L);
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (::IsIconic(*this)) bHandled = FALSE;
		return (wParam == 0) ? TRUE : FALSE;
	}

	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}

	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}

	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		POINT pt;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		::ScreenToClient(*this, &pt);

		RECT rcClient;
		::GetClientRect(*this, &rcClient);

		if (!::IsZoomed(*this)) {
			RECT rcSizeBox = m_pm.GetSizeBox();
			if (pt.y < rcClient.top + rcSizeBox.top) {
				if (pt.x < rcClient.left + rcSizeBox.left) return HTTOPLEFT;
				if (pt.x > rcClient.right - rcSizeBox.right) return HTTOPRIGHT;
				return HTTOP;
			}
			else if (pt.y > rcClient.bottom - rcSizeBox.bottom) {
				if (pt.x < rcClient.left + rcSizeBox.left) return HTBOTTOMLEFT;
				if (pt.x > rcClient.right - rcSizeBox.right) return HTBOTTOMRIGHT;
				return HTBOTTOM;
			}
			if (pt.x < rcClient.left + rcSizeBox.left) return HTLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTRIGHT;
		}

		RECT rcCaption = m_pm.GetCaptionRect();
		if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
			&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
			if (pControl && _tcscmp(pControl->GetClass(), DUI_CTR_BUTTON) != 0 &&
				_tcscmp(pControl->GetClass(), DUI_CTR_OPTION) != 0 &&
				_tcscmp(pControl->GetClass(), DUI_CTR_TEXT) != 0)
				return HTCAPTION;
		}

		return HTCLIENT;
	}



	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
		if (wParam == SC_CLOSE) {
			::PostQuitMessage(0L);
			bHandled = TRUE;
			return 0;
		}
		BOOL bZoomed = ::IsZoomed(*this);
		LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
		return lRes;
	}

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;
		BOOL bHandled = TRUE;
		switch (uMsg) {
		case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
		case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
		case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
		case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
		case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
		case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
		case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
		case WM_SYSCOMMAND:    lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
		default:
			bHandled = FALSE;
		}
		if (bHandled) return lRes;
		if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
		return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	}
public:
	CPaintManagerUI m_pm;

	//...
};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);

	//从文件中加载zip
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
	//CPaintManagerUI::SetResourceZip(_T("ListRes.zip"));

	 //从资源中加载zip
	HRSRC hResource = ::FindResource(CPaintManagerUI::GetResourceDll(), MAKEINTRESOURCE(IDR_ZIPRES1), _T("ZIPRES"));
	if (hResource == NULL)
		return 0L;
	DWORD dwSize = 0;
	HGLOBAL hGlobal = ::LoadResource(CPaintManagerUI::GetResourceDll(), hResource);
	if (hGlobal == NULL)
	{
		::FreeResource(hResource);
		return 0L;
	}
	dwSize = ::SizeofResource(CPaintManagerUI::GetResourceDll(), hResource);
	if (dwSize == 0)
		return 0L;
	g_lpResourceZIPBuffer = new BYTE[dwSize];
	if (g_lpResourceZIPBuffer != NULL)
	{
		::CopyMemory(g_lpResourceZIPBuffer, (LPBYTE)::LockResource(hGlobal), dwSize);
	}
	::FreeResource(hResource);
	CPaintManagerUI::SetResourceZip(g_lpResourceZIPBuffer, dwSize);

	// 设置显示的窗体
	ListMainForm* pFrame = new ListMainForm();
	if (pFrame == NULL) return 0;
	pFrame->Create(NULL, _T("ListDemo"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 600, 320);
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);

	CPaintManagerUI::MessageLoop();

	return 0;
}