// GetHDSerial.cpp: implementation of the CGetHDSerial class.
// Download by http://www.newxing.com/
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "GetHDSerial.h"
char  m_buffer[256];
WORD  m_serial[256];
DWORD m_OldInterruptAddress;
DWORDLONG m_IDTR;

// �ȴ�Ӳ�̿���
static unsigned int WaitHardDiskIdle()
{
	BYTE byTemp;

Waiting:
	_asm
	{
		mov dx, 0x1f7
		in al, dx
		cmp al, 0x80
		jb Endwaiting
		jmp Waiting
	}
Endwaiting:
	_asm
	{
		mov byTemp, al
	}
	return byTemp;
}

//�жϷ������
void  _declspec(naked)InterruptProcess(void)
{
	int   byTemp;
	int   i;
	WORD temp;
	//����Ĵ���ֵ
	_asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
	}

	WaitHardDiskIdle();//�ȴ�Ӳ�̿���״̬
	_asm
	{
		mov dx, 0x1f6
		mov al, 0xa0
		out dx, al
	}
	byTemp = WaitHardDiskIdle(); //��ֱ����Ring3��ִ�еȴ�����������ѭ��
	if ((byTemp & 0x50) != 0x50)
	{
		_asm  // �ָ��ж��ֳ����˳��жϷ������
		{
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
			iretd
		}
	}

	_asm
	{
		mov dx, 0x1f6 //����˿�1f6,ѡ��������0
		mov al, 0xa0
		out dx, al
		inc dx
		mov al, 0xec
		out dx, al //���Ͷ���������������
	}
	byTemp = WaitHardDiskIdle();
	if ((byTemp & 0x58) != 0x58)
	{
		_asm  // �ָ��ж��ֳ����˳��жϷ������
		{
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
			iretd
		}
	}
	//��ȡӲ�̿�������ȫ����Ϣ
	for (i = 0; i<256; i++)
	{
		_asm
		{
			mov dx, 0x1f0
			in ax, dx
			mov temp, ax
		}
		m_serial[i] = temp;
	}
	_asm
	{
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
		iretd
	}
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGetHDSerial::CGetHDSerial()
{

}

CGetHDSerial::~CGetHDSerial()
{

}
// ��ȡӲ�����кź���
char* CGetHDSerial::GetHDSerial()
{
	m_buffer[0] = '\n';
	// �õ���ǰ����ϵͳ�汾
	OSVERSIONINFO OSVersionInfo;
	OSVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&OSVersionInfo);
	if (OSVersionInfo.dwPlatformId != VER_PLATFORM_WIN32_NT)
	{
		// Windows 9x/ME�¶�ȡӲ�����к�
		WORD m_wWin9xHDSerial[256];
		Win9xReadHDSerial(m_wWin9xHDSerial);
		strcpy(m_buffer, WORDToChar(m_wWin9xHDSerial, 10, 19));
	}
	else
	{
		// Windows NT/2000/XP�¶�ȡӲ�����к�
		DWORD m_wWinNTHDSerial[256];
		// �ж��Ƿ���SCSIӲ��
		if (!WinNTReadIDEHDSerial(m_wWinNTHDSerial))
			WinNTReadSCSIHDSerial(m_wWinNTHDSerial);
		strcpy(m_buffer, DWORDToChar(m_wWinNTHDSerial, 10, 19));
	}
	return m_buffer;
}

// Windows9X/MEϵͳ�¶�ȡӲ�����к�
void _stdcall CGetHDSerial::Win9xReadHDSerial(WORD * buffer)
{
	int i;
	for (i = 0; i<256; i++)
		buffer[i] = 0;
	_asm
	{
		push eax
		//��ȡ�޸ĵ��жϵ��ж����������ж��ţ���ַ
		sidt m_IDTR
		mov eax, dword ptr[m_IDTR + 02h]
		add eax, 3 * 08h + 04h
		cli
		//����ԭ�ȵ��ж���ڵ�ַ
		push ecx
		mov ecx, dword ptr[eax]
		mov cx, word ptr[eax - 04h]
		mov dword ptr m_OldInterruptAddress, ecx
		pop ecx
		//�����޸ĵ��ж���ڵ�ַΪ�µ��жϴ��������ڵ�ַ
		push ebx
		lea ebx, InterruptProcess
		mov word ptr[eax - 04h], bx
		shr ebx, 10h
		mov word ptr[eax + 02h], bx
		pop ebx
		//ִ���жϣ�ת��Ring 0������CIH����ԭ��
		int 3h
		//�ָ�ԭ�ȵ��ж���ڵ�ַ
		push ecx
		mov ecx, dword ptr m_OldInterruptAddress
		mov word ptr[eax - 04h], cx
		shr ecx, 10h
		mov word ptr[eax + 02h], cx
		pop ecx
		sti
		pop eax
	}
	for (i = 0; i<256; i++)
		buffer[i] = m_serial[i];
}

