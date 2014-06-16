
/******************************************************************************/

#include "stdafx.h"
#include "SJumpMapManager.h"
#include "SSceneObjectPtr.h"
#include "SPlayer.h"

/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------------------
    SJumpMapManager::SJumpMapManager()
    {

    }

    //--------------------------------------------------------------------------------------
    SJumpMapManager::~SJumpMapManager()
    {

    }

    //-----------------------------------------------------------------------------------
    // JumpTo
    //-----------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    void SJumpMapManager::playerJumpToScene( SPlayerPtr& playerPtr, SceneJumpInfo& jumpInfo )
    {
        playerJumpOut( playerPtr );
        playerJumpInScene( playerPtr, jumpInfo );
    }

    //--------------------------------------------------------------------------------------
    void SJumpMapManager::playerCharacterJumpToScene( SPlayerCharacterPtr& playerCharPtr, SceneJumpInfo& jumpInfo )
    {
        playerCharacterJumpOut( playerCharPtr );
        playerCharacterJumpInScene( playerCharPtr, jumpInfo );
    }

    //-----------------------------------------------------------------------------------
    // JumpOut
    //-----------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    void SJumpMapManager::playerJumpOut( SPlayerPtr& playerPtr )
    {
        SSceneObjectPtr scenePtr;
        playerPtr->getBelongScene( scenePtr );
        
        if ( scenePtr.isNull() == false )
        {
            // SSceneObjectPtr
            // 通知玩家所在的 SSceneObject 移除玩家信息
            // 然后SSceneObject内部会通知相关涉及模块
            // 通知其他服务器或客户端


            // 其他信息清除

            // SPlayerPtr
            scenePtr.setNull();
            // 清空玩家保存的SSceneObject
            playerPtr->setBelongScene( scenePtr );
        }
    }

    //--------------------------------------------------------------------------------------
    void SJumpMapManager::playerCharacterJumpOut( SPlayerCharacterPtr& playerCharPtr )
    {

    }

    //-----------------------------------------------------------------------------------
    // JumpIn
    //-----------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    void SJumpMapManager::playerJumpInScene( SPlayerPtr& playerPtr, SceneJumpInfo& jumpInfo )
    {
        SSceneObjectPtr scenePtr;
        //SWorldManager::getInstance().getSceneObject( scenePtr , ... )

        if ( scenePtr.isNull() == false )
        {
            // SSceneObjectPtr
            // 通知玩家所在的 SSceneObject 增加玩家信息
            // 然后SSceneObject内部会通知相关涉及模块
            // 通知其他服务器或客户端


            // 其他信息通知

            // SPlayerPtr
            // 保存玩家保存的SSceneObject
            playerPtr->setBelongScene( scenePtr );
        }
    }

    //--------------------------------------------------------------------------------------
    void SJumpMapManager::playerCharacterJumpInScene( SPlayerCharacterPtr& playerCharPtr, SceneJumpInfo& jumpInfo )
    {

        SSceneObjectPtr scenePtr;
        //SWorldManager::getSceneObject( scenePtr , ... )

        if ( scenePtr.isNull() == false )
        {

            // SSceneObjectPtr
            // 通知玩家所在的 SSceneObject 增加玩家角色信息
            // 获得GameObjectIndexIdInSceneType
            // 然后SSceneObject内部会通知相关涉及模块
            // 通知其他服务器或客户端


            // 其他信息通知

            // SPlayerCharacterPtr
            // 保存玩家角色保存的SSceneObject
            //playerCharPtr->setBelongScene( scenePtr, index );

            
        }


    }

}