// MentoHUSTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MentoHUST.h"
#include "MentoHUSTDlg.h"
#include "ConfigDlg.h"
#include "Algorithm.h"
#include "md5.h"
#include "HyperLink.h"
#include "zzudata.h"
#include "GetHDSerial.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink	m_LinkNew;
	CButtonLink	m_LinkContract;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnContract();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_SC_CHECKNEW, m_LinkNew);
	DDX_Control(pDX, IDC_SC_CONTRACT, m_LinkContract);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_SC_CONTRACT, OnContract)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_LinkNew.SetURL(LoadString(IDS_LINKURL));
	m_LinkNew.SetTipText(LoadString(IDS_LINKTIP));
	m_LinkContract.SetTipText(LoadString(IDS_CONTRACT));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnContract() 
{
	MessageBox(LoadString(IDS_TEXT_CONTRACT), LoadString(IDS_CONTRACT), MB_OK|MB_ICONWARNING);
	m_LinkContract.SetCapture();
}

/////////////////////////////////////////////////////////////////////////////
// CMentoHUSTDlg dialog

CMentoHUSTDlg::CMentoHUSTDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMentoHUSTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMentoHUSTDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_sStateBoard.LoadString(IDS_WELBOARD);		//MentoHUST
	m_sStateArea.LoadString(IDS_WELCOME);		//:: 欢迎使用MentoHUST!
	m_bFullSize = TRUE;
	m_bTimerSign = FALSE;
	m_bChanged = FALSE;
	m_sServerMsg = _T("");
	m_iState = IDT_DISCONNECT;
	m_pAccountList = NULL;
	m_pAdapterList = NULL;
	m_pAdapter = NULL;
	m_pCertThread = NULL;
	m_pDhcpThread = NULL;
}

void CMentoHUSTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMentoHUSTDlg)
	DDX_Control(pDX, IDC_SC_LOGO, m_linkLogo);
	DDX_Control(pDX, IDC_CB_ADAPTER, m_AdapterList);
	DDX_Control(pDX, IDC_CB_ACCOUNT, m_AccountList);
	DDX_Text(pDX, IDC_SC_STATE, m_sStateBoard);
	DDX_Text(pDX, IDC_ED_OUTPUT, m_sStateArea);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMentoHUSTDlg, CDialog)
	//{{AFX_MSG_MAP(CMentoHUSTDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BN_ABOUT, OnBnAbout)
	ON_BN_CLICKED(IDC_BN_CLEAR, OnBnClear)
	ON_BN_CLICKED(IDC_BN_HELP, OnBnHelp)
	ON_BN_CLICKED(IDC_BN_OPTION, OnBnOption)
	ON_BN_CLICKED(IDC_BN_OUTPUT, OnBnOutput)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMentoHUSTDlg message handlers