// Windows 9x/MEϵͳ�£��������ͣ�WORD����Ӳ����Ϣת��Ϊ�ַ����ͣ�char��
char * CGetHDSerial::WORDToChar(WORD diskdata[256], int firstIndex, int lastIndex)
{
	static char string[1024];
	int index = 0;
	int position = 0;

	// ���ո��ֽ���ǰ�����ֽ��ں��˳��������diskdata �����ݴ��뵽�ַ���string�� 
	for (index = firstIndex; index <= lastIndex; index++)
	{
		// �������еĸ��ֽ�
		string[position] = (char)(diskdata[index] / 256);
		position++;
		// �������еĵ��ֽ�
		string[position] = (char)(diskdata[index] % 256);
		position++;
	}
	//  ����ַ���������־
	string[position] = '\0';

	//  ɾ���ַ����пո�
	for (index = position - 1; index > 0 && ' ' == string[index]; index--)
		string[index] = '\0';

	return string;
}

// Windows NT/2000/XPϵͳ�£���˫�����ͣ�DWORD����Ӳ����Ϣת��Ϊ�ַ����ͣ�char��
char* CGetHDSerial::DWORDToChar(DWORD diskdata[256], int firstIndex, int lastIndex)
{
	static char string[1024];
	int index = 0;
	int position = 0;

	// ���ո��ֽ���ǰ�����ֽ��ں��˳��˫���еĵ��ִ��뵽�ַ���string�� 
	for (index = firstIndex; index <= lastIndex; index++)
	{
		// ��������еĸ��ֽ�
		string[position] = (char)(diskdata[index] / 256);
		position++;
		// ��������еĵ��ֽ�
		string[position] = (char)(diskdata[index] % 256);
		position++;
	}
	//  ����ַ���������־
	string[position] = '\0';

	//  ɾ���ַ����пո�
	for (index = position - 1; index > 0 && ' ' == string[index]; index--)
		string[index] = '\0';

	return string;
}

// Windows NT/2000/XP�¶�ȡIDEӲ�����к�
BOOL CGetHDSerial::WinNTReadIDEHDSerial(DWORD * buffer)
{
	BYTE IdOutCmd[sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];
	BOOL bFlag = FALSE;
	int  drive = 0;
	char driveName[256];
	HANDLE hPhysicalDriveIOCTL = 0;

	sprintf(driveName, "\\\\.\\PhysicalDrive%d", drive);
	//  Windows NT/2000/XP�´����ļ���Ҫ����ԱȨ��
	hPhysicalDriveIOCTL = CreateFileA(driveName,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING, 0, NULL);

	if (hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)
	{
		GETVERSIONOUTPARAMS VersionParams;
		DWORD               cbBytesReturned = 0;

		// �õ���������IO�������汾
		memset((void*)&VersionParams, 0, sizeof(VersionParams));
		if (DeviceIoControl(hPhysicalDriveIOCTL, IOCTL_GET_VERSION,
			NULL, 0, &VersionParams,
			sizeof(VersionParams),
			&cbBytesReturned, NULL))
		{
			if (VersionParams.bIDEDeviceMap > 0)
			{
				BYTE             bIDCmd = 0;   // IDE����ATAPIʶ������
				SENDCMDINPARAMS  scip;

				// ����������ǹ�������������IDE_ATAPI_IDENTIFY�� command,
				// �����������IDE_ATA_IDENTIFY��ȡ��������Ϣ
				bIDCmd = (VersionParams.bIDEDeviceMap >> drive & 0x10) ?
					IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;

				memset(&scip, 0, sizeof(scip));
				memset(IdOutCmd, 0, sizeof(IdOutCmd));
				// ��ȡ��������Ϣ
				if (WinNTGetIDEHDInfo(hPhysicalDriveIOCTL,
					&scip,
					(PSENDCMDOUTPARAMS)&IdOutCmd,
					(BYTE)bIDCmd,
					(BYTE)drive,
					&cbBytesReturned))
				{
					int m = 0;
					USHORT *pIdSector = (USHORT *)
						((PSENDCMDOUTPARAMS)IdOutCmd)->bBuffer;

					for (m = 0; m < 256; m++)
						buffer[m] = pIdSector[m];
					bFlag = TRUE;  // ��ȡӲ����Ϣ�ɹ�
				}
			}
		}
		CloseHandle(hPhysicalDriveIOCTL);  // �رվ��
	}
	return bFlag;
}

