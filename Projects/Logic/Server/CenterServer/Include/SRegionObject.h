//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\CenterServer\Include\SRegionObject.h
//        Author: yuanlinhu
//          Date: 2012-3-21
//          Time: 15:09
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-21      add
//////////////////////////////////////////////////////////////


/******************************************************************************/

#ifndef _S_REGION_OBJECT_NEW_H_
#define _S_REGION_OBJECT_NEW_H_

/******************************************************************************/

#include "CenterServerPreqs.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//CentServer使用的 区域基类
	/******************************************************************************/
	class SRegionObject
	{
	public:
		SRegionObject();
		virtual ~SRegionObject();

	public:
		virtual RegionIdType		getRegionId()			= NULL;
		virtual	REGION_OBJ_TYPE		getRegionType() const	= NULL;
	};
}

#endif	//_S_REGION_OBJECT_NEW_H_