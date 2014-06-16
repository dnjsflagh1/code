
#include "stdafx.h"
#include "link.h"

#define TIP_ID 1

CLink::CLink()
{
    m_bOver       = FALSE; 
	m_isLinker    = FALSE;
	m_bigFont     = FALSE;
	m_pParam      = NULL;
	//m_color1 = RGB(255,255,150);
	m_color1 = RGB(0,0,0);
    m_color2 = RGB(0,0,255);
	m_hLinkCursor = NULL; //初值设置为NULL，这样如果没有在程序中设置该值，就会使用默认的手形光标
}

CLink::~CLink()
{

}

BOOL CLink::DestroyWindow() 
{
    KillTimer(1);	
	return CStatic::DestroyWindow();
}

void CLink::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect(lpDrawItemStruct->rcItem);
	CFont * pOldFont = NULL;
	int iYOffset = 0, iXOffset = 0;
	CString strText;
	GetWindowText(strText);
	rect.top  += iYOffset;
	rect.left += iXOffset;
	if (m_bOver || m_bigFont)
	{
		if (fUnderline.GetSafeHandle() == NULL)
		{
			CFont * pFont = GetFont();
			ASSERT(pFont);
			LOGFONT lf;
			pFont->GetLogFont(&lf);
			if (m_bOver)
				lf.lfUnderline = TRUE;
//			if (m_bigFont)
//			{
//			}
			fUnderline.CreateFontIndirect(&lf);		
		}
		pOldFont = pDC->SelectObject(&fUnderline);
	}
	pDC->DrawText(strText, rect,  DT_VCENTER | DT_SINGLELINE);
	if (pOldFont) 
		pDC->SelectObject(pOldFont);
}

/*
BOOL CLink::PreTranslateMessage(MSG* pMsg) 
{
 //   m_ToolTip.RelayEvent(pMsg);
//    return CStatic::PreTranslateMessage(pMsg);
	return FALSE;
}
*/

void CLink::PreSubclassWindow() 
{
	CStatic::PreSubclassWindow();
}

BEGIN_MESSAGE_MAP(CLink, CStatic)
    //{{AFX_MSG_MAP(CLink)
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_SETCURSOR()
    ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

HBRUSH CLink::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	if (m_isLinker)
	{
		if (m_bOver)
			pDC->SetTextColor(m_color2);
		else
			pDC->SetTextColor(m_color1);
	}
	else
		pDC->SetTextColor(m_color1);
    pDC->SetBkMode(TRANSPARENT);   //设置背景是透明的
    return (HBRUSH)GetStockObject(NULL_BRUSH);
}

void CLink::OnMouseMove(UINT nFlags, CPoint point) 
{ 
	if (!m_bOver)
	{
		m_bOver = true;
		Invalidate();
		SetTimer(1, 100, NULL); //设置一个定时器，用于设置鼠标离开时的颜色
	}
    CStatic::OnMouseMove(nFlags, point);
}

void CLink::OnTimer(UINT nIDEvent) 
{
    CPoint pt(::GetMessagePos());
    ScreenToClient(&pt);
    CRect rc;
    GetClientRect(rc);
    if (!rc.PtInRect(pt))
    {
        m_bOver = false;
        KillTimer(1);        
        Invalidate();
		ShowWindow(SW_HIDE);
		ShowWindow(SW_SHOW);
    }    
	CStatic::OnTimer(nIDEvent);
}

BOOL CLink::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/) 
{
    if (m_hLinkCursor)  //如果设置了光标，就使用新设置的 光标
    {
        ::SetCursor(m_hLinkCursor);
        return true;
    }
    return false;
}

BOOL CLink::OnEraseBkgnd(CDC* pDC) 
{
	COLORREF cr = GetSysColor(COLOR_3DFACE);
	int r = GetRValue(cr);
	int g = GetGValue(cr);
	int b = GetBValue(cr);
	if (r > 1) r -= 2;
	if (g > 1) g -= 2;
	if (r < 3 && g < 3 && b < 253) b += 2;
	COLORREF cr1 = RGB(r,g,b);
	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(rc, cr1);
	return CStatic::OnEraseBkgnd(pDC);
}

void CLink::SetToolTipText(CString str)
{
	m_ToolTip.UpdateTipText(str,this,TIP_ID);
}

void CLink::SetLinkCursor(HCURSOR hCursor)
{ 
    m_hLinkCursor = hCursor;
    if (m_hLinkCursor == NULL)
        SetDefaultCursor();
}

void CLink::SetDefaultCursor()   //从winhlp32.exe中提取手形光标，用做默认的光标
{    
	CString str;
	::GetWindowsDirectory(str.GetBuffer(MAX_PATH), MAX_PATH);
	str.ReleaseBuffer();
	str += _T("\\winhlp32.exe");
	HMODULE hModule = ::LoadLibrary(str);
	if (hModule) 
	{
		HCURSOR hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
		if (hHandCursor)
			m_hLinkCursor =CopyCursor(hHandCursor);
	}
	FreeLibrary(hModule);
}

void CLink:: SetParam(bool linker,bool bigFont,void * pParam,COLORREF color1,COLORREF color2)
{
	m_isLinker    = linker;
	m_pParam      = pParam;
	m_bigFont     = bigFont;
	m_color1      = color1;
	m_color2      = color2;      
	if (m_isLinker)
	{
		DWORD dwStyle = GetStyle();  //修改属性，使之可接受消息
		::SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle|SS_NOTIFY|SS_OWNERDRAW);
		SetDefaultCursor();     //设置默认光标为手形光标
		CRect rect; 
		GetClientRect(rect);
		m_ToolTip.Create(this);
		m_ToolTip.SetDelayTime(100);
		m_ToolTip.SetMaxTipWidth(200);
		m_ToolTip.AddTool(this, L"", rect, TIP_ID);   
	}
}

