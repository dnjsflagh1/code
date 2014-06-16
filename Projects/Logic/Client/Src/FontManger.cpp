//******************************************************************************************************************************
#include "stdafx.h"
#include "FontManger.h"
#include "ClientMain.h"
#include "GameSettingManager.h"
//******************************************************************************************************************************
namespace MG
{
	void FontManager::setTrueFontName( std::string _name )
	{
		ClientMain::getInstance().getFont()->setTrueFont(_name);	
	}
	//-----------------------------------------------------------------------------------------------------------------
	MG::Str8 FontManager::getTrueFontName()
	{
		return GameSettingManager::getInstance().getTrueFontName();
	}
}