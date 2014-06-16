//******************************************************************************************************
#include "stdafx.h"
#include "BuffObject.h"
//******************************************************************************************************
namespace MG
{
	Bool BuffObject::update( Flt delta )
	{
		//判断是否是角色。（只有角色才有周期性）
		//?
		if ( mBuffData.mpStatusBaseInfo->TimeType != STATUS_TIMETYPE_FOREVER )
		{
			//计算是否到了一个时间间隔。
			if ( mBuffData.update(delta) )
			{
				updateBuffOther(delta);
				//如果时间跑完了
				if ( mBuffData.mTimeUse <= 0 )
				{
					return false;
				}
			}
		}

		return true;
	}
	//-------------------------------------------------------------------
	MG::Bool BuffObject::checkCanAdd(  const StatusData* pStatusData, UInt& addNum  )
	{
		//检查自己是否有Buff。
		if ( isClear() == false )
		{
			//是否能堆叠
			if ( pStatusData->StatusId == mBuffData.mBuffId  &&  mBuffData.mpStatusBaseInfo->MaxAddNum > 1 )
			{
				if ( mBuffData.mCurAddNum + addNum < mBuffData.mpStatusBaseInfo->MaxAddNum )	
					addNum += mBuffData.mCurAddNum;
				else 
					addNum = mBuffData.mpStatusBaseInfo->MaxAddNum;

				return true;
			}
			//是否能替换;
			else
			{
				if ( pStatusData->mpStatusBaseInfo->SlotPriority >= mBuffData.mpStatusBaseInfo->SlotPriority )
				{
					clear();
					if ( addNum > pStatusData->mpStatusBaseInfo->MaxAddNum )
						addNum = pStatusData->mpStatusBaseInfo->MaxAddNum;
					return true;
				}
			}
		}
		//新buff
		else
		{
			if ( addNum > pStatusData->mpStatusBaseInfo->MaxAddNum )
				addNum = pStatusData->mpStatusBaseInfo->MaxAddNum;
			return true;
		}

		return false;
	}
	//-------------------------------------------------------------------
	void BuffObject::init( const StatusData* pStatusData, Int timeUse, Int addNum )
	{
		mBuffData.init(pStatusData, addNum, timeUse);
		initBuffOther(pStatusData, timeUse);
	}
	//-------------------------------------------------------------------
	void BuffObject::clear(Bool isCal)
	{
		clearBuffOther(isCal);
		mBuffData.clear();
	}
	//-------------------------------------------------------------------
	void BuffObject::addBuff(  const StatusData* pStatusData, UInt addNum )
	{
		if ( checkCanAdd(pStatusData, addNum) == true )
		{
			init(pStatusData, pStatusData->mpStatusBaseInfo->HoldTime, addNum);
			addBuffOther();
		}
	}
	//-------------------------------------------------------------------
	void BuffObject::addBuff( const StatusData* pStatusData, Int timeUse, Int addNum )
	{
		if ( checkCanAdd(pStatusData, (UInt&)addNum) == true )
		{
			init(pStatusData, timeUse, addNum);
			addBuffOther();
		}	
	}
}