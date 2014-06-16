//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\STroopNew.h
//        Author: yuanlinhu
//          Date: 2012-4-25
//          Time: 10:10
//   Description: 
//			计算属性的最小单位
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-25      add
//////////////////////////////////////////////////////////////


/******************************************************************************/
#ifndef _S_TROOP_H_
#define _S_TROOP_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "DataSetManager.h"
#include "SCharacter.h"
#include "TroopData.h"

/******************************************************************************/

namespace MG
{


	class STroop : public SCharacter
	{
	public:
		STroop(TroopIdType soldierId, STroopGroup* ownerTroopGroup, Int soldierNum, RegionIdType regionId, InstanceUIdType instanceId, Int troopTemplateId);
		virtual ~STroop();


        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

		virtual Bool            initialize( PlayerCharacterIdType playerCharacterId, PlayerCharacterData& pData ){return 0;}
		virtual Bool            unInitialize(){ return true;}
		virtual void            clear(){}
        void					update(Flt delta);


        //-----------------------------------------------------------------------------------
        // Alive
        //-----------------------------------------------------------------------------------


        virtual void	        dead(SCharacter* murderer);

        //-----------------------------------------------------------------------------------
        // Player
        //-----------------------------------------------------------------------------------

		SPlayer*		        getParentPlayer();		//根据上层的SArmy 决定 我是由谁来控制

        //-----------------------------------------------------------------------------------
        // Army & Camp
        //-----------------------------------------------------------------------------------

		SArmy*			        getOwnerArmy();
		SCamp*			        getOwnerCamp();


        //-----------------------------------------------------------------------------------
        // Base Info
        //-----------------------------------------------------------------------------------


		U64				        getTroopTemplateId();

		TroopData*		        getTroopData();

        //-----------------------------------------------------------------------------------
        // World Op
        //-----------------------------------------------------------------------------------

		Bool			        getIsInitTroopPos() const;
		void			        setIsInitTroopPos(Bool isInit);

	private:

		STroopGroup*			mOwnerTroopGroup;

	};


	/******************************************************************************/
	//SPlayerCharacter智能指针
	/******************************************************************************/

	class STroopPtr : public SharedPtr<STroop> 
	{
		friend class STroopFactory;

	protected:

		STroopFactory* mFactory;

	public:

		virtual ~STroopPtr() { release(); }
		STroopPtr() : SharedPtr<STroop>(),mFactory(NULL){}
		explicit STroopPtr(STroop* rep) : SharedPtr<STroop>(rep),mFactory(NULL){}
		STroopPtr(const STroopPtr& r) : SharedPtr<STroop>(r),mFactory(r.mFactory) {} 

		STroopPtr& operator=(const STroopPtr& r) 
		{
			if (pRep == r.pRep)
				return *this;

			STroopPtr tmp(r);
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

#endif	//_S_TROOP_H_