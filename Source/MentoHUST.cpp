// MentoHUST.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MentoHUST.h"
#include "MentoHUSTDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CALLBACK EnumWndProc(HWND hwnd,LPARAM lParam);
/////////////////////////////////////////////////////////////////////////////
// CMentoHUSTApp

BEGIN_MESSAGE_MAP(CMentoHUSTApp, CWinApp)
	//{{AFX_MSG_MAP(CMentoHUSTApp)
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMentoHUSTApp construction

CMentoHUSTApp::CMentoHUSTApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMentoHUSTApp object

CMentoHUSTApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMentoHUSTApp initialization

BOOL CMentoHUSTApp::InitInstance()
{
	HWND oldHWnd = NULL;
	EnumWindows(EnumWndProc,(LPARAM)&oldHWnd);	//枚举所有运行的窗口
	if(oldHWnd != NULL)
	{
		::SendMessage(oldHWnd, WM_COMMAND, ID_MENU_RESTORE, 0);
		return false;
	}

	// Standard initialization
	CMentoHUSTDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CALLBACK EnumWndProc(HWND hwnd,LPARAM lParam)	//枚举窗口
{
	HANDLE h = GetProp(hwnd, GUI_ID);
	if (h == (HANDLE)1)
	{
		*(HWND*)lParam = hwnd;
		return false;
	}
	return true;
}

CString LoadString(UINT nID)
{
	CString strTemp;
	strTemp.LoadString(nID);
	return strTemp;
}

CString GetAppPath()
{
	CString strPath;
	GetModuleFileName(AfxGetInstanceHandle(), strPath.GetBuffer(MAX_PATH), MAX_PATH);
	strPath.ReleaseBuffer();
	return strPath.Left(strPath.ReverseFind('\\')+1);
}

char *UnicodeToUTF8(LPCTSTR uniString)	//此函数用于将Unicode转换为UTF8，需要在函数外使用delete以防内存泄露。
{
#ifdef UNICODE
	int iLen = WideCharToMultiByte(CP_UTF8, 0, uniString, -1, NULL, 0, NULL, NULL);
	char *u8String = new char[iLen+1];
	WideCharToMultiByte(CP_UTF8, 0, uniString, -1, u8String, iLen, NULL, NULL);
	return u8String;
#else
	return (char *)uniString;
#endif
}
