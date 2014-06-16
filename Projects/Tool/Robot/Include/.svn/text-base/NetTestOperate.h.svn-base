/******************************************************************************/
#ifndef _NETTESTOPERATE_H_
#define _NETTESTOPERATE_H_
/******************************************************************************/
namespace MG
{
	class NetTestOperate : public BaseOperate
	{
	public:
		NetTestOperate(OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type);
		virtual~NetTestOperate(){};

		virtual Bool        onEnter();
		virtual	Bool		isFinish();
		virtual void        onNetEvent(Byte channel,Byte type,void* data);
		virtual void        onLeave();
		virtual	void		onCloseByLoginServer();
		virtual	void		onCloseByFrontServer();

		static U32			mEnterTick;		//操作进入时间
		static U32			mIntervalTime;		//操作间隔时间
	};
}
#endif //_NETTESTOPERATE_H_