BOOL CMentoHUSTDlg::OnInitDialog()
{
	SetProp(m_hWnd, GUI_ID, (HANDLE)1);

	CDialog::OnInitDialog();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);	//关于 MentoHUST(&A)...
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	MyInitDialog();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMentoHUSTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
		OnBnAbout();
	else
	{
		switch (nID)
		{
		case SC_MINIMIZE:
			ToTray(1);
			break;
		case IDT_SHOWMSG:
			ChangeTrayIcon();
			break;
		case IDT_INIT_DATA://1131
			InitCertData();
			break;
		case IDT_DHCP_RENEW:
		case IDT_DISCONNECT:
		case IDT_FIND_SERVER:
		case IDT_ACK_NAME:
		case IDT_ACK_PSWD:
		case IDT_ACK_ECHO:
			OnCertCommand(nID);
			break;
		default:
			CDialog::OnSysCommand(nID, lParam);
		}
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMentoHUSTDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CMentoHUSTDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMentoHUSTDlg::MyInitDialog()
{
	InitInterface();		//初始化界面
	ReadConfig();			//读取配置
	InitAccountList();		//初始化账号列表
	if (!InitAdapterList())	//初始化网卡列表，若找不到网卡
		MessageBox(LoadString(IDS_FIND_NONIC), LoadString(IDS_NOTIFYMSG), MB_OK|MB_ICONWARNING);
	else if (m_bAutoCert)		//若运行后自动认证
		OnOK();
	InitTrayData();			//初始化托盘图标
}

int CMentoHUSTDlg::ShowDlg(CDialog *dlg)
{
	int iRetVal;
	if (m_bFullSize)
	{
		OnBnOutput();
		iRetVal = dlg->DoModal();
		OnBnOutput();
	}
	else
		iRetVal = dlg->DoModal();
	return iRetVal;
}

void CMentoHUSTDlg::OnBnAbout() 
{
	CAboutDlg dlg;
	ShowDlg(&dlg);
}

void CMentoHUSTDlg::OnBnOption() 
{
	CConfigDlg dlg;
	if (IDOK == ShowDlg(&dlg))
	{
		m_bChanged = TRUE;
		if (m_iState == IDT_DISCONNECT)
			ReadAccountAgain();
	}
}

void CMentoHUSTDlg::ReadAccountAgain()
{
	if (m_bChanged)
	{
		if (m_pAccountList != NULL)
		{
			delete m_pAccountList;
			m_pAccountList = NULL;
			m_AccountList.ResetContent();
		}
		InitAccountList();
		ReadConfig();
		m_bChanged = FALSE;
	}
	else
	{
		if (m_bBandMac == 2) m_bBandMac = 1;
		if (m_iDhcpMode >= 4) m_iDhcpMode -= 3;
	}
}

void CMentoHUSTDlg::OnBnClear() 
{
	m_sServerMsg.Empty();
	m_sStateArea.LoadString(IDS_WELCOME);	//:: 欢迎使用 MentoHUST!
	SetDlgItemText(IDC_ED_OUTPUT, m_sStateArea);
}

void CMentoHUSTDlg::OnBnHelp() 
{
	CString strFileName = GetAppPath()+_T("Readme.txt");
	if (ShellExecute(NULL, _T("open"), strFileName, NULL, NULL, SW_SHOWNORMAL) < (HANDLE)32)
	{	//温馨提示|在程序所在目录找不到帮助文件 Readme.txt！
		MessageBox(LoadString(IDS_HELPERROR), LoadString(IDS_NOTIFYMSG), MB_OK|MB_ICONWARNING);
	}
}

void CMentoHUSTDlg::OnBnOutput()
{
	CRect dlgRect;
	GetWindowRect(&dlgRect);
	if (m_bFullSize)
	{
		dlgRect.bottom = dlgRect.top + m_iSmallHeight;
		SetDlgItemText(IDC_BN_OUTPUT, LoadString(IDS_OUTPUT_D));	//输出↑->输出↓
	}
	else
	{
		dlgRect.bottom = dlgRect.top + m_iBigHeight;
		SetDlgItemText(IDC_BN_OUTPUT, LoadString(IDS_OUTPUT_U));	//输出↓->输出↑
	}
	MoveWindow(&dlgRect);
	m_bFullSize = !m_bFullSize;
}

void CMentoHUSTDlg::InitInterface()
{
	CRect dlgRect, msgRect;
	GetWindowRect(&dlgRect);
	GetDlgItem(IDC_ED_OUTPUT)->GetWindowRect(&msgRect);
	m_iBigHeight = dlgRect.Height();
	m_iSmallHeight = msgRect.top - dlgRect.top;
	OnBnOutput();
	SetWindowPos(&CWnd::wndTopMost, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);

	CString strFileName = GetAppPath() + LoadString(IDS_LOGO_FILE);
	HBITMAP hLogoBmp = (HBITMAP)LoadImage(AfxGetInstanceHandle(), strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	if (hLogoBmp != NULL)
		m_linkLogo.SetBitmap(hLogoBmp);
	strFileName = GetAppPath() + LoadString(IDS_INI_FILE);
	CString strKeyValue;
	GetPrivateProfileString(_T("Parameters"), _T("Caption"), LoadString(IDS_WNDCAPTION), strKeyValue.GetBuffer(100), 100, strFileName);
	strKeyValue.ReleaseBuffer();
	SetWindowText(strKeyValue);
	GetPrivateProfileString(_T("Parameters"), _T("LinkURL"), LoadString(IDS_LINKURL), strKeyValue.GetBuffer(256), 256, strFileName);
	strKeyValue.ReleaseBuffer();
	m_linkLogo.SetURL(strKeyValue);
	GetPrivateProfileString(_T("Parameters"), _T("LinkTip"), LoadString(IDS_LINKTIP), strKeyValue.GetBuffer(256), 256, strFileName);
	strKeyValue.ReleaseBuffer();
	m_linkLogo.SetTipText(strKeyValue);
}

void CMentoHUSTDlg::OnCancel() 
{
	//退出提示|确定退出？
	if (MessageBox(LoadString(IDS_EXITMSG), LoadString(IDS_NOTIFYMSG), MB_OKCANCEL | MB_ICONWARNING ) == IDOK)
	{
		CDialog::OnCancel();
	}
}

void CMentoHUSTDlg::OnDestroy() 
{
	if (m_iState != IDT_DISCONNECT)
		SendMessage( WM_SYSCOMMAND, IDT_DISCONNECT );
	Shell_NotifyIcon(NIM_DELETE, &m_tnid);
	CDialog::OnDestroy();
	if (m_pAdapter != NULL)
		pcap_close(m_pAdapter);
	if (m_pAccountList != NULL)
		delete m_pAccountList;
	if (m_pAdapterList != NULL)
		delete m_pAdapterList;
}

BOOL CMentoHUSTDlg::ReadRuijieAccount()
{
	HKEY hKey;
	TCHAR szUsername[90], szPassword[90];
	DWORD cbUsername = sizeof(szUsername), cbPassword = sizeof(szPassword);
	DWORD type = REG_SZ;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, LoadString(IDS_RUIJIE_ERG), 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		return FALSE;
	if (RegQueryValueEx(hKey, _T("UserName"), NULL, &type, (LPBYTE)szUsername, &cbUsername) != ERROR_SUCCESS
		|| RegQueryValueEx(hKey, _T("Password"), NULL, &type, (LPBYTE)szPassword, &cbPassword) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return FALSE;
	}
	RegCloseKey(hKey);

	CString strUsername = _T(""), strPassword = szPassword;
	char buf[90];
#ifndef UNICODE
	if (DecodeRuijie(buf, szUsername))
		strUsername = buf;
#else
	char *name = UnicodeToUTF8(szUsername);
	if (DecodeRuijie(buf, name))
		strUsername = buf;
	delete []name;
#endif
	if (strUsername.IsEmpty() || strPassword.IsEmpty())
		return FALSE;

	CString strFileName = GetAppPath() + LoadString(IDS_INI_FILE);
	WritePrivateProfileString(_T("Parameters"), _T("AccountCount"), _T("1"), strFileName);
	WritePrivateProfileString(_T("Parameters"), _T("DefaultAccount"), _T("Account0"), strFileName);
	WritePrivateProfileString(_T("Account0"), _T("Username"), strUsername, strFileName);
	WritePrivateProfileString(_T("Account0"), _T("Password"), strPassword, strFileName);
	return TRUE;
}

void CMentoHUSTDlg::InitAccountList()
{
	CString strFileName = GetAppPath() + LoadString(IDS_INI_FILE);
	int AccountCount = GetPrivateProfileInt(_T("Parameters"), _T("AccountCount"), 0, strFileName);
	if (AccountCount == 0)
	{
		if (ReadRuijieAccount())
			InitAccountList();
		return;
	}
	CString strSectionName, strKeyValue;
	StringList *pTemp;
	for (int i=0; i<AccountCount; i++)
	{
		strSectionName.Format(_T("Account%d"), i);
		GetPrivateProfileString(strSectionName, _T("Username"), _T(""), strKeyValue.GetBuffer(70), 70, strFileName);
		strKeyValue.ReleaseBuffer();
		if (strKeyValue.IsEmpty())
			continue;
		pTemp = new StringList(strSectionName);
		if (m_pAccountList == NULL)
			m_pAccountList = pTemp;
		else
			m_pAccountList->AddString(pTemp);
		m_AccountList.AddString(strKeyValue);
	}
	if (m_pAccountList == NULL)
		return;
	GetPrivateProfileString(_T("Parameters"), _T("DefaultAccount"), _T(""), strKeyValue.GetBuffer(20), 20, strFileName);
	strKeyValue.ReleaseBuffer();
	int nIndex = m_pAccountList->FindString(strKeyValue);
	if (nIndex == -1)
		nIndex = 0;
	m_AccountList.SetCurSel(nIndex);
}

BOOL CMentoHUSTDlg::InitAdapterList()
{
	pcap_if_t *alldevs = NULL;
	char errbuf[PCAP_ERRBUF_SIZE];
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
		return FALSE;
	CString strAdapterName;
	CString strDescription;
	StringList *pTemp;
	for(pcap_if_t *d=alldevs; d!=NULL; d=d->next)
	{
		strAdapterName = d->name;
		strDescription = d->description;
		if (!(d->flags & PCAP_IF_LOOPBACK))
		{
			pTemp = new StringList(strAdapterName);
			if (m_pAdapterList == NULL)
				m_pAdapterList = pTemp;
			else
				m_pAdapterList->AddString(pTemp);
			m_AdapterList.AddString(strDescription);
		}
	}
	pcap_freealldevs(alldevs);
	if (m_pAdapterList == NULL)
		return FALSE;
	CString strFileName = GetAppPath() + LoadString(IDS_INI_FILE);
	GetPrivateProfileString(_T("Parameters"), _T("DefaultAdapter"), _T(""), strAdapterName.GetBuffer(60), 60, strFileName);
	strAdapterName.ReleaseBuffer();
	int nIndex = m_pAdapterList->FindString(strAdapterName);
	if (nIndex == -1)
		nIndex = 0;
	m_AdapterList.SetCurSel(nIndex);
	return TRUE;
}

void CMentoHUSTDlg::SaveAccountAndAdapter()
{
	CString strFileName = GetAppPath() + LoadString(IDS_INI_FILE);
	CString strKeyValue;
	strKeyValue = m_pAccountList->GetString(m_AccountList.GetCurSel());
	WritePrivateProfileString(_T("Parameters"), _T("DefaultAccount"), strKeyValue, strFileName);
	strKeyValue = m_pAdapterList->GetString(m_AdapterList.GetCurSel());
	WritePrivateProfileString(_T("Parameters"), _T("DefaultAdapter"), strKeyValue, strFileName);
}

BOOL CMentoHUSTDlg::GetAccount()
{
	if (m_pAccountList == NULL)
		return FALSE;
	CString strFileName = GetAppPath() + LoadString(IDS_INI_FILE);
	CString strSectionName, strIP;
	strSectionName = m_pAccountList->GetString(m_AccountList.GetCurSel());
	GetDlgItemText(IDC_CB_ACCOUNT, m_sUsername);
	GetPrivateProfileString(strSectionName, _T("Password"), _T(""), m_sPassword.GetBuffer(70), 70, strFileName);
	m_sPassword.ReleaseBuffer();
	char buf[90];
#ifndef UNICODE
	if (DecodeRuijie(buf, (char *)(LPCTSTR)m_sPassword))
		m_sPassword = buf;
#else
	char *szPassword = UnicodeToUTF8(m_sPassword);
	if (DecodeRuijie(buf, szPassword))
		m_sPassword = buf;
	delete []szPassword;
#endif
	GetPrivateProfileString(strSectionName, _T("IP"), _T("0.0.0.0"), strIP.GetBuffer(20), 20, strFileName);
	strIP.ReleaseBuffer();
#ifndef UNICODE
	m_uIP = inet_addr(strIP);
#else
	char *szIP = UnicodeToUTF8(strIP);	//对于ASCII字符GB和UTF8内存占用相同，为图方便，直接转换为UTF8
	m_uIP = inet_addr(szIP);
	delete []szIP;
#endif
	if (m_sUsername.IsEmpty() || m_sPassword.IsEmpty())
		return FALSE;
	return TRUE;
}

BOOL CMentoHUSTDlg::OpenAdapter()
{
	if (m_pAdapter != NULL)
		return TRUE;
	if (m_pAdapterList == NULL)
		return FALSE;
	char errbuf[PCAP_ERRBUF_SIZE];
	CString strAdapterName = m_pAdapterList->GetString(m_AdapterList.GetCurSel());
#ifndef UNICODE
	m_pAdapter = pcap_open_live(strAdapterName, 65535, 0, 500, errbuf);
#else
	char *szAdapterName = UnicodeToUTF8(strAdapterName);
	m_pAdapter = pcap_open_live(szAdapterName, 65535, 0, 500, errbuf);
	delete []szAdapterName;
#endif

	char filter[512];
	sprintf(filter,"ether dst %02X",m_bLocalMAC[0]);
	char tempchar;
	for (int ii = 1; ii < 6; ii++)
	{
		sprintf(&tempchar,":%02x",m_bLocalMAC[ii]);
		strcat(filter,&tempchar);
	}
	pcap_compile(m_pAdapter,&m_bfilter,filter,1,0xffffff00);
	pcap_setfilter(m_pAdapter,&m_bfilter);
	if (m_pAdapter == NULL)
		return FALSE;
	return TRUE;
}

void CMentoHUSTDlg::ReadConfig()
{
	CString strFileName = GetAppPath() + LoadString(IDS_INI_FILE);
	TCHAR szCertFlag[15];
	GetPrivateProfileString(_T("Parameters"), _T("CertFlag"), _T("001110030300"), szCertFlag, 15, strFileName);
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
}

void CMentoHUSTDlg::Output(LPCTSTR Msg, int Type)
{
	CEdit *StateEdit = (CEdit *)GetDlgItem(IDC_ED_OUTPUT);
	if (StateEdit->GetLineCount() > MAX_OUTPUT_LINES)
		m_sStateArea.Format(LoadString(IDS_MSGCLEAR), MAX_OUTPUT_LINES);	//:: 输出超过 %d, 自动清空。
	switch (Type)
	{
	case 1:
		SetDlgItemText(IDC_SC_STATE, Msg);
		return;
	case 2:
		m_sStateArea = m_sStateArea + _T("\r\n") + Msg;
		break;
	default:
		SetDlgItemText(IDC_SC_STATE, Msg);
		m_sStateArea = m_sStateArea + _T("\r\n") + Msg;
	}
	SetDlgItemText(IDC_ED_OUTPUT, m_sStateArea);
	StateEdit->SetSel(-2, -1);
}

void CMentoHUSTDlg::InitTrayData()
{
	m_tnid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_tnid.hWnd = GetSafeHwnd();
	m_tnid.uID = 0;
	m_tnid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP|NIF_INFO;
	m_tnid.uTimeout = 10000;
	m_tnid.uCallbackMessage = WM_COMMAND;
	m_tnid.dwInfoFlags = NIIF_INFO;
	m_tnid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_FAILED));
	lstrcpy(m_tnid.szInfoTitle, LoadString(IDS_SERVERMSG));
	lstrcpy(m_tnid.szInfo, m_sServerMsg);
	lstrcpy(m_tnid.szTip, LoadString(IDS_TRAY_DISCONNECT));
	Shell_NotifyIcon(NIM_ADD, &m_tnid);
}

