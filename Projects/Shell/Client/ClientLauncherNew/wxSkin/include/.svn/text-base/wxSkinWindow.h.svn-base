/////////////////////////////////////////////////////////////////////////////////////////
// Name:		wxSkin
// Author:      Ren?Kraus aka upCASE <himself@upcase.de>
// Copyright:   Ren?Kraus (c)
// Licence:     wxWindows license <http://www.wxwidgets.org/licence3.txt>
//				with the addendum that you notify the author about projects using wxSkin
///////////////////////////////////////////////////////////////////////////////////////// 
#ifndef __WXSKINWINDOW_H
#define __WXSKINWINDOW_H

#include <wx/wx.h>
#include <wx/image.h>

enum{
	TYPE_BUTTON,
	TYPE_CHECKBOX,
	TYPE_RADIOBUTTON,
	TYPE_GAUGE,
	TYPE_SLIDER,
	TYPE_RADIOBUTTTON,
	TYPE_PANEL,

	TYPE_TEXT,
	TYPE_BITMAP
};

///wxSkinWindow is the abstract base class for all skinned controls in wxSkin
/**wxSkinWindow manages the skin files for all controls in wxSkin. In addition to that it handles the most basic
events, like painting and sizing a control. Drawing the "over" state is also done here.
*/
class wxSkinWindow : public wxWindow
{
	bool m_bInside;
protected:
	wxImage bmp_normal;
	wxImage bmp_state2;
	wxImage bmp_over;
	wxImage bmp_disabled;
	//xcl
	wxImage bmp_fixedBitmap;
	int m_stateFlag;
	int m_fontState;//记录文字当前状态，因为有可能状态不同则颜色不同
	//-xcl
	int m_type;
	bool m_bScaleFill;
public:
	//xcl
	void SetFixedBitmap(const wxImage& bitmap = wxNullImage);
	void SetStateFlag(const int stateflag = 0);
	wxImage GetNormalSkin(){return bmp_normal;}
	void ShowNormalSkin();
	int GetFontState(){return m_fontState;}
	//-xcl
	///Contructor
	wxSkinWindow(){};
	///Standard Contructor
	wxSkinWindow(wxWindow* parent,
				wxWindowID id,
				const wxPoint& pos = wxDefaultPosition,
				const wxSize& size = wxDefaultSize,
				long style = wxNO_BORDER,
				const wxString& name = wxPanelNameStr,
				const int type = -1);

	///Set the normal, meaning standard skin
	void SetNormalSkin(const wxImage& skin = wxNullImage);
	///Set the "second state" skin
	/**What this skin image actually contains is up to the control derived from wxSkinWindow.
	For a button for example this is the skin in "pressed" state.
	*/
	void SetState2Skin(const wxImage& skin = wxNullImage);
	///Set the skin displayed when the mouse is over the control.
	void SetOverSkin(const wxImage& skin = wxNullImage);
	///Set a skin for disabled state.
	void SetDisabledSkin(const wxImage& skin = wxNullImage);

	bool SetShape(const wxRegion& region);
	bool SetShape(const wxImage& img);
	bool SetShape(const wxBitmap& img);

	///Sets "scaled" mode. In "scaled" mode the skin will be scaled to exactly mathc the controls size.
	void SetScaleFill(bool b){ m_bScaleFill = b;}

	int GetSkinWindowType(){ return m_type; }

	///Overwrite this method in derived classses
	/**This method will be called after the standard drawing action has been completed. This allows to do some non-standard
	drawing in dervied controls.
	*/
	virtual void DrawCustom(wxDC& dc) = 0;

	virtual bool HasTransparentBackground() const {return true;}

	void wxOnAssert(char const *,int,char const *,char const *,char const *){}
private:
	void OnErase(wxEraseEvent& e);
	void OnSize(wxSizeEvent& e);
	void OnPaint(wxPaintEvent& e);
	void OnEnterWindow(wxMouseEvent& WXUNUSED(event));
	void OnLeaveWindow(wxMouseEvent& WXUNUSED(event));
	
	DECLARE_ABSTRACT_CLASS(wxSkinWindow);
	DECLARE_EVENT_TABLE()
};
#endif //__WXSKINWINDOW_H
