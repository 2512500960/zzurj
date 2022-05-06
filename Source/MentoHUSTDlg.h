// MentoHUSTDlg.h : header file
//

#if !defined(AFX_MENTOHUSTDLG_H__A269FD29_1BD5_4C51_8515_4CD8DF52099C__INCLUDED_)
#define AFX_MENTOHUSTDLG_H__A269FD29_1BD5_4C51_8515_4CD8DF52099C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "StringList.h"
#include "HyperLink.h"

const LPCTSTR GUI_ID = _T("MentoHUST-8BDAA526-CBE4-4797-8D3E-E63C8D362894");
const UINT WM_TASKBARCREATED = ::RegisterWindowMessage(_T("TaskbarCreated"));
#define PCAP_FILTER		"(ether[12:2]=0x888e and ether dst %02x:%02x:%02x:%02x:%02x:%02x) or ether[12:2]=0x0806"

#define IDT_DISCONNECT				(WM_USER+101)
#define IDT_FIND_SERVER				(WM_USER+102)
#define IDT_ACK_NAME				(WM_USER+103)
#define IDT_ACK_PSWD				(WM_USER+104)
#define	IDT_ACK_ECHO				(WM_USER+105)
#define	IDT_DHCP_RENEW				(WM_USER+106)  // wm_user=1024
#define IDT_INIT_DATA				(WM_USER+107)
#define IDT_SHOWMSG					(WM_USER+108)
#define CERT_CYCLE_TIMER			(WM_USER+109)
#define SHOW_CYCLE_TIMER			(WM_USER+110)

#define MAX_OUTPUT_LINES						500
#define MAX_ERROR_TIMES							5

UINT DhcpThreadFunc( LPVOID pParam );
UINT CertThreadFunc( LPVOID pParam );
/////////////////////////////////////////////////////////////////////////////
// CMentoHUSTDlg dialog

class CMentoHUSTDlg : public CDialog
{
// Construction
public:
	CMentoHUSTDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMentoHUSTDlg)
	enum { IDD = IDD_MENTOHUST_DIALOG };
	CHyperLink	m_linkLogo;
	CComboBox	m_AdapterList;
	CComboBox	m_AccountList;
	CString	m_sStateBoard;
	CString	m_sStateArea;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMentoHUSTDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnCertCommand(UINT nID);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	int InitStartPacket(byte * startpacket);

	int sendstart();

	int InitIdentifyPacket(byte * identifypacket);

	int sendidentify();

	int InitMD5ChallengePacket(byte * packet);

	int sendmd5challenge();

	char * computePwd(const unsigned char * md5, const char * username, const char * password);

	UINT8 * getdhcpinfo();

	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMentoHUSTDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnAbout();
	afx_msg void OnBnClear();
	afx_msg void OnBnHelp();
	afx_msg void OnBnOption();
	afx_msg void OnBnOutput();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void Output(LPCTSTR Msg, int Type = 0);	//���״̬
	BOOL SendPackage();				//��������
	
	int	m_iState;				//��֤״̬
	pcap_t	*m_pAdapter;		//�������
	struct bpf_program m_bfilter;	//������
	BYTE	m_bDestMAC[6];		//������MAC
	BYTE	m_bMD5Source[0x20];	//MD5����
	BYTE    m_bMD5SeedV3[16];	//MD5����v3
	BYTE    m_requestID[1];        //����������ID
	BYTE	m_bEchoSource[4];	//Echoʱ������
	CString	m_sServerMsg;		//��������Ϣ
	CString m_sShowMsg;			//����ʾ��Ϣ
	BOOL	m_bBandMac;			//������MAC��
	BYTE	m_bGateMAC[6];		//����MAC
	BYTE	m_bGateIP[4];		//��������
	BYTE	m_bLocalIP[4];		//����IP

