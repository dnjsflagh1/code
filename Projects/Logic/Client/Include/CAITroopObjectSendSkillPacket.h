/******************************************************************************/
#ifndef _CAITROOPOBJECTSENDSKILLPACKET_H_
#define _CAITROOPOBJECTSENDSKILLPACKET_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"

/******************************************************************************/

namespace MG
{

	class CAITroopObjectSendSkillPacket : public LinedStateObject, public LinedStateObjectListener
	{
	public:
		CAITroopObjectSendSkillPacket();
		virtual ~CAITroopObjectSendSkillPacket();

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

	protected:
		void											sendSkillPacket();

	public:
		void											addSendSkill( UInt soldierId, CSkillObject* skillObject );
		////////////////////////////////////////////////////////////////////////

	protected:

	private:
		std::map<UInt, CSkillObject*>					mSendSkillList;
		Flt												mIntervalTime;
		Bool											mIsSendPacket;
	};
}

#endif