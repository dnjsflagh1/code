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
    //玩家对象
    //主要管理家族对象,目前一个玩家只有一个家族
    /******************************************************************************/
    class CPlayer : public Player
	{
	public:
		CPlayer();
		virtual	~CPlayer();
	
    public:
        ///因为登录阶段，有一个选择氏族的界面，故客户端需要保持氏族list
        ///玩家进入游戏后只能操作一个氏族，使用最多的是当前氏族。
        ///故关于氏族list只需要操作add和delete。

        //添加一个氏族。
        CClan*  addClan( ClanData* pData );

        //根据id删除氏族
        void    deleteClan( U64 clanId );

        //删除所有的氏族
        void    deleteAllClan();

        //设置active氏族
        void    setActive( U64 clanID );

        //得到一个氏族表
        std::map<U64, CClan*>* getClanList(){return &mClanList;}

        //test
        void				testAttr();
        void				testHurt();
    public:

        ///还原所有玩家信息
        void				restore();
    
        ///得到一个活动的家族
        CClan*				getActiveClan();
		void				ClearAllData();	//清掉内存

		void				setSelectId(IdType id)		{mSelectId = id;}
		IdType				getSelectId()				{return mSelectId;}

		void				setInstanceUid(InstanceUIdType instanceId)	
							{ 
								mInstanceUid = instanceId; 
								//MG_LOG(out_error,"-------------------副本%d--------------------\n",mInstanceUid);
							}
		InstanceUIdType		getInstanceUid() const						{ return mInstanceUid; }

		CPlayerCharacter*	getPlayerCharacter(PlayerCharacterIdType playerCharacterId);
    protected:

        ///还原一个活动的家族
        void    restoreActiveClan();

	private:
        std::map<U64, CClan*>			mClanList;
		CClan*							mClan;
		IdType							mSelectId;
		InstanceUIdType					mInstanceUid;


	};
}
#endif