// WindowsNT/2000/XPϵͳ�¶�ȡSCSIӲ�����к�
BOOL CGetHDSerial::WinNTReadSCSIHDSerial(DWORD * buffer)
{
	buffer[0] = '\n';
	int controller = 0;
	HANDLE hScsiDriveIOCTL = 0;
	char   driveName[256];
	sprintf(driveName, "\\\\.\\Scsi%d:", controller);
	//  Windows NT/2000/XP���κ�Ȩ�޶����Խ���
	hScsiDriveIOCTL = CreateFileA(driveName,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING, 0, NULL);

	if (hScsiDriveIOCTL != INVALID_HANDLE_VALUE)
	{
		int drive = 0;
		DWORD dummy;
		for (drive = 0; drive < 2; drive++)
		{
			char buffer[sizeof(SRB_IO_CONTROL) + SENDIDLENGTH];
			SRB_IO_CONTROL *p = (SRB_IO_CONTROL *)buffer;
			SENDCMDINPARAMS *pin =
				(SENDCMDINPARAMS *)(buffer + sizeof(SRB_IO_CONTROL));
			// ׼������
			memset(buffer, 0, sizeof(buffer));
			p->HeaderLength = sizeof(SRB_IO_CONTROL);
			p->Timeout = 10000;
			p->Length = SENDIDLENGTH;
			p->ControlCode = IOCTL_SCSI_MINIPORT_IDENTIFY;
			strncpy((char *)p->Signature, "SCSIDISK", 8);
			pin->irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;
			pin->bDriveNumber = drive;
			// �õ�SCSIӲ����Ϣ
			if (DeviceIoControl(hScsiDriveIOCTL, IOCTL_SCSI_MINIPORT,
				buffer,
				sizeof(SRB_IO_CONTROL) +
				sizeof(SENDCMDINPARAMS) - 1,
				buffer,
				sizeof(SRB_IO_CONTROL) + SENDIDLENGTH,
				&dummy, NULL))
			{
				SENDCMDOUTPARAMS *pOut =
					(SENDCMDOUTPARAMS *)(buffer + sizeof(SRB_IO_CONTROL));
				IDSECTOR *pId = (IDSECTOR *)(pOut->bBuffer);
				if (pId->sModelNumber[0])
				{
					int n = 0;
					USHORT *pIdSector = (USHORT *)pId;

					for (n = 0; n < 256; n++)
						buffer[n] = pIdSector[n];
					return TRUE;  // ��ȡ�ɹ�                               
				}
			}
		}
		CloseHandle(hScsiDriveIOCTL);  // �رվ��
	}
	return FALSE;   // ��ȡʧ��
}

// Windows NT/2000/XP�¶�ȡIDE�豸��Ϣ
BOOL CGetHDSerial::WinNTGetIDEHDInfo(HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS pSCIP,
	PSENDCMDOUTPARAMS pSCOP, BYTE bIDCmd, BYTE bDriveNum,
	PDWORD lpcbBytesReturned)
{
	// Ϊ��ȡ�豸��Ϣ׼������
	pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;
	pSCIP->irDriveRegs.bFeaturesReg = 0;
	pSCIP->irDriveRegs.bSectorCountReg = 1;
	pSCIP->irDriveRegs.bSectorNumberReg = 1;
	pSCIP->irDriveRegs.bCylLowReg = 0;
	pSCIP->irDriveRegs.bCylHighReg = 0;

	// ����������λ��
	pSCIP->irDriveRegs.bDriveHeadReg = 0xA0 | ((bDriveNum & 1) << 4);

	// ���ö�ȡ����
	pSCIP->irDriveRegs.bCommandReg = bIDCmd;
	pSCIP->bDriveNumber = bDriveNum;
	pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;

	// ��ȡ��������Ϣ
	return (DeviceIoControl(hPhysicalDriveIOCTL, IOCTL_GET_DRIVE_INFO,
		(LPVOID)pSCIP,
		sizeof(SENDCMDINPARAMS) - 1,
		(LPVOID)pSCOP,
		sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1,
		lpcbBytesReturned, NULL));
}