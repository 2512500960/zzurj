// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__060A3A39_3B5A_4EDD_8F3B_190C5BAB648B__INCLUDED_)
#define AFX_STDAFX_H__060A3A39_3B5A_4EDD_8F3B_190C5BAB648B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _WIN32_IE                       // ָ��Ҫ������ƽ̨�� Internet Explorer 7.0��
#define _WIN32_IE 0x0700        // ����ֵ����Ϊ��Ӧ��ֵ���������� IE �������汾��
#endif

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls

#include "pcap.h"
#include "iphlpapi.h"
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib,"wpcap.lib")
#pragma comment(lib,"iphlpapi.lib")
#pragma comment(lib,"v3hash_.lib")
#endif // _AFX_NO_AFXCMN_SUPPORT



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__060A3A39_3B5A_4EDD_8F3B_190C5BAB648B__INCLUDED_)
