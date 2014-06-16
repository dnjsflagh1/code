//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SBuilding.h
//        Author: yuanlinhu
//          Date: 2012-3-13
//          Time: 15:35
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-13      add
//////////////////////////////////////////////////////////////



/******************************************************************************/
#ifndef _S_BATTLE_BUILDING_NEW_H_
#define _S_BATTLE_BUILDING_NEW_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "SCharacter.h"
#include "BuildingData.h"
#include "SPlayerIdentifyInfo.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//建筑对象类
	/******************************************************************************/
	class SBuilding : public SCharacter
	{
	public:
		SBuilding(GameObjectIndexIdInSceneType indexId);
		virtual ~SBuilding();

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

		virtual Bool                            initialize(){ return true; }
        virtual Bool                            unInitialize(){ return true; }
        virtual void                            clear(){}

        virtual	void							update(Flt delta){}


        //-----------------------------------------------------------------------------------
        // Base Info
        //-----------------------------------------------------------------------------------


		BuildingData*			getBuildingData();
		void					init();
		CHAR_BUILD_TYPE			getBuildingType();


        //-----------------------------------------------------------------------------------
        // Player
        //-----------------------------------------------------------------------------------

		SPlayerIdentifyInfo*	getParentPlayerIdentifyInfo();

        //-----------------------------------------------------------------------------------
        // Attr
        //-----------------------------------------------------------------------------------

		virtual void			calAttrOther();


	private:

		SPlayerIdentifyInfo			mPlayerIndentifyInfo;
	};


	/******************************************************************************/
	//SBuilding智能指针
	/******************************************************************************/

	class SBuildingPtr : public SharedPtr<SBuilding> 
	{
		friend class SBuildingFactory;

	protected:

		SBuildingFactory* mFactory;

	public:

		virtual ~SBuildingPtr() { release(); }
		SBuildingPtr() : SharedPtr<SBuilding>(),mFactory(NULL){}
		explicit SBuildingPtr(SBuilding* rep) : SharedPtr<SBuilding>(rep),mFactory(NULL){}
		SBuildingPtr(const SBuildingPtr& r) : SharedPtr<SBuilding>(r),mFactory(r.mFactory) {} 

		SBuildingPtr& operator=(const SBuildingPtr& r) 
		{
			if (pRep == r.pRep)
				return *this;

			SBuildingPtr tmp(r);
			if ( isNull() == false )
			{
				tmp.mFactory = mFactory;
			}

			swap(tmp);

			mFactory = r.mFactory;

			return *this;
		}

	protected:

		virtual void    destroy(void){}

	};
}

#endif	//_S_BATTLE_BUILDING_NEW_H_