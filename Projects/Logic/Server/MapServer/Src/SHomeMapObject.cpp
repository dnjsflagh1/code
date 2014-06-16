
/******************************************************************************/

#include "stdafx.h"
#include "SHomeMapObject.h"
#include "HomeObjectData.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	SHomeMapObject::SHomeMapObject()
		:SMapObject(MG_NEW HomeObjectData(NULL))
	{
	}

	//-----------------------------------------------------------------------------
	SHomeMapObject::~SHomeMapObject()
	{
	}

	//-----------------------------------------------------------------------------
	void SHomeMapObject::createScene(SHomeSceneObjectPtr& ptr, InstanceUIdType instanceUid)
	{
		if (getScene(ptr, instanceUid))
		{
			DYNAMIC_EEXCEPT_LOG("already exist SHomeMapObject!");
			destroyScene( instanceUid );
			ptr.setNull();
		}

		mSHomeSceneObjectFactory.createSHomeSceneObjectPtr(ptr, instanceUid);
		//³õÊ¼»¯ÄÚ´æ

		mSHomeSceneObjectListCs.writeLock();
		{
			mSHomeSceneObjecList[instanceUid] = ptr;
		}
		mSHomeSceneObjectListCs.writeUnLock();
	}

	//-----------------------------------------------------------------------------
	Bool SHomeMapObject::getScene(SHomeSceneObjectPtr& ptr, InstanceUIdType instanceUid)
	{
		Bool result = false;

		mSHomeSceneObjectListCs.readLock();
		{
			std::map<InstanceUIdType,SHomeSceneObjectPtr>::iterator iter = mSHomeSceneObjecList.find(instanceUid);
			if ( iter != mSHomeSceneObjecList.end() )
			{
				ptr = iter->second;
				result = true;
			}
		}
		mSHomeSceneObjectListCs.readUnLock();

		return result;
	}

	//-----------------------------------------------------------------------------
	void SHomeMapObject::destroyScene(InstanceUIdType instanceUid)
	{
		mSHomeSceneObjectListCs.writeLock();
		{
			std::map<InstanceUIdType,SHomeSceneObjectPtr>::iterator iter = mSHomeSceneObjecList.find(instanceUid);
			if ( iter != mSHomeSceneObjecList.end() )
			{
				iter->second->clear();
				mSHomeSceneObjecList.erase( iter );
			}
		}
		mSHomeSceneObjectListCs.writeUnLock();
	}

	//-----------------------------------------------------------------------------
	void SHomeMapObject::destroyAllScene()
	{
		mSHomeSceneObjectListCs.writeLock();
		{
			//SPlayerPtr ptr;

			std::map<InstanceUIdType,SHomeSceneObjectPtr>::iterator iter = mSHomeSceneObjecList.begin();
			for ( ;iter != mSHomeSceneObjecList.end(); iter++ )
			{
				iter->second->clear();
				//iter->second->setPlayer( ptr );
			}
			mSHomeSceneObjecList.clear();

		}
		mSHomeSceneObjectListCs.writeUnLock();
	}

}	//namespace MG