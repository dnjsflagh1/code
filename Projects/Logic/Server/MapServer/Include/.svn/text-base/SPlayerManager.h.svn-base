
/******************************************************************************/
#ifndef _S_PLAYER_MANAGER_H_
#define _S_PLAYER_MANAGER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "SPlayerObjectFactory.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //Player管理者
    /******************************************************************************/
    class SPlayerManager
    {
    public:
        SPlayerManager();
        ~SPlayerManager();
        SINGLETON_INSTANCE(SPlayerManager);

        //-----------------------------------------------------------------------------

        Bool        initialize(ServerLauncherInterface* launcher);
        Bool        unInitialize();
        void        update(Flt delta);
        
        //-----------------------------------------------------------------------------

        // 增加一个玩家
        Bool        addPlayer( AccountIdType accountId,  I32 frontId,  I32 client_id, U64 clanId );
        // 移除一个玩家
        void        removePlayer(AccountIdType accountId);
        // 得到一个玩家
        Bool        getPlayer(SPlayerPtr& player, AccountIdType accountId);

        // FrontServer退出的时候 移除该服务器的所有玩家
        void        removePlayerByFrontServer(const NetIdType frontId);
        // 移除该服务器的所有玩家
        void        removeAllPlayer();

        //-----------------------------------------------------------------------------

    protected:

        SPlayerFactory*  mSPlayerFactory;

        std::map<AccountIdType,SPlayerPtr> mPlayerMap;
        RWLocker    mPlayerMapCs;

    };
}

#endif	//_S_PLAYER_MANAGER_H_