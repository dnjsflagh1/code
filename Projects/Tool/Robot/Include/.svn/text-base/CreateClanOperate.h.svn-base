/******************************************************************************/
#ifndef _CREATECLANOPERATE_H_
#define _CREATECLANOPERATE_H_
/******************************************************************************/
namespace MG
{
	class CreateClanOperate : public BaseOperate
	{
	public:
		CreateClanOperate(OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type);
		virtual~CreateClanOperate(){};

		virtual Bool        onEnter();
		virtual	Bool		isFinish();
		virtual void        onNetEvent(Byte channel,Byte type,void* data);
		virtual void        onLeave();
		virtual	void		onCloseByLoginServer();
		virtual	void		onCloseByFrontServer();
	};
	//--------------------------------------------------------
	class CreateTroopOperate : public BaseOperate
	{
	public:
		CreateTroopOperate(OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type);
		virtual~CreateTroopOperate(){};

		virtual Bool        onEnter();
		virtual	Bool		isFinish();
		virtual void        onNetEvent(Byte channel,Byte type,void* data);
		virtual void        onLeave();
		virtual	void		onCloseByLoginServer();
		virtual	void		onCloseByFrontServer();
	};
}
#endif //_CREATECLANOPERATE_H_