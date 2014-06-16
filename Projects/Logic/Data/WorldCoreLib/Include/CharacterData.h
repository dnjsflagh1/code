//*****************************************************************************************************
#ifndef _H_CHARACTER_DATA_
#define _H_CHARACTER_DATA_
//*****************************************************************************************************
#include "GameObjectData.h"

//*****************************************************************************************************
namespace MG
{
    //*****************************************************************************************************
    //CharacterData  注：（模板属性和战斗属性在类中包含）
    struct CharacterData : public GameObjectData
    {
        U32					mCharacterTemplateID;			// 角色模板ID
        U32					mLevel              ;			// 角色当前等级
		Vec3				mBirthPos			;			// 出生点位置
        Vec3				mPos                ;			// 自己的位置  【当前位置】
        Vec3				mDir                ;			// 自己的朝向
		U32					mHp					;			// 当前血值
		U32					mMp					;			// 当前魔值
		U32					mSp					;			// 当前体力值
		U32					mLineageNum			;			// 当前转生次数。
		//此字段作废，下次重构代码时去掉。
        REGION_OBJ_TYPE		mRegionType         ;			// 所在地域类型
        RegionIdType		mRegionID           ;			// 所在地域编号
		InstanceUIdType		mInstanceUId		;			// 所在地域副本ID
		
        
        //------------------------------------------------------------------------  
        CharacterData()
            :mCharacterTemplateID(0)
            ,mLevel(1)
			,mBirthPos(0,0,0)
			,mPos(0,0,0)
			,mDir(0,0,0)
			,mRegionType(ROT_UNKNOWN)
			,mRegionID(0)
			,mInstanceUId(0)
			,mHp(0)
			,mMp(0)
			,mSp(0)
			,mLineageNum(0)
        {

        }
        //------------------------------------------------------------------------
        CharacterData& operator=(const CharacterData& A)
        {
			if (this == &A)
			{
				return *this;
			}

            GameObjectData::operator =(A);

            mCharacterTemplateID     =   A.mCharacterTemplateID     ;
            mLevel                   =   A.mLevel                   ;
			mBirthPos				 =	 A.mBirthPos				;
            mPos                     =   A.mPos                     ;
            mDir                     =   A.mDir                     ;
            mRegionID                =   A.mRegionID                ;
            mRegionType              =   A.mRegionType              ;
			mInstanceUId			 =	 A.mInstanceUId				;
			mHp						 =	 A.mHp						;
			mMp						 =	 A.mMp						;
			mSp						 =	 A.mSp						;
			mLineageNum				 =	 A.mLineageNum				;

            return *this;
        }

		//-----------------------------------------------------------------------
		virtual void print()
		{
			GameObjectData::print();
			MG_LOG(out_sys, "【CharacterData】mRegionID[%i], mInstanceUId[%d]\n ", mRegionID,  mInstanceUId);
		}
    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************