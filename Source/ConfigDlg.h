#if !defined(AFX_CONFIGDLG_H__FCF39FB5_4DC2_47FA_9278_CF905F671639__INCLUDED_)
#define AFX_CONFIGDLG_H__FCF39FB5_4DC2_47FA_9278_CF905F671639__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDlg.h : header file
//
#include "AccountPage.h"
#include "SystemPage.h"
/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

class CConfigDlg : public CDialog
{
// Construction
public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_CONFIGBOX };
	CTabCtrl	m_TabCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void InitTabPages();
	void ShowPage(int index);

	CAccountPage AccountPage;
	CSystemPage SystemPage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__FCF39FB5_4DC2_47FA_9278_CF905F671639__INCLUDED_)
