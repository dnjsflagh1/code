/******************************************************************************/
#ifndef _SIMPLEPLAYERCHARACTER_H_
#define _SIMPLEPLAYERCHARACTER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CPlayerCharacter.h"
#include "MapListCsv.h"
//*************************************************************************************

namespace MG
{
    
	//玩家能选择的角色数量
    const U32 SPCHARACTER_COUNT = 8;
	/*
	 用于绑定在每个角色IMG上，做逻辑判断
	*/
	struct SimpleCharacterResInfo
	{
		U32				id;
		U32				templateid;
		Str16			name;
        GENDER_TYPE		sex;  
		U32				articonid;
		RegionIdType    maplistip;
		MapType			maplisttype;
        U32             pointresid; 
		SimpleCharacterResInfo():id(0),templateid(0),name(L""),sex(GENDER_TYPE_NULL),articonid(0),
		maplistip(0),maplisttype(MT_Null),pointresid(0)
		{
			;
		}
       
		SimpleCharacterResInfo& operator = (const SimpleCharacterResInfo& resinfo)
		{
			if (this == &resinfo)
			{
                 return *this;
			}
			id				=			resinfo.id;
			templateid		=	        resinfo.templateid;
			name			=			resinfo.name;
			sex				=			resinfo.sex;
			articonid		=		    resinfo.articonid;
            maplistip		=           resinfo.maplistip;
			pointresid		=           resinfo.pointresid;
			maplisttype     =           resinfo.maplisttype;
			return *this;

		}

	};


	/*
	用于绑定玩家登录创建角色时 绑定每个角色的初始属性值 如力量,敏捷,智力....
	*/
	struct SimplePlayerCharacterData
	{

       
		Flt mPower;                                      //力量
		Flt mAgile;                                      //敏捷
		Flt mIntellect;                                  //智力
		Flt mSpirt;                                      //精神
		Flt mPhysicalStrength;                           //体力
		Flt mEnergy;                                     //精力
		//------------------------------------------------------------------------
		SimplePlayerCharacterData()
			:mPower(0.0),mAgile(0.0),mIntellect(0.0),mSpirt(0.0),
			mPhysicalStrength(0.0),mEnergy(0.0){}
	};

   
	class SimplePlayerCharacter
     {
     public:
		 SINGLETON_INSTANCE(SimplePlayerCharacter)

	 public:
		 void                                     init( U32 tempid[]  );
		 SimplePlayerCharacterData                mPlayerCharacterData[SPCHARACTER_COUNT];
     private:
         CPlayerCharacter						  mPlayerCharacter[SPCHARACTER_COUNT];
		 
		
     };

}


#endif