//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SHomeInstance.h
//        Author: yuanlinhu
//          Date: 2012-4-23
//          Time: 19:34
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-23      add
//////////////////////////////////////////////////////////////


//*************************************************************************************************//

#ifndef _S_HOME_INSTANCE_H_
#define _S_HOME_INSTANCE_H_

//*************************************************************************************************//

#include "MapServerPreqs.h"
#include "DataSetManager.h"

#include "SInstanceBase.h"
#include "InstanceHomeListCsv.h"

//*************************************************************************************************//

namespace MG
{
	class SHomeInstance : public SInstanceBase
	{
	public:
		SHomeInstance(InstanceListCsvInfo* instanceListInfo);
		~SHomeInstance();

		InstanceHomeListCsvInfo*		getHomeCsv();

	private:
		InstanceHomeListCsvInfo*		mHomeListCsv;

	private:
		SHomeInstance();
		SHomeInstance(const SHomeInstance&);
		SHomeInstance operator=(const SHomeInstance&);
	};
}

#endif	//_S_HOME_INSTANCE_H_