//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SThirdPartyCharacter.h
//        Author: yuanlinhu
//          Date: 2012-4-23
//          Time: 14:16
//   Description: 
//			第三方角色
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-23      add
//////////////////////////////////////////////////////////////

/******************************************************************************/

#ifndef _S_THIRD_PART_CHARACTER_H_
#define _S_THIRD_PART_CHARACTER_H_

/******************************************************************************/

#include "MapServerPreqs.h"
#include "SCharacter.h"

/******************************************************************************/
namespace MG
{
	class SThirdPartCharacter : public SCharacter
	{
	public:
		SThirdPartCharacter(SThirdPartCharacter& rhs);
		SThirdPartCharacter(GameObjectIndexIdInSceneType indexId);
		~SThirdPartCharacter();


        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------


		virtual Bool            initialize( PlayerCharacterIdType playerCharacterId, PlayerCharacterData& pData ){ return true;}
		virtual Bool            unInitialize(){ return true;}
		virtual void            clear(){}
		void					update(Flt delta){}


	};


	/******************************************************************************/
	//SThirdPartCharacter智能指针
	/******************************************************************************/

	class SThirdPartCharacterPtr : public SharedPtr<SThirdPartCharacter> 
	{
		friend class SThirdPartCharacterFactory;

	protected:

		SThirdPartCharacterFactory* mFactory;

	public:

		virtual ~SThirdPartCharacterPtr() { release(); }
		SThirdPartCharacterPtr() : SharedPtr<SThirdPartCharacter>(),mFactory(NULL){}
		explicit SThirdPartCharacterPtr(SThirdPartCharacter* rep) : SharedPtr<SThirdPartCharacter>(rep),mFactory(NULL){}
		SThirdPartCharacterPtr(const SThirdPartCharacterPtr& r) : SharedPtr<SThirdPartCharacter>(r),mFactory(r.mFactory) {} 

		SThirdPartCharacterPtr& operator=(const SThirdPartCharacterPtr& r) 
		{
			if (pRep == r.pRep)
				return *this;

			SThirdPartCharacterPtr tmp(r);
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

#endif	//_S_THIRD_PART_CHARACTER_H_