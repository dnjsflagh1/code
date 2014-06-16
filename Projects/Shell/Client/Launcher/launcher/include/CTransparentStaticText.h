/***************************************************
** Copyright (C) 2006-2010 Orsh
** This file is part of the "Game Launcher".
** All rights reserved
****************************************************/
#ifndef _MY_STATICTEXT_CTRL_H_
#define _MY_STATICTEXT_CTRL_H_

#ifdef __GNUG__
#pragma interface "CTransparentStaticText.h"
#endif

#include <wx/wxprec.h>

class CTransparentStaticText : public wxStaticText
{ 
	DECLARE_DYNAMIC_CLASS (CTransparentStaticText)
public:
	CTransparentStaticText();
	CTransparentStaticText(
		wxWindow* parent,
		wxWindowID id,
		const wxString& label,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxString& name= wxStaticTextNameStr
		);

	bool Create(
		wxWindow* parent,
		wxWindowID id,
		const wxString& label,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxString& name= wxStaticTextNameStr
		);

	virtual bool HasTransparentBackground() { return true; };
	virtual void OnPaint(wxPaintEvent& event);
	DECLARE_EVENT_TABLE()
};

#endif