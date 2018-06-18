// MentoHUST.h : main header file for the MENTOHUST application
//

#if !defined(AFX_MENTOHUST_H__080C77D2_EFC2_45B8_89E6_0A26347040E8__INCLUDED_)
#define AFX_MENTOHUST_H__080C77D2_EFC2_45B8_89E6_0A26347040E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

CString LoadString(UINT nID);		//返回资源字符串
CString GetAppPath();				//获取程序所在目录
char *UnicodeToUTF8(LPCTSTR uniString);	//将Unicode转换为UTF8
/////////////////////////////////////////////////////////////////////////////
// CMentoHUSTApp:
// See MentoHUST.cpp for the implementation of this class
//

class CMentoHUSTApp : public CWinApp
{
public:
	CMentoHUSTApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMentoHUSTApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMentoHUSTApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENTOHUST_H__080C77D2_EFC2_45B8_89E6_0A26347040E8__INCLUDED_)
