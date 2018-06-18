// StringList.h
//

#ifndef HUSTMOON_STRINGLIST_H
#define	HUSTMOON_STRINGLIST_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// StringList
class StringList
{
public:
	StringList(LPCTSTR String);
	virtual ~StringList();
	void AddString(StringList *Next);
	CString GetString(int iIndex);
	int FindString(LPCTSTR String, BOOL bNoCase=FALSE);
	StringList *GetNext();

private:
	CString m_sString;
	StringList *m_pNext;
};
#endif