/////////////////////////////////////////////////////////////////////////////////////////
// Name:		wxSkin
// Author:      Ren?Kraus aka upCASE <himself@upcase.de>
// Copyright:   Ren?Kraus (c)
// Licence:     wxWindows license <http://www.wxwidgets.org/licence3.txt>
//				with the addendum that you notify the author about projects using wxSkin
///////////////////////////////////////////////////////////////////////////////////////// 
#ifdef __GNUG__
	#pragma implementation "wxSkinBitmap.h"
#endif

#include "wxSkinBitmap.h"

#if wxCHECK_VERSION(2, 7, 0)
	#define ISOK IsOk
#else
	#define ISOK Ok
#endif

IMPLEMENT_DYNAMIC_CLASS(wxSkinBitmap,wxSkinWindow)

//Default
wxSkinBitmap::wxSkinBitmap()
	: wxSkinWindow()
{
}
//Passing images
wxSkinBitmap::wxSkinBitmap(wxWindow* parent,
 				int id,
				const wxString& label,
  				const wxPoint& pos,
         		const wxSize& size,
				long style,
				const wxString& name)
	:wxSkinWindow(parent,id,pos,size,style,name,TYPE_BITMAP)
{
	wxString tmp_lab = label;
	tmp_lab.Replace(wxT("&"),wxT(""));
	SetLabel(tmp_lab);
}

wxSkinBitmap::~wxSkinBitmap()
{
}

wxSize wxSkinBitmap::DoGetBestSize() const
{	
	if(!GetLabel().IsEmpty())
	{	int x, y;
		wxClientDC dc((wxWindow*)this);
		dc.GetTextExtent(GetLabel(),&x,&y);
	
		return	wxSize( x+6, y+6 );
	}
	else
		if(bmp_fixedBitmap.ISOK())
			return wxSize(bmp_fixedBitmap.GetWidth(),bmp_fixedBitmap.GetHeight());

	return wxSize(10,10);
}

void wxSkinBitmap::SetLabel(const wxString& label)
{
	wxSkinWindow::SetLabel(label);
	Refresh();
}

void wxSkinBitmap::DrawCustom(wxDC& dc)
{	
	wxString label = GetLabel();
	if(!label.IsEmpty())
	{	int h, w;
		GetSize(&h,&w);

		dc.SetFont(GetFont());
		
		int x, y;
		dc.GetTextExtent(label,&x,&y);
		x = (h - x ) / 2;
		y = (w - y) / 2;
		
		if ( IsEnabled() )
			dc.SetTextForeground(/*GetForegroundColour()*/ m_fontColor);
		else
			dc.SetTextForeground(wxGREY_PEN->GetColour());

		dc.DrawText(label, x , y );
	}
}

