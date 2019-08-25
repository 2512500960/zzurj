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
	void Output(LPCTSTR Msg, int Type = 0);	//输出状态
	BOOL SendPackage();				//发包控制
	
	int	m_iState;				//认证状态
	pcap_t	*m_pAdapter;		//网卡句柄
	struct bpf_program m_bfilter;	//过滤器
	BYTE	m_bDestMAC[6];		//服务器MAC
	BYTE	m_bMD5Source[0x20];	//MD5种子
	BYTE    m_bMD5SeedV3[16];	//MD5种子v3
	BYTE	m_bEchoSource[4];	//Echo时的种子
	CString	m_sServerMsg;		//服务器消息
	CString m_sShowMsg;			//待显示消息
	BOOL	m_bBandMac;			//绑定网关MAC？
	BYTE	m_bGateMAC[6];		//网关MAC
	BYTE	m_bGateIP[4];		//本地网关
	BYTE	m_bLocalIP[4];		//本地IP

private:
	void MyInitDialog();			//初始化对话框	
	void InitTrayData();			//初始化托盘数据
	BOOL OpenAdapter();				//打开选择的网卡
	BOOL GetAccount();				//获取用户名密码IP
	void SaveAccountAndAdapter();	//保存选择的账号和网卡
	BOOL InitAdapterList();			//初始化网卡列表
	void InitAccountList();			//初始化账号列表
	void ReadConfig();				//读取配置
	BOOL ReadRuijieAccount();		//假如账号列表为空，就读取锐捷注册表账号
	void InitInterface();			//初始化界面
	void ChangeTrayIcon();			//改变托盘图标
	void ToTray(int nTray);			//最小化到托盘
	int ShowDlg(CDialog *dlg);		//显示“关于”和“设置”对话框
	void CheckRuijie();				//客户端校验算法
	void FileError(BYTE *pBuffer, BOOL bStart);	//读取文件出错
	void InitCertData();			//初始化数据
	void InitHeader();				//初始化数据包头不
	void InitDefault(BOOL bStart);	//默认初始化
	void InitPackage(BOOL bStart);	//初始化包
	BOOL GetAdapterInfo();			//获取网卡信息
	int SendStartPackage();			//Start包
	int SendIdentityPackage();		//Identity包
	int SendMD5ChallengePackage();	//Md5包
	int SendEchoPackage();			//Echo包
	int SendLogoffPackage();		//Logoff包
	void SendArpPackage();			//ARP包
	void TimerCtrl(int timer);		//定时器控制
	void ReadAccountAgain();		//设置改变后重新读取

	CWinThread *m_pDhcpThread;		//DHCP线程
	CWinThread *m_pCertThread;		//认证线程
	int	m_iBigHeight;			//完整对话框高度
	int	m_iSmallHeight;			//隐藏部分后高度
	int m_iLastState;			//上一次状态
	int m_iErrorTimes;			//失败次数
	BOOL	m_bFullSize;		//是否完整显示
	NOTIFYICONDATA	m_tnid;		//托盘图标
	StringList	*m_pAccountList;//账号列表
	StringList	*m_pAdapterList;//网卡列表
	CString	m_sUsername;		//用户名
	CString	m_sPassword;		//密码
	u_int32_t	m_uIP;			//IP
	BOOL	m_bAutoCert;		//运行后自动认证？
	BOOL	m_bAutoMin;			//认证成功最小化？
	int		m_iStartMode;		//开始组播模式
	int		m_iDhcpMode;		//DHCP方式
	int		m_iTimeout;			//超时间隔
	int		m_iEchoTime;		//响应间隔
	BOOL	m_bUsePackage;		//是否使用自定义数据包
	CString	m_sFilePath;		//自定义数据包路径
	BYTE	m_bSendPackage[0x3E8];//用来发送的包
	BYTE	m_bPackage[0x217];	//包后半部分数据
	u_int32_t	m_uEchoNo;	//Echo时第二部分初始值
	BYTE	m_bLocalMAC[6];		//本地MAC
	BYTE	m_bLocalMask[4];	//本地掩码
	BYTE	m_bLocalDNS[4];		//本地DNS
	BOOL	m_bTimerSign;		//定时器是否开启
	BOOL	m_bChanged;			//参数是否改变
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
