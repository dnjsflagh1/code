/******************************************************************************/

#include "stdafx.h"
#include "BattleStatics.h"
#include "BattleFieldNoticeListCsv.h"
#include "SBattleScoreNetPacketProcesser.h"

/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------
	BattleStatics::BattleStatics()
			:mKillGeneralPoint(0)
			,mSupKillGeneralPoint(0)
			,mGeneralHurtPoint(0)
			,mKillArmyPoint(0)
			,mSupKillArmyPoint(0)			//5
			,mArmyHurtPoint(0)
			,mDestoryBuildPoint(0)
			,mSupDestoryBuildPoint(0)
			,mBuildHurtPoint(0)
			,mDestoryForcePoint(0)			//10
			,mSupDestoryForcePoint(0)
			,mForceHurtPoint(0)
			,mHealGeneralPoint(0)
			,mHealArmyPoint(0)
			,mHealBuildPoint(0)				//15
			,mDeathPoint(0)
			,mNormalRevivePoint(0)
			,mPotionRevivePoint(0)
			,mConstructBuildPoint(0)
			,mLastKillGeneralTime(0)		//20
			,mContinueKillGeneralPoint(0)
	{

	}

	//--------------------------------------------------------------------------
	void BattleStatics::clearData()
	{
		mKillGeneralPoint = 0;
		mSupKillGeneralPoint = 0;
		mGeneralHurtPoint = 0;
		mKillArmyPoint = 0;
		mSupKillArmyPoint = 0;
		
		mArmyHurtPoint = 0;
		mDestoryBuildPoint = 0;
		mSupDestoryBuildPoint = 0;
		mBuildHurtPoint = 0;
		mDestoryForcePoint = 0;

		mSupDestoryForcePoint = 0;
		mForceHurtPoint = 0;
		mHealGeneralPoint = 0;
		mHealArmyPoint = 0;
		mHealBuildPoint = 0;

		mDeathPoint = 0;
		mNormalRevivePoint = 0;
		mPotionRevivePoint = 0;
		mConstructBuildPoint = 0;
		mLastKillGeneralTime = 0;
		mContinueKillGeneralPoint = 0;
	}

	//--------------------------------------------------------------------------
	BattleStatics::~BattleStatics()
	{

	}

	//--------------------------------------------------------------------------
	void BattleStatics::NotifyBattleScoreByConditionType(const BattleFieldConditionType conditionType, SRegionObjectBase* region)
	{
		BattleFieldNoticeListCsvInfo* noticeInfo = BattleFieldNoticeListCsv::getInstance().getNoticeInfoByConditionType(conditionType);
		if (NULL != noticeInfo && noticeInfo->conditionValue == mKillGeneralPoint)
		{
			//·¢ËÍ¹«¸æ
			//sendNotice();
			int ii = 0;
			SBattleScoreNetPacketProcesser::getInstance().sendBattleScoreNotify(noticeInfo->rankId, region);
		}
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementKillGeneralPoint(SRegionObjectBase* region)
	{
		++mKillGeneralPoint;
		if (NULL != region)
		{
			NotifyBattleScoreByConditionType(BFCT_KillGeneral, region);
		}
	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getKillGeneralPoint() const
	{
		return mKillGeneralPoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementSupKillGeneralPoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getSupKillGeneralPoint() const
	{
		return mSupKillGeneralPoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementGeneralHurtPoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getGeneralHurtPoint() const
	{
		return mGeneralHurtPoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementKillArmyPoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getKillArmyPoint() const
	{
		return mKillArmyPoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementSupKillArmyPoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getSupKillArmyPoint() const
	{
		return mSupKillArmyPoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementArmyHurtPoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getArmyHurtPoint()const
	{
		return mArmyHurtPoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementDestoryBuildPoint()
	{

	}
	//--------------------------------------------------------------------------
	Int BattleStatics::getDestoryBuildPoint()const
	{
		return mDestoryBuildPoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementSupDestoryBuildPoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getSupDestoryBuildPoint()const
	{
		return mSupDestoryBuildPoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementBuildHurtPoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getBuildHurtPoint()const
	{
		return mBuildHurtPoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementDestoryForcePoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getDestoryForcePoint()const
	{
		return mDestoryForcePoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementSupDestoryForcePoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getSupDestoryForcePoint()const
	{
		return mSupDestoryForcePoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementForceHurtPoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getForceHurtPoint()const
	{
		return mForceHurtPoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementHealGeneralPoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getHealGeneralPoint()const
	{
		return mHealGeneralPoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementHealArmyPoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getHealArmyPoint()const
	{
		return mHealArmyPoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementHealBuildPoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getHealBuildPoint()const
	{
		return mHealBuildPoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementDeathPoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getDeathPoint()const
	{
		return mDeathPoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementNormalRevivePoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getNormalRevivePoint()const
	{
		return mNormalRevivePoint;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementPotionRevivePoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getPotionRevivePoint() const
	{
		return mPotionRevivePoint;
	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getConstructBuildPoint() const
	{
		return mConstructBuildPoint;
	}


	//--------------------------------------------------------------------------
	void BattleStatics::incrementLastKillGeneralTime()
	{

	}

	//--------------------------------------------------------------------------
	U64 BattleStatics::getLastKillGeneralTime()const
	{
		return mLastKillGeneralTime;
	}

	//--------------------------------------------------------------------------
	void BattleStatics::incrementContinueKillGeneralPoint()
	{

	}

	//--------------------------------------------------------------------------
	Int BattleStatics::getContinueKillGeneralPoint()const
	{
		return mContinueKillGeneralPoint;
	}
}
