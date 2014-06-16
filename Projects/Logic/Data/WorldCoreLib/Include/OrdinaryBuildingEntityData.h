//*****************************************************************************************************
#ifndef _ORDINARYBUILDINGENTITYDATA_H_
#define _ORDINARYBUILDINGENTITYDATA_H_
//*****************************************************************************************************
#include "NoCharacterEntityData.h"
//*****************************************************************************************************
namespace MG
{
	//*****************************************************************************************************
	//ArmyData
	struct OrdinaryBuildingEntityData : public NoCharacterEntityData
	{ 	
		ORDINARY_BUILDING_TYPE    buildingType    ;
		
		//------------------------------------------------------------------------
		OrdinaryBuildingEntityData()
			:buildingType(OBLT_UNKNOWN)
		{

		}

		//------------------------------------------------------------------------
		OrdinaryBuildingEntityData& operator=(const OrdinaryBuildingEntityData& A)
		{
			if (this == &A)
			{
				return *this;
			}

			NoCharacterEntityData::operator =(A);

			buildingType			=	A.buildingType;

			return *this;
		}  

	};
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************