//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: CampaignStatics.h
//        Author: yuanlinhu
//          Date: 2012-4-23
//          Time: 10:18
//   Description: 
//			战斗统计数据 （内存）
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-7-9      add
//////////////////////////////////////////////////////////////

#ifndef _BATTLE_STATICS_H_
#define _BATTLE_STATICS_H_

/******************************************************************************/

#include "MapServerPreqs.h"
#include "BattleFieldNoticeListCsv.h"

/******************************************************************************/

namespace MG
{
	class BattleStatics
	{
	public:
		BattleStatics();
		~BattleStatics();

		void clearData();

		void	incrementKillGeneralPoint(SRegionObjectBase* region);
		Int		getKillGeneralPoint() const;

		void	incrementSupKillGeneralPoint();		//辅助击破敌将数
		Int		getSupKillGeneralPoint() const;

		void	incrementGeneralHurtPoint();		//对武将的伤害总量
		Int		getGeneralHurtPoint() const;

		void	incrementKillArmyPoint();			//击破军队数
		Int		getKillArmyPoint() const;

		void	incrementSupKillArmyPoint();		//辅助击破军队数			//5
		Int		getSupKillArmyPoint() const;
		
		void	incrementArmyHurtPoint();			//对军队的伤害总量
		Int		getArmyHurtPoint()const;
		
		void	incrementDestoryBuildPoint();		//击破建筑数
		Int		getDestoryBuildPoint()const;
		
		void	incrementSupDestoryBuildPoint();	//辅助击破建筑数
		Int		getSupDestoryBuildPoint()const;
		
		void	incrementBuildHurtPoint();			//对建筑的伤害总量
		Int		getBuildHurtPoint()const;
		
		void	incrementDestoryForcePoint();		//击破重要据点数			//10
		Int		getDestoryForcePoint()const;
		
		void	incrementSupDestoryForcePoint();	//辅助击破重要据点数
		Int		getSupDestoryForcePoint()const;
		
		void	incrementForceHurtPoint();			//对重要据点的伤害总量
		Int		getForceHurtPoint()const;
		
		void	incrementHealGeneralPoint();		//治疗武将总量
		Int		getHealGeneralPoint()const;
		
		void	incrementHealArmyPoint();			//治疗军队总量
		Int		getHealArmyPoint()const;
		
		void	incrementHealBuildPoint();			//修复建筑耐久总量			//15
		Int		getHealBuildPoint()const;
		
		void	incrementDeathPoint();				//死亡次数
		Int		getDeathPoint()const;
		
		void	incrementNormalRevivePoint();		//普通复活次数
		Int		getNormalRevivePoint()const;
		
		void	incrementPotionRevivePoint();		//使用复活药复活次数
		Int		getPotionRevivePoint()const;

		Int		getConstructBuildPoint() const;

		
		void	incrementLastKillGeneralTime();		//最后一次击破敌将的时间
		U64		getLastKillGeneralTime()const;
		
		void	incrementContinueKillGeneralPoint();
		Int		getContinueKillGeneralPoint()const;

	private:
		void	NotifyBattleScoreByConditionType(const BattleFieldConditionType conditionType, SRegionObjectBase* region);

	private:
		Int		mKillGeneralPoint;			//击破敌将数
		Int		mSupKillGeneralPoint;		//辅助击破敌将数
		Int		mGeneralHurtPoint;			//对武将的伤害总量
		Int		mKillArmyPoint;				//击破军队数
		Int		mSupKillArmyPoint;			//辅助击破军队数			//5
		Int		mArmyHurtPoint;				//对军队的伤害总量
		Int		mDestoryBuildPoint;			//击破建筑数
		Int		mSupDestoryBuildPoint;		//辅助击破建筑数
		Int		mBuildHurtPoint;			//对建筑的伤害总量
		Int		mDestoryForcePoint;			//击破重要据点数			//10
		Int		mSupDestoryForcePoint;		//辅助击破重要据点数
		Int		mForceHurtPoint;			//对重要据点的伤害总量
		Int		mHealGeneralPoint;			//治疗武将总量
		Int		mHealArmyPoint;				//治疗军队总量
		Int		mHealBuildPoint;			//修复建筑耐久总量			//15
		Int		mDeathPoint;				//死亡次数
		Int		mNormalRevivePoint;			//普通复活次数
		Int		mPotionRevivePoint;			//使用复活药复活次数
		Int		mConstructBuildPoint;		//建筑建造量
		U64		mLastKillGeneralTime;		//最后一次击破敌将的时间
		Int		mContinueKillGeneralPoint;	//连杀敌将数				//20
	};
}

#endif	//_BATTLE_STATICS_H_