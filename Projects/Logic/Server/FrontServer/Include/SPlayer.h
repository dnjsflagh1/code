/******************************************************************************/
#ifndef _SPLAYER_H_
#define _SPLAYER_H_
/******************************************************************************/
#include "FrontServerPreqs.h"
#include "Player.h"

#include "HeartBeatObject.h"
#include "SClan.h"
#include "SGameObjectFactory.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//客户端登入玩家对象
    //主要管理家族对象,目前一个玩家只有一个家族
	/******************************************************************************/
	class SPlayer : public Player, public HeartBeatObject
	{
	public:

		SPlayer();
		virtual ~SPlayer();
	
	public:

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool                    initialize( AccountIdType accountId, I32 client_id, Str16& accName );
        virtual Bool                    unInitialize();

        virtual Bool                    update(Flt delta);

        virtual void                    clear();

        //-----------------------------------------------------------------------------------
        // Debug
        //-----------------------------------------------------------------------------------

        //打印信息
        void                            print();


        //-----------------------------------------------------------------------------------
        // Net Info
        //-----------------------------------------------------------------------------------

		// 网络ID
		NetIdType			            getClientNetID()	const;
		NetIdType			            getMapServerNetID()	const;
		void				            setMapServerNetID(NetIdType mapServerNetID);
		Bool							isCheckDisconnect();
        

        //-----------------------------------------------------------------------------------
        // Clan
        //-----------------------------------------------------------------------------------

        Bool                            addClan( SClanPtr& clan, ClanData& clanData );
        void                            removeClan(ClanIdType clanId);
        Bool                            getClan(SClanPtr& clan, ClanIdType clanId);
        Bool                            hasClan(ClanIdType clanId);
        Bool                            hasClan();
        void                            removeAllClan();

        // 主家族
        Bool							getMainClan( SClanPtr& clan );
        void							setFirstMainClan();
        void							setMainClan(ClanIdType clanId);

		//-----------------------------------------------------------------------------------
		// Campaign
		//-----------------------------------------------------------------------------------

		// 战场ID
		void				            setCampaignId(const CampaignIdType campaignId);
		CampaignIdType		            getCampaignId() const;

		//-----------------------------------------------------------------------------------
		// Pve
		//-----------------------------------------------------------------------------------

		// PVE 房间ID
		void                            setPveRoomId(Int pveRoomId);
		Int                             getPveRoomId() const;
		//-----------------------------------------------------------------------------------
		// Region
		//-----------------------------------------------------------------------------------

		// 区域
		void				            setCurrentRegion(REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid);
		REGION_OBJ_TYPE		            getCurrentRegionType()	const;
		RegionIdType		            getCurrentRegionId()	const;
		InstanceUIdType		            getCurrentInstanceUid() const;

	private:
		// 战场ID
		CampaignIdType						mCampaignId;
		// PVE 房间ID
		Int									mPveRoomId;

		// 当前所在地图信息   主武将所在题图
		REGION_OBJ_TYPE 					mCurrentRegionType;
		RegionIdType						mCurrentRegionId;
		InstanceUIdType						mCurrentInstanceUid;

		// 网路ID
		NetIdType							mClientNetId;

        // 当前所在地图信息   主武将所在题图
        NetIdType							mCurrentMapServerNetId;		//当前所在地图的MapServer 网络id

        //家族 
        SClanFactory                        mSClanFactory;
        std::map<ClanIdType,SClanPtr>       mClanMap;
        RWLocker                            mClanMapCs;
        ClanIdType                          mMainClanID;

		//氏族ID生产管理器。
		IDBuilderManager					mClanIDBuilderManager;
	};



    /******************************************************************************/
    //SPlayer智能指针
    /******************************************************************************/

    class SPlayerPtr : public SharedPtr<SPlayer> 
    {
        friend class SPlayerFactory;

    protected:

        SPlayerFactory* mFactory;

    public:

        virtual ~SPlayerPtr() { release(); }
        SPlayerPtr() : SharedPtr<SPlayer>(),mFactory(NULL){}
        explicit SPlayerPtr(SPlayer* rep) : SharedPtr<SPlayer>(rep),mFactory(NULL){}
        SPlayerPtr(const SPlayerPtr& r) : SharedPtr<SPlayer>(r),mFactory(r.mFactory) {} 

        SPlayerPtr& operator=(const SPlayerPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;

            SPlayerPtr tmp(r);
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

#endif


	