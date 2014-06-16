/******************************************************************************/
#ifndef _JOINGAMEOPERATE_H_
#define _JOINGAMEOPERATE_H_
/******************************************************************************/
namespace MG
{
	class JoinGameOperate : public BaseOperate
	{
	public:
		JoinGameOperate(OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type);
		virtual~JoinGameOperate(){};

		virtual Bool        onEnter();
		virtual	Bool		isFinish();
		virtual void        onNetEvent(Byte channel,Byte type,void* data);
		virtual void        onLeave();
		virtual	void		onCloseByLoginServer();
		virtual	void		onCloseByFrontServer();
	};
}
#endif //_JOINGAMEOPERATE_H_