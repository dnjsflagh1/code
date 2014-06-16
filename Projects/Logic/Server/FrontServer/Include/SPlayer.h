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
	//�ͻ��˵�����Ҷ���
    //��Ҫ����������,Ŀǰһ�����ֻ��һ������
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

        //��ӡ��Ϣ
        void                            print();


        //-----------------------------------------------------------------------------------
        // Net Info
        //-----------------------------------------------------------------------------------

		// ����ID
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

        // ������
        Bool							getMainClan( SClanPtr& clan );
        void							setFirstMainClan();
        void							setMainClan(ClanIdType clanId);

		//-----------------------------------------------------------------------------------
		// Campaign
		//-----------------------------------------------------------------------------------

		// ս��ID
		void				            setCampaignId(const CampaignIdType campaignId);
		CampaignIdType		            getCampaignId() const;

		//-----------------------------------------------------------------------------------
		// Pve
		//-----------------------------------------------------------------------------------

		// PVE ����ID
		void                            setPveRoomId(Int pveRoomId);
		Int                             getPveRoomId() const;
		//-----------------------------------------------------------------------------------
		// Region
		//-----------------------------------------------------------------------------------

		// ����
		void				            setCurrentRegion(REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid);
		REGION_OBJ_TYPE		            getCurrentRegionType()	const;
		RegionIdType		            getCurrentRegionId()	const;
		InstanceUIdType		            getCurrentInstanceUid() const;

	private:
		// ս��ID
		CampaignIdType						mCampaignId;
		// PVE ����ID
		Int									mPveRoomId;

		// ��ǰ���ڵ�ͼ��Ϣ   ���佫������ͼ
		REGION_OBJ_TYPE 					mCurrentRegionType;
		RegionIdType						mCurrentRegionId;
		InstanceUIdType						mCurrentInstanceUid;

		// ��·ID
		NetIdType							mClientNetId;

        // ��ǰ���ڵ�ͼ��Ϣ   ���佫������ͼ
        NetIdType							mCurrentMapServerNetId;		//��ǰ���ڵ�ͼ��MapServer ����id

        //���� 
        SClanFactory                        mSClanFactory;
        std::map<ClanIdType,SClanPtr>       mClanMap;
        RWLocker                            mClanMapCs;
        ClanIdType                          mMainClanID;

		//����ID������������
		IDBuilderManager					mClanIDBuilderManager;
	};



    /******************************************************************************/
    //SPlayer����ָ��
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


	