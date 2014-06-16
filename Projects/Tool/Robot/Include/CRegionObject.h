//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: CRegionObjectNew.h
//        Author: yuanlinhu
//          Date: 2012-3-15
//          Time: 11:39
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-15      add
//////////////////////////////////////////////////////////////


/******************************************************************************/
#ifndef _CREGIONOBJECTNEW_H_
#define _CREGIONOBJECTNEW_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "RegionObjectData.h"
#include "District.h"
/******************************************************************************/
namespace MG
{
	class CRegionObject
	{
	public:
		CRegionObject(RegionObjectData* data);
		virtual ~CRegionObject();

		 RegionObjectData*	getData();
	public:
		virtual RegionIdType		getRegionId()				= NULL;
		virtual	REGION_OBJ_TYPE		getRegionType() const		= NULL;
		virtual	DistrictIdType		getDistrictId()				= NULL;		//绑定的政区ID
		virtual DistrictRankType	getDistrictRankType()		= NULL;		//政区的类型

		Str&				getFilePath();
		Str&				getFileName();
		Str&				getBaseFilePath();

	private:
		void			    _create();

	private:
       
		RegionObjectData*	mRegionData;

		Str					mFilePath;
		Str					mFileName;
		Str					mBaseFilePath;

		Bool				mHasCreated;

	private:
		CRegionObject();
		CRegionObject(const CRegionObject&);
		CRegionObject& operator=(const CRegionObject&);
	};

}

#endif	//_CREGIONOBJECTNEW_H_