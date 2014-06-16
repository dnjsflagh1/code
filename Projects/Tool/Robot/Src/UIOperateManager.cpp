//***********************************************************************************************************
#include "stdafx.h"
#include "UIOperateManager.h"
//***********************************************************************************************************
namespace MG
{

	//--------------------------------------------------------------------------------
	UiOperateManager::UiOperateManager( CClient* client )
	{
		DYNAMIC_ASSERT(client);
		mOwer = client;
		mCurrOrderIndex		= 0;
		mAutoJoinGameOp		= MG_NEW AutoJoinGameOp();
		mAccountLoginOp		= MG_NEW AccountLoginOp();
		mConnectLsOp		= MG_NEW ConnectLsOp();
		mSendDataToLsOp		= MG_NEW SendDataToLsOp();	
		mLoginLsOp			= MG_NEW LoginLsOp();			
		mConnectFsOp		= MG_NEW ConnectFsOp();		
		mSendDataToFsOp		= MG_NEW SendDataToFsOp();		
		mLoginFsOp			= MG_NEW LoginFsOp();			
		mJoinGameOp			= MG_NEW JoinGameOp();			
		mCreateClanOp		= MG_NEW CreateClanOp();		
		mCreateCharacterOp	= MG_NEW CreateCharacterOp();
		mRandMoveOp			= MG_NEW RandMoveOp();			
		mCreateTroopOp		= MG_NEW CreateTroopOp();		
		mTestSkillOp		= MG_NEW TestSkillOp();		
		mJumpMapOp			= MG_NEW JumpMapOp();
		mCloseNetOp			= MG_NEW CloseNetOp();
		mOnceOp = NULL;
		mCurrOrderOperateGroup.clear();
		mCurrOrderOp = NULL;
		mCurrRandomOperateGroup.clear();
		mCurrRandomOp = NULL;
		mOffsetTime = NULL;
		mCurrOperateMode = UIOperateMode_Null;
	}
	//--------------------------------------------------------------------------------
	UiOperateManager::~UiOperateManager()
	{
		mOwer = NULL;
		mCurrOrderOperateGroup.clear();
		mCurrOrderOp = NULL;
		mCurrRandomOperateGroup.clear();
		mCurrRandomOp = NULL;
		mCurrOrderIndex = 0;
		mOnceOp = NULL;
		MG_SAFE_DELETE(mAutoJoinGameOp		);
		MG_SAFE_DELETE(mAccountLoginOp		);
		MG_SAFE_DELETE(mConnectLsOp			);
		MG_SAFE_DELETE(mSendDataToLsOp		);
		MG_SAFE_DELETE(mLoginLsOp			);
		MG_SAFE_DELETE(mConnectFsOp			);
		MG_SAFE_DELETE(mSendDataToFsOp		);
		MG_SAFE_DELETE(mLoginFsOp			);
		MG_SAFE_DELETE(mJoinGameOp			);
		MG_SAFE_DELETE(mCreateClanOp		);
		MG_SAFE_DELETE(mCreateCharacterOp	);
		MG_SAFE_DELETE(mRandMoveOp			);
		MG_SAFE_DELETE(mCreateTroopOp		);
		MG_SAFE_DELETE(mTestSkillOp			);
		MG_SAFE_DELETE(mJumpMapOp			);
		MG_SAFE_DELETE(mCloseNetOp			);

	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::setOperateMode( UIOperateMode mode )
	{
		CriticalArmor Ca(mCs);
		mCurrOperateMode = mode;
		_clearOperate();
	}
	//--------------------------------------------------------------------------------
	UIOperateMode UiOperateManager::getOperateMode()
	{
		CriticalArmor Ca(mCs);
		return mCurrOperateMode;
	}

	void UiOperateManager::update(Flt delta)
	{
		mOffsetTime += delta;
		if (mOffsetTime > 0.2f)
		{
			mOffsetTime = 0.0f;
			BaseUiOperate* op =  getCurrOperate();
			if (op)
			{
				op->exe(mOwer);
			}
		}
		
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::addAutoJoinGameOp()
	{
		CriticalArmor Ca(mCs);
		mAutoJoinGameOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mAutoJoinGameOp;
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mAutoJoinGameOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mAutoJoinGameOp);
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::addAccountLoginOp()
	{
		CriticalArmor Ca(mCs);
		mAccountLoginOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mAccountLoginOp;
			return ;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mAccountLoginOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mAccountLoginOp);
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::addConnectLsOp()
	{
		CriticalArmor Ca(mCs);
		mConnectLsOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mConnectLsOp;
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mConnectLsOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mConnectLsOp);
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::addSendDataToLsOp( U32 size,U32 intervalTick,U32 lifeCycle )
	{
		CriticalArmor Ca(mCs);
		mSendDataToLsOp->setParam(size,intervalTick,lifeCycle);
		mSendDataToLsOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mSendDataToLsOp;
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mSendDataToLsOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mSendDataToLsOp);
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::addLoginLsOp()
	{
		CriticalArmor Ca(mCs);
		mLoginLsOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mLoginLsOp;
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mLoginLsOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mLoginLsOp);
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::addConnectFsOp()
	{
		CriticalArmor Ca(mCs);
		mConnectFsOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mConnectFsOp;
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mConnectFsOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mConnectFsOp);
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::addSendDataToFsOp( U32 size,U32 intervalTick,U32 lifeCycle )
	{
		CriticalArmor Ca(mCs);
		mSendDataToFsOp->setParam(size,intervalTick,lifeCycle);
		mSendDataToFsOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mSendDataToFsOp;
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mSendDataToFsOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mSendDataToFsOp);
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::addLoginFsOp()
	{
		CriticalArmor Ca(mCs);
		mLoginFsOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mLoginFsOp;
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mLoginFsOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mLoginFsOp);
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::addJoinGameOp()
	{
		CriticalArmor Ca(mCs);
		mJoinGameOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mJoinGameOp;
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mJoinGameOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mJoinGameOp);
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::addCreateClanOp()
	{
		CriticalArmor Ca(mCs);
		mCreateClanOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mCreateClanOp;
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mCreateClanOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mCreateClanOp);
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::addCreateCharacterOp()
	{
		CriticalArmor Ca(mCs);
		mCreateCharacterOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mCreateCharacterOp;
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mCreateCharacterOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mCreateCharacterOp);
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::addRandMoveOp( U32 intervalTick,U32 lifeCycle )
	{
		CriticalArmor Ca(mCs);
		mRandMoveOp->setParam(intervalTick,lifeCycle);
		mRandMoveOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mRandMoveOp;
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mRandMoveOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mRandMoveOp);
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::addCreateTroopOp()
	{
		CriticalArmor Ca(mCs);
		mCreateTroopOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mCreateTroopOp;
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mCreateTroopOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mCreateTroopOp);
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::addTestSkillOp(U32 intervalTick,U32 lifeCycle)
	{
		CriticalArmor Ca(mCs);
		mTestSkillOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mTestSkillOp;
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mTestSkillOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mTestSkillOp);
		}
	}	
	//--------------------------------------------------------------------------------
	void UiOperateManager::addJumpMapOp()
	{
		CriticalArmor Ca(mCs);
		mJumpMapOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mJumpMapOp;
			return;;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mJumpMapOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mJumpMapOp);
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::_clearOperate()
	{
		mCurrOrderOperateGroup.clear();
		mCurrOrderOp = NULL;
		mCurrRandomOperateGroup.clear();
		mCurrRandomOp = NULL;
		mCurrOrderIndex = 0;
		mOnceOp = NULL;
	}
	//--------------------------------------------------------------------------------
	BaseUiOperate* UiOperateManager::getCurrOperate()
	{
		CriticalArmor Ca(mCs);
		// 未初始化
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			//DYNAMIC_ASSERT(false);
			return NULL;
		}
		// 一次操作不采取 获取操作
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			BaseUiOperate* temp = mOnceOp;
			mOnceOp = NULL;
			return temp;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			if (mCurrOrderOp)
			{
				// 检测生存周期是否结束

				if(mCurrOrderOp->isFinish())
				// 此操作生存周期结束
				{
					if (mCurrOrderOperateGroup.size() == 0)
					{
						return NULL;
					}
					else
					{
						if (mCurrOrderIndex == mCurrOrderOperateGroup.size() - 1)
						{
							mCurrOrderOp = mCurrOrderOperateGroup[0];
							mCurrOrderIndex = 0;
							mCurrOrderOp->reset();
						}
						else
						{
							mCurrOrderOp = mCurrOrderOperateGroup[++mCurrOrderIndex];
							mCurrOrderOp->reset();
						}
					}
	
					return mCurrOrderOp;
				}
				else
				// 生存周期未结束 
				{
					// 操作间隔是否结束
					if (mCurrOrderOp->canGet())
					{
						return mCurrOrderOp;
					}
					else
					{
						return NULL;
					}
				}
			}
			else
			{
				if (mCurrOrderOperateGroup.size() == 0)
				{
					return NULL;
				}
				else
				{
					mCurrOrderOp = mCurrOrderOperateGroup[0];
					mCurrOrderIndex = 0;
					mCurrOrderOp->reset();
					return mCurrOrderOp;
				}
				
				
			}
			
		}
		else
		{
			if (mCurrRandomOp)
			{
				if(mCurrRandomOp->isFinish())
				{
					if (mCurrRandomOperateGroup.size() == 0)
					{
						mCurrRandomOp = NULL;
					}
					else if (mCurrRandomOperateGroup.size() == 1)
					{
						mCurrRandomOp = mCurrRandomOperateGroup[0];
						mCurrRandomOp->reset();
					}
					else
					{
						mCurrRandomOp = mCurrRandomOperateGroup[MGRandom::getInstance().rand_ab_One(0,mCurrRandomOperateGroup.size()-1)];
						mCurrRandomOp->reset();
					}
					return mCurrRandomOp;
				}
				else
				{
					if (mCurrRandomOp->canGet())
					{
						return mCurrRandomOp;
					}
					else
					{
						return NULL;
					}
				}
			}
			else
			{
				if (mCurrRandomOperateGroup.size() == 0)
				{
					return NULL;
				}
				else if (mCurrRandomOperateGroup.size() == 1)
				{
					mCurrRandomOp = mCurrRandomOperateGroup[0];
				}
				else
				{
					mCurrRandomOp = mCurrRandomOperateGroup[MGRandom::getInstance().rand_ab_One(0,mCurrRandomOperateGroup.size()-1)];
				}
				return mCurrRandomOp;
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateManager::addCloseNetOp()
	{
		CriticalArmor Ca(mCs);
		mCloseNetOp->reset();
		if (mCurrOperateMode == UIOperateMode_Null)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else if (mCurrOperateMode == UIOperateMode_Once)
		{
			mOnceOp = mCloseNetOp;
			return;;
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Order)
		{
			mCurrOrderOperateGroup.push_back(mCloseNetOp);
		}
		else if (mCurrOperateMode == UIOperateMode_Repeatedly_Random)
		{
			mCurrRandomOperateGroup.push_back(mCloseNetOp);
		}
	}
	//--------------------------------------------------------------------------------
}