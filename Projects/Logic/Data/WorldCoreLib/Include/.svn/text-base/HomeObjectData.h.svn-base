//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\Game\WorldCoreLib\Include\HomeObjectData.h
//        Author: yuanlinhu
//          Date: 2012-9-14
//          Time: 9:14
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-9-14      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _HOME_OBJECT_DATA_H_
#define _HOME_OBJECT_DATA_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
#include "RegionObjectData.h"

#include "InstanceListCsv.h"
#include "InstanceHomeListCsv.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//
	/******************************************************************************/
	class HomeObjectData : public RegionObjectData
	{
	public:
		HomeObjectData(InstanceListCsvInfo* instanceInfo);
		virtual ~HomeObjectData();

		virtual InstanceIdType			getInstanceId();

		InstanceListCsvInfo*			getListCsvInfo();
		InstanceHomeListCsvInfo*		getHomeCsvInfo();

	private:
		InstanceListCsvInfo*				mListCsvInfo;
		InstanceHomeListCsvInfo*			mHomeCsvInfo;

	private:
		HomeObjectData();
		HomeObjectData(const HomeObjectData&);
		HomeObjectData& operator=(const HomeObjectData&);
	};
}

#endif	//_HOME_OBJECT_DATA_H_