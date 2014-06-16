/******************************************************************************/
#ifndef _CAMPAIGNOPERATE_H_
#define _CAMPAIGNOPERATE_H_
/******************************************************************************/

/******************************************************************************/
#include "Operate.h"
/******************************************************************************/
namespace MG
{
	/*struct CampaignManagerInfo
	{
		I32 memberCount;
		I32 campaignCount;
	};*/
	class CampaignOperate : public BaseOperate
	{
	public:
		CampaignOperate(OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type);
		virtual~CampaignOperate(){};

		virtual Bool        onEnter();
		virtual	Bool		isFinish();
		virtual void        onNetEvent(Byte channel,Byte type,void* data);
		virtual void        onLeave();
		virtual	void		onCloseByLoginServer();
		virtual	void		onCloseByFrontServer();

		Bool				mIsActiveDisconnect;

		//CampaignManagerInfo*	m

		static Bool mIsContinueOperate;
	};
}
#endif //_CAMPAIGNOPERATE_H_