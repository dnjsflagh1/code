//***************************************************************************************
#ifndef _H_BUFFDATA_
#define _H_BUFFDATA_
//***************************************************************************************
#include "WorldCoreDefine.h"
#include "StatusList.h"
#include "StatusBaseInfo.h"
#include "StatusCharacterList.h"
//***************************************************************************************
namespace MG
{
	struct BuffData 
	{
		U32 mTimeStart;			//状态的开始时间
		Flt mTimeUse;			//状态的使用时间
		Flt mTimeSpaceLast;		//间隔剩余时间
		Int mCurAddNum;			//状态的叠加层次
		Int mBuffId;			//状态的Id
		Flt mTimeSpace;			//记录时间间隔。
		//状态的模板信息
		const StatusBaseInfo* mpStatusBaseInfo;
		//----------------------------------------------------------------
		BuffData()
			:mTimeStart(0)
			,mTimeUse(0)
			,mTimeSpaceLast(0)
			,mCurAddNum(1)
			,mBuffId(0)
			,mpStatusBaseInfo(NULL)
			,mTimeSpace(0)
		{

		}
		//----------------------------------------------------------------
		~BuffData()
		{
			clear();
		}
		//----------------------------------------------------------------
		template <typename T>
		const T* getStatusBaseInfo() const
		{
			return (const T*)((void*)mpStatusBaseInfo);
		}
		//----------------------------------------------------------------
		void init(const StatusData* pStatusData, UInt addNum, UInt timeUse)
		{
			//获得buff模板信息
			DYNAMIC_ASSERT(pStatusData);

			mBuffId = pStatusData->StatusId;
			mpStatusBaseInfo = pStatusData->mpStatusBaseInfo;
			mTimeStart = MGTimeOp::getCurrTick();
			mCurAddNum = addNum;
			mTimeUse = timeUse;
		}
		//----------------------------------------------------------------
		void clear()
		{
			mTimeStart = 0;
			mTimeUse = 0.f;
			mTimeSpaceLast = 0.f;
			mCurAddNum = 1;
			mBuffId = 0;
			mpStatusBaseInfo = NULL;
			mTimeSpace  = 0.f;
		}
		
		//----------------------------------------------------------------
		Bool isClear(){return mpStatusBaseInfo == NULL;}
		//----------------------------------------------------------------
		void	setAddNum()
		{
			++mCurAddNum;
		}
		//----------------------------------------------------------------
		Bool update(Flt delta)
		{
			if ( mTimeSpaceLast != 0 )
			{
				mTimeSpaceLast -= delta*1000;
				mTimeUse -= delta*1000;
				if ( mTimeSpaceLast <= 0 )
				{	
					mTimeSpaceLast = mTimeSpace;
					return true;
				}
			}

			return false;
		}
		//----------------------------------------------------------------
		BuffData& operator =(const BuffData& A)
		{
			mBuffId = A.mBuffId;
			mCurAddNum = A.mCurAddNum;
			mpStatusBaseInfo = A.mpStatusBaseInfo;
			mTimeSpaceLast = A.mTimeSpaceLast;
			mTimeStart = A.mTimeStart;
			mTimeUse = A.mTimeUse;

			return *this;
		}
	};
}
//***************************************************************************************
#endif
//***************************************************************************************