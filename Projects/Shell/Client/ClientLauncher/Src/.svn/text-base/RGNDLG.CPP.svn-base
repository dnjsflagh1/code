// DlgEx.cpp : implementation file
//

#include "stdafx.h"
#include "RGNDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

			

/////////////////////////////////////////////////////////////////////////////
// CRGNDlg dialog

extern std::string gAppPath;
extern Memfile g_xMemFile;
CRGNDlg::CRGNDlg(UINT nIDTemplate,CWnd* pParent,std::string rgnfile)
		: CDialog(nIDTemplate, pParent)
{
	//{{AFX_DATA_INIT(CRGNDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bTrackMove = FALSE;
	m_rgnfile    =  rgnfile;	
	m_xScale     = 1;
	m_yScale     = 1;

}
CRGNDlg::~CRGNDlg()
{	
}



void CRGNDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRGNDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRGNDlg, CDialog)
	//{{AFX_MSG_MAP(CRGNDlg)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRGNDlg message handlers



BOOL CRGNDlg::OnInitDialog() 
{
	/*scaling for the 'small fonts' / 'large fonts' problem
	 The problem:
	 ------------
	 For example you have "small fonts" selected in your desktop display config.
	 You happily create your dialog box , put in your bmp and insert
	 all the required controls aligning them carefully to the background bmp. 
	 You then triumphantly send out your app and then get people complaining
	 that things don't line up.
	 The cause:
	 ----------
	 These people have 'large fonts' selected. Windows scales the dialog box and
	 its controls according to the font. The font in turn is dependent on the 
	 'small/large' font setting - so Ms Sans Serif 8 is not the same 'size'.
	 Since the image and the rgn are pixel based there is a problem.
     The solution:
	 -------------
	 There are two possible solutions -
	 1. Scaling
	    This is what I have implemented here. 
		What you do is design your dialog and image using the 
		mode (small fonts or large fonts) that the app is going to 
		be used in.
        This is a bit crude I know but the first time your create your
		dialog put a break on 
		 MapDialogRect(rect); 
        execute to it and see what it converts the rect.right and rect.bottom
		to. DESIGNX is then set to rect.right and DESIGNY to rect.bottom.
		So when I designed this they were 150 and 163.

		The drawback of scaling is that it is not exact. 
		E.g. Scaling from an app designed in "small fonts" is a bit blocky 
		if scaled up for "large fonts".

	 2. Have two separate images and two RGN files.
	    I suggest that you design your dialog and then base two dialogs
		on the original one and setup one to use large image and one to use
		the smaller image.
		A "reliable" way of determing the font mode is
		if (dc.GetDeviceCaps(LOGPIXELSX) == 120) then its large
		else its small  //dc.GetDeviceCaps(LOGPIXELSX)==96
	    
     Tis not my fault.
	*/
	int DESIGNX  =  150;
	int DESIGNY  =  163;
	
	CRect rect;
	rect.SetRect(0,0,100,100);
	MapDialogRect(rect);
	m_xScale  = (float)((float)rect.right /  (float) DESIGNX);          
	m_yScale  = (float)((float)rect.bottom / (float) DESIGNY);          

	std::string	fileName = "Update\\img.bmp";
	fileName = gAppPath + fileName;
	CBitmap bmp;
	HBITMAP hBitMap = NULL;
	hBitMap =  (HBITMAP)::LoadImageA( AfxGetInstanceHandle(), fileName.c_str(), IMAGE_BITMAP, 0, 0, 
		LR_CREATEDIBSECTION|LR_LOADFROMFILE); 
	if (!hBitMap)
	{
		DWORD err = GetLastError();
		return FALSE;
	}
 
	BITMAP bitmap;
	bmp.Attach(hBitMap);
	bmp.GetObject(sizeof(BITMAP),&bitmap);
	mRect.left = 0;
	mRect.top = 0;
	mRect.bottom = bitmap.bmHeight;
	mRect.right = bitmap.bmWidth;
	SetWindowPos(NULL,0,0,bitmap.bmWidth,bitmap.bmHeight,SWP_DRAWFRAME);
	mBh.CreatePatternBrush(&bmp);

	//CDC* pDC = GetDC();
	//CDC ImageDC; 
	//ImageDC.CreateCompatibleDC(pDC);
	//ImageDC.SelectObject(&mBh);
	//TransparentBlt(pDC->m_hDC, 0, 0,mRect.Width(),mRect.Height(), ImageDC.m_hDC, 0, 0,mRect.Width(),mRect.Height(),RGB(0,0,0)); 
	
	bmp.DeleteObject();
	

	int bytes;
    BYTE*rgndata = g_xMemFile.popenfunc(m_rgnfile.c_str(),bytes);       	 
	 if (rgndata) {
 	  HRGN rgn;	  
	  XFORM xform;	  
	  xform.eM11 = (FLOAT) m_xScale;          
	  xform.eM22 = (FLOAT) m_yScale; 
	  xform.eM12 = (FLOAT) 0.0;       
	  xform.eM21 = (FLOAT) 0.0;             
      xform.eDx  = (FLOAT) 0.0;             
	  xform.eDy  = (FLOAT) 0.0; 

	  m_dialogrgn = ExtCreateRegion(&xform,sizeof(RGNDATAHEADER) + (sizeof(RECT) * ((RGNDATA*)rgndata)->rdh.nCount),(RGNDATA*)rgndata);
	  VERIFY(m_dialogrgn!=NULL); // if you want more comprehensive checking - feel free!
	  rgn = ExtCreateRegion(&xform, sizeof(RGNDATAHEADER) + (sizeof(RECT) * ((RGNDATA*)rgndata)->rdh.nCount),(RGNDATA*)rgndata);
      VERIFY(rgn!=NULL);  // if you want more comprehensive checking - feel free!
	  ::SetWindowRgn(m_hWnd, rgn, TRUE);
	  g_xMemFile.pclosefunc(rgndata);
	 }

	CDialog::OnInitDialog();	
	
	return TRUE; 
}

