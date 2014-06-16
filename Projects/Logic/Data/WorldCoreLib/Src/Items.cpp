//**********************************************************************************************************
#include "stdafx.h"
#include "Items.h"
#include "PlayerItem.h"
#include "PlayerItemFactory.h"
//**********************************************************************************************************
namespace MG
{
    Items::Items()
        :mSize(0)
    {

    }
    //--------------------------------------------------------------------------------------------
    Items::~Items()
    {
        clear();
    }
    //--------------------------------------------------------------------------------------------
    void        Items::addItem( PlayerItem* pItem )
    {
        mPlayerItemMap[pItem->getItemDBID()] = pItem;
        if ( mSize != 0 )
            mIndexMap[pItem->getItemIndex()] = pItem->getItemDBID();
    }
    //--------------------------------------------------------------------------------------------
   PlayerItem* Items::removeItem( IdType itemDBID )
    {
        PlayerItem* pItem = NULL;

        std::map<IdType, PlayerItem*>::iterator iter = mPlayerItemMap.find(itemDBID);
        if ( mPlayerItemMap.end() != iter )
        {
            pItem = iter->second;
            pItem->setCharacterID(0);
            mPlayerItemMap.erase(iter);

            if ( mSize != 0 )
            {
                std::map<U32, IdType>::iterator indexIter = mIndexMap.find( pItem->getItemIndex() );
                if ( mIndexMap.end() != indexIter )
                {   
                    mIndexMap.erase(indexIter);
                }
            }
            
        }

        return pItem;
    }
	
    //--------------------------------------------------------------------------------------------
    PlayerItem* Items::removeItem( U32 index )
    {
		PlayerItem* pItem = NULL;

		std::map<U32, IdType>::iterator indexIter = mIndexMap.find(index);
		if ( mIndexMap.end() != indexIter )
		{
			std::map<IdType, PlayerItem*>::iterator itemIter = mPlayerItemMap.find(indexIter->second);
			if ( mPlayerItemMap.end() != itemIter )
			{ 
				pItem = itemIter->second;
				pItem->setCharacterID(0);
				mPlayerItemMap.erase(itemIter);
			}
			mIndexMap.erase(indexIter);
		}

		return pItem;
    }
    //--------------------------------------------------------------------------------------------
    ITEM_DELETE_ERROR        Items::deleteItem( IdType itemDBID )
    {
        std::map<IdType, PlayerItem*>::iterator iter = mPlayerItemMap.find(itemDBID);
        if ( mPlayerItemMap.end() != iter )
        {
            //check
            //?
            if ( mSize != 0 )
            {
                std::map<U32, IdType>::iterator indexIter = mIndexMap.find( iter->second->getItemIndex() );
                if ( mIndexMap.end() != indexIter )
                {  
                    mIndexMap.erase(indexIter); 
                }
            }
            //增加删除标志位
			iter->second->setItemPos(ITEM_SITE_TYPE_DEL);
			mPlayerItemMap.erase(iter);
            return ITEM_DELETE_ERROR_SUCCEED;
        }

        return ITEM_DELETE_ERROR_NONE;
    }
    //--------------------------------------------------------------------------------------------
    ITEM_DELETE_ERROR        Items::deleteItem( U32 index )
    {
		std::map<U32, IdType>::iterator indexIter = mIndexMap.find(index);
		if ( mIndexMap.end() != indexIter )
		{
			//check
			//?
			std::map<IdType, PlayerItem*>::iterator itemIter = mPlayerItemMap.find(indexIter->second);
			if ( mPlayerItemMap.end() != itemIter )
			{ 
				//增加删除标志位
				itemIter->second->setItemPos(ITEM_SITE_TYPE_DEL);
				mIndexMap.erase(indexIter);
				return ITEM_DELETE_ERROR_SUCCEED;
			}
			mPlayerItemMap.erase(itemIter);

		}
		return ITEM_DELETE_ERROR_NONE;
    }
    //--------------------------------------------------------------------------------------------
    PlayerItem* Items::findItem( IdType itemDBID )
    {
        std::map<IdType, PlayerItem*>::iterator iter = mPlayerItemMap.find(itemDBID);
        if ( mPlayerItemMap.end() != iter )
        {
            return iter->second;
        }

        return NULL;
    }
	
