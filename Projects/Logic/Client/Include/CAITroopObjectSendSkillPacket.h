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