/******************************************************************************/
#ifndef _CAIGROUP_H_
#define _CAIGROUP_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //游戏操作对象
    /******************************************************************************/
    struct  AIEntity
    {
        CCharacterSceneEntity* entity;
    };

	struct AIEntityGroupList
	{
		std::map<IdType, AIEntity>			objectList;	
	};

    struct AIEntityTypeGroupList
    {
        GAMEOBJ_TYPE						type;
        std::map<IdType, AIEntityGroupList>  objectGroupList;
    };




    /******************************************************************************/
    // 实体组AI
    /******************************************************************************/
    class CAIEntityGroup : public LinedStateObject
    {
    public:
        CAIEntityGroup( Str name );
        virtual ~CAIEntityGroup();

        ///更新事件
        virtual void        							update( Flt delta );

        void                							addSceneEntity( CCharacterSceneEntity* entity, IdType parentId = 0 ) ;
        void                							removeSceneEntity( CCharacterSceneEntity* entity );
        void                							removeSceneEntity( GAMEOBJ_TYPE objType, IdType id, IdType parentId = 0 );

		UInt											getAIEntityTypeGroupListNum();
		AIEntityTypeGroupList*							getAIEntityTypeGroupList(UInt index);


    protected:

        // 过滤失效的游戏对象列表
        void											filterOperationObjectList();

    protected:

        std::map<GAMEOBJ_TYPE,AIEntityTypeGroupList>	mGameObjectList;

    };
}

#endif