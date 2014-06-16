//***********************************************************************************************************
#ifndef _UIOPERATEMANAGER_H_
#define _UIOPERATEMANAGER_H_
//***********************************************************************************************************
#include "UIOperate.h"
//***********************************************************************************************************
namespace MG
{

	enum UIOperateMode
	{
		UIOperateMode_Null,				// 不可用状态
		UIOperateMode_Once,				// 一次操作
		UIOperateMode_Repeatedly_Order,	// 多次顺序操作
		UIOperateMode_Repeatedly_Random	// 多次随机操作

	};
	/*********************************************************************************
		#界面 ->UIOperateManager 状态 <- UIOperateManager
		# 状态
			需要知道管理器操作模式（由管理器通知状态）
			当为 一次操作时 管理器告诉状态可否取操作，可取操作时，状态上次操作处理完毕 取新操作
			当为 多次操作是 状态上次操作完毕，取新的操作
			状态如何判断操作完毕
		# 界面 分为配置、一次操作，多次顺序（分组），多次随机（分组）页
			 界面当前操作组对应管理器当前操作组
			 一次对应 当前操作
	/*********************************************************************************/
	class UiOperateManager
	{
	public:
		UiOperateManager(CClient* client);
		~UiOperateManager();
	public:
		void					update(Flt delta);

	public:
		void					setOperateMode(UIOperateMode mode);
		UIOperateMode			getOperateMode();
		
		void					addAutoJoinGameOp();
		void					addAccountLoginOp();
		void					addConnectLsOp();
		void					addSendDataToLsOp(U32 size,U32 intervalTick,U32 lifeCycle);
		void					addLoginLsOp();
		void					addConnectFsOp();
		void					addSendDataToFsOp(U32 size,U32 intervalTick,U32 lifeCycle);
		void					addLoginFsOp();
		void					addJoinGameOp();
		void					addCreateClanOp();
		void					addCreateCharacterOp();
		void					addRandMoveOp(U32 intervalTick,U32 lifeCycle);
		void					addCreateTroopOp();
		void					addTestSkillOp(U32 intervalTick,U32 lifeCycle);
		void					addJumpMapOp();
		void					addCloseNetOp();
		
		BaseUiOperate*			getCurrOperate();

	private:	
		void					_clearOperate();

	private:
		UIOperateMode				mCurrOperateMode;
		
		std::vector<BaseUiOperate*>	mCurrOrderOperateGroup;
		BaseUiOperate*				mCurrOrderOp;
		U32							mCurrOrderIndex;
		
		std::vector<BaseUiOperate*>	mCurrRandomOperateGroup;
		BaseUiOperate*				mCurrRandomOp;

		BaseUiOperate*				mOnceOp;
		//############################################################################
		AutoJoinGameOp*				mAutoJoinGameOp;
		AccountLoginOp*				mAccountLoginOp;
		ConnectLsOp*				mConnectLsOp;
		SendDataToLsOp*				mSendDataToLsOp;
		LoginLsOp*					mLoginLsOp;
		ConnectFsOp*				mConnectFsOp;
		SendDataToFsOp*				mSendDataToFsOp;
		LoginFsOp*					mLoginFsOp;
		JoinGameOp*					mJoinGameOp;
		CreateClanOp*				mCreateClanOp;
		CreateCharacterOp*			mCreateCharacterOp;
		RandMoveOp*					mRandMoveOp;
		CreateTroopOp*				mCreateTroopOp;
		TestSkillOp*				mTestSkillOp;
		JumpMapOp*					mJumpMapOp;
		CloseNetOp*					mCloseNetOp;
		//############################################################################

		CClient*					mOwer;
		const Critical				mCs;

		Flt							mOffsetTime;
	};
}
#endif