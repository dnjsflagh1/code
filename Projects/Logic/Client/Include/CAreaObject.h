//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: CNewArea.h
//        Author: yuanlinhu
//          Date: 2012-3-10
//          Time: 13:26
//   Description: 
//			ÐÂ°æ±¾ ÇøÓò
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-10      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _C_NEW_AREA_H_
#define _C_NEW_AREA_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CRegionObject.h"

/******************************************************************************/
namespace MG
{
	class CAreaObject : public CRegionObject
	{
	public:
		CAreaObject(MapListCsvInfo* mapCsvInfo);
		~CAreaObject();
	

	private:
		CAreaObject();
	};

}


#endif	//_C_NEW_AREA_H_