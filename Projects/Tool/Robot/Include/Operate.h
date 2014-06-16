/******************************************************************************/
#ifndef _OPERATE_H_
#define _OPERATE_H_
/******************************************************************************/
namespace MG
{
	enum OperateType
	{
		OperateType_null,
		OperateType_AccountLogin,
		OperateType_CreateClan,
		OperateType_DeleteClan,
		OperateType_JoinGame,
		OperateType_Close,
		OperateType_AutoJoinGame,
		OperateType_UseSkill,
		OperateType_JumpRegion,
		OperateType_NetTest,
		OperateType_RandMove,
		OperateType_CreateTroop,
		OperateType_CreateCampaign,
		OperateType_TestNetLogin,
		OperateType_connectLogin,
		OperateType_netChat,
		OperateType_Max,
	};
	//==============================================================================
	class CClient;
	class OperateManager;
	class CClientMessage;
	class BaseOperate
	{
	public:
		BaseOperate(OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type);
		virtual ~BaseOperate();

	public:
		virtual Bool        onEnter();
		virtual void        onNetEvent(Byte channel,Byte type,void* data) = NULL;
		virtual void        onLeave() = NULL;
		virtual	void		onCloseByLoginServer() = NULL;
		virtual	void		onCloseByFrontServer() = NULL;     
		virtual void        update();

		OperateType			getType(){return mType;};
		void				setTimeOut(Bool timeOut = true);
		Bool				isTimeOut();
		void				reset();

		Bool				isEnter();
		Bool				isLeave();
		virtual	Bool		isFinish() = NULL;
		OperateManager*		getManager();

	protected:
		OperateManager*		mManager;
		CClient*			mClient;
		CClientMessage*		mMsg;

		Bool				mIsTimeOut;
		U32					mEnterTick;

		Bool				mIsEnter;
		Bool				mIsLeave;
		Bool				mIsFinish;
		Bool				mIsNormalExit;

		OperateType         mType;
		// 
	};
}
#endif //_OPERATE_H_