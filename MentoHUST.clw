; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMentoHUSTDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MentoHUST.h"

ClassCount=6
Class1=CMentoHUSTApp
Class2=CMentoHUSTDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_MENTOHUST_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_CFG_ACCOUNT
Resource4=IDD_CFG_SYSTEM
Resource5=IDD_CONFIGBOX
Class4=CConfigDlg
Resource6=IDD_ABOUTBOX
Class5=CSystemPage
Class6=CAccountPage
Resource7=IDR_TRAY_MENU

[CLS:CMentoHUSTApp]
Type=0
HeaderFile=source\mentohust.h
ImplementationFile=source\mentohust.cpp
BaseClass=CWinApp
LastObject=CMentoHUSTApp

[CLS:CMentoHUSTDlg]
Type=0
HeaderFile=source\mentohustdlg.h
ImplementationFile=source\mentohustdlg.cpp
BaseClass=CDialog
LastObject=CMentoHUSTDlg
Filter=D
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=source\mentohustdlg.h
ImplementationFile=source\mentohustdlg.cpp
BaseClass=CDialog
LastObject=CAboutDlg
Filter=D
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177294
Control2=IDC_STATIC,static,1350696960
Control3=IDOK,button,1342373889
Control4=IDC_SC_CONTRACT,static,1342374144
Control5=IDC_SC_CHECKNEW,static,1342373888

[DLG:IDD_MENTOHUST_DIALOG]
Type=1
Class=CMentoHUSTDlg
ControlCount=15
Control1=IDC_SC_LOGO,static,1342177806
Control2=IDC_STATIC,button,1342177287
Control3=IDOK,button,1342242817
Control4=IDC_BN_OUTPUT,button,1342242816
Control5=IDC_BN_OPTION,button,1342242816
Control6=IDCANCEL,button,1342242816
Control7=IDC_BN_ABOUT,button,1342242816
Control8=IDC_BN_HELP,button,1342242816
Control9=IDC_BN_CLEAR,button,1342242816
Control10=IDC_STATIC,static,1342308864
Control11=IDC_CB_ACCOUNT,combobox,1344339971
Control12=IDC_STATIC,static,1342308864
Control13=IDC_CB_ADAPTER,combobox,1344339971
Control14=IDC_SC_STATE,static,1350697472
Control15=IDC_ED_OUTPUT,edit,1352665284

[DLG:IDD_CONFIGBOX]
Type=1
Class=CConfigDlg
ControlCount=3
Control1=IDC_TAB,SysTabControl32,1342242816
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[DLG:IDD_CFG_ACCOUNT]
Type=1
Class=CAccountPage
ControlCount=6
Control1=IDC_ED_USERNAME,edit,1350631552
Control2=IDC_ED_PASSWORD,edit,1350631552
Control3=IDC_IPADDRESS,SysIPAddress32,1342242816
Control4=IDC_BN_ADD,button,1342242816
Control5=IDC_BN_DEL,button,1342242816
Control6=IDC_LS_ACCOUNT,SysListView32,1350631425

[DLG:IDD_CFG_SYSTEM]
Type=1
Class=CSystemPage
ControlCount=15
Control1=IDC_CK_AUTORUN,button,1342242819
Control2=IDC_CK_AUTOCERT,button,1342242819
Control3=IDC_CK_AUTOMIN,button,1342242819
Control4=IDC_CK_BANDMAC,button,1342242819
Control5=IDC_STATIC,static,1342308864
Control6=IDC_CB_STARTMODE,combobox,1344339971
Control7=IDC_STATIC,static,1342308864
Control8=IDC_CB_DHCPMODE,combobox,1344339971
Control9=IDC_STATIC,static,1342308864
Control10=IDC_ED_TIMEOUT,edit,1350639744
Control11=IDC_STATIC,static,1342308864
Control12=IDC_ED_ECHOTIME,edit,1350639744
Control13=IDC_CK_PACKAGE,button,1342242819
Control14=IDC_BN_BROWSER,button,1342242816
Control15=IDC_ED_PATH,edit,1350633600

[CLS:CConfigDlg]
Type=0
HeaderFile=Source\ConfigDlg.h
ImplementationFile=Source\ConfigDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CConfigDlg

[MNU:IDR_TRAY_MENU]
Type=1
Class=?
Command1=ID_MENU_RESTORE
Command2=ID_MENU_CONNECT
Command3=ID_MENU_CONFIG
Command4=ID_MENU_HELP
Command5=ID_MENU_ABOUT
Command6=ID_MENU_EXIT
CommandCount=6

[CLS:CSystemPage]
Type=0
HeaderFile=Source\SystemPage.h
ImplementationFile=Source\SystemPage.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BN_CATCH
VirtualFilter=dWC

[CLS:CAccountPage]
Type=0
HeaderFile=Source\AccountPage.h
ImplementationFile=Source\AccountPage.cpp
BaseClass=CDialog
Filter=D
LastObject=CAccountPage
VirtualFilter=dWC

