//******************************************************************************************************
#include "stdafx.h"
#include "BuffManager.h"
#include "BuffObject.h"
//******************************************************************************************************
namespace MG
{
	void BuffManager::update( Flt delta )
	{
		std::map<UInt, BuffObject*>::iterator front = mMapBuffObject.begin();
		std::map<UInt, BuffObject*>::iterator back = mMapBuffObject.end();
		while (front != back)
		{
			if ( front->second->update(delta) == false )
			{	
				deleteBuff(front);
				continue;
			}
			++front;
		}
	}
	//------------------------------------------------------------------
	void BuffManager::addNewBuff( UInt buffId, UInt addNum, UInt objLvl )
	{
		const StatusData* pStatusData = StatusList::getInstance().getStatusData(buffId, objLvl);
		if ( pStatusData == NULL ) return;

		std::map<UInt, BuffObject*>::iterator iter = mMapBuffObject.find(pStatusData->mpStatusBaseInfo->SlotNum);
		if ( iter != mMapBuffObject.end() )
		{
			iter->second->addBuff(pStatusData, addNum);
		}
		else
		{
			BuffObject* pBuffObject = createBuff(pStatusData->StatusType);
			pBuffObject->addBuff(pStatusData, addNum);
			mMapBuffObject[pStatusData->mpStatusBaseInfo->SlotNum] = pBuffObject;
		}
	}

	void BuffManager::addOldBuff( UInt buffId, UInt timeUse, UInt addNum )
	{
		const StatusData* pStatusData = StatusList::getInstance().getStatusData(buffId);
		if ( pStatusData == NULL ) return;

		std::map<UInt, BuffObject*>::iterator iter = mMapBuffObject.find(pStatusData->mpStatusBaseInfo->SlotNum);
		if ( iter != mMapBuffObject.end() )
		{
			iter->second->addBuff(pStatusData, timeUse, addNum);
		}
		else
		{
			BuffObject* pBuffObject = createBuff(pStatusData->StatusType);
			pBuffObject->addBuff(pStatusData, timeUse, addNum);
			mMapBuffObject[pStatusData->mpStatusBaseInfo->SlotNum] = pBuffObject;
		}
	}
	//------------------------------------------------------------------
	void BuffManager::init()
	{
	}
	//------------------------------------------------------------------
	void BuffManager::clear()
	{
		std::map<UInt, BuffObject*>::iterator front = mMapBuffObject.begin();
		std::map<UInt, BuffObject*>::iterator back = mMapBuffObject.end();
		while (front != back)
		{
			deleteBuff(front, false);
		}
	}
	//------------------------------------------------------------------
	void BuffManager::deleteBuff( UInt buffId )
	{
		const StatusData* pStatusData = StatusList::getInstance().getStatusData(buffId);
		DYNAMIC_ASSERT(pStatusData);

		std::map<UInt, BuffObject*>::iterator iter = mMapBuffObject.find(pStatusData->mpStatusBaseInfo->SlotNum);
		if ( iter != mMapBuffObject.end() )
			deleteBuff(iter);
	}
	//------------------------------------------------------------------
	void BuffManager::deleteBuff( std::map<UInt, BuffObject*>::iterator& iter, Bool isCal )
	{
		iter->second->clear(isCal);
		delete iter->second;
		iter = mMapBuffObject.erase(iter);
	}
	//------------------------------------------------------------------
	BuffManager::~BuffManager()
	{
		clear();
	}
	//------------------------------------------------------------------
	BuffManager::BuffManager( void* parent )
		:mParent(parent)
	{

	}
	//------------------------------------------------------------------
	
}