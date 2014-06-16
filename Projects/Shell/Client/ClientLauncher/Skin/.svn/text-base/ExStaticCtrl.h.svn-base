#if !defined(AFX_STATICVIEW_H__3E54AA16_75F6_445F_A394_62683D67315E__INCLUDED_)
#define AFX_STATICVIEW_H__3E54AA16_75F6_445F_A394_62683D67315E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticView window

class CStaticEx : public CStatic
{
// Construction
public:
	CStaticEx();

// Attributes
public:
	void		SetViewString(LPCTSTR szString,BOOL bDrawBack = FALSE,char* url=NULL);
	CString		GetViewString(){return m_szViewString;}
	void		SetColor(COLORREF color){m_ref = color;}
	void		SetTxtAlign(UINT nAlign){m_nFormat = nAlign;}
// Operations
public:
	void		Draw();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticView)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	CString		m_szViewString;
	COLORREF	m_ref;
	UINT		m_nFormat;
	BOOL		m_bDrawBack;
	CString		m_szUrl;
	HCURSOR		m_hCur;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICVIEW_H__3E54AA16_75F6_445F_A394_62683D67315E__INCLUDED_)
