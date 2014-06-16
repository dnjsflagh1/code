//*****************************************************************************************************
#include "stdafx.h"
#include "ItemGroupTemplate.h"
//*****************************************************************************************************
namespace MG
{
    ItemGroupTemplate::~ItemGroupTemplate()
    {
        clear();
    }
    //-----------------------------------------------------------------------------------------
	// MG_CN_MODIFY
    MG::Bool ItemGroupTemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
    {
        CsvReader csvreader;
		// MG_CN_MODIFY
        if(!csvreader.create(fileName, packManager))
        {
            return false;
        }

        CsvData* csvdata = NULL;
        Int RowCount = csvreader.count();

        for(int i = 0; i < RowCount; ++i)
        {
            csvdata = csvreader.findValue(i);
            if(!csvdata)
            {
                continue;
            }

            ItemGroupInfo* tempInfo = new ItemGroupInfo;
            UInt nCol = 2;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempInfo->type      );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->GroupID         );
            MGStrOp::toU64(csvdata->mData[nCol++].c_str(), tempInfo->ItemTemplateId  );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ItemNum         );
            if ( tempInfo->ItemNum == 0 )
                tempInfo->ItemNum = 1;

            addItemGroupInfo( tempInfo );
        }

        return true;
    }
    //-----------------------------------------------------------------------------------------
    MG::Bool ItemGroupTemplate::getItemGroupInfo( U32 groupId, std::vector<ItemNum>& info )
    {
        const std::vector<const ItemGroupInfo*>* pInfo = mItemGroupInfoMap[groupId];
        if (pInfo)
        {
            ItemNum tempNum;

            std::vector<const ItemGroupInfo*>::const_iterator front = pInfo->begin();
            std::vector<const ItemGroupInfo*>::const_iterator back = pInfo->end();
            while (front != back)
            {
                tempNum.itemTemplate = (*front)->ItemTemplateId;
                tempNum.num = (*front)->ItemNum;
                info.push_back( tempNum );

                ++front;
            }

            return true;
        }

        return false;
    }
    //-----------------------------------------------------------------------------------------
    MG::Bool ItemGroupTemplate::getItemGroupInfo( U32 groupId, std::list<ItemNum>& info )
    {
        const std::vector<const ItemGroupInfo*>* pInfo = mItemGroupInfoMap[groupId];
        if (pInfo)
        {
            ItemNum tempNum;

            std::vector<const ItemGroupInfo*>::const_iterator front = pInfo->begin();
            std::vector<const ItemGroupInfo*>::const_iterator back = pInfo->end();
            while (front != back)
            {
                tempNum.itemTemplate = (*front)->ItemTemplateId;
                tempNum.num = (*front)->ItemNum;
                info.push_back( tempNum );

                ++front;
            }

            return true;
        }

        return false;
    }
    //-----------------------------------------------------------------------------------------
    MG::Bool ItemGroupTemplate::getItemAndNum( U32 groupId, ItemNum& item )
    {
		std::map<U32, std::vector<const ItemGroupInfo*>*>::iterator iter = mItemGroupInfoMap.find(groupId);
		if (iter == mItemGroupInfoMap.end())
		{
			//未找到
			return false;
		}

        std::vector<const ItemGroupInfo*>* pInfo = iter->second;
        if (pInfo)
        {
			//每组里面roll 一个物品
            U32 tempRand = pInfo->size();
            if ( tempRand > 1 )
                tempRand = MGRandom::getInstance().rand_ab_One(1, tempRand);

            const ItemGroupInfo*  pGoupInfo = (*pInfo)[tempRand-1];
            DYNAMIC_ASSERT(pGoupInfo);

            item.itemTemplate = pGoupInfo->ItemTemplateId;
            item.num = pGoupInfo->ItemNum;

            return true;
        }

        return false;
    }

	std::vector<const ItemGroupInfo*>* ItemGroupTemplate::getItemGroupListByGroupId(U32 groupId)
	{
		std::map<U32, std::vector<const ItemGroupInfo*>*>::iterator iter = mItemGroupInfoMap.find(groupId);
		if (iter != mItemGroupInfoMap.end())
		{
			return iter->second;
		}

		return NULL;
	}

    //-----------------------------------------------------------------------------------------
    void ItemGroupTemplate::clear()
    {
        std::map<U32, std::vector<const ItemGroupInfo*>*>::iterator front = mItemGroupInfoMap.begin();
        std::map<U32, std::vector<const ItemGroupInfo*>*>::iterator back = mItemGroupInfoMap.end();
        while (front != back)
        {
            std::vector<const ItemGroupInfo*>* pVectorInfo = front->second;
            DYNAMIC_ASSERT( pVectorInfo );
            std::vector<const ItemGroupInfo*>::iterator frontV = pVectorInfo->begin();
            std::vector<const ItemGroupInfo*>::iterator backV = pVectorInfo->end();
            while (frontV != backV)
            {
                delete (*frontV);
                ++frontV;
            }
            pVectorInfo->clear();
            delete pVectorInfo;

            ++front;
        }

        mItemGroupInfoMap.clear();
    }
    //-----------------------------------------------------------------------------------------
    void ItemGroupTemplate::addItemGroupInfo( const ItemGroupInfo* pInfo )
    {
        std::map<U32, std::vector<const ItemGroupInfo*>*>::iterator iter = mItemGroupInfoMap.find(pInfo->GroupID);
        if ( mItemGroupInfoMap.end() != iter )
        {
            iter->second->push_back(pInfo);
        }
        else
        {
            std::vector<const ItemGroupInfo*>* tempVector = new std::vector<const ItemGroupInfo*>;
            mItemGroupInfoMap[pInfo->GroupID] = tempVector;
            tempVector->push_back(pInfo);
        }
    }
}