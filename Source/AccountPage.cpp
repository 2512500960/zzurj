// AccountPage.cpp : implementation file
//

#include "stdafx.h"
#include "MentoHUST.h"
#include "AccountPage.h"
#include "Algorithm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccountPage dialog


CAccountPage::CAccountPage(CWnd* pParent /*=NULL*/)
	: CDialog(CAccountPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAccountPage)
	m_sUsername = _T("");
	m_sPassword = _T("");
	//}}AFX_DATA_INIT
}


void CAccountPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccountPage)
	DDX_Control(pDX, IDC_LS_ACCOUNT, m_ListCtrl);
	DDX_Control(pDX, IDC_IPADDRESS, m_IPCtrl);
	DDX_Text(pDX, IDC_ED_USERNAME, m_sUsername);
	DDV_MaxChars(pDX, m_sUsername, 65);
	DDX_Text(pDX, IDC_ED_PASSWORD, m_sPassword);
	DDV_MaxChars(pDX, m_sPassword, 63);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAccountPage, CDialog)
	//{{AFX_MSG_MAP(CAccountPage)
	ON_BN_CLICKED(IDC_BN_ADD, OnBnAdd)
	ON_BN_CLICKED(IDC_BN_DEL, OnBnDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccountPage message handlers

BOOL CAccountPage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitListCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAccountPage::InitListCtrl()
{
	m_ListCtrl.InsertColumn(0, LoadString(IDS_USERNAME), LVCFMT_LEFT, 87);		//�û���
	m_ListCtrl.InsertColumn(1, LoadString(IDS_PASSWORD), LVCFMT_LEFT, 87);		//����
	m_ListCtrl.InsertColumn(2, LoadString(IDS_IPADDRESS), LVCFMT_LEFT, 102);	//IP��ַ
	DWORD dwStyle = m_ListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;		//ѡ��ĳ��ʹ���и���
	dwStyle |= LVS_EX_GRIDLINES;			//�����ߣ�ֻ������report����listctrl��
	m_ListCtrl.SetExtendedStyle(dwStyle);	//������չ���
	ReadConfig();							//��ʼ������
}

void CAccountPage::OnBnAdd()
{
	if (!UpdateData())
		return;
	if (m_sUsername.IsEmpty() || m_sPassword.IsEmpty())
	{	//��ܰ��ʾ|�û��������벻����Ϊ��ֵ��
		MessageBox(LoadString(IDS_ACCOUNT_EMPTY), LoadString(IDS_NOTIFYMSG), MB_OK|MB_ICONWARNING);
		return;
	}
	LVFINDINFO info;
	info.flags = LVFI_PARTIAL|LVFI_STRING;   
	info.psz = m_sUsername;
	if (m_ListCtrl.FindItem(&info) != -1)
	{	//��ܰ��ʾ|���˺��Ѵ��ڣ�
		MessageBox(LoadString(IDS_ACCOUNT_EXIST), LoadString(IDS_NOTIFYMSG), MB_OK|MB_ICONWARNING);
		return;
	}
	CString strPassword;
	char *szPassword = UnicodeToUTF8(m_sPassword);
	char buf[90];
	EncodeRuijie(buf, szPassword);
	delete []szPassword;
	strPassword = buf;
	BYTE bIP[4];
	m_IPCtrl.GetAddress((DWORD &)bIP);
	CString strIP;
	strIP.Format(_T("%d.%d.%d.%d"), bIP[3], bIP[2], bIP[1], bIP[0]);
	int nItem = m_ListCtrl.GetItemCount();
	m_ListCtrl.InsertItem(nItem, m_sUsername);
	m_ListCtrl.SetItemText(nItem, 1, strPassword);
	m_ListCtrl.SetItemText(nItem, 2, strIP);
}

void CAccountPage::OnBnDel() 
{
	for(int i=0; i<m_ListCtrl.GetItemCount(); )
	{
		if (m_ListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			m_ListCtrl.DeleteItem(i);
		else
			i++;
	}
}

BOOL CAccountPage::WriteConfig()
{
	CString strFileName = GetAppPath() + LoadString(IDS_INI_FILE);
	CString strSectionName, strKeyValue;
	int oldAccountCount = GetPrivateProfileInt(_T("Parameters"), _T("AccountCount"), 0, strFileName);
	int newAccountCount = m_ListCtrl.GetItemCount();
	strKeyValue.Format(_T("%d"), newAccountCount);
	if (!WritePrivateProfileString(_T("Parameters"), _T("AccountCount"), strKeyValue, strFileName))
	{	//��ܰ��ʾ|��������ʧ�ܣ�
		MessageBox(LoadString(IDS_WRITE_ERROR), LoadString(IDS_NOTIFYMSG), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	int i;
	for (i=0; i<newAccountCount; i++)
	{
		strSectionName.Format(_T("Account%d"), i);
		strKeyValue = m_ListCtrl.GetItemText(i, 0);
		WritePrivateProfileString(strSectionName, _T("Username"), strKeyValue, strFileName);
		strKeyValue = m_ListCtrl.GetItemText(i, 1);
		WritePrivateProfileString(strSectionName, _T("Password"), strKeyValue, strFileName);
		strKeyValue = m_ListCtrl.GetItemText(i, 2);
		WritePrivateProfileString(strSectionName, _T("IP"), strKeyValue, strFileName);
	}
	for (i=newAccountCount; i<oldAccountCount; i++)
	{
		strSectionName.Format(_T("Account%d"), i);
		WritePrivateProfileString(strSectionName, NULL, NULL, strFileName);
	}
	return TRUE;
}

void CAccountPage::ReadConfig()
{
	CString strFileName = GetAppPath() + LoadString(IDS_INI_FILE);
	CString strSectionName, strKeyValue;
	TCHAR szKeyValue[70];
	int AccountCount = GetPrivateProfileInt(_T("Parameters"), _T("AccountCount"), 0, strFileName);
	int nItem = -1;
	for (int i=0; i<AccountCount; i++)
	{
		strSectionName.Format(_T("Account%d"), i);
		GetPrivateProfileString(strSectionName, _T("Username"), _T(""), szKeyValue, 70, strFileName);
		strKeyValue = szKeyValue;
		if (strKeyValue.IsEmpty())
			continue;
		m_ListCtrl.InsertItem(++nItem, strKeyValue);
		GetPrivateProfileString(strSectionName, _T("Password"), _T(""), szKeyValue, 70, strFileName);
		strKeyValue = szKeyValue;
		m_ListCtrl.SetItemText(nItem, 1, strKeyValue);
		GetPrivateProfileString(strSectionName, _T("IP"), _T("0.0.0.0"), szKeyValue, 70, strFileName);
		strKeyValue = szKeyValue;
		m_ListCtrl.SetItemText(nItem, 2, strKeyValue);
	}
	UpdateData(FALSE);
}

void CAccountPage::OnOK()
{
	OnBnAdd();
}

void CAccountPage::OnCancel()
{
	::PostMessage(GetParent()->m_hWnd, WM_CLOSE, 0, 0);
	CDialog::OnCancel();
}
