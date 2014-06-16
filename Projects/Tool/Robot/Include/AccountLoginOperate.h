/******************************************************************************/
#ifndef _ACCOUNTLOGINOPERATE_H_
#define _ACCOUNTLOGINOPERATE_H_
/******************************************************************************/
namespace MG
{
	//==============================================================================
	class AccountLoginOperate : public BaseOperate
	{
	public:
		AccountLoginOperate(OperateManager* mgr ,CClient* client,CClientMessage* msg,OperateType type);
		virtual~AccountLoginOperate();

		virtual Bool        onEnter();
		virtual	Bool		isFinish();
		virtual void        onNetEvent(Byte channel,Byte type,void* data);
		virtual void        onLeave();
		virtual	void		onCloseByLoginServer();
		virtual	void		onCloseByFrontServer();

	};
}
#endif //_ACCOUNTLOGINOPERATE_H_