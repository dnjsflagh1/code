/******************************************************************************/
#ifndef _DELETECLANOPERATE_H_
#define _DELETECLANOPERATE_H_
/******************************************************************************/
namespace MG
{
	
	class DeleteClanOperate : public BaseOperate
	{
	public:
		DeleteClanOperate(OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type);
		virtual~DeleteClanOperate(){};

		virtual Bool        onEnter();
		virtual	Bool		isFinish();
		virtual void        onNetEvent(Byte channel,Byte type,void* data);
		virtual void        onLeave();
		virtual	void		onCloseByLoginServer();
		virtual	void		onCloseByFrontServer();
	};

}
#endif //_DELETECLANOPERATE_H_