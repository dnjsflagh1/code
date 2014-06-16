//***************************************************************************************************
#include "stdafx.h"
#include "UIInteractiveControl.h"
#include "CSceneManager.h"
#include "CSceneEntity.h"
#include "UINpc.h"
#include "UIItemShop.h"
#include "UISelectPlace.h"
#include "CPlayer.h"
#include "UIRecruitGeneral.h"
#include "UIChangeRecruit.h"
#include "CPlayerCharacterEntity.h"
//***************************************************************************************************
namespace MG
{
	
	//----------------------------------------------------------------------------------------
	UIInteractiveControl::UIInteractiveControl()
		:mTargetId(0)
		,mtargetType(GOT_UNKNOWN)
		,mOperateEntity(NULL)
	{
	}
	//----------------------------------------------------------------------------------------
	void MG::UIInteractiveControl::update(Flt delta)
	{
		if (mTargetId != 0 && mtargetType != GOT_UNKNOWN && mOperateEntity != NULL)
		{
			Bool isContinue    = true;
			Bool isNeedCloseUI = false;
			CSceneEntity* targetEntity = CSceneManager::getInstance().getSceneEntity(mTargetId,mtargetType);
			if (targetEntity != NULL)
			{
				Flt distance = targetEntity->getEntity()->getModelObject()->getWidth() + 
					mOperateEntity->getEntity()->getModelObject()->getPatherRadius() + 6.0f;
				Vec3  Pos;
				Vec3 tartgetPos;
				mOperateEntity->getWorldPos(Pos);
				Pos.y = 0;
				targetEntity->getWorldPos(tartgetPos);
				tartgetPos.y = 0;
				Pos -= tartgetPos;
				Flt length = Pos.length();
				//超过一定距离关闭交互窗口
				if (length >= distance ) 
				{
					isNeedCloseUI =true;
                    isContinue   = false;
				}
				if (isContinue)
                {
                      CPlayerCharacterEntity* playerCharEntity = dynamic_cast<CPlayerCharacterEntity*>(mOperateEntity);
					  if (playerCharEntity)
					  {   
						  //战斗状态
						  if (playerCharEntity->getDynamicData()->isFightState)
						  {
							  isNeedCloseUI = true;
							  isContinue   = false;
						  }
					  }
                }
				//
			}
			else
			{
				isNeedCloseUI = true;
                isContinue   = false;
			}
			//
			if (isNeedCloseUI)
			{    
				//关闭与NPC相关的UI界面
				closeUIByType(mtargetType);
				//clear
				clear();
			}
		}
		
	}
	//----------------------------------------------------------------------------------------
	void UIInteractiveControl::setInteractiveObject( U64 targetId,U64 operateEntityID,GAMEOBJ_TYPE targetType )
	{   
		//暂时过滤掉
		if (operateEntityID != mOperateEntityID)
		{
           CSceneEntity* entity = CSceneManager::getInstance().getSceneEntity(operateEntityID,GOT_PLAYERCHARACTER);
		   DYNAMIC_ASSERT_LOG(entity,"error: operateEntity == NULL!");
		   if (entity)
		   {
			   mOperateEntity = entity;  
			   mOperateEntityID = operateEntityID;
		   }
		}
         mTargetId = targetId;
		 mtargetType = targetType;
	}
	//----------------------------------------------------------------------------------------
	void UIInteractiveControl::clear()
	{
        mTargetId = 0;
		mtargetType = GOT_UNKNOWN;

	}
	//----------------------------------------------------------------------------------------
	void UIInteractiveControl::clearInteractiveInfo()
	{
		mOperateEntityID = 0;
		mOperateEntity =NULL;
		mTargetId = 0;
		mtargetType = GOT_UNKNOWN;

	}
	//----------------------------------------------------------------------------------------
	void UIInteractiveControl::closeUIByType( GAMEOBJ_TYPE targetType )
	{
		if (targetType == GOT_NPC)
		{  
			if (UINpc::getInstance().isOpen())
			{
				UINpc::getInstance().closeGui();
			}
			if (UIItemShop::getInstance().isOpen())
			{
				UIItemShop::getInstance().closeGui();
			}
			if (UIRecruitGeneral::getInstance().isOpen())
			{
				UIRecruitGeneral::getInstance().closeGui();
			}
			if (UIChangeRecruit::getInstance().isOpen())
			{
				UIChangeRecruit::getInstance().closeGui();
			}

		}
		else if (targetType == GOT_ORDINARY_BUILDING)
		{
			if (UISelectPlace::getInstance().isOpen())
			{
				UISelectPlace::getInstance().closeGui();
			}
		}
	}
	//----------------------------------------------------------------------------------------
}
