/////////////////////////////////////////////////////////////////////////////////////////
// Name:		wxSkin
// Author:      Ren?Kraus aka upCASE <himself@upcase.de>
// Copyright:   Ren?Kraus (c)
// Licence:     wxWindows license <http://www.wxwidgets.org/licence3.txt>
//				with the addendum that you notify the author about projects using wxSkin
///////////////////////////////////////////////////////////////////////////////////////// 
#ifndef __WXSKINBITMAP_H
#define __WXSKINBITMAP_H

#ifdef __GNUG__
	#pragma interface "wxSkinBitmap.h"
#endif

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

#include <wx/image.h>
#include "wxSkinWindow.h"
///wxSkinButton is a simple skinned button class
/**wxSkinButton is a button created from different skins. To catch its events use the standard EVT_BUTTON() macro.
*/
class wxSkinBitmap : public wxSkinWindow
{

public:
	
	wxSkinBitmap();
	
	wxSkinBitmap(wxWindow* parent,
 				int id,
				const wxString& label = wxEmptyString,
  				const wxPoint& pos = wxDefaultPosition,
         		const wxSize& size = wxDefaultSize,
				long style = wxNO_BORDER,
				const wxString& name = wxT("wxSkinBitmap"));
	
 	~wxSkinBitmap();
	void SetLabel(const wxString& label);	
	///Set an optional text label. The label will be rendered inside the skin.
	virtual void DrawCustom(wxDC& dc);

	inline void SetFontColor(wxColor color){m_fontColor = color; }

protected:
	virtual wxSize DoGetBestSize() const;

private:
	wxColor m_fontColor;

	DECLARE_DYNAMIC_CLASS(wxSkinBitmap);
};


#endif

