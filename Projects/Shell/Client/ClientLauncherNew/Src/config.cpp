//**************************************************************************************************
#include "config.h"
#include <wx/wx.h> 
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>

#include "IEHtmlWin.h"
#include <wx/fileconf.h>
#include <wx/wfstream.h>
#include <wx/wxchar.h>
//**************************************************************************************************
Config& Config::getInstance()
{
	static Config config;
	return config;
}
//---------------------------------------------------------
bool Config::load( wxString& path )
{
	if(path.IsEmpty())
	{
		return false;
	}
	mPath = path;
	wxFileInputStream fis(path);
	if (!fis.Ok())
	{
		assert("Config file not found.");
		return false;
	}
	wxFileConfig *conf = new wxFileConfig(fis);
	bool result = conf->Read(_("config/currVersion"), &mCurrVersion);
	if (!result)
	{
		assert("config currVersion not found.");
		return false;
	}
	result = conf->Read(_("config/versionPath"), &mVersionPath);
	if (!result)
	{
		assert("config versionPath not found.");
		return false;
	}
	result = conf->Read(_("config/isUpdate"), &mIsUpdate);
	if (!result)
	{
		assert("config isUpdate not found.");
		return false;
	}
	return true;

}

bool Config::save()
{
	wxFileInputStream fis(mPath);
	if (!fis.Ok())
	{
		assert("Config file not found.");
		return false;
	}
	wxFileConfig *conf = new wxFileConfig(fis);
	bool result = conf->Write(_("config/currVersion"), mCurrVersion);
	result = conf->Write(_("config/versionPath"), mVersionPath);
	result = conf->Write(_("config/isUpdate"), mIsUpdate);
	wxFileOutputStream os(mPath);
	conf->Save(os);
	os.Close();	
	delete conf;
	return result;
}

//---------------------------------------------------------
wxString Config::getCurrVersion()
{
	return mCurrVersion;
}
//---------------------------------------------------------
wxString Config::getVersionPath()
{
	return mVersionPath;
}
//---------------------------------------------------------
void Config::setCurrVersion( wxString& version )
{
	mCurrVersion = version;
}
//---------------------------------------------------------
void Config::setVersionPate( wxString& path )
{
	mVersionPath = path;
}

Config::Config()
{
	mIsUpdate = false;
}

Config::~Config()
{

}


bool Config::isUpdate()
{
	return mIsUpdate;
}

void Config::setUpdate( bool update )
{
	mIsUpdate = update;
}
//**************************************************************************************************
