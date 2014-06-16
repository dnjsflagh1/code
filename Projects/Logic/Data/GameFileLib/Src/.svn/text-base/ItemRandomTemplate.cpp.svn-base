//*****************************************************************************************************
#include "stdafx.h"
#include "ItemRandomTemplate.h"
#include "ItemGroupTemplate.h"
//*****************************************************************************************************
namespace MG
{
    ItemRandomTemplate::~ItemRandomTemplate()
    {
        clear();
    }
    //------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
    MG::Bool ItemRandomTemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
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

            ItemRandomInfo* tempInfo = new ItemRandomInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ItemRandomID               );
			nCol++;
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempInfo->useType              );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempInfo->randomType           );

            for (Int j=0; j<ITEM_RANDOM_GROUP_NUM; j++)
            {
                MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->groupArray[j].itemGroupId        );
                MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->groupArray[j].num                );
            }

            mItemRandomInfoMap[tempInfo->ItemRandomID] = tempInfo;
        }

        return true;
    }
    //------------------------------------------------------------------------------------------
    void ItemRandomTemplate::clear()
    {
        std::map<U32, ItemRandomInfo*>::iterator front = mItemRandomInfoMap.begin();
        std::map<U32, ItemRandomInfo*>::iterator back = mItemRandomInfoMap.end();
        while (front != back)
        {
            delete front->second;
            ++front;
        }

        mItemRandomInfoMap.clear();
    }
    //------------------------------------------------------------------------------------------
    MG::Bool ItemRandomTemplate::getItemRandomInfo( U32 randomId, std::vector<ItemNum>& info )
    {
		std::map<U32, ItemRandomInfo*>::iterator iter = mItemRandomInfoMap.find(randomId);
		if (iter == mItemRandomInfoMap.end())
		{
			//Î´ÕÒµ½
			return false;
		}

        const ItemRandomInfo* pInfo = iter->second;
        if (pInfo)
        {
            if ( pInfo->randomType == ITEM_RANDOM_TYPE_ONCE )
            {
                randOnce(pInfo, info);
            }
            else
            {
                randEvery(pInfo, info);
            }
            return true;
        }

        return false;
    }
    //------------------------------------------------------------------------------------------
    MG::Bool ItemRandomTemplate::getItemRandomInfo( U32 randomId, std::list<ItemNum>& info )
    {
        const ItemRandomInfo* pInfo = mItemRandomInfoMap[randomId];
        if (pInfo)
        {
            if ( pInfo->randomType == ITEM_RANDOM_TYPE_ONCE )
            {
                randOnce(pInfo, info);
            }
            else
            {
                randEvery(pInfo, info);
            }
            return true;
        }

        return false;
    }
    //------------------------------------------------------------------------------------------
    void ItemRandomTemplate::randOnce( const ItemRandomInfo*& pInfo, std::vector<ItemNum>& info )
    {
        U32 tempRandom = MGRandom::getInstance().rand_ab_One(0, ITEM_RANDOM_NUM_BASE);

        ItemNum tempItemNum;

        for (U32 i=0; i<ITEM_RANDOM_GROUP_NUM; i++)
        {
            if ( pInfo->groupArray[i].num > tempRandom )
            {
                tempItemNum.itemTemplate = 0;
				tempItemNum.num = 0;
                ItemGroupTemplate::getInstance().getItemAndNum(pInfo->groupArray[i].itemGroupId, tempItemNum);

				if (tempItemNum.itemTemplate > 0 && tempItemNum.num > 0)
				{
					info.push_back(tempItemNum);
				}
            }
        }
    }
    //------------------------------------------------------------------------------------------
    void ItemRandomTemplate::randOnce( const ItemRandomInfo*& pInfo, std::list<ItemNum>& info )
    {
        U32 tempRandom = MGRandom::getInstance().rand_ab_One(0, ITEM_RANDOM_NUM_BASE);

        ItemNum tempItemNum;

        for (U32 i=0; i<ITEM_RANDOM_GROUP_NUM; i++)
        {
            if ( pInfo->groupArray[i].num > tempRandom )
            {

                ItemGroupTemplate::getInstance().getItemAndNum(pInfo->groupArray[i].itemGroupId, tempItemNum);

				if (tempItemNum.itemTemplate > 0 && tempItemNum.num > 0)
				{
					info.push_back(tempItemNum);
				}
            }
        }
    }
    //------------------------------------------------------------------------------------------
    void ItemRandomTemplate::randEvery( const ItemRandomInfo*& pInfo, std::vector<ItemNum>& info )
    {
        ItemNum tempItemNum;

        for (U32 i=0; i<ITEM_RANDOM_GROUP_NUM; i++)
        {
            U32 tempRandom = MGRandom::getInstance().rand_ab_One(0, ITEM_RANDOM_NUM_BASE);

            if ( pInfo->groupArray[i].num > tempRandom )
            {
                ItemGroupTemplate::getInstance().getItemAndNum(pInfo->groupArray[i].itemGroupId, tempItemNum);
				if (tempItemNum.itemTemplate > 0 && tempItemNum.num > 0)
				{
					info.push_back(tempItemNum);
				}
            }
        }
    }
    //------------------------------------------------------------------------------------------
    void ItemRandomTemplate::randEvery( const ItemRandomInfo*& pInfo, std::list<ItemNum>& info )
    {
        ItemNum tempItemNum;

        for (U32 i=0; i<ITEM_RANDOM_GROUP_NUM; i++)
        {
            U32 tempRandom = MGRandom::getInstance().rand_ab_One(0, ITEM_RANDOM_NUM_BASE);

            if ( pInfo->groupArray[i].num > tempRandom )
            {
                ItemGroupTemplate::getInstance().getItemAndNum(pInfo->groupArray[i].itemGroupId, tempItemNum);
				if (tempItemNum.itemTemplate > 0 && tempItemNum.num > 0)
				{
					info.push_back(tempItemNum);
				}
            }
        }
    }
}