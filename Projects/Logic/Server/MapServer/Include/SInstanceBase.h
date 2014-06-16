//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\RegionInstance.h
//        Author: yuanlinhu
//          Date: 2012-4-13
//          Time: 14:59
//   Description: 
//			区域副本 基类
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-13      add
//////////////////////////////////////////////////////////////

/******************************************************************************/

#ifndef _S_INSTANCE_BASE_H_
#define _S_INSTANCE_BASE_H_

/******************************************************************************/

#include "MapServerPreqs.h"

#include "InstanceListCsv.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//MapServer使用的 副本基类
	/******************************************************************************/
	class SInstanceBase
	{
	public:
		SInstanceBase(InstanceListCsvInfo* instanceListInfo);
		virtual ~SInstanceBase();

		InstanceIdType			getInstanceId() const;
		InstanceType			getInstanceType();

	private:
		InstanceListCsvInfo*	mInstanceListInfo;

	private:
		SInstanceBase();
		SInstanceBase(const SInstanceBase&);
		SInstanceBase operator=(const SInstanceBase&);
	};
}

#endif	//_S_INSTANCE_BASE_H_