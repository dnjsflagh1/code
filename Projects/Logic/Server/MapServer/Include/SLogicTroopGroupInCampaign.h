//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: STroopGroupNew.h
//        Author: yuanlinhu
//          Date: 2012-4-25
//          Time: 10:10
//   Description: 
//			军营能创建的最小单位
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-25      add
//////////////////////////////////////////////////////////////


/******************************************************************************/
#ifndef _SLOGICTROOPGROUPINCAMPAIGN_H_
#define _SLOGICTROOPGROUPINCAMPAIGN_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "DataSetManager.h"
#include "SCharacter.h"
#include "STroop.h"
#include "TroopData.h"
#include "BattleConfig.h"

/******************************************************************************/

namespace MG
{
    class SLogicTroopGroupInCampaign 
    {
    public:

        SLogicTroopGroupInCampaign();
        virtual ~SLogicTroopGroupInCampaign();

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------


        virtual Bool            initialize( PlayerCharacterIdType playerCharacterId, PlayerCharacterData& pData );
        virtual Bool            unInitialize();
        virtual void            clear();
        void					update(Flt delta);

        //-----------------------------------------------------------------------------------
        // Player
        //-----------------------------------------------------------------------------------

        SPlayer*		        getParentPlayer();		//根据上层的SArmy 决定 我是由谁来控制


        //-----------------------------------------------------------------------------------
        // Alive
        //-----------------------------------------------------------------------------------

        virtual void	        dead(SCharacter* murderer);

        //-----------------------------------------------------------------------------------
        // BaseInfo
        //-----------------------------------------------------------------------------------

        SArmy*			        getOwnerArmy();
        SCamp*			        getOwnerCamp();

        U64				        getTroopTemplateId();

        TroopData*		        getTroopData();


        //-----------------------------------------------------------------------------------
        // Soldier
        //-----------------------------------------------------------------------------------


        Int				        getSoldierNum();


        //-----------------------------------------------------------------------------------
        // World Op
        //-----------------------------------------------------------------------------------

        Bool			        getIsInitTroopPos() const;
        void			        setIsInitTroopPos(Bool isInit);

        void			        setSoldierPos(Int soldierNum, NetVec2* pos);
        void			        getSoldierPos(const Int soldierNum, NetVec2* outPos);

        Bool			        isAllTroopDead();

        void			        createActiveTroopGroup(SCharacter* murderer);

    private:


        SArmy*  mOwnerArmy;

        SimpleMapDataSetManager<TroopIdType, STroop>		mTroopList;

        Bool    mIsActiveInCampaign;		//通过此值确定是否发送军队信息到客户端


    private:

        STroopGroup();
    };

    /******************************************************************************/
    //STroopGroupNew智能指针
    /******************************************************************************/

    class SLogicTroopGroupInCampaignPtr : public SharedPtr<SLogicTroopGroupInCampaignPtr> 
    {
        friend class SLogicTroopGroupInCampaignFactory;

    protected:

        SLogicTroopGroupInCampaignFactory* mFactory;

    public:

        virtual ~SLogicTroopGroupInCampaignPtr() { release(); }
        SLogicTroopGroupInCampaignPtr() : SharedPtr<SLogicTroopGroupInCampaignPtr>(),mFactory(NULL){}
        explicit SLogicTroopGroupInCampaignPtr(SLogicTroopGroupInCampaignPtr* rep) : SharedPtr<SLogicTroopGroupInCampaignPtr>(rep),mFactory(NULL){}
        SLogicTroopGroupInCampaignPtr(const SLogicTroopGroupInCampaignPtr& r) : SharedPtr<SLogicTroopGroupInCampaignPtr>(r),mFactory(r.mFactory) {} 

        SLogicTroopGroupInCampaignPtr& operator=(const SLogicTroopGroupInCampaignPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;

            SLogicTroopGroupInCampaignPtr tmp(r);
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

#endif	//_S_TROOP_GROUP_H_