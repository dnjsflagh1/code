//******************************************************************************************************************************
#include "stdafx.h"
#include "DEFont.h"
//******************************************************************************************************************************
namespace MG
{

	void DEFont::setTrueFont( std::string _name )
	{
		MyGUI::FontManager* pFontManager = MyGUI::FontManager::getInstancePtr();
		pFontManager->setTrueFontName(_name);
	}
	
}