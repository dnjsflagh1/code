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
#ifndef _TIRO_OBJECT_DATA_H_
#define _TIRO_OBJECT_DATA_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
#include "RegionObjectData.h"

#include "InstanceListCsv.h"
#include "InstanceTiroListCsv.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//
	/******************************************************************************/
	class TiroObjectData : public RegionObjectData
	{
	public:
		TiroObjectData(InstanceListCsvInfo* instanceInfo);
		virtual ~TiroObjectData();

		virtual InstanceIdType			getInstanceId();

		InstanceListCsvInfo*			getListCsvInfo();
		InstanceTiroListCsvInfo*		getTiroCsvInfo();

	private:
		InstanceListCsvInfo*				mListCsvInfo;
		InstanceTiroListCsvInfo*			mTiroCsvInfo;

	private:
		TiroObjectData();
		TiroObjectData(const TiroObjectData&);
		TiroObjectData& operator=(const TiroObjectData&);
	};
}

#endif	//_TIRO_OBJECT_DATA_H_