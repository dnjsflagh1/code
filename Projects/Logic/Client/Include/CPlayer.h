/******************************************************************************/
#ifndef _CPLAYER_H_
#define _CPLAYER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "Singleton.h"
#include "Player.h"
#include "CClan.h"
//#include "CCampaignSystemInRegion.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //��Ҷ���
    //��Ҫ����������,Ŀǰһ�����ֻ��һ������
    /******************************************************************************/
    class CPlayer : public Player
	{
	public:
		CPlayer();
		virtual	~CPlayer();
		SINGLETON_INSTANCE(CPlayer);
	
    public:
        ///��Ϊ��¼�׶Σ���һ��ѡ������Ľ��棬�ʿͻ�����Ҫ��������list
        ///��ҽ�����Ϸ��ֻ�ܲ���һ�����壬ʹ�������ǵ�ǰ���塣
        ///�ʹ�������listֻ��Ҫ����add��delete��

        //���һ�����塣
        CClan*  addClan( ClanData* pData );

        //����idɾ������
        void    deleteClan( U64 clanId );

        //ɾ�����е�����
        void    deleteAllClan();

        //����active����
        void    setActive( U64 clanID );

        //�õ�һ�������
        std::map<U64, CClan*>* getClanList(){return &mClanList;}

        //test
        void    testAttr();
        void    testHurt();
    public:

        ///��ԭ���������Ϣ
        void    restore();
    
        ///�õ�һ����ļ���
        CClan*  getActiveClan();

		ClanIdType	getActiveClanId() const;

		//CCampaignSystemInRegion*	getCampaignSystemInRegion();
		//void						setCampaignSystemInRegion(CampaignSystemInRegion* campaignSystem);
		//void						setCampaignSystemInResionByCampaignId(CPlaceObject* placeObj, const U64 campaignId);
		//void						setCampaignSystemInResionByCampaignId(const U64 regionId, const U64 campaignId);

		void			setMyCampaignByCampaignId(CampaignIdType campaignId);
		void			setMyCampaign(SCampaign* myCampaign);
		SCampaign*		getMyCampaign();
		CampaignIdType	getMyCampaignId();

		Bool			campaignCreatorIsMe();



		void	ClearAllData();	//����ڴ�


		//void		setMyForce(FORCE force)		{ mCampaignSystem->setMyForce(force);	}
		//FORCE		getMyForce()				{ return mCampaignSystem->getMyForce();	}

		void		setSelectId(IdType id)		{mSelectId = id;}
		IdType		getSelectId()				{return mSelectId;}

		void				setInstanceUid(InstanceUIdType instanceId)	{ mInstanceUid = instanceId; }
		InstanceUIdType		getInstanceUid() const						{ return mInstanceUid; }

		void				setForce(const FORCE force);
		FORCE				getForce() const;

		CPlayerCharacter*	getPlayerCharacter(PlayerCharacterIdType playerCharacterId);

		CPlayerCharacter*		getMainGenreal();
		PlayerCharacterIdType	getMainPlayerCharacterId();
    protected:

        ///��ԭһ����ļ���
        void    restoreActiveClan();

	private:
        std::map<U64, CClan*> mClanList;

		CClan* mClan;

		//CCampaignSystemInRegion*		mCampaignSystem;
		SCampaign*						mCampaign;

		IdType							mSelectId;

		InstanceUIdType					mInstanceUid;

		FORCE							mForce;

	public:
		//CCampaignSystemInRegion*		getCampaignSystem() { return mCampaignSystem; }

	};
}
#endif