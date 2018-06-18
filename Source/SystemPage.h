#if !defined(AFX_SYSTEMPAGE_H__59C5EC53_616A_4EC4_BA7C_4D2733AB20D0__INCLUDED_)
#define AFX_SYSTEMPAGE_H__59C5EC53_616A_4EC4_BA7C_4D2733AB20D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SystemPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSystemPage dialog

class CSystemPage : public CDialog
{
// Construction
public:
	CSystemPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSystemPage)
	enum { IDD = IDD_CFG_SYSTEM };
	BOOL	m_bAutoRun;
	BOOL	m_bAutoCert;
	BOOL	m_bAutoMin;
	BOOL	m_bBandMac;
	int		m_iStartMode;
	int		m_iDhcpMode;
	int		m_iTimeout;
	int		m_iEchoTime;
	BOOL	m_bUsePackage;
	CString	m_sFilePath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSystemPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnBrowser();
	afx_msg void OnOK();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL WriteConfig();		//写入配置
private:
	void SetAutoRun(BOOL bAutoRun);		//开机自动运行？
	void ReadConfig();		//读取配置
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMPAGE_H__59C5EC53_616A_4EC4_BA7C_4D2733AB20D0__INCLUDED_)
