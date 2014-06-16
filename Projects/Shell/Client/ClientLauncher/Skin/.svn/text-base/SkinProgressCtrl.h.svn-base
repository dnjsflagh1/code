#if !defined(AFX_MYPROGRESSCTRL_H__B5FB9D84_8D3C_4905_84C4_9CA8976A3C90__INCLUDED_)
#define AFX_MYPROGRESSCTRL_H__B5FB9D84_8D3C_4905_84C4_9CA8976A3C90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyProgressCtrl.h : header file
//
#include "MemFileDef.h"
/////////////////////////////////////////////////////////////////////////////
// CMyProgressCtrl window

class CSkinProgressCtrl : public CProgressCtrl
{
	HBITMAP m_hbitmapBar;
	HBITMAP m_hbitmapBkgnd;
	HBRUSH	m_brushBar;
	HBRUSH	m_brushBkgnd;
	HRGN	m_rgnBar;
	HRGN	m_rgnBkgnd;
	int		m_pos;
	int		m_nMax;
	void	_ShowBmp();
	void	_GetRegion(HBITMAP hBitmap, CRect* pBitmapArea,HRGN& wndRgn,DWORD dwColorKey);
// Construction
public:
	CSkinProgressCtrl();
	void	SetPoint(int pos);
	int		GetPoint();
	void	SetRange(int nMax);
	int		GetRange();
	BOOL	SetBitmap(UINT nIDResource);
	BOOL	SetBitmapBarFromFile(const char* szFileName,Memfile xFunc,DWORD dwColorKey);
	BOOL	SetBitmapBkgndFromFile(const char* szFileName,Memfile xFunc,DWORD dwColorKey);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyProgressCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkinProgressCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyProgressCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPROGRESSCTRL_H__B5FB9D84_8D3C_4905_84C4_9CA8976A3C90__INCLUDED_)
