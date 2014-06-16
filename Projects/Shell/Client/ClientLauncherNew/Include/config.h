//**************************************************************************************************
#ifndef _CONFIG_H_
#define _CONFIG_H_
//**************************************************************************************************
#include "wx/string.h"
class Config
{
public:
	Config();
	~Config();
	static Config& getInstance();

public:
	bool			load(wxString& path);
	bool			save();

	wxString		getCurrVersion();
	wxString		getVersionPath();
	void			setCurrVersion(wxString& version);
	void			setVersionPate(wxString& path);
	bool			isUpdate();
	void			setUpdate(bool update);

private:
	wxString		mCurrVersion;
	wxString		mVersionPath;
	bool			mIsUpdate;
	wxString		mPath;
};
//**************************************************************************************************
#endif