//*************************************************************************************************//
#include "stdafx.h"
#include "CGameMessageConfig.h"
//*************************************************************************************************//
namespace MG
{
    CGameMessageConfig::CGameMessageConfig()
    {

    }
    //------------------------------------------------------------------------------
    CGameMessageConfig::~CGameMessageConfig()
    {
        unloadFile();
    }
    //------------------------------------------------------------------------------
	// MG_CN_MODIFY
    Bool CGameMessageConfig::loadFile( std::wstring fileName, IMGExternalPackManager* packManager/* = NULL */)
    {
        assert ( fileName.length() > 4  );
		// MG_CN_MODIFY
        return mUini.create( fileName, packManager);
    }
    //------------------------------------------------------------------------------
    Int CGameMessageConfig::getMsgConfigNum()
    {
        return mUini.getGroupCount();
    }
    //------------------------------------------------------------------------------
    /*std::wstring CGameMessageConfig::getStr( Int index )
    {

    }*/
    //------------------------------------------------------------------------------
    std::wstring CGameMessageConfig::getStr( std::wstring sectionname, std::wstring keyname, std::wstring defaultVal  )
    {
        return mUini.getValue( sectionname, keyname, defaultVal );
    }

    std::wstring CGameMessageConfig::getStr( std::wstring keyname, std::wstring defaultVal )
    {
        return mUini.getValue( keyname, defaultVal );
    }
    //------------------------------------------------------------------------------
    void CGameMessageConfig::unloadFile()
    {
        
    }

    void CGameMessageConfig::setSection( std::wstring sectionname )
    {
        mUini.setGroup( sectionname );
    }
	//----------------------------------------------------------------------------------------
	void  CGameMessageConfig::getMoneyString(Int money,Str16& outStr)
	{
		if (money < 0)
		{
			money = -money;
		}
		
		U32 guanStr = money/1000;
		U32 wenStr = money-1000*guanStr;
		Char16 tempStr[32]=L"";
		if (guanStr > 0 && wenStr > 0)
		{
			swprintf_s(
				tempStr, 32, 
				CGameMessageConfig::getInstance().getStr(L"itemmoney1", L"itemmoney").c_str(),
				guanStr,
				wenStr
				) ;
			
		}
		else if (wenStr == 0)
		{
			swprintf_s(
				tempStr, 32, 
				CGameMessageConfig::getInstance().getStr(L"itemmoney2", L"itemmoney").c_str(),
				guanStr
				) ;
		
		}
		else if (guanStr == 0)
		{
			swprintf_s(
				tempStr, 32, 
				CGameMessageConfig::getInstance().getStr(L"itemmoney3", L"itemmoney").c_str(),
				wenStr
				) ;
			
		}
		outStr = tempStr;
	}
}
