//*****************************************************************************************************
#ifndef _NOCHARACTERENTITYDATA_H_
#define _NOCHARACTERENTITYDATA_H_
//*****************************************************************************************************
#include "SceneObjectData.h"
//*****************************************************************************************************
namespace MG
{
	//*****************************************************************************************************
	//ArmyData
	struct NoCharacterEntityData : public SceneObjectData
	{ 	
		Vec3				mPos                ;        // 自己的位置
		Vec3				mDir                ;        // 自己的朝向
		REGION_OBJ_TYPE		mRegionType         ;        // 所在地域类型
		RegionIdType		mRegionID           ;        // 所在地域编号

		//------------------------------------------------------------------------
		NoCharacterEntityData()
			:mRegionType(ROT_UNKNOWN)
			,mRegionID(0) 
		{

		}

		//------------------------------------------------------------------------
		NoCharacterEntityData& operator=(const NoCharacterEntityData& A)
		{
			if (this == &A)
			{
				return *this;
			}

			SceneObjectData::operator =(A);

			mPos                     =   A.mPos                     ;
			mDir                     =   A.mDir                     ;
			mRegionID                =   A.mRegionID                ;
			mRegionType              =   A.mRegionType              ;

			return *this;
		}  

	};
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************