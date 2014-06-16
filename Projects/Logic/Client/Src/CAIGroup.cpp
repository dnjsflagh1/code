/******************************************************************************/
#include "stdafx.h"
#include "CAIGroup.h"
#include "CCharacterSceneEntity.h"
#include "CSceneManager.h"
/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------
    CAIEntityGroup::CAIEntityGroup( Str name )
        :LinedStateObject(name)
    {

    }
    
    //--------------------------------------------------------------------------
    CAIEntityGroup::~CAIEntityGroup()
    {
        
    }

    //--------------------------------------------------------------------------
    void CAIEntityGroup::update( Flt delta )
    {
        filterOperationObjectList();
    }

    //--------------------------------------------------------------------------
    void CAIEntityGroup::addSceneEntity( CCharacterSceneEntity* entity, IdType parentId )
    {
        GAMEOBJ_TYPE objType            = entity->getType();

		IdType groupId = 0;
		IdType id = 0;
		if(parentId == 0)
		{
			groupId						= entity->getID();
			id							= groupId;
		}
		else
		{
			groupId						= parentId;
			id							= entity->getID();					
		}
    
        AIEntityTypeGroupList& objList  = mGameObjectList[objType];
        objList.type                    = objType;

        AIEntity obj;
        obj.entity                      = entity;

        objList.objectGroupList[groupId].objectList[id] = obj;
    }

    //--------------------------------------------------------------------------
    void CAIEntityGroup::removeSceneEntity( CCharacterSceneEntity* entity )
    {
        removeSceneEntity( entity->getType(), entity->getID() );
    }

    //--------------------------------------------------------------------------
    void CAIEntityGroup::removeSceneEntity( GAMEOBJ_TYPE objType, IdType id, IdType parentId )
    {
        AIEntityTypeGroupList& objTypeList    = mGameObjectList[objType];
		IdType groupId = 0;
		if(parentId == 0)
		{
			groupId = id;
		}
		else
		{
			groupId = parentId;
		}

		AIEntityGroupList& objList = objTypeList.objectGroupList[groupId];

        std::map<IdType, AIEntity>::iterator iter = objList.objectList.find( id );
        if ( iter != objList.objectList.end() )
        {
            objList.objectList.erase( iter );
        }
    }

    //--------------------------------------------------------------------------
    void CAIEntityGroup::filterOperationObjectList()
    {
        std::map<GAMEOBJ_TYPE,AIEntityTypeGroupList>::iterator iter = mGameObjectList.begin();
        for ( ; iter != mGameObjectList.end() ; iter++ )
        {
            GAMEOBJ_TYPE objType      = iter->first;
            AIEntityTypeGroupList& typeList = iter->second;

			std::map<IdType, AIEntityGroupList>::iterator jter = typeList.objectGroupList.begin();
			for( ; jter != typeList.objectGroupList.end(); ++jter)
			{
				AIEntityGroupList& groupList = jter->second;

				std::map<IdType, AIEntity>::iterator kter = groupList.objectList.begin();
				for ( ; kter != groupList.objectList.end() ; )
				{
					IdType id               = 0;
					UInt index				= 0;
					AIEntity& obj           = kter->second; 
					obj.entity              = NULL;

					if ( objType == GOT_PLAYERCHARACTER )
					{
						id = kter->first;
						index = id;
					}
					else if( objType == GOT_SOLDIER )
					{
						id = jter->first;
						index = kter->first;
					}

					CCharacterSceneEntity* entity = CSceneManager::getInstance().getCharacterSceneEntity( objType, id, index );
					if(!entity)
					{
						kter = groupList.objectList.erase(kter);
						continue;
					}
					obj.entity = (MG::CCharacterSceneEntity *)entity;
					kter++;
				}
			}
        }
    }

	//--------------------------------------------------------------------------
	UInt CAIEntityGroup::getAIEntityTypeGroupListNum()
	{
		return mGameObjectList.size();
	}

	//--------------------------------------------------------------------------
	AIEntityTypeGroupList* CAIEntityGroup::getAIEntityTypeGroupList(UInt index)
	{
		UInt aiEntityTypeGroupListIndex = 0;
		for(std::map<GAMEOBJ_TYPE,AIEntityTypeGroupList>::iterator it = mGameObjectList.begin(); it != mGameObjectList.end(); ++it)
		{
			if(index == aiEntityTypeGroupListIndex)
			{
				return &(it->second);
			}

			aiEntityTypeGroupListIndex++;
		}

		return NULL;
	}

}