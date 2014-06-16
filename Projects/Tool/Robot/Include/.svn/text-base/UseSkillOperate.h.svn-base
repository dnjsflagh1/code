/******************************************************************************/
#ifndef _USESKILLOPERATE_H_
#define _USESKILLOPERATE_H_
/******************************************************************************/
#include "Operate.h"
/******************************************************************************/
namespace MG
{
	class UseSkillOperate : public BaseOperate
	{
	public:
		UseSkillOperate(OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type);
		virtual~UseSkillOperate(){};

		virtual Bool        onEnter();
		virtual	Bool		isFinish();
		virtual void        onNetEvent(Byte channel,Byte type,void* data);
		virtual void        onLeave();
		virtual	void		onCloseByLoginServer();
		virtual	void		onCloseByFrontServer();

		static U32			mEnterTick;			//操作进入时间
		static U32			mIntervalTime;		//操作间隔时间
	};
	
}
#endif //_USESKILLOPERATE_H_