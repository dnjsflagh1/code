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

		//״̬����
		static Str STATE_NAME;

		///�����¼�
		virtual void        							update( Flt delta );
		///�Ƿ������
		virtual Bool        							isFinished();
		///��ȥ״̬�¼�
		virtual void        							onEnter();
		///�뿪״̬�¼�
		virtual void        							onLeave();

		void											notifySelectSkill( UInt skillId );

		void											setSelectSkill( std::vector<SkillRatio>& skillRatioList );


	private:

		std::vector<SkillInterval>						mSkillIntervalList;
		UInt											mMaxRatio;
		
	};
}

#endif