void CMentoHUSTDlg::ChangeTrayIcon()
{
	lstrcpy(m_tnid.szInfo, m_sServerMsg);
	switch (m_iState)
	{
	case IDT_DISCONNECT:
		m_tnid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_FAILED));
		lstrcpy(m_tnid.szTip, LoadString(IDS_TRAY_DISCONNECT));
		break;
	case IDT_DHCP_RENEW:
		m_tnid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_CERTTING));
		lstrcpy(m_tnid.szTip, LoadString(IDS_TRAY_DHCP));
		break;
	case IDT_FIND_SERVER:
		m_tnid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_CERTTING));
		lstrcpy(m_tnid.szTip, LoadString(IDS_TRAY_START));
		break;
	case IDT_ACK_NAME:
		m_tnid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_CERTTING));
		lstrcpy(m_tnid.szTip, LoadString(IDS_TRAY_USERNAME));
		break;
	case IDT_ACK_PSWD:
		m_tnid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_CERTTING));
		lstrcpy(m_tnid.szTip, LoadString(IDS_TRAY_PASSWORD));
		break;
	case IDT_ACK_ECHO:
		m_tnid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
		lstrcpy(m_tnid.szTip, LoadString(IDS_TRAY_SUCCESS));
		break;
	default:
		break;
	}
	Shell_NotifyIcon(NIM_MODIFY, &m_tnid);
}

void CMentoHUSTDlg::ToTray(int nTray)
{
	if (nTray == 0)
		ShowWindow(SW_SHOWNORMAL);
	else if (nTray == 1)
	{
		ShowWindow(SW_MINIMIZE);
		ShowWindow(SW_HIDE);
		ChangeTrayIcon();
	}
	else
	{
		WINDOWPLACEMENT wndpl;
		GetWindowPlacement(&wndpl);
		if( wndpl.showCmd == SW_SHOWMINIMIZED )
			ToTray(0);
		else
			ToTray(1);
	}
}

void CMentoHUSTDlg::CheckRuijie()
{
	CString strTemp;
	strTemp.Format(LoadString(IDS_RUIJIE_VERSION), m_bPackage[0x3B], m_bPackage[0x3C], m_bPackage[0x3D], m_bPackage[0x3E]);
	Output(strTemp, 2);
	if (ntohl(*(u_int32_t *)(m_bPackage+0x3B)) < 0x02380000)		//2.56.0.0之前
	{
		Output(LoadString(IDS_NO_CLIENTCHECK), 2);
		return;
	}
	u_int32_t nReadLength;
	BYTE *pBuffer = NULL;
	try{
		CFile File(m_sFilePath, CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary);
		nReadLength = File.GetLength();
		pBuffer = new BYTE[nReadLength];
		File.Read(pBuffer, nReadLength);
		File.Close();
	}catch(...){
		FileError(pBuffer, FALSE);
		return;
	}
	u_int32_t nData = *(u_int32_t *)pBuffer ^ *(u_int32_t *)(pBuffer + 4);
	SYSTEMTIME stLocal;
	::GetLocalTime(&stLocal);
	u_int32_t nCurrentDate = stLocal.wYear*10000 + stLocal.wMonth*100 + stLocal.wDay;
	if (nData < nCurrentDate)
	{
		FileError(pBuffer, FALSE);
		return;
	}
	nReadLength = (*(u_int32_t *)pBuffer ^ *(u_int32_t *)(pBuffer + 8)) + 16;
	unsigned i, j;
	for (i=16; i<nReadLength; i+=16)
	{
		for (j=0; j<16; j++)
			pBuffer[i+j] ^= pBuffer[j];
	}
	nData = (*(u_int32_t *)pBuffer ^ *(u_int32_t *)(pBuffer + 12)) + 16;
	BYTE *pCheckBuffer = new BYTE[nData];
	memcpy(pCheckBuffer, pBuffer, nReadLength);
	memset(pCheckBuffer + nReadLength, 0, nData - nReadLength);
	delete []pBuffer;	
	BYTE *pTable = new BYTE[144];
	BYTE *md5rev = m_bMD5Source + 0x08;
	BYTE *md5Dig;
	nData = (nData - 16) / 8;
	for (i=0; i<8; i++)
	{
		memcpy(pCheckBuffer + nData * i, md5rev, 16);
		md5Dig = ComputeHash(pCheckBuffer + nData * i, nData + 16);
		pTable[18*i] = md5rev[2*i];
		memcpy(pTable+18*i+1, md5Dig, 16);
		pTable[18*i+17] = md5rev[2*i+1];
	}
	md5Dig = ComputeHash(pTable, 144);
	delete []pCheckBuffer;
	delete []pTable;
	CString strHash = _T("");
	for(i=0; i<16; i++)
	{
		strTemp.Format(_T("%02x"), md5Dig[i]);
		strHash = strHash + strTemp;
	}
	Output(LoadString(IDS_MD5_STRING) + strHash, 2);
#ifndef UNICODE
	pBuffer = (BYTE *)strHash.GetBuffer(0);
	memcpy(m_bPackage+0x4E, pBuffer, 32);
	strHash.ReleaseBuffer();
#else
	pBuffer = (BYTE *)UnicodeToUTF8(strHash);
	memcpy(m_bPackage+0x4E, pBuffer, 32);
	delete []pBuffer;
#endif
}

BOOL CMentoHUSTDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch ( wParam )
	{
	case ID_MENU_RESTORE:
		ToTray(2);
		break;
	case ID_MENU_CONNECT:
		OnOK();
		break;
	case ID_MENU_CONFIG:
		OnBnOption();
		break;
	case ID_MENU_HELP:
		OnBnHelp();
		break;
	case ID_MENU_ABOUT:
		OnBnAbout();
		break;
	case ID_MENU_EXIT:
		CDialog::OnCancel();
		break;
	case 0:
		switch (lParam)
		{
		case WM_LBUTTONDOWN:
			SetTimer(SHOW_CYCLE_TIMER, 300, NULL);
			break;
		case WM_LBUTTONDBLCLK:
			KillTimer(SHOW_CYCLE_TIMER);
			ToTray(2);
			break;
		case WM_RBUTTONUP:
			CMenu menu;
			VERIFY(menu.LoadMenu(IDR_TRAY_MENU));
			CMenu *pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			if (m_iState != IDT_DISCONNECT)
				pPopup->ModifyMenu(ID_MENU_CONNECT, MF_BYCOMMAND|MF_STRING, ID_MENU_CONNECT, LoadString(IDS_DISCONNECT));
			POINT pt;   
			GetCursorPos(&pt);
			::SetForegroundWindow(m_hWnd);
			pPopup->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
			menu.Detach();
			menu.DestroyMenu();
			break;
		}
	default:
		break;
	}
	return CDialog::OnCommand(wParam, lParam);
}

