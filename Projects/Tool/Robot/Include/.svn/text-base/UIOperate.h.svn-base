//***********************************************************************************************************
#ifndef _UIOPERATE_H_
#define _UIOPERATE_H_
//***********************************************************************************************************

//***********************************************************************************************************
namespace MG
{
	/*
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
	*/
	// UI²Ù×÷
	class CClient;
	class BaseUiOperate
	{
	public:
		BaseUiOperate(){}
		virtual ~BaseUiOperate(){}

	public:
		virtual	void exe(CClient* client) = 0;
		virtual void reset() = 0;
		virtual	Bool isFinish() {return true;}
		virtual	Bool canGet(){return true;}
	};
	//--------------------------------------------------------------------------------
	class AutoJoinGameOp : public BaseUiOperate
	{
	public:
		AutoJoinGameOp(){}
		virtual ~AutoJoinGameOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
	};
	//--------------------------------------------------------------------------------
	class AccountLoginOp : public BaseUiOperate
	{
	public:
		AccountLoginOp(){}
		virtual ~AccountLoginOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
	};
	//--------------------------------------------------------------------------------
	class ConnectLsOp : public BaseUiOperate
	{
	public:
		ConnectLsOp(){}
		virtual ~ConnectLsOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
	};
	//--------------------------------------------------------------------------------
	class SendDataToLsOp : public BaseUiOperate
	{
	public:
		SendDataToLsOp(){}
		virtual ~SendDataToLsOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
		virtual	Bool isFinish();
		virtual	Bool canGet();
		void		 setParam(U32 size,U32 intervalTick,U32 lifeCycle);
	private:
		U32			mSize;
		U32			mStartTick;
		U32			mLifeCycle;
		U32			mLastTick;
		U32			mIntervalTick;
	};
	//--------------------------------------------------------------------------------
	class LoginLsOp : public BaseUiOperate
	{
	public:
		LoginLsOp(){}
		virtual ~LoginLsOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
	};
	//--------------------------------------------------------------------------------
	class ConnectFsOp : public BaseUiOperate
	{
	public:
		ConnectFsOp(){}
		virtual ~ConnectFsOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
	};	
	//--------------------------------------------------------------------------------
	class SendDataToFsOp : public BaseUiOperate
	{
	public:
		SendDataToFsOp(){}
		virtual ~SendDataToFsOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
		virtual	Bool isFinish();
		virtual	Bool canGet();
		void		setParam(U32 size,U32 intervalTick, U32 lifeCycle);
		U32			mSize;
		U32 		mIntervalTick;
		U32			mLastTick;
		U32 		mStartTick;
		U32 		mLifeCycle;
	};
	//--------------------------------------------------------------------------------
	class LoginFsOp : public BaseUiOperate
	{
	public:
		LoginFsOp(){}
		virtual ~LoginFsOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
	};

	//--------------------------------------------------------------------------------
	class CreateClanOp : public BaseUiOperate
	{
	public:
		CreateClanOp(){}
		virtual ~CreateClanOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
	};
	//--------------------------------------------------------------------------------
	class CreateCharacterOp : public BaseUiOperate
	{
	public:
		CreateCharacterOp(){}
		virtual ~CreateCharacterOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
	};
	//--------------------------------------------------------------------------------
	class JoinGameOp : public BaseUiOperate
	{
	public:
		JoinGameOp(){}
		virtual ~JoinGameOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
	};	
	//--------------------------------------------------------------------------------
	class RandMoveOp : public BaseUiOperate
	{
	public:
		RandMoveOp(){}
		virtual~RandMoveOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
		virtual	Bool isFinish();
		virtual	Bool canGet();
		void		setParam(U32 intervalTick, U32 lifeCycle);

	private:
		U32 		mIntervalTick;
		U32			mLastTick;
		U32 		mStartTick;
		U32 		mLifeCycle;

	};
	//--------------------------------------------------------------------------------
	class CreateTroopOp : public BaseUiOperate
	{
	public:
		CreateTroopOp(){}
		virtual ~CreateTroopOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
	};
	//--------------------------------------------------------------------------------
	class TestSkillOp : public BaseUiOperate
	{
	public:
		TestSkillOp(){}
		virtual ~TestSkillOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
		virtual	Bool isFinish();
		virtual	Bool canGet();

	private:
		U32 		mIntervalTick;
		U32			mLastTick;
		U32 		mStartTick;
		U32 		mLifeCycle;
	};
	//--------------------------------------------------------------------------------
	class JumpMapOp : public BaseUiOperate
	{
	public:
		JumpMapOp(){}
		virtual ~JumpMapOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
	};
	//--------------------------------------------------------------------------------
	class CloseNetOp : public BaseUiOperate
	{
	public:
		CloseNetOp(){mLifeCycle = 200;}
		virtual ~CloseNetOp(){}

	public:
		virtual	void exe(CClient* client);
		virtual void reset();
		virtual	Bool isFinish();
		virtual	Bool canGet();
		U32 		mIntervalTick;
		U32			mLastTick;
		U32 		mStartTick;
		U32 		mLifeCycle;
	};
	//--------------------------------------------------------------------------------
}
#endif