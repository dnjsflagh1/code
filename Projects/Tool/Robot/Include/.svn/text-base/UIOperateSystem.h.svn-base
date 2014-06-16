//***********************************************************************************************************
#ifndef _UIOPERATESYSTEM_H_
#define _UIOPERATESYSTEM_H_
//***********************************************************************************************************
namespace MG
{
	enum UIOperateMode;
	class UiOperateSystem
	{
		UiOperateSystem(){};
		~UiOperateSystem(){};
		SINGLETON_INSTANCE(UiOperateSystem);

	public:
		void					setOperateMode(UIOperateMode mode);
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
		//Bool					addCreateCampaginOp(U32 campaginNum,U32 generalNum);
	};
}
#endif