void CMentoHUSTDlg::OnOK()
{
	if (m_iState == IDT_DISCONNECT)
	{
		if (!GetAccount() || !OpenAdapter())
		{
			MessageBox(LoadString(IDS_OPEN_ERROR), LoadString(IDS_NOTIFYMSG), MB_OK | MB_ICONWARNING);
			return;
		}
		SaveAccountAndAdapter();
		if (m_iDhcpMode == 3)
			PostMessage(WM_SYSCOMMAND, IDT_DHCP_RENEW);
		else
			PostMessage(WM_SYSCOMMAND, IDT_INIT_DATA);
	}
	else
		PostMessage(WM_SYSCOMMAND, IDT_DISCONNECT);
}

BOOL CMentoHUSTDlg::GetAdapterInfo()
{
	PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO *) malloc( sizeof(IP_ADAPTER_INFO) );
	DWORD dwRetVal;
	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) 
	{
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen);
	}
	dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen);
	if(dwRetVal == NO_ERROR)
	{
		CString strAdapterName = m_pAdapterList->GetString(m_AdapterList.GetCurSel());
		strAdapterName = strAdapterName.Right(38);
		CString strAdapterID;
		for (PIP_ADAPTER_INFO pAdapter = pAdapterInfo; pAdapter; pAdapter = pAdapter->Next)
		{
			strAdapterID = pAdapter->AdapterName;
			if (strAdapterName.Compare(strAdapterID) == 0)
			{
				memcpy(m_bLocalMAC, pAdapter->Address, 6);
				*(u_int32_t *)m_bLocalIP = inet_addr(pAdapter->IpAddressList.IpAddress.String);
				*(u_int32_t *)m_bLocalMask = inet_addr(pAdapter->IpAddressList.IpMask.String);
				*(u_int32_t *)m_bGateIP = inet_addr(pAdapter->GatewayList.IpAddress.String);
				break;
			}
		}
	}
	if (pAdapterInfo != NULL)
	{
		free(pAdapterInfo);
		pAdapterInfo = NULL;
	}
	if(dwRetVal == ERROR_NO_DATA)
	{
		MessageBox(LoadString(IDS_OPEN_ERROR), LoadString(IDS_NOTIFYMSG), MB_OK|MB_ICONWARNING);
		return FALSE;
	}

	FIXED_INFO *pFixedInfo = (FIXED_INFO *) malloc( sizeof( FIXED_INFO ) );
	ulOutBufLen = sizeof( FIXED_INFO );
	if ( GetNetworkParams( pFixedInfo, &ulOutBufLen ) == ERROR_BUFFER_OVERFLOW ) 
	{
		free( pFixedInfo );
		pFixedInfo = (FIXED_INFO *) malloc( ulOutBufLen );
	}
	if(GetNetworkParams( pFixedInfo, &ulOutBufLen ) == NO_ERROR)
		*(u_int32_t *)m_bLocalDNS = inet_addr(pFixedInfo->DnsServerList.IpAddress.String);
	if (pFixedInfo != NULL)
	{
		free( pFixedInfo );
		pFixedInfo = NULL;
	}

	CString strTemp;
	strTemp.Format(LoadString(IDS_LOCALMAC), m_bLocalMAC[0], m_bLocalMAC[1], m_bLocalMAC[2], m_bLocalMAC[3], m_bLocalMAC[4], m_bLocalMAC[5]);
	Output(strTemp, 2);
	strTemp.Format(LoadString(IDS_LOCALIP), m_bLocalIP[0], m_bLocalIP[1], m_bLocalIP[2], m_bLocalIP[3]);
	Output(strTemp, 2);
	strTemp.Format(LoadString(IDS_LOCALMASK), m_bLocalMask[0], m_bLocalMask[1], m_bLocalMask[2], m_bLocalMask[3]);
	Output(strTemp, 2);
	strTemp.Format(LoadString(IDS_LOCALGATE), m_bGateIP[0], m_bGateIP[1], m_bGateIP[2], m_bGateIP[3]);
	Output(strTemp, 2);
	strTemp.Format(LoadString(IDS_LOCALDNS), m_bLocalDNS[0], m_bLocalDNS[1], m_bLocalDNS[2], m_bLocalDNS[3]);
	Output(strTemp, 2);

	char packet_filter[256];
	sprintf(packet_filter, PCAP_FILTER, m_bLocalMAC[0], m_bLocalMAC[1], m_bLocalMAC[2], m_bLocalMAC[3], m_bLocalMAC[4], m_bLocalMAC[5]);	
	struct bpf_program fcode; 
	if (pcap_compile(m_pAdapter, &fcode, packet_filter, 1, *(u_int32_t *)m_bLocalMask) < 0
		||pcap_setfilter(m_pAdapter, &fcode) < 0)
		Output(LoadString(IDS_FILTER_ERROR), 2);
	return TRUE;
}

void CMentoHUSTDlg::InitCertData()
{
	if (!GetAdapterInfo())
	{
		PostMessage( WM_SYSCOMMAND, IDT_DISCONNECT );
		return;
	}
	if (m_iDhcpMode == 5)
	{
		Output(LoadString(IDS_SUCCESS));
		PostMessage( WM_SYSCOMMAND, IDT_ACK_ECHO );
		return;
	}
	InitHeader();
	PostMessage( WM_SYSCOMMAND, IDT_FIND_SERVER );
}

void CMentoHUSTDlg::InitHeader()
{
	memset(m_bPackage, 0, 0x217);
	*(u_int16_t *)(m_bPackage+0x02) = htons(0x1311);
	if (m_iDhcpMode != 0)
		m_bPackage[0x04] = 0x01;
	if (m_uIP != 0)
	{
		BYTE *bIP = m_bPackage + 0x05;
		*(u_int32_t *)bIP = m_uIP;
		CString strTemp;
		strTemp.Format(LoadString(IDS_USEIP), bIP[0], bIP[1], bIP[2], bIP[3]);
		Output(strTemp, 2);
	}
	else
		memcpy(m_bPackage+0x05, m_bLocalIP, 4);
	memcpy(m_bPackage+0x09, m_bLocalMask, 4);
	memcpy(m_bPackage+0x0D, m_bGateIP, 4);
	memcpy(m_bPackage+0x11, m_bLocalDNS, 4);
	Blog(m_bPackage, 21, m_bPackage+0x15);
	for (int i=0; i<23; i++)
		m_bPackage[i] = Alog(m_bPackage[i]);
}

void CMentoHUSTDlg::InitPackage(BOOL bStart)
{
	if (!bStart)
		CheckRuijie();
	else
	{
		try{
			CFile File(m_sFilePath, CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary);
			File.Seek(-0x200, CFile::end);
			File.Read(m_bPackage+0x17, 0x200);
			File.Close();
		}catch(...)
		{
			FileError(NULL, TRUE);
			return;
		}
		//if (m_iDhcpMode == 4 || m_iDhcpMode == 5)
		//	m_bPackage[0x3F] = 0x00;
		if (m_iDhcpMode == 1 || m_iDhcpMode == 2)
			m_bPackage[0x79] = 0x01;
		else
			m_bPackage[0x79] = 0x00;
		memcpy(m_bPackage+0x82, m_bLocalMAC, 6);
		if (m_iDhcpMode != 0)
			m_bPackage[0x98] = 0x01;
		else
			m_bPackage[0x98] = 0x00;
	}
}

