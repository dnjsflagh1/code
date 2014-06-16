//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: CampaignStatics.h
//        Author: yuanlinhu
//          Date: 2012-4-23
//          Time: 10:18
//   Description: 
//			ս��ͳ������ ���ڴ棩
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

		void	incrementSupKillGeneralPoint();		//�������Ƶн���
		Int		getSupKillGeneralPoint() const;

		void	incrementGeneralHurtPoint();		//���佫���˺�����
		Int		getGeneralHurtPoint() const;

		void	incrementKillArmyPoint();			//���ƾ�����
		Int		getKillArmyPoint() const;

		void	incrementSupKillArmyPoint();		//�������ƾ�����			//5
		Int		getSupKillArmyPoint() const;
		
		void	incrementArmyHurtPoint();			//�Ծ��ӵ��˺�����
		Int		getArmyHurtPoint()const;
		
		void	incrementDestoryBuildPoint();		//���ƽ�����
		Int		getDestoryBuildPoint()const;
		
		void	incrementSupDestoryBuildPoint();	//�������ƽ�����
		Int		getSupDestoryBuildPoint()const;
		
		void	incrementBuildHurtPoint();			//�Խ������˺�����
		Int		getBuildHurtPoint()const;
		
		void	incrementDestoryForcePoint();		//������Ҫ�ݵ���			//10
		Int		getDestoryForcePoint()const;
		
		void	incrementSupDestoryForcePoint();	//����������Ҫ�ݵ���
		Int		getSupDestoryForcePoint()const;
		
		void	incrementForceHurtPoint();			//����Ҫ�ݵ���˺�����
		Int		getForceHurtPoint()const;
		
		void	incrementHealGeneralPoint();		//�����佫����
		Int		getHealGeneralPoint()const;
		
		void	incrementHealArmyPoint();			//���ƾ�������
		Int		getHealArmyPoint()const;
		
		void	incrementHealBuildPoint();			//�޸������;�����			//15
		Int		getHealBuildPoint()const;
		
		void	incrementDeathPoint();				//��������
		Int		getDeathPoint()const;
		
		void	incrementNormalRevivePoint();		//��ͨ�������
		Int		getNormalRevivePoint()const;
		
		void	incrementPotionRevivePoint();		//ʹ�ø���ҩ�������
		Int		getPotionRevivePoint()const;

		Int		getConstructBuildPoint() const;

		
		void	incrementLastKillGeneralTime();		//���һ�λ��Ƶн���ʱ��
		U64		getLastKillGeneralTime()const;
		
		void	incrementContinueKillGeneralPoint();
		Int		getContinueKillGeneralPoint()const;

	private:
		void	NotifyBattleScoreByConditionType(const BattleFieldConditionType conditionType, SRegionObjectBase* region);

	private:
		Int		mKillGeneralPoint;			//���Ƶн���
		Int		mSupKillGeneralPoint;		//�������Ƶн���
		Int		mGeneralHurtPoint;			//���佫���˺�����
		Int		mKillArmyPoint;				//���ƾ�����
		Int		mSupKillArmyPoint;			//�������ƾ�����			//5
		Int		mArmyHurtPoint;				//�Ծ��ӵ��˺�����
		Int		mDestoryBuildPoint;			//���ƽ�����
		Int		mSupDestoryBuildPoint;		//�������ƽ�����
		Int		mBuildHurtPoint;			//�Խ������˺�����
		Int		mDestoryForcePoint;			//������Ҫ�ݵ���			//10
		Int		mSupDestoryForcePoint;		//����������Ҫ�ݵ���
		Int		mForceHurtPoint;			//����Ҫ�ݵ���˺�����
		Int		mHealGeneralPoint;			//�����佫����
		Int		mHealArmyPoint;				//���ƾ�������
		Int		mHealBuildPoint;			//�޸������;�����			//15
		Int		mDeathPoint;				//��������
		Int		mNormalRevivePoint;			//��ͨ�������
		Int		mPotionRevivePoint;			//ʹ�ø���ҩ�������
		Int		mConstructBuildPoint;		//����������
		U64		mLastKillGeneralTime;		//���һ�λ��Ƶн���ʱ��
		Int		mContinueKillGeneralPoint;	//��ɱ�н���				//20
	};
}

#endif	//_BATTLE_STATICS_H_