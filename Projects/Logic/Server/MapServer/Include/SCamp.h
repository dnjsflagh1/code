//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SCamp.h
//        Author: yuanlinhu
//          Date: 2012-4-25
//          Time: 11:53
//   Description: 
//			军营
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-25      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _S_CAMP_H_
#define _S_CAMP_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "DataSetManager.h"
#include "SBuilding.h"
#include "BattleConfig.h"

/******************************************************************************/
namespace MG
{
	
	class SCamp : public SBuilding
	{
	public:
		SCamp();
		~SCamp();


        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool                    initialize( PlayerCharacterIdType playerCharacterId, PlayerCharacterData& pData ){return 0;}
        virtual Bool                    unInitialize(){return 0;}
        virtual void                    clear(){}
        void					        update(Flt delta);


        //-----------------------------------------------------------------------------------
        // Alive
        //-----------------------------------------------------------------------------------

		virtual void                    dead(SCharacter* murderer);

        //-----------------------------------------------------------------------------------
        // Army
        //-----------------------------------------------------------------------------------

		void				            createActiveArmy();


		Bool				            isAllArmyDead();
		
		void				            setControlTroopGroupAccountId(const AccountIdType targetAccountId);
		AccountIdType		            getControlTroopGroupAccountId() const;

		SArmy*				            getCurControlArmy();
		void				            setCurControlArmy(SArmy* curArmy);

		STroopGroup*                    getCurControlTroopGroup();


		SArmy*				            getAliveArmy();

		STroopGroup*		            getTroopGroupById(TroopIdType troopId);

        //-----------------------------------------------------------------------------------
        // Camp
        //-----------------------------------------------------------------------------------

		CampIdType			            getCampId();

		CampaignIdType		            getCamaignId() const;
		void				            setCamaignId(const CampaignIdType campaignId);


        //-----------------------------------------------------------------------------------
        // World Op
        //-----------------------------------------------------------------------------------

		Vec3		                    getPos();
		void		                    setPos(Vec3& pos);
		Vec3		                    getDir();
		void		                    setDir(Vec3& dir);
		Int			                    getArmyNum() const;
		U32			                    getCampTemplateId();

		Bool		                    isDestroyed() const;

		void		                    setIsQuarter(const Bool isQuarter);
		Bool		                    getIsQuarter() const;

        Vec3		                    getTroopBornPos(Int index);
        void		                    setTroopBornPos(Int index, Vec3& pos);
        Vec3		                    getTroopBornDir(Int index);
        void		                    setTroopBornDir(Int index, Vec3& dir);

        //-----------------------------------------------------------------------------------
        // Troop Group
        //-----------------------------------------------------------------------------------

		//把Army创建的Troop信息 保存到Camp中的List
		void		                    addTroopGroupToList(STroopGroup* newTroop);

		void		                    addControlTroopGroup(STroopGroup* troopGroup);
		void		                    delControlTroopGroup(STroopGroup* troopGroup);


		Int			                    getAllTroopNumInCamp() const { return mAllTroopNumInCamp; }

		SPlayerIdentifyInfo*	    getSPlayerIdentifyInfo();

	private:

		//SimpleMapDataSetManager<CampIdType, SArmy>			mArmyList;

		//MapManager<TroopGroupIdType, STroopGroup*>		    mAllTroopGroupList;		//管理所有的军队
		
		//std::map<TroopGroupIdType, STroopGroup*>			mControlTroopGroupList;//当前在战场外部创建的军队， 并能控制它

		AccountIdType	mControlTroopGroupAccountId;		//控制军队的玩家

		Int				mArmyNum;							//有几个军队
		
		CampaignIdType  mCampaignId;						//所属的战斗ID

		SArmy*			mCurControlArmy;					//当前控制的Army

		Bool			mIsDestroyed;						//被玩家摧毁了
		Bool			mIsHeadQuarter;						//是否是大本营

		Vec3			mTroopBornPos[TROOP_GROUP_NUM];		//创建军队的点
		Vec3			mTroopBornDir[TROOP_GROUP_NUM];		//创建军队的方向

		Int				mAllTroopNumInCamp;					//所有军队的数量

		SPlayerIdentifyInfo	mSPlayerIdentifyInfo;

	};


	/******************************************************************************/
	//SCamp智能指针
	/******************************************************************************/

	class SCampPtr : public SharedPtr<SCamp> 
	{
		friend class SCampFactory;

	protected:

		SCampFactory* mFactory;

	public:

		virtual ~SCampPtr() { release(); }
		SCampPtr() : SharedPtr<SCamp>(),mFactory(NULL){}
		explicit SCampPtr(SCamp* rep) : SharedPtr<SCamp>(rep),mFactory(NULL){}
		SCampPtr(const SCampPtr& r) : SharedPtr<SCamp>(r),mFactory(r.mFactory) {} 

		SCampPtr& operator=(const SCampPtr& r) 
		{
			if (pRep == r.pRep)
				return *this;

			SCampPtr tmp(r);
			if ( isNull() == false )
			{
				tmp.mFactory = mFactory;
			}

			swap(tmp);

			mFactory = r.mFactory;

			return *this;
		}

	protected:

		virtual void    destroy(void);

	};
}

#endif	//_S_CAMP_H_
