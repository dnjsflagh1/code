/******************************************************************************/
#include "stdafx.h"
#include "GameNetPacketFilter.h"

#include "AttributeNetPacket.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------------
    GameNetPacketFilter::GameNetPacketFilter()
    {
    }

    //-----------------------------------------------------------------------------
    GameNetPacketFilter::~GameNetPacketFilter()
    {
    }

    //-----------------------------------------------------------------------------
    Bool GameNetPacketFilter::initialize()
    {
        //Attribute
        addDescribe( MG_NEW PT_ATTR_S2C_ATTR_HPMPSP_DESCRIBE );

        //BattleScore

        //Buff

        //Build

        //Campaign

        //CD

        //Chat

        //Instance

        //Item

        //LineUp

        //Login

        //Map

        //Monster

        //NetTranspond

        //Pack

        //Place

        //Player

        //PlayerCharacter

        //PVE

        //Quest

        //Region

        //ServerState

        //Shop

        //Skill

        //SysLog

        //Test

        //Time

        //Troop

        return true;
    }

    //-----------------------------------------------------------------------------
    Bool GameNetPacketFilter::update()
    {
        
        return false;
    }

    //-----------------------------------------------------------------------------
    Bool GameNetPacketFilter::unInitialize()
    {
        GameNetPacketDataDescribeMap::iterator iter = mGameNetPacketDataDescribeMap.begin();
        for ( ;iter!=mGameNetPacketDataDescribeMap.end(); iter++ )
        {
            GameNetPacketDataDescribeList& list = iter->second; 
            GameNetPacketDataDescribeList::iterator jter = list.begin();
            for ( ;jter!=list.end(); jter++ )
            {
                MG_SAFE_DELETE( jter->second );
            }
        }
        mGameNetPacketDataDescribeMap.clear();

        return false;
    }

    //-----------------------------------------------------------------------------
    Bool GameNetPacketFilter::checkRecvPacketValid( I32 handle,I32 id, GameNetPacketHeader* packet,I32 packetSize )
    {
        UNREFERENCED_PARAMETER(id);
        UNREFERENCED_PARAMETER(handle);

        if ( packetSize < GameNetPacketData_INFO::headSize )
        {
            DYNAMIC_EEXCEPT_LOG( "GameNetPacketFilter::checkRecvPacketValid : packetSize < GameNetPacketData_INFO::headSize " );
            return false;
        }

        GameNetPacketData* data = static_cast<GameNetPacketData*>( packet );
        if ( data == NULL )
        {
            DYNAMIC_EEXCEPT_LOG( "GameNetPacketFilter::checkRecvPacketValid : static_cast<GameNetPacketData*> is NULL " );
            return false;
        }

        GameNetPacketDataDescribe* describe = getDescribe( data->channel , data->type );
        if ( describe == NULL )
        {
            //DYNAMIC_ASSERT_LOG( false, "GameNetPacketFilter::checkRecvPacketValid : getDescribe is NULL " );
            //return false;
        }else
        if ( describe->checkDataValid( data, packetSize ) == false )
        {
            DYNAMIC_EEXCEPT_LOG( "GameNetPacketFilter::checkRecvPacketValid : describe->checkDataValid is false " );
            return false;
        }

        return true;
    }

    //-----------------------------------------------------------------------------
    void GameNetPacketFilter::addDescribe( GameNetPacketDataDescribe* describe )
    {
        if ( getDescribe( describe->getChannel(), describe->getType() ) )
        {
            DYNAMIC_EEXCEPT_LOG("GameNetPacketFilter::addDescribe :  duplicate!")
        }

        GameNetPacketDataDescribeList& list = mGameNetPacketDataDescribeMap[ describe->getChannel() ];
        
        list[ describe->getType() ] = describe;
    }

    //-----------------------------------------------------------------------------
    GameNetPacketDataDescribe* GameNetPacketFilter::getDescribe( Byte channel, Byte type )
    {
        GameNetPacketDataDescribe* describe = NULL;

        GameNetPacketDataDescribeList& list = mGameNetPacketDataDescribeMap[ channel ];
        GameNetPacketDataDescribeList::iterator iter = list.find( type );
        if ( iter != list.end() )
        {
            describe = iter->second;
        }

        return describe;
    }

}


