//*****************************************************************************************************
#ifndef _CHARACTERENTITYDATA_H_
#define _CHARACTERENTITYDATA_H_
//*****************************************************************************************************
#include "SceneObjectData.h"
//*****************************************************************************************************
namespace MG
{
	//*****************************************************************************************************
	//ArmyData
	struct CharacterEntityData : public SceneObjectData
	{ 	
		Bool    isDied				;			//是否死亡
		Bool	isFightState		;			//是否在战斗状态

		Int     hp					;			//当前血
		Int     mp					;			//当前魔
		Int     sp					;			//当前体力
		Int     hpmax				;			//最大血
		Int     mpmax				;			//最大魔
		Int     spmax				;			//最大体力
		U32		mCharacterTemplateID;			// 角色模板ID
		U32		mLineageNum			;			// 角色转生次数
		U32		mLevel              ;			// 角色当前等级
		Vec3	mBirthPos			;			// 出生点位置
		Vec3	mPos                ;			// 自己的位置  【当前位置】
		Vec3	mDir                ;			// 自己的朝向
		UInt    charArtIcon         ;            //头像ID
		Str16   surName             ;           //角色的姓
		//------------------------------------------------------------------------
		CharacterEntityData()
			:isDied(false)				
			,isFightState(false)		
			,hp(0)				
			,mp(0)					
			,sp(0)					
			,hpmax(0)				
			,mpmax(0)				
			,spmax(0)				
			,mCharacterTemplateID(0)
			,mLevel(1)    
			,mLineageNum(0)
			,charArtIcon(30015)
			,surName(L"")
		{

		}
		//------------------------------------------------------------------------
		CharacterEntityData& operator=(const CharacterEntityData& A)
		{
			if (this == &A)
			{
				return *this;
			}

			SceneObjectData::operator =(A);

			isDied					=		A.isDied				;
			isFightState			=		A.isFightState			;
											
			hp						=		A.hp					;
			mp						=		A.mp					;
			sp						=		A.sp					;
			hpmax					=		A.hpmax					;
			mpmax					=		A.mpmax					;
			spmax					=		A.spmax					;
			mCharacterTemplateID	=		A.mCharacterTemplateID	;
			mLevel					=		A.mLevel				;
			mBirthPos				=		A.mBirthPos				;
			mPos					=		A.mPos					;
			mDir					=		A.mDir					;
			mLineageNum				=		A.mLineageNum			;
            charArtIcon             =       A.charArtIcon           ;
			surName                 =       A.surName               ;
			return *this;
		}  

	};
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************