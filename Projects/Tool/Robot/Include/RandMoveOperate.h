/******************************************************************************/
#ifndef _RANDMOVEOPERATE_H_
#define _RANDMOVEOPERATE_H_
/******************************************************************************/
#include "RandMoveOperate.h"
/******************************************************************************/
namespace MG
{
	class RandMoveOperate : public BaseOperate
	{
	public:
		RandMoveOperate(OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type);
		virtual~RandMoveOperate(){};

		virtual Bool        onEnter();
		virtual	Bool		isFinish();
		virtual void        onNetEvent(Byte channel,Byte type,void* data);
		virtual void        onLeave();
		virtual	void		onCloseByLoginServer();
		virtual	void		onCloseByFrontServer();
        virtual void        update();
		U32					mEnterTick;				//操作进入时间
		static U32			mIntervalTime;			//操作间隔时间
		static U32			lifePeroid;				//生命周期
		U32					mLastMoveTime;          //上一次移动的时间
	};
	/******************************************************************************/
	class ConnectLoginOperate : public BaseOperate
	{
	public:
		ConnectLoginOperate(OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type);
		virtual~ConnectLoginOperate(){};

		virtual Bool        onEnter();
		virtual	Bool		isFinish();
		virtual void        onNetEvent(Byte channel,Byte type,void* data);
		virtual void        onLeave();
		virtual	void		onCloseByLoginServer();
		virtual	void		onCloseByFrontServer();
	};
	/******************************************************************************/
	class NetTestLoginOperate : public BaseOperate
	{
	public:
		NetTestLoginOperate(OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type);
		virtual~NetTestLoginOperate(){};

		virtual Bool        onEnter();
		virtual	Bool		isFinish();
		virtual void        onNetEvent(Byte channel,Byte type,void* data);
		virtual void        onLeave();
		virtual	void		onCloseByLoginServer();
		virtual	void		onCloseByFrontServer();
		U32					mEnterTick;				//操作进入时间
		static	U32			mIntervalTime;			//操作间隔时间
		U32					mLastSendTime;          //上一次发送的时间
		static	I32			mSize;		
	};
	
}
#endif //_RANDMOVEOPERATE_H_