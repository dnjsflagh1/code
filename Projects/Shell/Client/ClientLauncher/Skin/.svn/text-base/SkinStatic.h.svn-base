#ifndef _JCH_SKIN_STATIC_H
#define _JCH_SKIN_STATIC_H
#include "MemFileDef.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CSkinStatic : public CStatic
{
	// Construction
public:
	CSkinStatic();

	// Attributes
public:
	BOOL		SetBitmapsByRes(UINT nBitmapID,DWORD dwColorKey =0x00FF00FF);
	BOOL		SetBitmapsByRes(LPCTSTR pBitmapName,DWORD dwColorKey =0x00FF00FF);
	BOOL		SetBitmapsByFile(const char* pFileName,Memfile xFunc,DWORD dwColorKey =0x00FF00FF);
	void		SetRegion(HBITMAP hBitmap, CRect* pBitmapArea, DWORD dwColorKey = 0x00FF00FF);
	// Operations
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticView)
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CSkinStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	HBITMAP		_bmpBackGround;
	DWORD		_bmpColorKey;
};

#endif