void CMentoHUSTDlg::InitDefault(BOOL bStart)
{
	m_bUsePackage = FALSE;
	*(u_int16_t *)(m_bPackage+0x19) = *(u_int16_t *)(m_bPackage+0x42) =
		*(u_int16_t *)(m_bPackage+0x4a) = *(u_int16_t *)(m_bPackage+0x72) =
		*(u_int16_t *)(m_bPackage+0x7E) = *(u_int16_t *)(m_bPackage+0x8C) = htons(0x1311);
	memcpy(m_bPackage+0x1B, "8021x.exe", 9);
	*(u_int16_t *)(m_bPackage+0x3B) = htons(0x021F);	//版本为2.31.0.0
	*(u_int32_t *)(m_bPackage+0x44) = htonl(0x00281A28);
	*(u_int16_t *)(m_bPackage+0x4C) = htons(0x1722);
	BYTE Start[0x20] = {
		0x92, 0x68, 0x64, 0x66, 0x92, 0x94, 0x62, 0x66, 0x91, 0x93, 0x95, 0x62, 0x93, 0x93, 0x91, 0x94,
		0x64, 0x61, 0x64, 0x64, 0x65, 0x66, 0x68, 0x94, 0x98, 0xA7, 0x61, 0x67, 0x65, 0x67, 0x9C, 0x6B};
		BYTE Md5[0x20] = {
			0x96, 0x96, 0x96, 0x96, 0x96, 0x96, 0x96, 0x96, 0x96, 0x96, 0x96, 0x96, 0x67, 0x61, 0x96, 0x96,
			0x64, 0x62, 0x67, 0x91, 0x96, 0x96, 0x96, 0x96, 0x9e, 0xc9, 0xcd, 0x96, 0x67, 0x67, 0x98, 0x96};
			if(bStart)
				memcpy(m_bPackage+0x4E, Start, 0x20);
			else
				memcpy(m_bPackage+0x4E, Md5, 0x20);
}

void CMentoHUSTDlg::FileError(BYTE *pBuffer, BOOL bStart)
{
	if (pBuffer != NULL)
		delete pBuffer;
	Output(LoadString(IDS_FILE_ERROR), 2);
	InitDefault(bStart);
}

void CMentoHUSTDlg::OnCertCommand(UINT nID)
{
	m_iState = nID;
	switch (nID)
	{
	case IDT_DHCP_RENEW:
		TimerCtrl(0);
		if (m_iDhcpMode == 1) m_iDhcpMode = 4;
		else if (m_iDhcpMode == 2) m_iDhcpMode = 5;
		if (m_pDhcpThread == NULL)
			m_pDhcpThread = AfxBeginThread(DhcpThreadFunc, this, THREAD_PRIORITY_TIME_CRITICAL);
		break;
	case IDT_FIND_SERVER:
		if (m_bUsePackage)
			InitPackage(TRUE);
		else
			InitDefault(TRUE);
		m_iErrorTimes = 0;
		m_iLastState = IDT_DISCONNECT;
		Output(LoadString(IDS_FIND_SERVER));
		if (m_pCertThread == NULL)
			m_pCertThread = AfxBeginThread(CertThreadFunc, this, THREAD_PRIORITY_TIME_CRITICAL);
		TimerCtrl(m_iTimeout);
		SendPackage();
		break;
	case IDT_ACK_NAME:
		Output(LoadString(IDS_SEND_NAME));
		TimerCtrl(m_iTimeout);
		SendPackage();
		break;
	case IDT_ACK_PSWD:
		Output(LoadString(IDS_SEND_PASSWORD));
		if (m_bUsePackage)
			InitPackage(FALSE);
		else
			InitDefault(TRUE);
		m_uEchoNo = 0x0000102b;
		TimerCtrl(m_iTimeout);
		SendPackage();
		break;
	case IDT_ACK_ECHO:
		SendPackage();
		if(m_iDhcpMode == 1 || m_iDhcpMode == 2)
			PostMessage(WM_SYSCOMMAND, IDT_DHCP_RENEW);
		else
		{
			TimerCtrl(m_iEchoTime);
			if (m_bAutoMin)
				ToTray(1);
		}
		break;
	case IDT_DISCONNECT:
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		TimerCtrl(0);
		if (m_pDhcpThread != NULL)
		{
			WaitForSingleObject(m_pDhcpThread->m_hThread, 1000);
			m_pDhcpThread = NULL;
		}
		if (m_pCertThread != NULL)
		{
			WaitForSingleObject(m_pCertThread->m_hThread, 1000);
			m_pCertThread = NULL;
		}
		if (m_iDhcpMode > 2)
		{
			m_pDhcpThread = AfxBeginThread(DhcpThreadFunc, this, THREAD_PRIORITY_TIME_CRITICAL);
			WaitForSingleObject(m_pDhcpThread->m_hThread, 1000);
			m_pDhcpThread = NULL;
		}
		else
			Output(LoadString(IDS_TEXT_DISCONNECT));
		SendLogoffPackage();
		ReadAccountAgain();
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		break;
	default:
		break;
	}
	if (m_iState == IDT_DISCONNECT)
	{
		SetDlgItemText(IDOK, LoadString(IDS_BN_CONNECT));
		GetDlgItem(IDC_CB_ACCOUNT)->EnableWindow(TRUE);
		GetDlgItem(IDC_CB_ADAPTER)->EnableWindow(TRUE);
	}
	else
	{
		SetDlgItemText(IDOK, LoadString(IDS_BN_DISCONNECT));
		GetDlgItem(IDC_CB_ACCOUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CB_ADAPTER)->EnableWindow(FALSE);
	}
	if (m_iState != IDT_ACK_ECHO)
		m_sServerMsg.Empty();
	ChangeTrayIcon();
}

BOOL CMentoHUSTDlg::SendPackage()
{
	if( m_iLastState == m_iState && m_iState != IDT_ACK_ECHO )
		m_iErrorTimes++;
	else
	{
		m_iLastState = m_iState;
		m_iErrorTimes = 0;
	}
	if ( m_iErrorTimes >= MAX_ERROR_TIMES )
	{
		switch( m_iState )
		{
		case IDT_FIND_SERVER:
			if( m_iDhcpMode == 4 )
			{
				Output(LoadString(IDS_SUCCESS));
				PostMessage( WM_SYSCOMMAND, IDT_ACK_ECHO );
				return TRUE;
			}
			Output(LoadString(IDS_SERVER_ERROR));
			break;
		case IDT_ACK_NAME:
			Output(LoadString(IDS_ID_ERROR));
			break;
		case IDT_ACK_PSWD:
			Output(LoadString(IDS_MD5_ERROR));
			break;
		}
		SendLogoffPackage();
		PostMessage( WM_SYSCOMMAND, IDT_FIND_SERVER );
		return TRUE;
	}
	switch ( m_iState )
	{
	case IDT_FIND_SERVER:			//寻找服务器
		if ( /*SendStartPackage()*/sendstart() )
			return FALSE;
		break;
	case IDT_ACK_NAME:				//以用户名应答
		if (/* SendIdentityPackage()*/sendidentify() )
			return FALSE;
		break;
	case IDT_ACK_PSWD:				//以MD5计算得到的值应答
		if ( /*SendMD5ChallengePackage()*/ sendmd5challenge())
			return FALSE;
		break;
	case IDT_ACK_ECHO:				//运行时echo包
		if ( SendEchoPackage() )
			return FALSE;
		if ( m_bBandMac != 0 )
			SendArpPackage();
		break;
	}
	return TRUE;
}

int CMentoHUSTDlg::SendStartPackage()
{
	BYTE StandardAddr[]	= {0x01, 0x80, 0xC2, 0x00, 0x00, 0x03};
	BYTE RuijieAddr[]	= {0x01, 0xD0, 0xF8, 0x00, 0x00, 0x03};

	memset(m_bSendPackage, 0, 0x3E8);
	if(m_iDhcpMode == 4 || m_iDhcpMode == 5)
		memcpy(m_bSendPackage, m_bDestMAC, 6);
	else if(m_iStartMode)
		memcpy(m_bSendPackage, RuijieAddr, 6);
	else
		memcpy(m_bSendPackage, StandardAddr, 6);
	memcpy(m_bSendPackage+0x06, m_bLocalMAC, 6);
	*(u_int32_t *)(m_bSendPackage+0x0c) = htonl(0x888E0101);
	memcpy(m_bSendPackage+0x12, m_bPackage, 0x217);
	return pcap_sendpacket(m_pAdapter, m_bSendPackage, 0x3E8);
}

