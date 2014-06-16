//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Client\Core\MGClient\Include\CRegionObjectNew.h
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
#ifndef _C_REGION_OBJECT_NEW_H_
#define _C_REGION_OBJECT_NEW_H_
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


		//是否是 slg, 还是 rpg
		GameType			getGameType();

		Str&				getFilePath();
		Str&				getFileName();
		Str&				getBaseFilePath();

		Str16&				getRegionNameStr16();
		Str&				getRegionNameStr8();

		MapType				getMapType();


	public:
		void			setStartCampaignTime(U32 prepareTimeSecond);	//准备的时间 【30秒】
		U64				getStartCampaignTime() const;

	private:
		void			    _create();

	private:

		RegionObjectData*	mRegionData;

		Str					mFilePath;
		Str					mFileName;
		Str					mBaseFilePath;
		Str					mRegionName;

		U64					mStartCampaignTime;		//开始战斗时间

	private:
		CRegionObject();
		CRegionObject(const CRegionObject&);
		CRegionObject& operator=(const CRegionObject&);
	};

}

#endif	//_C_REGION_OBJECT_NEW_H_