#if !defined(AFX_RGNDLG_H__INCLUDED_)
#define AFX_RGNDLG_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRGNDlg dialog

class CRGNDlg : public CDialog
{
// Construction
public:
	CRGNDlg(UINT nIDTemplate,CWnd* pParent,std::string rgnfile);

	~CRGNDlg();
	
// Dialog Data
	//{{AFX_DATA(CRGNDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGNDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    float    m_xScale;
	float    m_yScale;


	std::string	m_rgnfile;
	HRGN     m_dialogrgn;
	CDC      m_dc;
	BOOL     m_bTrackMove;
	CPoint   m_ptMouse, 
		     m_ptLast;

	void InvertTracker(CPoint point);
	// Generated message map functions
	//{{AFX_MSG(CRGNDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CBrush mBh;
	CRect	mRect;
};

//{{AFX_INSERT_LOCATION}}

#endif 