int CMentoHUSTDlg::SendIdentityPackage()
{
	memset(m_bSendPackage, 0, 0x3E8);
	memcpy(m_bSendPackage, m_bDestMAC, 6);
	memcpy(m_bSendPackage+0x06, m_bLocalMAC, 6);
	*(u_int32_t *)(m_bSendPackage+0x0c) = htonl(0x888E0100);
#ifndef UNICODE
	char *szUsername = m_sUsername.GetBuffer(0);
#else
	char *szUsername = UnicodeToUTF8(m_sUsername);
#endif
	int iLen = strlen(szUsername);
	*(u_int16_t *)(m_bSendPackage+0x14) = *(u_int16_t *)(m_bSendPackage+0x10) = htons(5 + iLen);
	m_bSendPackage[0x12] = 0x02;
	m_bSendPackage[0x13] = m_bMD5Source[0x03];
	m_bSendPackage[0x16] = m_bMD5Source[0x06];
	memcpy(m_bSendPackage+0x17, szUsername, iLen);
#ifdef UNICODE
	delete []szUsername;
#endif
	memcpy(m_bSendPackage+0x17+iLen, m_bPackage, 0x217);
	return pcap_sendpacket(m_pAdapter, m_bSendPackage, 0x3E8);
}

int CMentoHUSTDlg::SendMD5ChallengePackage()
{
	memset(m_bSendPackage, 0, 0x3E8);
	memcpy(m_bSendPackage, m_bDestMAC, 6);
	memcpy(m_bSendPackage+0x06, m_bLocalMAC, 6);
	*(u_int32_t *)(m_bSendPackage+0x0c) = htonl(0x888E0100);
#ifndef UNICODE
	char *szUsername = m_sUsername.GetBuffer(0);
	char *szPassword = m_sPassword.GetBuffer(0);
#else
	char *szUsername = UnicodeToUTF8(m_sUsername);
	char *szPassword = UnicodeToUTF8(m_sPassword);
#endif
	int iNameLen = strlen(szUsername);
	*(u_int16_t *)(m_bSendPackage+0x14) = *(u_int16_t *)(m_bSendPackage+0x10) = htons(6+ m_bMD5Source[0x07] + iNameLen);
	m_bSendPackage[0x12] = 0x02;
	m_bSendPackage[0x13] = m_bMD5Source[0x03];
	m_bSendPackage[0x16] = m_bMD5Source[0x06];
	m_bSendPackage[0x17] = m_bMD5Source[0x07];
	BYTE md5src[80], *md5Dig;
	int iPassLen = strlen(szPassword);
	md5src[0] = m_bMD5Source[0x03];
	memcpy(md5src+1, szPassword, iPassLen);
	memcpy(md5src+1+iPassLen, m_bMD5Source+0x08, m_bMD5Source[0x07]);
	md5Dig = ComputeHash( md5src, 1+iPassLen+m_bMD5Source[0x07] );
	memcpy(m_bSendPackage+0x18, md5Dig, m_bMD5Source[0x07]);
	memcpy(m_bSendPackage+0x18+m_bMD5Source[0x07], szUsername, iNameLen);
#ifdef UNICODE
	delete []szPassword;
	delete []szUsername;
#endif
	memcpy(m_bSendPackage+0x18+m_bMD5Source[0x07]+iNameLen, m_bPackage, 0x217);
	return pcap_sendpacket(m_pAdapter, m_bSendPackage, 0x3E8);
}

int CMentoHUSTDlg::SendEchoPackage()
{
	BYTE echoPackage[0x2D] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x8e, 0x01, 0xbf,
		0x00, 0x1e, 0xff, 0xff, 0x37, 0x77, 0x7f, 0x9f, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x37, 0x77,
		0x7f, 0x9f, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x37, 0x77, 0x7f, 0x3f, 0xff};
		BYTE bPart1[4], bPart2[4];
		*(u_int32_t *)bPart1 = htonl(*(u_int32_t *)m_bEchoSource + m_uEchoNo);
		*(u_int32_t *)bPart2 = htonl(m_uEchoNo);
		m_uEchoNo++;
		memcpy( echoPackage, m_bDestMAC, 6 );
		memcpy( echoPackage+0x06, m_bLocalMAC, 6 );
		for (int i=0; i<4; i++)
		{
			echoPackage[0x18+i] = Alog(bPart1[i]);
			echoPackage[0x22+i] = Alog(bPart2[i]);
		}
		return pcap_sendpacket(m_pAdapter, echoPackage, 0x2D);
}

int CMentoHUSTDlg::SendLogoffPackage()
{
	memset(m_bSendPackage, 0, 0x3E8);
	memcpy(m_bSendPackage, m_bDestMAC, 6);
	memcpy(m_bSendPackage+0x06, m_bLocalMAC, 6);
	*(u_int32_t *)(m_bSendPackage+0x0c) = htonl(0x888E0102);
	memcpy(m_bSendPackage+0x12, m_bPackage, 0x217);
	return pcap_sendpacket(m_pAdapter, m_bSendPackage, 0x3E8);
}

void CMentoHUSTDlg::SendArpPackage()
{
	BYTE arpPackage[0x3C] = {	//Arp包
		0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x06,0x00,0x01,
		0x08,0x00,0x06,0x04,0x00};

		if (m_iDhcpMode == 1 || m_iDhcpMode == 2)
			return;
		if (m_bBandMac == 2)
		{
			memcpy( arpPackage, m_bGateMAC, 6 );
			memcpy( arpPackage+0x06, m_bLocalMAC, 6 );
			arpPackage[0x15]=0x02;
			memcpy( arpPackage+0x16, m_bLocalMAC, 6 );
			memcpy( arpPackage+0x1c, m_bLocalIP, 4 );
			memcpy( arpPackage+0x20, m_bGateMAC, 6 );
			memcpy( arpPackage+0x26, m_bGateIP, 4 );
			pcap_sendpacket( m_pAdapter, arpPackage, 0x3C );
		}
		memset(arpPackage, 0xFF, 6);
		memcpy( arpPackage+0x06, m_bLocalMAC, 6 );
		arpPackage[0x15]=0x01;
		memcpy( arpPackage+0x16, m_bLocalMAC, 6 );
		memcpy( arpPackage+0x1c, m_bLocalIP, 4 );
		memset( arpPackage+0x20, 0, 6 );
		memcpy( arpPackage+0x26, m_bGateIP, 4 );
		pcap_sendpacket( m_pAdapter, arpPackage, 0x2A );
}

void CMentoHUSTDlg::TimerCtrl(int timer)
{
	if( m_bTimerSign )
		KillTimer(CERT_CYCLE_TIMER);
	if( timer == 0 )
	{
		m_bTimerSign = FALSE;
		return;
	}
	SetTimer(CERT_CYCLE_TIMER, 1000*timer, NULL);
	m_bTimerSign = TRUE;
}

