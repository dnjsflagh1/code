//*************************************************************************************************//
#include "stdafx.h"
#include "CSelectServerConfig.h"
#include "Ini.h"
//*************************************************************************************************//
namespace MG
{
    CSelectServerConfig::CSelectServerConfig()
    {
        mpServerConfigList = NULL;
    }
    //--------------------------------------------------------------------------
    CSelectServerConfig::~CSelectServerConfig()
    {
        unloadFile();
    }
    //--------------------------------------------------------------------------
	// MG_CN_MODIFY
    Bool CSelectServerConfig::loadFile( std::wstring fileName, IMGExternalPackManager* packManager/* = NULL */)
    {
        assert(fileName.length() > 4);
        assert(NULL == mpServerConfigList);

        //读取Ini文件
        UINI ini;
		// MG_CN_MODIFY
        if ( ini.create( fileName, packManager) )
        {
            mpServerConfigList = new std::vector<ServerConfig*>;
            assert( mpServerConfigList );
            ServerConfig* tempServerConfig = NULL;

            //根据Index取出ini内容
            Int nCount = ini.getGroupCount();
            for ( Int i=0; i<nCount; i++ )
            {
                tempServerConfig = new ServerConfig;
                assert(tempServerConfig);

                tempServerConfig->mServerName =  ini.getGroupName( i );
                ini.setGroup( tempServerConfig->mServerName );
                tempServerConfig->mServerIP = ini.getValue( L"ip", L"" );
                MGStrOp::toI32( ini.getValue( L"port", L"0" ).c_str(), tempServerConfig->mPort );

                //存贮ini文件信息。
                mpServerConfigList->push_back( tempServerConfig );

                tempServerConfig = NULL;
            }
            return true;
        }
        return false;
    }
    //--------------------------------------------------------------------------
    Int CSelectServerConfig::getServerConfigNum()
    {
        assert(mpServerConfigList);

        return mpServerConfigList->size();
    }
    //--------------------------------------------------------------------------
    CSelectServerConfig::ServerConfig* CSelectServerConfig::getServerConfigByIndex( Int index )
    {
        assert(mpServerConfigList);
        assert(index >= 0  &&  index < (Int)mpServerConfigList->size());
        
        return (*mpServerConfigList)[index];
    }
    //--------------------------------------------------------------------------
    void CSelectServerConfig::unloadFile()
    {
        if ( mpServerConfigList )
        {
            while (mpServerConfigList->begin() != mpServerConfigList->end())
            {
                delete *mpServerConfigList->begin();
                mpServerConfigList->erase(mpServerConfigList->begin());
            }
            mpServerConfigList->clear();
        }
    }
    //--------------------------------------------------------------------------
    CSelectServerConfig::ServerConfig* CSelectServerConfig::getServerConfigByName( std::wstring name )
    {
         assert(mpServerConfigList);
         assert(name.length() > 1);

         std::vector<ServerConfig*>::iterator pos = mpServerConfigList->begin();
         while ( pos != mpServerConfigList->end() )
         {
             if ( wcscmp( (*pos)->mServerName.c_str(), name.c_str() ) == 0 )
                 return *pos;
             ++pos;
         }

         return NULL;
    }
}

//*************************************************************************************************//