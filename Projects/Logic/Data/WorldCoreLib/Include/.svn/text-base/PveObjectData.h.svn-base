//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\Game\WorldCoreLib\Include\PlaceObjectData.h
//        Author: yuanlinhu
//          Date: 2012-3-16
//          Time: 16:14
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-16      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _PVE_OBJECT_DATA_H_
#define _PVE_OBJECT_DATA_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
#include "RegionObjectData.h"

#include "InstanceListCsv.h"
#include "InstancePveListCsv.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//
	/******************************************************************************/
	class PveObjectData : public RegionObjectData
	{
	public:
		PveObjectData(InstanceListCsvInfo* instanceInfo);
		virtual ~PveObjectData();

		virtual InstanceIdType			getInstanceId();

		InstanceListCsvInfo*			getListCsvInfo();
		InstancePVEListCsvInfo*			getPveCsvInfo();

	private:
		InstanceListCsvInfo*			mListCsvInfo;
		InstancePVEListCsvInfo*			mPveCsvInfo;

	private:
		PveObjectData();
		PveObjectData(const PveObjectData&);
		PveObjectData& operator=(const PveObjectData&);
	};
}

#endif	//_PVE_OBJECT_DATA_H_