BOOL CRGNDlg::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;

}

void CRGNDlg::InvertTracker(CPoint point)
{

	//just invert outline - slow for complex regions
	HRGN rgn1;
	rgn1 = CreateRectRgn(0, 0,1,1);
	CBrush b;
	b.CreateSolidBrush(RGB(0,0,255));
	CombineRgn(rgn1,m_dialogrgn,NULL,RGN_COPY);
	OffsetRgn(rgn1,point.x-m_ptMouse.x,point.y-m_ptMouse.y);
	SetROP2(m_dc.m_hDC,R2_NOT);	
	FrameRgn(m_dc.m_hDC,rgn1,(HBRUSH)b.m_hObject,2,2);
	b.DeleteObject();	
	DeleteObject(rgn1);	
	
	//otherwise invert entire region - fast
	/*HRGN rgn1;
	rgn1 = CreateRectRgn(0, 0,1,1);
	CBrush b;
	b.CreateSolidBrush(RGB(0,0,255));
	CombineRgn(rgn1,m_dialogrgn,NULL,RGN_COPY);
	OffsetRgn(rgn1,point.x-m_ptMouse.x,point.y-m_ptMouse.y);
	SetROP2(m_dc.m_hDC,R2_NOT);	
	FrameRgn(m_dc.m_hDC,rgn1,(HBRUSH)b.m_hObject,2,2);
	b.DeleteObject();	
	DeleteObject(rgn1);		
	*/

}


void CRGNDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
   m_dc.Attach(::GetDC(NULL));
   m_bTrackMove = TRUE;
   m_ptMouse = point;
   SetCapture();
   ClientToScreen(&point);
   InvertTracker(point);
   m_ptLast = point;
}

void CRGNDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bTrackMove)
	{
		m_bTrackMove=FALSE;
		ReleaseCapture();
		InvertTracker(m_ptLast);
		::ReleaseDC(NULL,m_dc.Detach());		
		ClientToScreen(&point);
		SetWindowPos(NULL, point.x-m_ptMouse.x, point.y-m_ptMouse.y,0,0,
				SWP_NOZORDER|SWP_NOSIZE);
		ShowWindow(SW_SHOW);
	}
	else CDialog::OnLButtonUp(nFlags, point);
}

void CRGNDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bTrackMove)
	{
		ClientToScreen(&point);
		InvertTracker(m_ptLast);
		m_ptLast = point;
		InvertTracker(m_ptLast);
	}
	else  CDialog::OnMouseMove(nFlags, point);
}

void CRGNDlg::OnPaint() 
{
   CPaintDC dc(this); // device context for painting
}

HBRUSH CRGNDlg::OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor )
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (pWnd == this)
	{
		return mBh;
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

