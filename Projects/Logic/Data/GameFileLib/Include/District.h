//////////////////////////////////////////////////////////////
//
// Copyright (C), 2012, YXZ Software Co., Ltd. 
//
//      FileName: District.h
//        Author: yuanlinhu
//          Date: 2012-2-28
//          Time: 14:40
// Description: 
//			1.读取政区列表
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-2-28      add

//////////////////////////////////////////////////////////////

#ifndef _DISTRICT_H_
#define _DISTRICT_H_
//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DistrictList.h"
#include "DistrictTree.h"

//*************************************************************************************************//

namespace MG
{

	//*************************************************************************************************//
	//struct DistrictInfo
	//{
	//	DistrictData*	mInfo;		//我自己的信息
	//	DistrictData*	mParent;	//我的父亲

	//	std::map<DistrictIdType, DistrictInfo*>	mChildren;
	//};

	//*************************************************************************************************//
	class District
	{
	public:
		District();
		~District();
		SINGLETON_INSTANCE(District);
		// MG_CN_MODIFY
		Bool load(const Char16* districtListFileName,
				  const Char16* districtTreeFileName,
				  IMGExternalPackManager* packManager = NULL);

		void	addRootNode(DistrictListCsvInfo* node);


		DistrictListCsvInfo* getDistrictInfo(DistrictIdType id);

		DistrictListCsvInfo* getCountryNode(const DistrictIdType id);	//查找国的节点

		DistrictListCsvInfo* getZhouNode(const DistrictIdType id);	//查找州的节点

		void	print();
	private:
		std::map<DistrictIdType, DistrictListCsvInfo*>		mTree;

		DistrictListCsv	mDistrictList;
		DistrictTreeCsv	mDistrictTree;
	};	
}


#endif	//_DISTRICT_H_