void CMentoHUSTDlg::OnTimer(UINT nIDEvent)
{
	switch( nIDEvent )
	{
	case CERT_CYCLE_TIMER:
		if (!SendPackage())
		{
			PostMessage( WM_SYSCOMMAND, IDT_DISCONNECT );
			MessageBox(LoadString(IDS_SEND_ERROR), LoadString(IDS_NOTIFYMSG), MB_OK | MB_ICONWARNING);
			pcap_close(m_pAdapter);
			m_pAdapter = NULL;
			ToTray(0);
		}
		break;
	case SHOW_CYCLE_TIMER:
		PostMessage(WM_COMMAND, 0, WM_LBUTTONDBLCLK);
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

UINT DhcpThreadFunc( LPVOID pParam )
{
	CMentoHUSTDlg *mainDlg = (CMentoHUSTDlg *)pParam;
	TCHAR sysPath[MAX_PATH];
	GetSystemDirectory(sysPath, MAX_PATH);
	SHELLEXECUTEINFO ShExecInfo;
	ShExecInfo.cbSize	= sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask	= SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd		= NULL;
	ShExecInfo.lpVerb	= NULL;
	ShExecInfo.lpFile	= _T("ipconfig.exe");
	ShExecInfo.lpDirectory	= sysPath;
	ShExecInfo.nShow	= SW_HIDE;
	ShExecInfo.hInstApp = NULL;
	if (mainDlg->m_iState == IDT_DHCP_RENEW)
	{
		ShExecInfo.lpParameters = _T("/renew");
		ShellExecuteEx(&ShExecInfo);
		mainDlg->Output(LoadString(IDS_DHCP_REMEW));
		int iRnt = WaitForSingleObject(ShExecInfo.hProcess, 10000);
		if(iRnt == WAIT_TIMEOUT)
			mainDlg->Output(LoadString(IDS_DHCP_TIMEOUT), 2);
		else if(iRnt == WAIT_FAILED)
			mainDlg->Output(LoadString(IDS_DHCP_FAILED), 2);
		else
			mainDlg->Output(LoadString(IDS_DHCP_END), 2);
		mainDlg->PostMessage( WM_SYSCOMMAND, IDT_INIT_DATA );
	}
	else
	{
		ShExecInfo.lpParameters = _T("/release");
		ShellExecuteEx(&ShExecInfo);
		mainDlg->Output(LoadString(IDS_DHCP_REMEW));
		int iRnt = WaitForSingleObject(ShExecInfo.hProcess, 10000);
		if(iRnt == WAIT_TIMEOUT) 
			mainDlg->Output(LoadString(IDS_DHCP_TIMEOUT), 2);
		else if(iRnt == WAIT_FAILED)
			mainDlg->Output(LoadString(IDS_DHCP_FAILED), 2);
		else
			mainDlg->Output(LoadString(IDS_DHCP_END), 2);
		mainDlg->Output(LoadString(IDS_TEXT_DISCONNECT));
	}
	CloseHandle(ShExecInfo.hProcess);
	return 0;
}

UINT CertThreadFunc( LPVOID pParam )
{
	CMentoHUSTDlg *mainDlg = (CMentoHUSTDlg *)pParam;
	BYTE *pRecvBuf;			//指向buf1，接收到的数据包
	BYTE *pRecvHeaderBuf;	//指向buf2，接收到的数据头
	BOOL bFirst = TRUE;
	USHORT sLen;
	CString strTemp;
	int retVal;

	while (mainDlg->m_iState != IDT_DISCONNECT)
	{
		retVal = pcap_next_ex(mainDlg->m_pAdapter, (pcap_pkthdr **)&pRecvHeaderBuf, (const u_char**)&pRecvBuf);
		if (retVal < 0)
		{
			mainDlg->SendPackage();
			return -1;
		}
		else if (retVal != 1)
			continue;
		if (pRecvBuf[0x0c]==0x88 && pRecvBuf[0x0d]==0x8e)		//判断是否802.1x
		{
			switch(pRecvBuf[0x12])
			{
			case 0x01:					//Request，验证用户名或者密码时收到
				switch (pRecvBuf[0x16])	//判断EAP Type
				{
				case 0x01:				//Request Identity
					if ( bFirst )
					{
						memcpy(mainDlg->m_bDestMAC ,pRecvBuf+6, 6);
						strTemp.Format(LoadString(IDS_DESTMAC), pRecvBuf[6], pRecvBuf[7], pRecvBuf[8], pRecvBuf[9], pRecvBuf[10], pRecvBuf[11]);
						mainDlg->Output(strTemp, 2);
						bFirst = FALSE;
					}
					memcpy( mainDlg->m_bMD5Source, pRecvBuf+0x10, 0x20 );
					mainDlg->PostMessage( WM_SYSCOMMAND, IDT_ACK_NAME );
					break;

				case 0x04:				//Request MD5-Challenge
					memcpy( mainDlg->m_bMD5Source, pRecvBuf+0x10, 0x20 );
					memcpy(mainDlg->m_bMD5SeedV3,pRecvBuf+24,16);//added by me
					mainDlg->PostMessage( WM_SYSCOMMAND, IDT_ACK_PSWD );
					break;
				}
				break;

			case 0x03:					//Success
				mainDlg->Output(LoadString(IDS_SUCCESS));
				sLen = ((USHORT)pRecvBuf[0x1a]<<8)|pRecvBuf[0x1b];
				if (sLen != 0)
				{
					char *serverMsg = new char[sLen-1];
					memcpy(serverMsg, pRecvBuf+0x1e, sLen-2);
					serverMsg[sLen-2] = '\0';
					mainDlg->m_sServerMsg = serverMsg;
					delete []serverMsg;
					mainDlg->Output(LoadString(IDS_SERVER_MSG)+mainDlg->m_sServerMsg);
				}
				else
					mainDlg->m_sServerMsg.Empty();
				mainDlg->PostMessage(WM_SYSCOMMAND, IDT_SHOWMSG);
				sLen = 0x1c+pRecvBuf[0x1b]+0x69+24;
				*(u_int32_t *)mainDlg->m_bEchoSource = ntohl(*(u_int32_t *)(pRecvBuf+sLen));
				for (sLen=0; sLen<4; sLen++)
					mainDlg->m_bEchoSource[sLen] = Alog(mainDlg->m_bEchoSource[sLen]);
				mainDlg->PostMessage( WM_SYSCOMMAND, IDT_ACK_ECHO );
				break;

			case 0x04:					//认证失败
				sLen = ((USHORT)pRecvBuf[0x1a]<<8)|pRecvBuf[0x1b];
				if (sLen != 0)
				{
					char *serverMsg = new char[sLen-1];
					memcpy(serverMsg, pRecvBuf+0x1e, sLen-2);
					serverMsg[sLen-2] = '\0';
					mainDlg->m_sServerMsg = serverMsg;
					delete []serverMsg;
					mainDlg->Output(LoadString(IDS_FAILURE));
					mainDlg->Output(LoadString(IDS_SERVER_MSG)+mainDlg->m_sServerMsg);
				}
				mainDlg->PostMessage(WM_SYSCOMMAND, IDT_SHOWMSG);
				if (mainDlg->m_iState == IDT_ACK_ECHO)
					mainDlg->PostMessage(WM_SYSCOMMAND, IDT_FIND_SERVER);
				break;
			}//end switch
		}//end if
		else if(pRecvBuf[0x0c] ==0x08 && pRecvBuf[0x0d]==0x06 && mainDlg->m_bBandMac!=0)		//判断是否ARP
		{
			if (memcmp(pRecvBuf+0x1c, mainDlg->m_bGateIP, 4)==0)
			{
				if (mainDlg->m_bBandMac == 1)
				{
					memcpy(mainDlg->m_bGateMAC, pRecvBuf+0x16, 6);
					strTemp.Format(LoadString(IDS_GATEMAC),
						pRecvBuf[0x16], pRecvBuf[0x17], pRecvBuf[0x18], pRecvBuf[0x19], pRecvBuf[0x1a], pRecvBuf[0x1b]);
					mainDlg->Output(strTemp, 2);
					strTemp.Format(_T("-s %d.%d.%d.%d %02x-%02x-%02x-%02x-%02x-%02x"),
						mainDlg->m_bGateIP[0], mainDlg->m_bGateIP[1], mainDlg->m_bGateIP[2], mainDlg->m_bGateIP[3],
						pRecvBuf[0x16], pRecvBuf[0x17], pRecvBuf[0x18], pRecvBuf[0x19], pRecvBuf[0x1a], pRecvBuf[0x1b]);
					ShellExecute(NULL, _T("open"), _T("arp"), strTemp, NULL, SW_HIDE);
					mainDlg->m_bBandMac = 2;
				}
				else if ((pRecvBuf[0x15]==0x02 && memcmp(pRecvBuf+0x26, mainDlg->m_bLocalIP, 4)==0))
				{
					if (memcmp(mainDlg->m_bGateMAC, pRecvBuf+0x16, 6) != 0)
					{
						mainDlg->m_sServerMsg.Format(LoadString(IDS_ARP_ALERT),
							pRecvBuf[0x16], pRecvBuf[0x17], pRecvBuf[0x18], pRecvBuf[0x19], pRecvBuf[0x1a], pRecvBuf[0x1b]);
						mainDlg->PostMessage(WM_SYSCOMMAND, IDT_SHOWMSG);
						mainDlg->Output(mainDlg->m_sServerMsg);
					}
				}
			}
		}
	}
	return 0;
}

LRESULT CMentoHUSTDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message == WM_QUERYENDSESSION)
		CDialog::OnCancel();
	else if (message == WM_TASKBARCREATED)
		Shell_NotifyIcon(NIM_ADD, &m_tnid);
	return CDialog::WindowProc(message, wParam, lParam);
}
int CMentoHUSTDlg::InitStartPacket(byte* startpacket)
{
	byte  temp[524];
	memset(temp,0,524);
	memcpy_s(temp,524,start_packet,524);
	//if modification is needy, do here
	memcpy_s(temp+0x06,6, m_bLocalMAC,6);
	memcpy_s(temp + 0x6c, 6, m_bLocalMAC, 6);
	UINT8 *dhcpinfo = getdhcpinfo();
	memcpy(temp + 0x12, dhcpinfo, 23);
	CGetHDSerial hdserial;
	char * hdserialchar = hdserial.GetHDSerial();
	memcpy(temp + 0x18b, hdserialchar, strlen(hdserialchar));
	memcpy_s(startpacket, 524, temp, 524);
	return 0;
}
int CMentoHUSTDlg::sendstart()
{
	byte packet[524];
	InitStartPacket(packet);
	return pcap_sendpacket(m_pAdapter, packet, 524);
}
int CMentoHUSTDlg::InitIdentifyPacket(byte* identifypacket)
{
	byte  temp[540];
	memset(temp, 0, 540);
	memcpy_s(temp, 540, identify_packet, 540);//学号必须是11位的。不然得改
	//if modification is needy, do here
	memcpy_s(temp + 0x06, 6, m_bLocalMAC, 6);
	memcpy_s(temp + 0x6c, 6, m_bLocalMAC, 6);
	memcpy_s(temp, 6, m_bDestMAC, 6);
	UINT8 *dhcpinfo = getdhcpinfo();
	memcpy(temp + 0x22, dhcpinfo, 23);
	//char* uname = (char*)m_sUsername.GetBuffer();

	int n = m_sUsername.GetLength();
	int len1 = WideCharToMultiByte(CP_ACP, 0, m_sUsername, n, NULL, 0, NULL, NULL);
	char *uname = new char[len1 + 1];
	WideCharToMultiByte(CP_ACP, 0, m_sUsername, n, uname, len1, NULL, NULL);
	uname[len1] = '\0';
	CGetHDSerial hdserial;
	char * hdserialchar = hdserial.GetHDSerial();
	memcpy(temp + 0x19b, hdserialchar, strlen(hdserialchar));
	memcpy(temp+23,uname,11);
	memcpy_s(identifypacket, 540, temp, 540);
	return 0;
}
int CMentoHUSTDlg::sendidentify()
{
	byte packet[540];
	InitIdentifyPacket(packet);
	return pcap_sendpacket(m_pAdapter, packet, 540);
}
typedef unsigned char u_char;
u_char *checkPass(u_char id, const u_char *md5Seed, int seedLen, char* password)//id=2
{
	u_char md5Src[80];
	int md5Len = strlen(password);
	md5Src[0] = id;
	memcpy(md5Src + 1, password, md5Len);
	md5Len++;
	memcpy(md5Src + md5Len, md5Seed, seedLen);
	md5Len += seedLen;
	return ComputeHash(md5Src, md5Len);
}

