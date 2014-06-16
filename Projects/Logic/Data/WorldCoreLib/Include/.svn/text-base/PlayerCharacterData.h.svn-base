//*****************************************************************************************************
#ifndef _H_PLAYER_CHARACTER_DATA_
#define _H_PLAYER_CHARACTER_DATA_
//*****************************************************************************************************
#include "CharacterData.h"
//*****************************************************************************************************
namespace MG
{


    //*****************************************************************************************************
    //PlayerCharacterData
    struct PlayerCharacterData : public CharacterData
    {
		PlayerIdType		charAccountId;					//玩家账号id
        ClanIdType          charClanId;                     //角色所属氏族ID
        U32                 charCurAge;                     //角色当前年龄
        U32                 charLifeSpan;                   //角色基础寿命
        U32                 charAddLifeSpan;                //角色增加的寿命
        U32                 charExp1;                       //角色当前经验
        U32                 charExp2;                       //角色当前名望
        U32                 charExp3;                       //角色当前功绩 
        U32					charArtMashID1;                 //角色的基础人模
        U32					charArtMashID2;                 //角色的服装模型
        U32                 charArtIcon;                    //角色的2d头像
        U32                 charInfluenceID;                //角色归属的势力
        U32                 charSkillPointAll;              //角色通过升级总共获得的技能点历史总计
        U32                 charNoAssignSkillPoint;         //角色当前的未分配的技能点数
        CHAR_STATE          charState;                      //角色当前的状态
        CHAR_LIFE_STATE     charLifeState;                  //角色的生存状态
        Flt                 charAttrRand[DB_RECORD_ATTR_NUM];   //角色的随机天赋属性
        Flt                 charAttrRandAdd[DB_RECORD_ATTR_NUM];//角色的随机天赋属性等级附加
		U32					charAttrAppendId;				//属性附加ID
		U32					charAttrAppendLvlAddId;			//属性等级附加ID
        Str16               charSurName;                      //角色姓
        //------------------------------------------------------------------------
        PlayerCharacterData()
            :charClanId(0),
			charAccountId(0),
            charCurAge(0),        
            charLifeSpan(0),      
            charAddLifeSpan(0),          
            charExp1(0), 
            charExp2(0),
            charExp3(0),
            charSkillPointAll(0),
            charNoAssignSkillPoint(0),
			charArtMashID1(0),
			charArtMashID2(0),       
            charArtIcon(0),         
            charInfluenceID(0),
			charAttrAppendId(0),
			charAttrAppendLvlAddId(0),
            charState(CHAR_STATE_Null),         
            charLifeState(CHAR_LIFE_STATE_Null)                   
        {           
            for (Int i=0; i<DB_RECORD_ATTR_NUM; i++)
            {
                charAttrRand[i] =  0.f;
                charAttrRandAdd[i] = 0.f;
            }
        }
        //------------------------------------------------------------------------
        PlayerCharacterData& operator=(const PlayerCharacterData& A)
        {  
            if (this == &A)
            {
                return *this;
            }

            CharacterData::operator =(A);

			charAccountId					 = A.charAccountId;
            charSurName                      = A.charSurName;       
            //charZiName                       = A.charZiName;        
            charClanId                       = A.charClanId;        
            charCurAge                       = A.charCurAge;        
            charLifeSpan                     = A.charLifeSpan;      
            charAddLifeSpan                  = A.charAddLifeSpan;
            charExp1                         = A.charExp1; 
            charExp2                         = A.charExp2;
            charExp3                         = A.charExp3;
            charArtMashID1                   = A.charArtMashID1;    
            charArtMashID2                   = A.charArtMashID2;       
            charArtIcon                      = A.charArtIcon;         
            charInfluenceID                  = A.charInfluenceID;   
            charSkillPointAll                = A.charSkillPointAll;
            charNoAssignSkillPoint           = A.charNoAssignSkillPoint;
            charState                        = A.charState;         
            charLifeState                    = A.charLifeState;   
			charAttrAppendId				 = A.charAttrAppendId;
			charAttrAppendLvlAddId			 = A.charAttrAppendLvlAddId;

            for (Int i=0; i<DB_RECORD_ATTR_NUM; i++)
            {
                charAttrRand[i] =  A.charAttrRand[i];
                charAttrRandAdd[i] = A.charAttrRandAdd[i];
            }

            return *this;
        }

		//-----------------------------------------------------------------------
		virtual void print()
		{
			CharacterData::print();
			MG_LOG(out_sys, "【NEW_PlayerCharacterData】charClanId[%d]\n ", charClanId);
		}
    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************