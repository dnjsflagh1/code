
/******************************************************************************/

#include "stdafx.h"
#include "DistrictList.h"

/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	DistrictListCsvInfo::DistrictListCsvInfo()
		:mMaster(NULL)
	{
		mSlaveList.clear();
	}

	//--------------------------------------------------------------------------
	DistrictListCsvInfo::~DistrictListCsvInfo()
	{
		mMaster = NULL;
		mSlaveList.clear();
	}

	//--------------------------------------------------------------------------
	void DistrictListCsvInfo::addNewSlave(DistrictListCsvInfo* newSlave)
	{
		if (NULL == newSlave || newSlave->getDistrictId() <= 0)
		{
			//DYNAMIC_ASSERT(0);
			return;
		}

		//子节点必须是均 州 郡 县
		DYNAMIC_ASSERT( DRT_ZHOU == newSlave->getRank() || 
						DRT_JUN == newSlave->getRank() || 
						DRT_XIAN == newSlave->getRank());
		
		std::map<DistrictIdType, DistrictListCsvInfo*>::iterator iter = mSlaveList.find(newSlave->getDistrictId());
		if (iter != mSlaveList.end())
		{
			DYNAMIC_ASSERT(0);
		}
		else
		{
			mSlaveList[newSlave->getDistrictId()] = newSlave;
		}
	}

	//--------------------------------------------------------------------------
	void DistrictListCsvInfo::setMaster(DistrictListCsvInfo* master)
	{
		if (NULL != mMaster)
		{
			DYNAMIC_ASSERT(0);
			//已经有父亲， 可能是填csv表有错误
			return;
		}

		mMaster = master;
	}

	//--------------------------------------------------------------------------
	DistrictIdType DistrictListCsvInfo::getDistrictId()
	{
		return mInfo.districtId;
	}

	//--------------------------------------------------------------------------
	void DistrictListCsvInfo::setDistrictId(DistrictIdType	districtId)
	{
		mInfo.districtId = districtId;
	}

	//--------------------------------------------------------------------------
	Str16& DistrictListCsvInfo::getName()
	{
		return mInfo.name;
	}

	//--------------------------------------------------------------------------
	void DistrictListCsvInfo::setName(const Str16& name)
	{
		mInfo.name = name;
	}

	//--------------------------------------------------------------------------
	Str16& DistrictListCsvInfo::getText()
	{
		return mInfo.text;
	}

	//--------------------------------------------------------------------------
	void DistrictListCsvInfo::setText(const Str16& text)
	{
		mInfo.text = text;
	}

	//--------------------------------------------------------------------------
	Str16& DistrictListCsvInfo::getTitle()
	{
		return mInfo.title;
	}

	//--------------------------------------------------------------------------
	void DistrictListCsvInfo::setTitle(const Str16& title)
	{
		mInfo.title = title;
	}

	//--------------------------------------------------------------------------
	DistrictOpenType DistrictListCsvInfo::getOpenType()
	{
		return mInfo.openType;
	}

	//--------------------------------------------------------------------------
	void DistrictListCsvInfo::setOpenType(const DistrictOpenType type)
	{
		mInfo.openType = type;
	}

	//--------------------------------------------------------------------------
	DistrictRankType DistrictListCsvInfo::getRank()
	{
		return mInfo.rank;
	}

	//--------------------------------------------------------------------------
	void DistrictListCsvInfo::setRank(const DistrictRankType rank)
	{
		mInfo.rank = rank;
	}

	//--------------------------------------------------------------------------
	DistrictListCsvInfo* DistrictListCsvInfo::getMaster()
	{
		return mMaster;
	}

	//--------------------------------------------------------------------------
	std::map<DistrictIdType, DistrictListCsvInfo*>* DistrictListCsvInfo::getSlaveList()
	{
		return &mSlaveList;
	}

	/******************************************************************************/
	DistrictListCsv::DistrictListCsv()
	{

	}

	//--------------------------------------------------------------------------
	DistrictListCsv::~DistrictListCsv()
	{
		mDistrictList.destroyAll();
	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool DistrictListCsv::loadCsv(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			DistrictIdType id;
			MGStrOp::toI32(csvdata->mData[DistrictListRow::districtId].c_str(), id);
			if (true == isInDistrictList(id))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			I32 openType = -1;
			MGStrOp::toI32(csvdata->mData[DistrictListRow::openType].c_str(), openType);
			if (DOT_OPEN != (DistrictOpenType)openType)
			{
				continue;
			}

			DistrictListCsvInfo* newDistrictInfo = mDistrictList.createOrRetrieve(id, false);
			
			newDistrictInfo->setDistrictId(id);
			newDistrictInfo->setName(csvdata->mData[DistrictListRow::name]);
			newDistrictInfo->setText(csvdata->mData[DistrictListRow::text]);
			newDistrictInfo->setTitle(csvdata->mData[DistrictListRow::title]);
			newDistrictInfo->setOpenType((DistrictOpenType)openType);

			I32 rank = -1;
			MGStrOp::toI32(csvdata->mData[DistrictListRow::districtRank].c_str(), rank);
			newDistrictInfo->setRank((DistrictRankType)rank);
			int kk = 0;
		}

		return true;
	}

	//--------------------------------------------------------------------------
	DistrictListCsvInfo* DistrictListCsv::getDistrictInfo(const DistrictIdType id)
	{
		return  mDistrictList.getData(id);
	}

	//--------------------------------------------------------------------------
	Bool DistrictListCsv::isInDistrictList(const DistrictIdType id)
	{
		return mDistrictList.hasData(id);
	}

	//--------------------------------------------------------------------------
	std::map<DistrictIdType, DistrictListCsvInfo*>* DistrictListCsv::getDistrictList()
	{
		return mDistrictList.getDataSet();
	}

	//--------------------------------------------------------------------------
	void DistrictListCsvInfo::print()
	{
		std::string strSlaveIds("");

		std::map<DistrictIdType, DistrictListCsvInfo*>::iterator iter = mSlaveList.begin();
		for ( ; iter != mSlaveList.end(); iter++)
		{
			//if (iter->second->getCanSeeByCamera() == false)
			//{
			//	continue;
			//}
			std::string id;
			MGStrOp::toString(iter->second->getDistrictId(), id);
			if (strSlaveIds.empty())
			{
				strSlaveIds = strSlaveIds + id;
			}
			else
			{
				strSlaveIds = strSlaveIds + ", " + id;
			}
		}

		if (strSlaveIds.empty())
		{
			strSlaveIds = "空";
		}

		std::string strMaster;
		if (NULL != mMaster)
		{
			MGStrOp::toString(mMaster->getDistrictId(), strMaster);
		}
		else
		{
			strMaster = "空";
		}


		MG_LOG(out_sys, "districtId = [%d], master = [%s], slaveId = [%s]\n", mInfo.districtId,strMaster.c_str(), strSlaveIds.c_str() );


		//打印孩子信息
		{
			std::map<DistrictIdType, DistrictListCsvInfo*>::iterator iterSlave = mSlaveList.begin();
			for ( ; iterSlave != mSlaveList.end(); iterSlave++)
			{
				iterSlave->second->print();
			}
		}
		
	}
	//--------------------------------------------------------------------------
}