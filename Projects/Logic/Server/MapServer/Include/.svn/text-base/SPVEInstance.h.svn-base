//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SPVEInstance.h
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

#ifndef _S_PVE_INSTANCE_H_
#define _S_PVE_INSTANCE_H_

//*************************************************************************************************//

#include "MapServerPreqs.h"
#include "DataSetManager.h"

#include "SInstanceBase.h"
#include "InstancePVEListCsv.h"

//*************************************************************************************************//

namespace MG
{
	class SPVEInstance : public SInstanceBase
	{
	public:
		SPVEInstance(InstanceListCsvInfo* instanceListInfo);
		~SPVEInstance();

		InstancePVEListCsvInfo*		getPVECsv();
		Int				getFinishCharacter() const;

	private:
		InstancePVEListCsvInfo*		mPVECsv;

	private:
		SPVEInstance();
		SPVEInstance(const SPVEInstance&);
		SPVEInstance operator=(const SPVEInstance&);
	};
}

#endif	//_S_PVE_INSTANCE_H_