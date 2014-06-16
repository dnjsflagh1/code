#ifndef LINK_H_
#define LINK_H_

class CLink : public CStatic
{
public:
    CLink();
    virtual ~CLink();

public:

	CFont fUnderline;
	bool m_bigFont;
	bool m_isLinker;
	void * m_pParam;
	COLORREF m_color1;
	COLORREF m_color2;

    void SetToolTipText(CString str);
    void SetLinkCursor(HCURSOR hCursor);
    void SetDefaultCursor();
	void SetParam(bool linker = FALSE,
		          bool bigFont = FALSE,
				  void * pParam = NULL,
				  COLORREF color1 = RGB(255,255,150),
				  COLORREF color2 = RGB(0,0,255));

	 //virtual BOOL PreTranslateMessage(MSG* pMsg);
    //{{AFX_VIRTUAL(CLink)
	public:
   
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL DestroyWindow();
	protected:
    virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

protected:
    BOOL     m_bOver;   
    HCURSOR  m_hLinkCursor; 
    CToolTipCtrl m_ToolTip;   

   
protected:
    //{{AFX_MSG(CLink)
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
#endif 