//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: STiroInstance.h
//        Author: yuanlinhu
//          Date: 2012-4-16
//          Time: 17:14
//   Description: 
//			新手副本
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-16      add
//////////////////////////////////////////////////////////////


//*************************************************************************************************//

#ifndef _S_TIRO_INSTANCE_H_
#define _S_TIRO_INSTANCE_H_

//*************************************************************************************************//

#include "MapServerPreqs.h"
#include "DataSetManager.h"

#include "SInstanceBase.h"
#include "InstanceTiroListCsv.h"

//*************************************************************************************************//

namespace MG
{
	class STiroInstance : public SInstanceBase
	{
	public:
		STiroInstance(InstanceListCsvInfo* instanceListInfo);
		~STiroInstance();

		InstanceTiroListCsvInfo*		getTiroCsv();
	private:
		InstanceTiroListCsvInfo*		mTiroCsv;

	private:
		STiroInstance();
		STiroInstance(const STiroInstance&);
		STiroInstance operator=(const STiroInstance&);
	};
}

#endif	//_S_TIRO_INSTANCE_H_