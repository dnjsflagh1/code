//**********************************************************************************************************
#include "stdafx.h"
#include "ClanItems.h"
#include "PlayerItemFactory.h"
#include "PlayerItem.h"
#include "ItemTemplate.h"
//**********************************************************************************************************
namespace MG
{
    //--------------------------------------------------------------------------------------------
    void        ClanItems::addItem( PlayerItem* pItem, Bool isServer )
    {
        pItem->setCharacterID(0);
        pItem->setItemPos(ITEM_SITE_TYPE_CLAN);

        Items::addItem(pItem);  
    }

	//--------------------------------------------------------------------------------------------
	MG::Bool ClanItems::checkIsNeedOverlay( U32 itemTemplateId )
	{ 
		 const ItemInfo* mItemInfo = ItemTemplate::getInstance().getItemInfo(itemTemplateId);
         return (mItemInfo->getItemBaseMaxPileNum() > 1);
	}
	//--------------------------------------------------------------------------------------------
	MG::Bool ClanItems::checkCanAddWhenNeddOverlay(U32 itemTemplateId, U32 itemAddNum )
	{
		std::vector<PlayerItem*> sameTemplateItemList;
        findItemByTemplateId(itemTemplateId,sameTemplateItemList);
		
		//该模版类型的最大堆叠数
		const ItemInfo* mItemInfo = ItemTemplate::getInstance().getItemInfo(itemTemplateId);
		U32 maxOverlayNum = mItemInfo->getItemBaseMaxPileNum();
		//剩余空格位
		U32 residuePos = getItemResidueNum();
		if (sameTemplateItemList.size() > 0)
		{
            U32 tempItemNum  = 0;
			std::vector<PlayerItem*>::iterator front = sameTemplateItemList.begin();
			std::vector<PlayerItem*>::iterator back = sameTemplateItemList.end();
			while(front != back)
			{
				tempItemNum = maxOverlayNum -((*front)->getItemNum());
				while( tempItemNum < maxOverlayNum)
				{
					tempItemNum++;
					itemAddNum --;
					if (itemAddNum == 0)
					{
						return true;
					}
				}

				front++;
			}

			if (itemAddNum < residuePos*maxOverlayNum)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (itemAddNum < residuePos*maxOverlayNum)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//return false;
		

	}
	//--------------------------------------------------------------------------------------------
	Bool ClanItems::checkClanItemsCanAdd( U32 itemTemplateId,U32 num )
	{
		  
          if (checkIsNeedOverlay(itemTemplateId))   
          {
                return checkCanAddWhenNeddOverlay(itemTemplateId,num); //堆叠
          }
		  else
		  {
			  return checkCanAdd(num);                                 //不能堆叠只需要判断是否有空格位
		  }
	}
	//--------------------------------------------------------------------------------------------
	MG::Bool ClanItems::checkClanItemsCanAdd( std::vector<ItemNum>& itemVector )
	{
		//剩余空各位
		U32 residuePos = getItemResidueNum();
		std::vector<PlayerItem*> sameTemplateItemList;
	
		//
		std::vector<ItemNum>::iterator front = itemVector.begin();
		std::vector<ItemNum>::iterator back = itemVector.end();
		while (front != back)
		{
			U32 itemTemplateId = (*front).itemTemplate;
			U32 AddNum            = (*front).num;
			if (checkIsNeedOverlay(itemTemplateId))   
			{
				 //堆叠
				const ItemInfo* mItemInfo = ItemTemplate::getInstance().getItemInfo(itemTemplateId);
				U32 maxOverlayNum = mItemInfo->getItemBaseMaxPileNum();
                 findItemByTemplateId(itemTemplateId,sameTemplateItemList);
				 if (sameTemplateItemList.size() > 0)
				 {   
					 std::vector<PlayerItem*>::iterator front = sameTemplateItemList.begin();
					 std::vector<PlayerItem*>::iterator back = sameTemplateItemList.end();
					 while(front != back)
					 {
						 U32 tempItemNum = maxOverlayNum -((*front)->getItemNum());
						 while( tempItemNum < maxOverlayNum)
						 {
							 tempItemNum++;
							 AddNum --;
							 if (AddNum == 0)
							 {
								 break;
							 }
						 }
						 if (AddNum == 0)
						 {
							break;
						 } 
						 if (AddNum < residuePos*maxOverlayNum)
						 {
							residuePos = residuePos - (AddNum/maxOverlayNum);
						 }
						 else
						 {
                             return false;
						 }
						 front++;
					 }
                         
				 }
				 else
				 {
                     if (AddNum < residuePos*maxOverlayNum)
                     {
						residuePos = residuePos - (AddNum/maxOverlayNum);
                     }
					 else
					 {
						 return false;
					 }
				 }
				  
			}
			else
			{     //不能堆叠
                  if (residuePos >= AddNum)
                  {
                       residuePos -= AddNum;
                  }
				  else if ((residuePos == 0)
					  || (residuePos < AddNum))
				  {
					  return false;
				  }
				  
			}

			
			front++;
		}

		return true;

	}
	//--------------------------------------------------------------------------------------------
	MG::Bool ClanItems::checkItemExistInClanBag( U32 itemTemplateId,U32 num )
	{
         Bool flag = false;
		 std::vector<PlayerItem*> sameTemplateItemList;
		 findItemByTemplateId(itemTemplateId,sameTemplateItemList);
		 if (sameTemplateItemList.size() >0 )
		 { 
			  U32 tempNum = 0;
			  std::vector<PlayerItem*>::iterator front = sameTemplateItemList.begin();
			  std::vector<PlayerItem*>::iterator back = sameTemplateItemList.end();
			  while (front != back)
			  {
                  tempNum += (*front)->getItemNum();
				  front++;
			  }
              if (tempNum >= num)
              {
                   flag =true;
              }
		 }

		 return flag;

         
	}
	//--------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------
}