extern "C"
{
	char * _cdecl _ZN10CVz_APIApp11PrepareDataEPciS0_PKc(char*, char*, unsigned int, unsigned char*);
}
int CMentoHUSTDlg::InitMD5ChallengePacket(byte * packet)
{
	byte temp[573] = { 0 };
	memcpy(temp,md5challenge_packet,573);
	memcpy_s(temp + 0x06, 6, m_bLocalMAC, 6);
	memcpy_s(temp + 0x7c, 6, m_bLocalMAC, 6);
	memcpy_s(temp, 6, m_bDestMAC, 6);
	UINT8 *dhcpinfo=getdhcpinfo();
	memcpy(temp+0x33,dhcpinfo,23);
//	char * uname = (char*)m_sUsername.GetBuffer();
	//char * pass = (char*)m_sPassword.GetBuffer();

		int n = m_sUsername.GetLength();
		int len1 = WideCharToMultiByte(CP_ACP,0,m_sUsername,n,NULL,0,NULL,NULL);
		char *uname = new char[len1 +1];
		WideCharToMultiByte(CP_ACP,0,m_sUsername,n,uname,len1,NULL,NULL);
		uname[len1] = '\0';


		int m = m_sPassword.GetLength();
		int len2 = WideCharToMultiByte(CP_ACP, 0, m_sPassword, m, NULL, 0, NULL, NULL);
		char *pass = new char[len2 + 1];
		WideCharToMultiByte(CP_ACP, 0, m_sPassword, m, pass, len2, NULL, NULL);
		pass[len2] = '\0';


	unsigned char* checkpass = checkPass(2,m_bMD5SeedV3,16,pass);
	memcpy(temp+0x18,checkpass,0x10);
	
	char *md52 = computePwd(m_bMD5SeedV3,uname,pass);
	memcpy(temp + 0x9b, md52, 16);
	unsigned int type = (m_bMD5SeedV3[0] + m_bMD5SeedV3[3]) % 5;
	char *unknown = (char*)malloc(4096);
	char  v3hash[256] = { 0 };
	_ZN10CVz_APIApp11PrepareDataEPciS0_PKc(unknown,v3hash,type,(unsigned char*)m_bMD5SeedV3);
	memcpy(temp+0x10c,v3hash,128);
	CGetHDSerial hdserial;
	char * hdserialchar= hdserial.GetHDSerial();
	memcpy(temp+0x1bc,hdserialchar,strlen(hdserialchar));
	memcpy(packet,temp,573);
	return 0;
}
int CMentoHUSTDlg::sendmd5challenge()
{
	byte packet[573];
	InitMD5ChallengePacket(packet);
	return pcap_sendpacket(m_pAdapter, packet, 573);
}
extern UCHAR* ComputeHash1(UCHAR* src, UINT4 len);
char * CMentoHUSTDlg::computePwd(const unsigned char *md5, const char* username, const char* password)
{
	static char buf[20];

	unsigned char tmp[40];
	int tmp_len = 0;
	tmp_len = strlen(username);
	strcpy((char*)tmp, username);
	memcpy(tmp + tmp_len, md5, 16);
	tmp_len += 16;

	memcpy(buf, ComputeHash(tmp, tmp_len), 16);

	memset(tmp, 0, 16);
	strcpy((char*)tmp, password);

	int i;
	for (i = 0; i<16; ++i)
		buf[i] ^= tmp[i];
	return buf;
}
static const uint16_t crc16tab[256] = {
	0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
	0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
	0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
	0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
	0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
	0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
	0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
	0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
	0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
	0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
	0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
	0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
	0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
	0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
	0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
	0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
	0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
	0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
	0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
	0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
	0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
	0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
	0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
	0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
	0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
	0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
	0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
	0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
	0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
	0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
	0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
	0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};

uint16_t crc16(const uint8_t *buf, int len) {
	int counter;
	uint16_t crc = 0;
	for (counter = 0; counter < len; counter++)
		crc = (crc << 8) ^ crc16tab[((crc >> 8) ^ *buf++) & 0x00FF];
	return crc;
}

void rj_encode(uint8_t *buf, int len)
{
	if (len > 0)
	{
		for (int i = 0; i < len; ++i)
		{
			buf[i] = ~(((buf[i] & 0x10) >> 1) | ((buf[i] & 0x20) >> 3) | ((buf[i] & 0x40) >> 5) | ((uint32_t)buf[i] >> 7) | (buf[i] & 8) << 1 | (buf[i] & 4) << 3 | (buf[i] & 2) << 5 | ((buf[i] & 1) << 7));
		}
	}
}

void rj_decode(uint8_t *buf, int len)
{
	if (len > 0)
	{
		for (int i = 0; i < len; ++i)
		{
			buf[i] = ((~buf[i] & 0x10) >> 1) | ((~buf[i] & 0x20) >> 3) | ((~buf[i] & 0x40) >> 5) | ((uint8_t)~buf[i] >> 7) | 2 * (~buf[i] & 8) | 8 * (~buf[i] & 4) | ((~buf[i] & 1) << 7) | 32 * (~buf[i] & 2);
		}
	}
}
UINT8 * CMentoHUSTDlg::getdhcpinfo()
{
	UINT8* temp = (UINT8 *)malloc(23);
	DHCP_INFO _dhcp_info = { 0 };
	DHCP_INFO * dhcp_info = &_dhcp_info;
	dhcp_info->magic[0] = 0x00;
	dhcp_info->magic[1] = 0x00;
	dhcp_info->magic[2] = 0x13;
	dhcp_info->magic[3] = 0x11;
	*(UINT32*)dhcp_info->gateway = *(UINT32*)m_bGateIP;
	*(UINT32*)dhcp_info->ip = *(UINT32*)m_bLocalIP;
	*(UINT32*)dhcp_info->netmask = *(UINT32*)m_bLocalMask;
	*(UINT32*)dhcp_info->dns = *(UINT32*)m_bLocalDNS;
	dhcp_info->dhcp_type = 0;
	*(uint16_t*)&_dhcp_info.crc16_hash = htons(crc16((uint8_t*)&_dhcp_info, 21));
	rj_encode((uint8_t*)&_dhcp_info, sizeof(_dhcp_info));
	memcpy(temp,dhcp_info,23);
	return temp;
}