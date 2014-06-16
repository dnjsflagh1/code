/******************************************************************************/
#ifndef _CCLAN_H_
#define _CCLAN_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "Singleton.h"
#include "Clan.h"
#include "CPlayerCharacter.h"
#include "GeneralRecruitNetPacket.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //家族对象
    //主要管理家族下的角色
    /******************************************************************************/
    class CClan : public Clan
    {
    public:
        CClan();
        virtual	~CClan();

    public:

        void                    init(ClanData* pData);

        void                    setOtherInfo();
        CCharacter*             getCharacter(IdType id, GAMEOBJ_TYPE type);
        
    public:

        //增加一个玩家角色
        CPlayerCharacter*		addPlayerCharacter( PlayerCharacterData* pData, Bool& isFirst );
		//判断是否存在一个玩家角色
		Bool					hasPlayerCharacter( U64 id );
        //得到一个玩家角色
        CPlayerCharacter*		getPlayerCharacter( U64 id );
        //移除一个玩家角色
        void					removePlayerCharacter( U64 id );
        //移除所有玩家角色
        void					removeAllPlayerCharacter();
        //获的角色的数量
        U32                     getPlayerCharacterNum(){return mPlayerCharacterList.size();}
        ////根据Index获得角色
        //CPlayerCharacter*       getPlayerCharacterByIndex(U32 index);
		
		CPlayerCharacter*		getMainGenreal();
		void					setMainPlayerCharacter(CPlayerCharacter* playerCharacter);
		std::map<U64, CPlayerCharacter*>*	getPlayerCharacterList()  { return &mPlayerCharacterList; }		

#if 0
	public:	//招募的武将
		void								clearRecruitGeneralList();
		void								loadRecruitGeneralInfo(NetRecuitGeneralInfo* generalInfo);
        std::map<U64, CPlayerCharacter*>*	getRecruitGeneralList();
#endif
    private:

        //玩家角色列表
        std::map<U64, CPlayerCharacter*>	mPlayerCharacterList;

		CPlayerCharacter*					mMainPlayerCharacter;
#if 0
		//已招募的武将列表
		std::map<U64, CPlayerCharacter*>	mRecruitGeneralList;
#endif

    };
}
#endif
