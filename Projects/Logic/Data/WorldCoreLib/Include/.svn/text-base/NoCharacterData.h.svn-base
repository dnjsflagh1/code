//*****************************************************************************************************
#ifndef _H_NOCHARACTER_DATA_
#define _H_NOCHARACTER_DATA_
//*****************************************************************************************************
#include "GameObjectData.h"

//*****************************************************************************************************
namespace MG
{
    //*****************************************************************************************************
    //CharacterData  注：（模板属性和战斗属性在类中包含）
    struct NoCharacterData : public GameObjectData
    {
        //------------------------------------------------------------------------

        Vec3				mPos                ;        // 自己的位置
        Vec3				mDir                ;        // 自己的朝向
        REGION_OBJ_TYPE		mRegionType         ;        // 所在地域类型
        RegionIdType		mRegionID           ;        // 所在地域编号

        //------------------------------------------------------------------------  
        NoCharacterData()
            :mPos(0,0,0)
            ,mDir(0,0,0)
            ,mRegionType(ROT_UNKNOWN)
            ,mRegionID(0)
        {

        }
        //------------------------------------------------------------------------
        NoCharacterData& operator=(const NoCharacterData& A)
        {
            if (this == &A)
            {
                return *this;
            }

            GameObjectData::operator =(A);

            mPos                     =   A.mPos                     ;
            mDir                     =   A.mDir                     ;
            mRegionID                =   A.mRegionID                ;
            mRegionType              =   A.mRegionType              ;

            return *this;
        }

        //-----------------------------------------------------------------------
        virtual void print()
        {
            GameObjectData::print();
            MG_LOG(out_sys, "【NEW_NoCharacterData】mRegionType[%d], mRegionID[%i]\n ", mRegionType, mRegionID);
        }
    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************