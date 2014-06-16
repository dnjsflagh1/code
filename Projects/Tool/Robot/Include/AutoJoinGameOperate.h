/******************************************************************************/
#ifndef _AUTOJOINGAMEOPERATE_H_
#define _AUTOJOINGAMEOPERATE_H_
/******************************************************************************/
namespace MG
{
	class AutoJoinGameOperate : public BaseOperate
	{
	public:
		AutoJoinGameOperate(OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type);
		virtual~AutoJoinGameOperate(){};

		virtual Bool        onEnter();
		virtual	Bool		isFinish();
		virtual void        onNetEvent(Byte channel,Byte type,void* data);
		virtual void        onLeave();
		virtual	void		onCloseByLoginServer();
		virtual	void		onCloseByFrontServer();

		Bool				mIsActiveDisconnect;
	};
}
#endif //_AUTOJOINGAMEOPERATE_H_