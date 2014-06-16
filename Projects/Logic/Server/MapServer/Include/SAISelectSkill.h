/******************************************************************************/
#ifndef _SAISELECTSKILL_H_
#define _SAISELECTSKILL_H_
/******************************************************************************/

#include "LinedState.h"
#include "SAI.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************

	******************************************************************************/

	struct SkillRatio
	{
		UInt skillId;
		UInt ratioVal;
	};

	/******************************************************************************/

	class SAISelectSkill : public SAI, public LinedStateObject
	{
		struct SkillInterval
		{
			UInt skillId;
			UInt minVal;
			UInt maxVal;
		};

	public:
		SAISelectSkill( SCharacter* owner );
		virtual ~SAISelectSkill();

		//状态名字
		static Str STATE_NAME;

		///更新事件
		virtual void        							update( Flt delta );
		///是否结束了
		virtual Bool        							isFinished();
		///进去状态事件
		virtual void        							onEnter();
		///离开状态事件
		virtual void        							onLeave();

		void											notifySelectSkill( UInt skillId );

		void											setSelectSkill( std::vector<SkillRatio>& skillRatioList );


	private:

		std::vector<SkillInterval>						mSkillIntervalList;
		UInt											mMaxRatio;
		
	};
}

#endif