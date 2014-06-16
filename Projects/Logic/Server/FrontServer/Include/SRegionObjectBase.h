//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\FrontServer\Include\SRegionObject.h
//        Author: yuanlinhu
//          Date: 2012-3-20
//          Time: 9:52
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-20      add
//////////////////////////////////////////////////////////////


/******************************************************************************/

#ifndef _S_REGION_OBJECT_NEW_H_
#define _S_REGION_OBJECT_NEW_H_

/******************************************************************************/

#include "FrontServerPreqs.h"
#include "DistrictList.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//FrontServer使用的 区域基类
	/******************************************************************************/
	class SRegionObjectBase
	{
	public:
		SRegionObjectBase(RegionObjectData* regionData);
		virtual ~SRegionObjectBase();

	public:
		virtual RegionIdType		getRegionId()				= NULL;
		virtual	REGION_OBJ_TYPE		getRegionType() const		= NULL;
		virtual	DistrictIdType		getDistrictId()				= NULL;		//绑定的政区ID
		virtual DistrictRankType	getDistrictRankType()		= NULL;		//政区的类型

		void			setMapServerNetId(const NetIdType mapServerNetId);
		NetIdType		getMapServerNetId() const;
		
		void			setCampaignId(const CampaignIdType campaignId);
		CampaignIdType	getCampaignId() const;

		Bool			isOpen();
	
		RegionObjectData*	getRegionData();

	private:
		NetIdType			mMapServerNetId;
		CampaignIdType		mCampaignId;
		RegionObjectData*	mRegionData;


	private:
		SRegionObjectBase();
		SRegionObjectBase(const SRegionObjectBase&);
		SRegionObjectBase& operator=(const SRegionObjectBase&);
	};
}

#endif	//_S_REGION_OBJECT_NEW_H_