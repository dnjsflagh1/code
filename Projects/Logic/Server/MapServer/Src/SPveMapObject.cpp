/******************************************************************************/

#include "stdafx.h"
#include "SPveMapObject.h"
#include "PveObjectData.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	SPveMapObject::SPveMapObject()
		:SMapObject(MG_NEW PveObjectData(NULL))
	{
	}

	//-----------------------------------------------------------------------------
	SPveMapObject::~SPveMapObject()
	{
	}
	//-----------------------------------------------------------------------------
	void SPveMapObject::createScene(SPveSceneObjectPtr& ptr, InstanceUIdType instanceUid)
	{
		if (getScene(ptr, instanceUid))
		{
			DYNAMIC_EEXCEPT_LOG("already exist SPveMapObject!");
			destroyScene( instanceUid );
			ptr.setNull();
		}

		mSPveSceneObjectFactory.createSPveSceneObjectPtr(ptr, instanceUid);
		//³õÊ¼»¯ÄÚ´æ

		mSPveSceneObjectListCs.writeLock();
		{
			mSPveSceneObjecList[instanceUid] = ptr;
		}
		mSPveSceneObjectListCs.writeUnLock();
	}

	//-----------------------------------------------------------------------------
	Bool SPveMapObject::getScene(SPveSceneObjectPtr& ptr, InstanceUIdType instanceUid)
	{
		Bool result = false;

		mSPveSceneObjectListCs.readLock();
		{
			std::map<InstanceUIdType,SPveSceneObjectPtr>::iterator iter = mSPveSceneObjecList.find(instanceUid);
			if ( iter != mSPveSceneObjecList.end() )
			{
				ptr = iter->second;
				result = true;
			}
		}
		mSPveSceneObjectListCs.readUnLock();

		return result;
	}

	//-----------------------------------------------------------------------------
	void SPveMapObject::destroyScene(InstanceUIdType instanceUid)
	{
		mSPveSceneObjectListCs.writeLock();
		{
			std::map<InstanceUIdType,SPveSceneObjectPtr>::iterator iter = mSPveSceneObjecList.find(instanceUid);
			if ( iter != mSPveSceneObjecList.end() )
			{
				iter->second->clear();
				mSPveSceneObjecList.erase( iter );
			}
		}
		mSPveSceneObjectListCs.writeUnLock();
	}

	//-----------------------------------------------------------------------------
	void SPveMapObject::destroyAllScene()
	{
		mSPveSceneObjectListCs.writeLock();
		{
			//SPlayerPtr ptr;

			std::map<InstanceUIdType,SPveSceneObjectPtr>::iterator iter = mSPveSceneObjecList.begin();
			for ( ;iter != mSPveSceneObjecList.end(); iter++ )
			{
				iter->second->clear();
				//iter->second->setPlayer( ptr );
			}
			mSPveSceneObjecList.clear();

		}
		mSPveSceneObjectListCs.writeUnLock();
	}


}	//namespace MG