
/******************************************************************************/

#include "stdafx.h"
#include "SPlaceMapObject.h"
#include "PlaceObjectData.h"


/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	SPlaceMapObject::SPlaceMapObject(PlaceListCsvInfo* placeListCsvInfo, DistrictIdType districtId)
		:SMapObject(MG_NEW PlaceObjectData(placeListCsvInfo, districtId))
		,mPlaceListCsvInfo(placeListCsvInfo)
	{
	}

	//-----------------------------------------------------------------------------
	SPlaceMapObject::~SPlaceMapObject()
	{
	}

	//-----------------------------------------------------------------------------
	DistrictIdType SPlaceMapObject::getDistrictId()
	{
		return getDistrictListCsvInfo()->getDistrictId();
	}

	//-----------------------------------------------------------------------------
	DistrictRankType SPlaceMapObject::getDistrictRankType()
	{
		DistrictListCsvInfo* districtListCsvInfo = getDistrictListCsvInfo();
		DYNAMIC_ASSERT(DRT_ZHOU == districtListCsvInfo->getRank() || 
			DRT_JUN == districtListCsvInfo->getRank() ||
			DRT_XIAN == districtListCsvInfo->getRank());
		return districtListCsvInfo->getRank();
	}

	//-----------------------------------------------------------------------------
	RegionIdType SPlaceMapObject::getRegionId()
	{
		return getPlaceData()->getPlaceId();
	}

	PlaceObjectData* SPlaceMapObject::getPlaceData()
	{
		return (PlaceObjectData*)getRegionData();
	}

	DistrictListCsvInfo* SPlaceMapObject::getDistrictListCsvInfo()
	{
		return getPlaceData()->getDistrictListCsvInfo();
	}

	//-----------------------------------------------------------------------------
	PlaceListCsvInfo* SPlaceMapObject::getPlaceListCsvInfo()
	{
		return mPlaceListCsvInfo;
	}

	//-----------------------------------------------------------------------------
	void SPlaceMapObject::createScene(SPlaceSceneObjectPtr& ptr, InstanceUIdType instanceUid)
	{
		if (getScene(ptr, instanceUid))
		{
			DYNAMIC_EEXCEPT_LOG("already exist SAtkMapObject!");
			destroyScene( instanceUid );
			ptr.setNull();
		}

		mPlaceSceneObjectFactory.createPlaceSceneObjectPtr(ptr, instanceUid);
		//初始化内存

		mSAtkSceneObjectListCs.writeLock();
		{
			mSAtkSceneObjecList[instanceUid] = ptr;
		}
		mSAtkSceneObjectListCs.writeUnLock();
	}

	//-----------------------------------------------------------------------------
	Bool SPlaceMapObject::getScene(SPlaceSceneObjectPtr& ptr, InstanceUIdType instanceUid)
	{
		Bool result = false;

		mSAtkSceneObjectListCs.readLock();
		{
			std::map<InstanceUIdType,SPlaceSceneObjectPtr>::iterator iter = mSAtkSceneObjecList.find(instanceUid);
			if ( iter != mSAtkSceneObjecList.end() )
			{
				ptr = iter->second;
				result = true;
			}
		}
		mSAtkSceneObjectListCs.readUnLock();

		return result;
	}

	//-----------------------------------------------------------------------------
	void SPlaceMapObject::destroyScene(InstanceUIdType instanceUid)
	{
		mSAtkSceneObjectListCs.writeLock();
		{
			std::map<InstanceUIdType,SPlaceSceneObjectPtr>::iterator iter = mSAtkSceneObjecList.find(instanceUid);
			if ( iter != mSAtkSceneObjecList.end() )
			{
				iter->second->clear();
				mSAtkSceneObjecList.erase( iter );
			}
		}
		mSAtkSceneObjectListCs.writeUnLock();
	}

	//-----------------------------------------------------------------------------
	void SPlaceMapObject::destroyAllScene()
	{
		mSAtkSceneObjectListCs.writeLock();
		{
			//SPlayerPtr ptr;

			std::map<InstanceUIdType,SPlaceSceneObjectPtr>::iterator iter = mSAtkSceneObjecList.begin();
			for ( ;iter != mSAtkSceneObjecList.end(); iter++ )
			{
				iter->second->clear();
				//iter->second->setPlayer( ptr );
			}
			mSAtkSceneObjecList.clear();

		}
		mSAtkSceneObjectListCs.writeUnLock();
	}

	//-----------------------------------------------------------------------------
	void SPlaceMapObject::createMainScene(SPlaceSceneObjectPtr& ptr)
	{
		//主城的话 副本Id为 0
		InstanceUIdType instanceUid = 0;
		if (getMainScene(ptr))
		{
			DYNAMIC_EEXCEPT_LOG("already exist Main SAtkMapObject!");
			destroyMainScene();
			ptr.setNull();
		}

		mPlaceSceneObjectFactory.createPlaceSceneObjectPtr(ptr, instanceUid);
		//初始化内存

		mSAtkSceneObjectListCs.writeLock();
		{
			mMainAtkSceneObject = ptr;
		}
		mSAtkSceneObjectListCs.writeUnLock();
	}

	//-----------------------------------------------------------------------------
	Bool SPlaceMapObject::getMainScene(SPlaceSceneObjectPtr& ptr)
	{
		if (false == mMainAtkSceneObject.isNull())
		{
			return false;
		}

		mSAtkSceneObjectListCs.readLock();
		{
			ptr = mMainAtkSceneObject;
		}
		mSAtkSceneObjectListCs.readUnLock();

		return true;
	}

	//-----------------------------------------------------------------------------
	void SPlaceMapObject::destroyMainScene()
	{
		mSAtkSceneObjectListCs.writeLock();
		{
			mMainAtkSceneObject->clear();
		}
		mSAtkSceneObjectListCs.writeUnLock();
	}
	//-----------------------------------------------------------------------------

}	//namespace MG