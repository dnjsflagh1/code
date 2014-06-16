/******************************************************************************/

#include "stdafx.h"
#include "STiroMapObject.h"
#include "TiroObjectData.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	STiroMapObject::STiroMapObject()
		:SMapObject(MG_NEW TiroObjectData(NULL))
	{
	}

	//-----------------------------------------------------------------------------
	STiroMapObject::~STiroMapObject()
	{
	}
	//-----------------------------------------------------------------------------
	void STiroMapObject::createScene(STiroSceneObjectPtr& ptr, InstanceUIdType instanceUid)
	{
		if (getScene(ptr, instanceUid))
		{
			DYNAMIC_EEXCEPT_LOG("already exist STiroMapObject!");
			destroyScene( instanceUid );
			ptr.setNull();
		}

		mSTiroSceneObjectFactory.createSTiroSceneObjectPtr(ptr, instanceUid);
		//³õÊ¼»¯ÄÚ´æ

		mSTiroSceneObjectListCs.writeLock();
		{
			mSTiroSceneObjecList[instanceUid] = ptr;
		}
		mSTiroSceneObjectListCs.writeUnLock();
	}

	//-----------------------------------------------------------------------------
	Bool STiroMapObject::getScene(STiroSceneObjectPtr& ptr, InstanceUIdType instanceUid)
	{
		Bool result = false;

		mSTiroSceneObjectListCs.readLock();
		{
			std::map<InstanceUIdType,STiroSceneObjectPtr>::iterator iter = mSTiroSceneObjecList.find(instanceUid);
			if ( iter != mSTiroSceneObjecList.end() )
			{
				ptr = iter->second;
				result = true;
			}
		}
		mSTiroSceneObjectListCs.readUnLock();

		return result;
	}

	//-----------------------------------------------------------------------------
	void STiroMapObject::destroyScene(InstanceUIdType instanceUid)
	{
		mSTiroSceneObjectListCs.writeLock();
		{
			std::map<InstanceUIdType,STiroSceneObjectPtr>::iterator iter = mSTiroSceneObjecList.find(instanceUid);
			if ( iter != mSTiroSceneObjecList.end() )
			{
				iter->second->clear();
				mSTiroSceneObjecList.erase( iter );
			}
		}
		mSTiroSceneObjectListCs.writeUnLock();
	}

	//-----------------------------------------------------------------------------
	void STiroMapObject::destroyAllScene()
	{
		mSTiroSceneObjectListCs.writeLock();
		{
			//SPlayerPtr ptr;

			std::map<InstanceUIdType,STiroSceneObjectPtr>::iterator iter = mSTiroSceneObjecList.begin();
			for ( ;iter != mSTiroSceneObjecList.end(); iter++ )
			{
				iter->second->clear();
				//iter->second->setPlayer( ptr );
			}
			mSTiroSceneObjecList.clear();

		}
		mSTiroSceneObjectListCs.writeUnLock();
	}


}	//namespace MG