private:
	void MyInitDialog();			//��ʼ���Ի���	
	void InitTrayData();			//��ʼ����������
	BOOL OpenAdapter();				//��ѡ�������
	BOOL GetAccount();				//��ȡ�û�������IP
	void SaveAccountAndAdapter();	//����ѡ����˺ź�����
	BOOL InitAdapterList();			//��ʼ�������б�
	void InitAccountList();			//��ʼ���˺��б�
	void ReadConfig();				//��ȡ����
	BOOL ReadRuijieAccount();		//�����˺��б�Ϊ�գ��Ͷ�ȡ���ע����˺�
	void InitInterface();			//��ʼ������
	void ChangeTrayIcon();			//�ı�����ͼ��
	void ToTray(int nTray);			//��С��������
	int ShowDlg(CDialog *dlg);		//��ʾ�����ڡ��͡����á��Ի���
	void CheckRuijie();				//�ͻ���У���㷨
	void FileError(BYTE *pBuffer, BOOL bStart);	//��ȡ�ļ�����
	void InitCertData();			//��ʼ������
	void InitHeader();				//��ʼ�����ݰ�ͷ��
	void InitDefault(BOOL bStart);	//Ĭ�ϳ�ʼ��
	void InitPackage(BOOL bStart);	//��ʼ����
	BOOL GetAdapterInfo();			//��ȡ������Ϣ
	int SendStartPackage();			//Start��
	int SendIdentityPackage();		//Identity��
	int SendMD5ChallengePackage();	//Md5��
	int SendEchoPackage();			//Echo��
	int SendLogoffPackage();		//Logoff��
	void SendArpPackage();			//ARP��
	void TimerCtrl(int timer);		//��ʱ������
	void ReadAccountAgain();		//���øı�����¶�ȡ

	CWinThread *m_pDhcpThread;		//DHCP�߳�
	CWinThread *m_pCertThread;		//��֤�߳�
	int	m_iBigHeight;			//�����Ի���߶�
	int	m_iSmallHeight;			//���ز��ֺ�߶�
	int m_iLastState;			//��һ��״̬
	int m_iErrorTimes;			//ʧ�ܴ���
	BOOL	m_bFullSize;		//�Ƿ�������ʾ
	NOTIFYICONDATA	m_tnid;		//����ͼ��
	StringList	*m_pAccountList;//�˺��б�
	StringList	*m_pAdapterList;//�����б�
	CString	m_sUsername;		//�û���
	CString	m_sPassword;		//����
	u_int32_t	m_uIP;			//IP
	BOOL	m_bAutoCert;		//���к��Զ���֤��
	BOOL	m_bAutoMin;			//��֤�ɹ���С����
	int		m_iStartMode;		//��ʼ�鲥ģʽ
	int		m_iDhcpMode;		//DHCP��ʽ
	int		m_iTimeout;			//��ʱ���
	int		m_iEchoTime;		//��Ӧ���
	BOOL	m_bUsePackage;		//�Ƿ�ʹ���Զ������ݰ�
	CString	m_sFilePath;		//�Զ������ݰ�·��
	BYTE	m_bSendPackage[0x3E8];//�������͵İ�
	BYTE	m_bPackage[0x217];	//����벿������
	u_int32_t	m_uEchoNo;	//Echoʱ�ڶ����ֳ�ʼֵ
	BYTE	m_bLocalMAC[6];		//����MAC
	BYTE	m_bLocalMask[4];	//��������
	BYTE	m_bLocalDNS[4];		//����DNS
	BOOL	m_bTimerSign;		//��ʱ���Ƿ���
	BOOL	m_bChanged;			//�����Ƿ�ı�
public:
//	afx_msg void OnStnClickedScLogo();
	afx_msg void OnStnClickedScLogo();
};
# define uint64_t unsigned __int64
# define uint32_t unsigned __int32
# define uint16_t unsigned __int16
# define uint8_t  unsigned __int8
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
typedef struct _dhcp_info {
	uint8_t magic[4]; /* 00 00 13 11 */
	uint8_t dhcp_type; /* dhcp_type == 1 */
	uint8_t ip[4];
	uint8_t netmask[4];
	uint8_t gateway[4];
	uint8_t dns[4];
	uint8_t crc16_hash[2]; /* Network byte order */
} DHCP_INFO;
#endif // !defined(AFX_MENTOHUSTDLG_H__A269FD29_1BD5_4C51_8515_4CD8DF52099C__INCLUDED_)
