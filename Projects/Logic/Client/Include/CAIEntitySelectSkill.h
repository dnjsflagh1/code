/******************************************************************************/
#ifndef _CAIENTITYSELECTSKILL_H_
#define _CAIENTITYSELECTSKILL_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "CAI.h"

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

	class CAIEntitySelectSkill : public CAI, public LinedStateObject
	{
		struct SkillInterval
		{
			UInt skillId;
			UInt minVal;
			UInt maxVal;
		};

	public:
		CAIEntitySelectSkill( CCharacterSceneEntity* characterSceneEntity );
		virtual ~CAIEntitySelectSkill();

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