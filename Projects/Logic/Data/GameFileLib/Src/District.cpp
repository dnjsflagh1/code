
/******************************************************************************/

#include "stdafx.h"
#include "District.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	District::District()
	{

	}

	//--------------------------------------------------------------------------
	District::~District()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool District::load(const Char16* districtListFileName/* = L"MapData\\DistrictList.csv"*/,
						const Char16* districtTreeFileName/* = L"MapData\\DistrictTree.csv"*/,
						IMGExternalPackManager* packManager/* = NULL*/)
	{
		// MG_CN_MODIFY
		mDistrictList.loadCsv(districtListFileName, packManager);
		mDistrictTree.loadCsv(districtTreeFileName, packManager);

		DYNAMIC_ASSERT(false == mDistrictList.getDistrictList()->empty() &&
						false == mDistrictTree.getDistrictTreeList()->empty());

		//首先搜索【根政区】
		std::map<DistrictTreeIdType, DistrictTreeInfo*>* allTree = mDistrictTree.getDistrictTreeList();
		for (std::map<DistrictTreeIdType, DistrictTreeInfo*>::iterator iter = allTree->begin(); iter != allTree->end(); ++iter)
		{
			DistrictTreeInfo* tempTreeInfo = iter->second;
			if (NULL == tempTreeInfo)
			{
				DYNAMIC_ASSERT(0);
				continue;
			}


			DistrictListCsvInfo* master = mDistrictList.getDistrictInfo(tempTreeInfo->masterDistrictId);
			DistrictListCsvInfo* slave = mDistrictList.getDistrictInfo(tempTreeInfo->slaveDistrictId);
			if (NULL != slave)
			{
				slave->setMaster(master);
			}

			if (NULL != master)
			{
				master->addNewSlave(slave);
			}
		}

		//把所有的根节点找出来
		std::map<DistrictIdType, DistrictTreeInfo*>* districtList = mDistrictTree.getDistrictTreeList();
		for (std::map<DistrictIdType, DistrictTreeInfo*>::iterator iter = districtList->begin(); iter != districtList->end(); ++iter)
		{
			DistrictTreeInfo* tempTreeInfo = iter->second;
			if (NULL != tempTreeInfo && RT_ROOT == tempTreeInfo->rootType)
			{
				DistrictListCsvInfo* rootNode = mDistrictList.getDistrictInfo(tempTreeInfo->masterDistrictId);
				if (NULL != rootNode && NULL != rootNode->getMaster())
				{
					DYNAMIC_ASSERT(0);
					//表示 根节点有他的父亲节点， csv表填写错误
					continue;
				}
				addRootNode(rootNode);
			}
		}

		DYNAMIC_ASSERT(false == mTree.empty());
		print();

		return true;
	}

	void District::addRootNode(DistrictListCsvInfo* rootNode)
	{
		if (NULL == rootNode || rootNode->getDistrictId() <= 0)
		{
			return;
		}

		std::map<DistrictIdType, DistrictListCsvInfo*>::iterator iter = mTree.find(rootNode->getDistrictId());
		//if (iter != mTree.end())
		//{
		//	return;
		//}
		//else
		{
			mTree[rootNode->getDistrictId()] = rootNode;
		}
	}

	void District::print()
	{
		MG_LOG(out_sys, " -------------------------- Tree 的结构 打印 开始 -------------------------- \n");
		for (std::map<DistrictIdType, DistrictListCsvInfo*>::iterator iter = mTree.begin(); iter != mTree.end(); ++iter)
		{
			MG_LOG(out_sys, " Root 节点  开始\n");
			iter->second->print();
			MG_LOG(out_sys, " Root 节点  结束\n");
		}

		MG_LOG(out_sys, " -------------------------- Tree 的结构 打印 结束 -------------------------- \n");
	}

	DistrictListCsvInfo* District::getDistrictInfo(DistrictIdType id)
	{
		return mDistrictList.getDistrictInfo(id);
	}

	DistrictListCsvInfo* District::getCountryNode(const DistrictIdType id)
	{
		std::map<DistrictIdType, DistrictListCsvInfo*>::iterator iter = mTree.find(id);
		if (iter != mTree.end())
		{
			return iter->second;
		}

		return NULL;
	}

	DistrictListCsvInfo* District::getZhouNode(const DistrictIdType id)
	{
		//std::map<DistrictIdType, DistrictListCsvInfo*>::iterator iter = mTree.begin()->find(id);
		//if (iter != mTree.end())
		//{
		//	return iter->second;
		//}

		return NULL;
	}
}