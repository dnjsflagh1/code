// SortStringArray.h: interface for the CSortStringArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SORTSTRINGARRAY_H__D7BE70A4_8781_11D4_BD73_000021479D21__INCLUDED_)
#define AFX_SORTSTRINGARRAY_H__D7BE70A4_8781_11D4_BD73_000021479D21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSortStringArray : public CStringArray  
{
public:
	CSortStringArray();
	virtual ~CSortStringArray();
public:
	void Sort();
private: 
	BOOL CompareAndSwap( int pos );
};

#endif // !defined(AFX_SORTSTRINGARRAY_H__D7BE70A4_8781_11D4_BD73_000021479D21__INCLUDED_)
