//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SAtkInstance.h
//        Author: yuanlinhu
//          Date: 2012-4-23
//          Time: 19:40
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-23      add
//////////////////////////////////////////////////////////////


//*************************************************************************************************//

#ifndef _S_ATK_INSTANCE_H_
#define _S_ATK_INSTANCE_H_

//*************************************************************************************************//

#include "MapServerPreqs.h"
#include "DataSetManager.h"

#include "SInstanceBase.h"
#include "InstanceAtkListCsv.h"
#include "InstanceAtkCampListCsv.h"
#include "InstanceAtkStrengthListCsv.h"

//*************************************************************************************************//

namespace MG
{
	class SCampListCsv
	{
	public:
		SCampListCsv(CampIdType campListId);
		~SCampListCsv();

		InstanceAtkStrengthListCsvInfo*		getAtkStrengthInfoByIndex(Int index);
	private:
		InstanceAtkCampListCsvInfo*		mAtkCampListCsvInfo;
		std::map<CampIdType, InstanceAtkStrengthListCsvInfo*>	mAtkStrengthListCsvList;

	private:
		SCampListCsv();
		SCampListCsv(const SCampListCsv&);
		SCampListCsv operator=(const SCampListCsv&);
	};

	class SAtkInstance : public SInstanceBase
	{
	public:
		SAtkInstance(InstanceListCsvInfo* instanceListInfo);
		~SAtkInstance();

		InstanceAtkListCsvInfo*			getAtkListCsvInfo();
		SCampListCsv*					getCampListByForce(FORCE force);
	private:
		InstanceAtkListCsvInfo*		mAtkListCsvInfo;
		std::vector<SCampListCsv*>	mAtkCampListCsvList;
		std::vector<SCampListCsv*>	mDefenseCampListCsvList;

	private:
		SAtkInstance();
		SAtkInstance(const SAtkInstance&);
		SAtkInstance operator=(const SAtkInstance&);
	};
}

#endif	//_S_ATK_INSTANCE_H_