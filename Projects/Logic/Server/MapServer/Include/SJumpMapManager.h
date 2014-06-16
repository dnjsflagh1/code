//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SWorldManagerNew.h
//        Author: yuanlinhu
//          Date: 2012-3-12
//          Time: 13:48
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-12      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _S_JUMPMAPMANAGER_H_
#define _S_JUMPMAPMANAGER_H_
/******************************************************************************/

#include "MapServerPreqs.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    // ������ת����Ϣ
    /******************************************************************************/
    struct SceneJumpInfo
    {
        REGION_OBJ_TYPE regionType;
        RegionIdType    regionId;
        InstanceUIdType instanceId;
        JUMP_TYPE       jumpType;
        Byte            jumpIndex;
        Int             pointId;
    };

    /******************************************************************************/
    //@��Һ���Ϸ��������л�
    //�����ת����
    /******************************************************************************/
    class SJumpMapManager
    {
    public:
        SJumpMapManager();
        ~SJumpMapManager();
        SINGLETON_INSTANCE(SJumpMapManager);

        //-----------------------------------------------------------------------------------
        // JumpTo
        //-----------------------------------------------------------------------------------

        void    playerJumpToScene( SPlayerPtr& playerPtr, SceneJumpInfo& jumpInfo );
        void    playerCharacterJumpToScene( SPlayerCharacterPtr& playerCharPtr, SceneJumpInfo& jumpInfo );
        
        //-----------------------------------------------------------------------------------
        // JumpOut
        //-----------------------------------------------------------------------------------

        void    playerJumpOut( SPlayerPtr& playerPtr );
        void    playerCharacterJumpOut( SPlayerCharacterPtr& playerCharPtr );

        //-----------------------------------------------------------------------------------
        // JumpIn
        //-----------------------------------------------------------------------------------

        void    playerJumpInScene( SPlayerPtr& playerPtr, SceneJumpInfo& jumpInfo );
        void    playerCharacterJumpInScene( SPlayerCharacterPtr& playerCharPtr, SceneJumpInfo& jumpInfo );



    };
}

#endif