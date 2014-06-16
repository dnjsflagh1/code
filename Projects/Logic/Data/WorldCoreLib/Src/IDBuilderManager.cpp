//************************************************************************************************
#include "stdafx.h"
#include "IDBuilderManager.h"
//************************************************************************************************
#define  MAX_BUILDER_ID 0x7FFF
//************************************************************************************************
namespace MG
{
	MG::Bool IDBuilderManager::addIDObject( IDObject* pIDObject )
	{
		GameObjectIdType id = pIDObject->getSelfCreateID();
		if ( 0 != id )
		{
			//判断该对象是否被用掉。（这是不允许的）
			std::map<GameObjectIdType, IDObject*>::iterator iter = mMapIDObject.find(id);
			if ( mMapIDObject.end() != iter )
			{
				DYNAMIC_ASSERT_LOG(0, "该对象已经存在");
				removeIDObject(id);
				mMapIDObject[id] = pIDObject;
				return false;	
			}
			//设置最大id
			if ( id > mCurMaxId )
				mCurMaxId = id;
			//id和逻辑对象绑定
			mMapIDObject[id] = pIDObject;
		}
		else
		{
			//如果没有ID，找一个没有用到的ID号
			id = getFreeID();
			if ( 0 == id )
			{
				DYNAMIC_ASSERT_LOG(0, "ID号已用完");
				return false;	
			}
			//设置ID，并和逻辑对象绑定
			pIDObject->setSelfCreateID( id );
			mMapIDObject[id] = pIDObject;
		}

		return true;
	}
	//-------------------------------------------------------------------------------
	MG::Bool IDBuilderManager::removeIDObject( IDObject* pIDObject )
	{
		return removeIDObject(pIDObject->getSelfCreateID());
	}
	//-------------------------------------------------------------------------------
	Bool	IDBuilderManager::removeIDObject(GameObjectIdType id)
	{
		if ( 0 == id )
		{
			DYNAMIC_ASSERT_LOG(0, "该对象的ID已经清空或者没有被设置");
			return false;	
		}
		//找到对象，并删除对象的绑定关系
		std::map<GameObjectIdType, IDObject*>::iterator iter = mMapIDObject.find(id);
		if ( mMapIDObject.end() != iter )
		{
			iter->second->setSelfCreateID(0);
			mMapIDObject.erase(iter);
		}
		else
		{
			DYNAMIC_ASSERT_LOG(0, "在list中找不到该对象的绑定关系");
			return false;	
		}

		return true;
	}
	//-------------------------------------------------------------------------------
	void	IDBuilderManager::init(GameObjectIdType maxId)
	{
		mMaxId = maxId;
		mCurMaxId = 1;
	}
	//-------------------------------------------------------------------------------
	void	IDBuilderManager::unInit()
	{
		mMaxId = 0;
		mCurMaxId = 1;
		mMapIDObject.clear();
	}
	//-------------------------------------------------------------------------------
	MG::GameObjectIdType IDBuilderManager::getFreeID()
	{
		//如果好没有达到最大值，直接在当前最大值上加一
		if ( mCurMaxId++ < mMaxId )
			return mCurMaxId;

		std::map<GameObjectIdType, IDObject*>::iterator iter;
		std::map<GameObjectIdType, IDObject*>::iterator end = mMapIDObject.end();
		//到了最大值，就必须从头开始找空闲的ID
		for (GameObjectIdType i = 1; i<MAX_BUILDER_ID; i++)
		{
			iter = mMapIDObject.find(i);
			if ( end == iter )
				return i;
		}

		DYNAMIC_ASSERT_LOG(0, "ID号已用完");
		return 0;
	}
	//-------------------------------------------------------------------------------
	void IDBuilderManager::clear()
	{
		mMapIDObject.clear();
	}
}