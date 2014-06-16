//*****************************************************************************************************
#ifndef _H_NOCHARACTER_DATA_
#define _H_NOCHARACTER_DATA_
//*****************************************************************************************************
#include "GameObjectData.h"

//*****************************************************************************************************
namespace MG
{
    //*****************************************************************************************************
    //CharacterData  ע����ģ�����Ժ�ս�����������а�����
    struct NoCharacterData : public GameObjectData
    {
        //------------------------------------------------------------------------

        Vec3				mPos                ;        // �Լ���λ��
        Vec3				mDir                ;        // �Լ��ĳ���
        REGION_OBJ_TYPE		mRegionType         ;        // ���ڵ�������
        RegionIdType		mRegionID           ;        // ���ڵ�����

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
            MG_LOG(out_sys, "��NEW_NoCharacterData��mRegionType[%d], mRegionID[%i]\n ", mRegionType, mRegionID);
        }
    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************