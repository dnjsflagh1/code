//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SPlayerCharacterNew.h
//        Author: yuanlinhu
//          Date: 2012-3-13
//          Time: 15:02
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-13      add
//////////////////////////////////////////////////////////////


//*************************************************************************************************

#ifndef _S_PLAYER_CHARACTER_NEW_H_
#define _S_PLAYER_CHARACTER_NEW_H_

//*************************************************************************************************

#include "MapServerPreqs.h"
#include "SPlayer.h"
#include "SCharacter.h"
#include "EquipItem.h"
#include "SPlayerIdentifyInfo.h"

//*************************************************************************************************
namespace MG
{
    /******************************************************************************/
    //SPlayerCharacter
    /******************************************************************************/

	class SPlayerCharacter : public SCharacter
	{
	public:
		SPlayerCharacter();
		~SPlayerCharacter();


        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool            initialize( PlayerCharacterIdType playerCharacterId, PlayerCharacterData& pData );
        virtual Bool            unInitialize();
        virtual void            clear();
		void					update(Flt delta);

        //-----------------------------------------------------------------------------------
        // Debug
        //-----------------------------------------------------------------------------------

		virtual void			print();

        //-----------------------------------------------------------------------------------
        // Base Data
        //-----------------------------------------------------------------------------------

		// 由子类的 SPlayerIdentifyInfo 实现
		virtual AccountIdType	getAccountId(){ return 0; }
		virtual NetIdType 		getFrontServerId(){ return 0; }
		virtual NetIdType 		getClientNetIdInFrontServer(){ return 0; }
		virtual ClanIdType		getClanId(){ return 0; }

		PlayerCharacterData*    getPlayerCharacterData();

        void                    setPlayer( SPlayerPtr& ptr );
        void                    getPlayer( SPlayerPtr& ptr );
		SPlayerIdentifyInfo*    getPlayerIdentifyInfo();

        //-----------------------------------------------------------------------------------
        // Equip
        //-----------------------------------------------------------------------------------

        EquipItem*              getEquipItem(){return &mEquipItem;}

        //-----------------------------------------------------------------------------------
        // Alive
        //-----------------------------------------------------------------------------------

		virtual void            dead(SCharacter* murderer);
		virtual void			setAlive(AliveType aliveType);		//复活操作

        //-----------------------------------------------------------------------------------
        // Attr
        //-----------------------------------------------------------------------------------

		virtual UInt            getLineageNum();
		virtual Flt             getDBAttrInit(UInt index);
		virtual Flt             getDBAttrLvlAdd(UInt index);
		virtual UInt			getDBAttrInitID();
		virtual UInt			getDBAttrLvlAddID();
		virtual void			calAttrOther();

        //-----------------------------------------------------------------------------------
        // Battle
        //-----------------------------------------------------------------------------------

		Bool					getIsBattleLeader() const;
		void					setIsBattleLeader(Bool isBattleLeader);

        //-----------------------------------------------------------------------------------
        // Move
        //-----------------------------------------------------------------------------------

		virtual void			moveToPos( Vec3 startMovePos, Vec3 MoveToPos, Bool isBlockCheck );
		virtual void			stopMove();

    private:

        SPlayerPtr								mSPlayerPtr;
		SPlayerIdentifyInfo						mSPlayerIdentifyInfo;
        PlayerCharacterData						mPlayerCharacterData;
        EquipItem   							mEquipItem;
		Bool        							mIsBattleLeader;

	};



    /******************************************************************************/
    //SPlayerCharacter智能指针
    /******************************************************************************/

    class SPlayerCharacterPtr : public SharedPtr<SPlayerCharacter> 
    {
        friend class SPlayerCharacterFactory;

    protected:

        SPlayerCharacterFactory* mFactory;

    public:

        virtual ~SPlayerCharacterPtr() { release(); }
        SPlayerCharacterPtr() : SharedPtr<SPlayerCharacter>(),mFactory(NULL){}
        explicit SPlayerCharacterPtr(SPlayerCharacter* rep) : SharedPtr<SPlayerCharacter>(rep),mFactory(NULL){}
        SPlayerCharacterPtr(const SPlayerCharacterPtr& r) : SharedPtr<SPlayerCharacter>(r),mFactory(r.mFactory) {} 

        SPlayerCharacterPtr& operator=(const SPlayerCharacterPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;

            SPlayerCharacterPtr tmp(r);
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