    //--------------------------------------------------------------------------------------------
    PlayerItem* Items::findItem( U32 index )
    {
		std::map<U32, IdType>::iterator indexIter = mIndexMap.find(index);
		if ( mIndexMap.end() != indexIter )
		{
			std::map<IdType, PlayerItem*>::iterator itemIter = mPlayerItemMap.find(indexIter->second);
			if ( mPlayerItemMap.end() != itemIter )
			{ 
				return itemIter->second;
			}
		}

		return NULL;
    }
	//--------------------------------------------------------------------------------------------
	PlayerItem* Items::findItemByTemplateId( U32 itemTemplateId )
	{
		  PlayerItem* playerItem = NULL;
          std::map<IdType, PlayerItem*>::iterator front = mPlayerItemMap.begin();
		  std::map<IdType, PlayerItem*>::iterator back = mPlayerItemMap.end();
		  while (front != back)
		  {
              if (front->second->getItemTempID() == itemTemplateId)
              {
                   playerItem = front->second;
              }

			  front++;
		  }

		  return playerItem;
	}
	//--------------------------------------------------------------------------------------------
	void Items::findItemByTemplateId( U32 itemTemplateId,std::vector<PlayerItem*>& itemList )
	{
         std::map<IdType, PlayerItem*>::iterator front = mPlayerItemMap.begin();
		  std::map<IdType, PlayerItem*>::iterator back = mPlayerItemMap.end();
		  while (front != back)
		  {
              if (front->second->getItemTempID() == itemTemplateId)
              {
                  itemList.push_back(front->second);
              }

			  front++;
		  }  
	}
	//--------------------------------------------------------------------------------------------
    void Items::clear()
    {
        //////////////////////////////////////////////////////////////

		std::map<IdType, PlayerItem*>::iterator front = mPlayerItemMap.begin();
		std::map<IdType, PlayerItem*>::iterator back = mPlayerItemMap.end();
		while (front != back)
		{
			PlayerItemFactory::getInstance().removeItem( front->second );

			++front;
		}

		mPlayerItemMap.clear();
		mIndexMap.clear();

		//////////////////////////////////////////////////////////////

		mSize = 0;
    }
    //--------------------------------------------------------------------------------------------
   /* void Items::setIndex( U32 index, IdType itemDBID )
    {
        mIndexMap[index] = itemDBID;
    }
	*/
    //--------------------------------------------------------------------------------------------
    void Items::removeIndex( U32 index )
    {
        std::map<U32, IdType>::iterator indexIter = mIndexMap.find(index);
        if ( mIndexMap.end() != indexIter )
        {
            mIndexMap.erase(indexIter);
        }
    }
	
    //--------------------------------------------------------------------------------------------
    MG::U32 Items::getFreeIndex()
    {
        std::map<U32,IdType>::iterator indexIter;
        std::map<U32,IdType>::iterator back = mIndexMap.end(); 

        for (U32 i=1; i<=mSize; i++)
        {
            indexIter = mIndexMap.find(i);
            if (back != indexIter)
                continue;
            else
                return i;
        }

        return 0;
    }
    //--------------------------------------------------------------------------------------------
   /* void Items::printfItemDBID()
    {
        OutputDebugStringA("\n");
        std::map<IdType, PlayerItem*>::iterator front = mPlayerItemMap.begin();
        std::map<IdType, PlayerItem*>::iterator back = mPlayerItemMap.end();
        while (front != back)
        {
            char temp[64] = "";
            sprintf(temp, "selfRemove: index = %d, DBID = %I64d\n", front->second->getItemIndex(), front->second->getItemDBID());
            OutputDebugStringA(temp);

            ++front;
        }
        OutputDebugStringA("\n");
    }
	*/
    //--------------------------------------------------------------------------------------------
    MG::Bool Items::checkItemFull()
    {
        if ( mSize != 0 )
        {
            return mPlayerItemMap.size() >= mSize;
        }

        return false;
    }
    //--------------------------------------------------------------------------------------------
    MG::Bool Items::checkCanAdd( U32 num )
    {
        if ( mSize != 0 )
        {
            return mPlayerItemMap.size() + num <= mSize;
        }

        return false;    
    }
	//--------------------------------------------------------------------------------------------
	MG::U32 Items::getItemCount( U32 itemTemplateId )
	{
		U32 itemCount = 0;
		std::vector<PlayerItem*> playerList;
        findItemByTemplateId(itemTemplateId,playerList);
		std::vector<PlayerItem*>::iterator front = playerList.begin();
		std::vector<PlayerItem*>::iterator back = playerList.end();
		while (front != back)
		{
            itemCount += (*front)->getItemNum();
			front++;
		}
		return itemCount;
	}
	//--------------------------------------------------------------------------------------------
	
}