/******************************************************************************/
#include "stdafx.h"
#include "GameObject.h"
#include "GameObjectData.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	GameObject::GameObject(GameObject& rhs)
		:mObjectData(rhs.mObjectData)
		,mType(rhs.mType)
		,mQueryType(rhs.mQueryType)
	{
	}

	//-----------------------------------------------------------------------
    GameObject::GameObject( GAMEOBJ_TYPE type, GAMEOBJ_QUERY_TYPE queryType, GameObjectData* data, IdType id)
        :mObjectData(data)
        ,mType(type)
		,mQueryType(queryType)
    {
		if ( id )
		{	
			setID(id);
		}
    }
    //-----------------------------------------------------------------------
    GameObject::~GameObject()
    {
        MG_SAFE_DELETE(mObjectData);
    }
    //-----------------------------------------------------------------------
    void GameObject::setID( GameObjectIdType id )
    {
        DYNAMIC_ASSERT( mObjectData );

        mObjectData->mId = id;
    }

    //-----------------------------------------------------------------------
    GameObjectIdType GameObject::getID()
    {
        DYNAMIC_ASSERT( mObjectData );

        return mObjectData->mId;
    }
    //-----------------------------------------------------------------------
    MG::GAMEOBJ_TYPE GameObject::getType()
    {
        return mType;
    }

	//-----------------------------------------------------------------------
	GAMEOBJ_QUERY_TYPE GameObject::getQueryType()
	{
		return mQueryType;
	}

    //-----------------------------------------------------------------------
    void GameObject::setName( CChar16* name )
    {
        DYNAMIC_ASSERT( mObjectData );

        mObjectData->mName = name;
    }
    //-----------------------------------------------------------------------
    Str16& GameObject::getName()
    {
        DYNAMIC_ASSERT( mObjectData );

        return mObjectData->mName;
    }

    //-----------------------------------------------------------------------
    GameObjectData* GameObject::getGameObjectData()
    {
        return mObjectData;
    }

    //-----------------------------------------------------------------------
    void GameObject::setGameObjectData( GameObjectData* pData )
    {
        mObjectData = pData;
    }

	//-----------------------------------------------------------------------
	void GameObject::print()
	{
		MG_LOG(out_sys, "\n 打印 Data 开始、\n ");
		if (NULL != mObjectData)
		{
			mObjectData->print();
		}

		MG_LOG(out_sys, " 打印 Data 结束、\n ");

		MG_LOG(out_sys, "\n【NEW_GameObject】mType[%d], \n", mType);
	}

	//-----------------------------------------------------------------------
}