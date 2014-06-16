
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
    //Player������
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

        // ����һ�����
        Bool        addPlayer( AccountIdType accountId,  I32 frontId,  I32 client_id, U64 clanId );
        // �Ƴ�һ�����
        void        removePlayer(AccountIdType accountId);
        // �õ�һ�����
        Bool        getPlayer(SPlayerPtr& player, AccountIdType accountId);

        // FrontServer�˳���ʱ�� �Ƴ��÷��������������
        void        removePlayerByFrontServer(const NetIdType frontId);
        // �Ƴ��÷��������������
        void        removeAllPlayer();

        //-----------------------------------------------------------------------------

    protected:

        SPlayerFactory*  mSPlayerFactory;

        std::map<AccountIdType,SPlayerPtr> mPlayerMap;
        RWLocker    mPlayerMapCs;

    };
}

#endif	//_S_PLAYER_MANAGER_H_