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
    //��Ϸ��������
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
    // ʵ����AI
    /******************************************************************************/
    class CAIEntityGroup : public LinedStateObject
    {
    public:
        CAIEntityGroup( Str name );
        virtual ~CAIEntityGroup();

        ///�����¼�
        virtual void        							update( Flt delta );

        void                							addSceneEntity( CCharacterSceneEntity* entity, IdType parentId = 0 ) ;
        void                							removeSceneEntity( CCharacterSceneEntity* entity );
        void                							removeSceneEntity( GAMEOBJ_TYPE objType, IdType id, IdType parentId = 0 );

		UInt											getAIEntityTypeGroupListNum();
		AIEntityTypeGroupList*							getAIEntityTypeGroupList(UInt index);


    protected:

        // ����ʧЧ����Ϸ�����б�
        void											filterOperationObjectList();

    protected:

        std::map<GAMEOBJ_TYPE,AIEntityTypeGroupList>	mGameObjectList;

    };
}

#endif