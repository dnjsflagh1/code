/******************************************************************************/
#ifndef _CLOSEOPERATE_H_
#define _CLOSEOPERATE_H_
/******************************************************************************/
namespace MG
{

	class CloseOperate : public BaseOperate
	{
	public:
		CloseOperate(OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type);
		virtual~CloseOperate(){};

		virtual Bool        onEnter();
		virtual	Bool		isFinish();
		virtual void        onNetEvent(Byte channel,Byte type,void* data);
		virtual void        onLeave();
		virtual	void		onCloseByLoginServer();
		virtual	void		onCloseByFrontServer();
	};
	
}
#endif //_CLOSEOPERATE_H_