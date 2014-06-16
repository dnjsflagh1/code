//////////////////////////////////////////////////////////////
//
// Copyright (C), 2012, YXZ Software Co., Ltd. 
//
//      FileName: SCharacterQuestCsv.h
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

//*************************************************************************************************//
#ifndef _DISTRICT_LIST_H_
#define _DISTRICT_LIST_H_
//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

//*************************************************************************************************//
namespace MG
{

	//对应【DistrictList.csv】里的每一列
	enum DistrictListRow
	{
		districtId		= 0,
		note,
		name,
		text,
		title,
		openType,
		districtRank,
	};

	//政区是否开放
	enum DistrictOpenType
	{
		DOT_NULL	= 0,		//无意义

		DOT_OPEN	= 1,		//开放
		DOT_CLOSED	= 2,		//不开放

		DOT_MAX
	};

	//政区等级
	enum DistrictRankType
	{
		DRT_NULL	= 0,		//无意义

		DRT_JIE		= 1,		//界
		DRT_ZHOU	= 2,		//州
		DRT_JUN		= 3,		//郡
		DRT_XIAN	= 4,		//县
	
		DRT_MAX
	};

	//*************************************************************************************************//
	//单个政区的信息
	//*************************************************************************************************//
	//--------------------------------------------------------------------------
	struct DistrictData
	{
		DistrictIdType		districtId;
		Str16				name;
		Str16				text;
		Str16				title;
		DistrictOpenType	openType;
		DistrictRankType	rank;

		DistrictData()
			:districtId(0)
			,openType(DOT_NULL)
			,rank(DRT_NULL)
		{
		}
	};

	//--------------------------------------------------------------------------
	//单个政区的信息管理器
	class DistrictListCsvInfo
	{
	public:
		DistrictListCsvInfo();
		~DistrictListCsvInfo();
		
		void											addNewSlave(DistrictListCsvInfo* child);
		void											setMaster(DistrictListCsvInfo* master);
		DistrictListCsvInfo*							getMaster();
		std::map<DistrictIdType, DistrictListCsvInfo*>*	getSlaveList();


		DistrictIdType								getDistrictId();
		void										setDistrictId(DistrictIdType districtId);

		Str16&										getName();
		void										setName(const Str16& name);

		Str16&										getText();
		void										setText(const Str16& text);

		Str16&										getTitle();
		void										setTitle(const Str16& title);

		DistrictOpenType							getOpenType();
		void										setOpenType(const DistrictOpenType type);

		DistrictRankType							getRank();
		void										setRank(const DistrictRankType rank);

		

		void										print();
	public:
		DistrictData										mInfo;		//我自己的信息
		DistrictListCsvInfo*								mMaster;	//我的父亲
		std::map<DistrictIdType, DistrictListCsvInfo*>		mSlaveList;
	};

	//*************************************************************************************************//
	//保存政区列表
	class DistrictListCsv
	{
	public:
		DistrictListCsv();
		~DistrictListCsv();
		//SINGLETON_INSTANCE(DistrictListCsv);
		// MG_CN_MODIFY
		Bool												loadCsv(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		DistrictListCsvInfo*								getDistrictInfo(const DistrictIdType id);
		Bool												isInDistrictList(const DistrictIdType id);
		std::map<DistrictIdType, DistrictListCsvInfo*>*		getDistrictList();

	private:
		SimpleMapDataSetManager<DistrictIdType, DistrictListCsvInfo>		mDistrictList;
	};
}



#endif	//_DISTRICT_LIST_H_