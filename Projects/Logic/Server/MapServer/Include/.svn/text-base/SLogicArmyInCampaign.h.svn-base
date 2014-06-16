//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SArmy.h
//        Author: yuanlinhu
//          Date: 2012-4-25
//          Time: 11:25
//   Description: 
//		客户端能编辑的最小单位		
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-25      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _SLOGICARMYINCAMPAIGN_H_
#define _SLOGICARMYINCAMPAIGN_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "DataSetManager.h"
#include "ArmyData.h"

/******************************************************************************/

namespace MG
{
    class SLogicArmyInCampaign
    {
    public:

        SLogicArmyInCampaign(SCamp* ownerCamp, ArmyIdType armyId, RegionIdType regionid, InstanceUIdType instanceUid, CampConfigInfo* campInfo);
        ~SLogicArmyInCampaign();


        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool                    initialize( PlayerCharacterIdType playerCharacterId, PlayerCharacterData& pData );
        virtual Bool                    unInitialize();
        virtual void                    clear();
        void					        update(Flt delta);


        //-----------------------------------------------------------------------------------
        // Alive
        //-----------------------------------------------------------------------------------

        Bool			                isDead();


        //-----------------------------------------------------------------------------------
        // Player
        //-----------------------------------------------------------------------------------

        SPlayerIdentifyInfo*  getParentPlayer();


        //-----------------------------------------------------------------------------------
        // Camp
        //-----------------------------------------------------------------------------------

        SCamp*			                getOwnerCamp();


        //-----------------------------------------------------------------------------------
        // Troop
        //-----------------------------------------------------------------------------------

        void				            createActiveTroopGroup();

        STroopGroup*		            getAliveTroopGroup();

        STroopGroup*		            getNextBornTroopGroup();

        //所有的TroopGroup都被创建了
        Bool				            isAllTroopGroupCreated();


        //-----------------------------------------------------------------------------------
        // Ctrl
        //-----------------------------------------------------------------------------------

        void				            setCurControlTroopGroup(STroopGroup* curControlTroopGroup);
        STroopGroup*		            getCurControlTroopGroup();

    private:

        SimpleMapDataSetManager<TroopGroupIdType, STroopGroup>		mTroopGroupList;

        ArmyIdType		mArmyId;
        SCamp*			mOwnerCamp;

        ArmyData		mArmyData;

        Bool			mIsDead;		//所以的士兵都死了， 说明次Army 已经死了

    };


    /******************************************************************************/
    //SArmy智能指针
    /******************************************************************************/

    class SLogicArmyInCampaignPtr : public SharedPtr<SLogicArmyInCampaign> 
    {
        friend class SLogicArmyInCampaignFactory;

    protected:

        SLogicArmyInCampaignFactory* mFactory;

    public:

        virtual ~SLogicArmyInCampaignPtr() { release(); }
        SLogicArmyInCampaignPtr() : SharedPtr<SLogicArmyInCampaign>(),mFactory(NULL){}
        explicit SLogicArmyInCampaignPtr(SLogicArmyInCampaign* rep) : SharedPtr<SLogicArmyInCampaign>(rep),mFactory(NULL){}
        SLogicArmyInCampaignPtr(const SLogicArmyInCampaignPtr& r) : SharedPtr<SLogicArmyInCampaign>(r),mFactory(r.mFactory) {} 

        SLogicArmyInCampaignPtr& operator=(const SLogicArmyInCampaignPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;

            SLogicArmyInCampaignPtr tmp(r);
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

#endif	//_S_ARMY_H_