
/******************************************************************************/
#ifndef _S_GAME_OBJECT_FACTORY_H_
#define _S_GAME_OBJECT_FACTORY_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "ObjectPool.h"
//#include "SPlayerCharacter.h"
//#include "SClan.h"

//class SClan;
//class SPlayerCharacter;
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    // 氏族工厂
    /******************************************************************************/
    class SClanFactory
    {

        friend class SClanPtr;

    public:

        SClanFactory();
        ~SClanFactory();

    public:

        void    createSClanPtr( SClanPtr& ptr, ClanIdType clanId, AccountIdType accountId, ClanData& clanData );

    protected:  

        void    destroySClanPtr( SClanPtr& ptr );

    private:    

        ObjectPool<SClan,false> mSClanPtrPool;
        Critical    mSClanPtrPoolCs;
    };




    /******************************************************************************/
    // 角色工厂
    /******************************************************************************/
    class SPlayerCharacterFactory
    {
        friend class SPlayerCharacterPtr;
    public:
        SPlayerCharacterFactory();
        ~SPlayerCharacterFactory();

    public:

        void    createSPlayerCharacterPtr( SPlayerCharacterPtr& ptr, PlayerCharacterData& clarData );

    protected:  

        void    destroySPlayerCharacterPtr( SPlayerCharacterPtr& ptr );

    private:    

        ObjectPool<SPlayerCharacter,false> mSPlayerCharacterPool;
        Critical    mSPlayerCharacterPoolCs;
    };



}

#endif	//_S_GAME_OBJECT_FACTORY_H_