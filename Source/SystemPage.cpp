// SystemPage.cpp : implementation file
//

#include "stdafx.h"
#include "MentoHUST.h"
#include "SystemPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT CatchThreadFunc(LPVOID pParam);			//抓包线程

/////////////////////////////////////////////////////////////////////////////
// CSystemPage dialog

CSystemPage::CSystemPage(CWnd* pParent /*=NULL*/)
	: CDialog(CSystemPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSystemPage)
	m_bAutoRun = FALSE;
	m_bAutoCert = FALSE;
	m_bAutoMin = FALSE;
	m_bBandMac = FALSE;
	m_iStartMode = 1;
	m_iDhcpMode = 0;
	m_iTimeout = 3;
	m_iEchoTime = 30;
	m_bUsePackage = FALSE;
	m_sFilePath = _T("");
	//}}AFX_DATA_INIT
}


void CSystemPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystemPage)
	DDX_Check(pDX, IDC_CK_AUTORUN, m_bAutoRun);
	DDX_Check(pDX, IDC_CK_AUTOCERT, m_bAutoCert);
	DDX_Check(pDX, IDC_CK_AUTOMIN, m_bAutoMin);
	DDX_Check(pDX, IDC_CK_BANDMAC, m_bBandMac);
	DDX_CBIndex(pDX, IDC_CB_STARTMODE, m_iStartMode);
	DDX_CBIndex(pDX, IDC_CB_DHCPMODE, m_iDhcpMode);
	DDX_Text(pDX, IDC_ED_TIMEOUT, m_iTimeout);
	DDV_MinMaxInt(pDX, m_iTimeout, 0, 99);
	DDX_Text(pDX, IDC_ED_ECHOTIME, m_iEchoTime);
	DDV_MinMaxInt(pDX, m_iEchoTime, 0, 999);
	DDX_Check(pDX, IDC_CK_PACKAGE, m_bUsePackage);
	DDX_Text(pDX, IDC_ED_PATH, m_sFilePath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSystemPage, CDialog)
	//{{AFX_MSG_MAP(CSystemPage)
	ON_BN_CLICKED(IDC_BN_BROWSER, OnBnBrowser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemPage message handlers

BOOL CSystemPage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	ReadConfig();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSystemPage::ReadConfig()
{
	CString strFileName = GetAppPath() + LoadString(IDS_INI_FILE);
	TCHAR szCertFlag[15];
	GetPrivateProfileString(_T("Parameters"), _T("CertFlag"), _T("001110030300"), szCertFlag, 15, strFileName);
	m_bAutoRun = (szCertFlag[0]-'0') % 2;
	m_bAutoCert = (szCertFlag[1]-'0') % 2;
	m_bAutoMin = (szCertFlag[2]-'0') % 2;
	m_bBandMac = (szCertFlag[3]-'0') % 2;
	m_iStartMode = (szCertFlag[4]-'0') % 2;
	m_iDhcpMode = (szCertFlag[5]-'0') % 4;
	m_iTimeout = ((szCertFlag[6]-'0')*10 + (szCertFlag[7]-'0')) % 100;
	m_iEchoTime = ((szCertFlag[8]-'0')*100 + (szCertFlag[9]-'0')*10 + (szCertFlag[10]-'0')) % 1000;
	m_bUsePackage = (szCertFlag[11]-'0') % 2;
	GetPrivateProfileString(_T("Parameters"), _T("PackagePath"), _T(""), m_sFilePath.GetBuffer(MAX_PATH), MAX_PATH, strFileName);
	m_sFilePath.ReleaseBuffer();
	UpdateData(FALSE);
}

BOOL CSystemPage::WriteConfig()
{
	if (!UpdateData())
		return FALSE;
	CString strFileName = GetAppPath() + LoadString(IDS_INI_FILE);
	CString strKeyValue;
	strKeyValue.Format(_T("%d%d%d%d%d%d%02d%03d%d"),
		m_bAutoRun, m_bAutoCert, m_bAutoMin, m_bBandMac, m_iStartMode, m_iDhcpMode, m_iTimeout, m_iEchoTime, m_bUsePackage);
	if (!WritePrivateProfileString(_T("Parameters"), _T("CertFlag"), strKeyValue, strFileName))
	{	//温馨提示|保存设置失败！
		MessageBox(LoadString(IDS_WRITE_ERROR), LoadString(IDS_NOTIFYMSG), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	WritePrivateProfileString(_T("Parameters"), _T("PackagePath"), m_sFilePath, strFileName);
	SetAutoRun(m_bAutoRun);
	return TRUE;
}

void CSystemPage::SetAutoRun(BOOL bAutoRun)
{
	HKEY hKey;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS, &hKey);
	if (bAutoRun)
	{
		TCHAR FileName[MAX_PATH];
		memset(FileName, 0, MAX_PATH*sizeof(TCHAR));
		GetModuleFileName(AfxGetInstanceHandle(), FileName+1, MAX_PATH-2);
		FileName[lstrlen(FileName+1)+1] = FileName[0] = '"';
		LPBYTE lpData = (LPBYTE)(LPCTSTR)FileName;
		if(RegSetValueEx(hKey, _T("MentoHUST"), 0, REG_SZ, lpData, lstrlen(FileName)*sizeof(TCHAR)) != ERROR_SUCCESS)
			//温馨提示|设为开机自动运行失败！
			MessageBox(LoadString(IDS_SETRUN_ERROR), LoadString(IDS_NOTIFYMSG), MB_OK | MB_ICONWARNING );
	}
	else
		RegDeleteValue(hKey, _T("MentoHUST"));
	RegCloseKey(hKey);
}

void CSystemPage::OnBnBrowser() 
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_ENABLESIZING, LoadString(IDS_PACKAGE_FILTER));
	dlg.m_ofn.lStructSize = 88;
	if (dlg.DoModal() == IDCANCEL)
		return;
	SetDlgItemText(IDC_ED_PATH, dlg.GetPathName());
}

void CSystemPage::OnOK()
{
}

void CSystemPage::OnCancel()
{
	::PostMessage(GetParent()->m_hWnd, WM_CLOSE, 0, 0);
	CDialog::OnCancel();
}
