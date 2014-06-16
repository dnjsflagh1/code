#include "CTransparentStaticText.h"

IMPLEMENT_DYNAMIC_CLASS (CTransparentStaticText, wxStaticText)

BEGIN_EVENT_TABLE(CTransparentStaticText, wxStaticText)
	EVT_PAINT(CTransparentStaticText::OnPaint)
END_EVENT_TABLE()

CTransparentStaticText::CTransparentStaticText() {}

CTransparentStaticText::CTransparentStaticText(wxWindow* parent, wxWindowID id, const wxString& label,const wxPoint& pos, const wxSize& size, long style, const wxString& name ) 
{
	Create(parent, id, label, pos, size, style, name);
}

bool CTransparentStaticText::Create(wxWindow* parent, wxWindowID id, const wxString& label,const wxPoint& pos, const wxSize& size, long style, const wxString& name ) 
{
	bool bRetVal = wxStaticText::Create(parent, id, label, pos, size, style|wxTRANSPARENT_WINDOW, name);
	SetBackgroundColour(parent->GetBackgroundColour());
	SetBackgroundStyle(wxBG_STYLE_COLOUR);
	SetForegroundColour(parent->GetForegroundColour());
	return bRetVal;
}

void CTransparentStaticText::OnPaint(wxPaintEvent& /*event*/) 
{
	wxPaintDC dc(this);
	dc.SetFont(GetFont());
	dc.SetTextForeground(GetForegroundColour());	
	dc.DrawText(GetLabel(), 0, 0);
}