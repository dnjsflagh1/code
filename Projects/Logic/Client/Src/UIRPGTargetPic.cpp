//***************************************************************************************************
#include "stdafx.h"
#include "UIRPGTargetPic.h"
#include "CPlayer.h"
#include "CSceneManager.h"
#include "ClientMain.h"
#include "CNpcEntity.h"
#include "CMonsterEntity.h"
#include "CPlayerCharacterEntity.h"
#include "CharacterNpcList.h"
#include "CharacterList.h"
#include "SLGCameraOpCtrl.h"
#include "ArtIconResCsv.h"
//***************************************************************************************************
namespace MG
{
	UIRPGTargetPic::UIRPGTargetPic() 
		: mTargetEntity(NULL)
		,mCharacterId(0)
		,mCharacterType(GOT_UNKNOWN)
    {
    }
    //----------------------------------------------------------------------------------------
    UIRPGTargetPic::~UIRPGTargetPic()
    {
		mTargetEntity = NULL;
    }
    //----------------------------------------------------------------------------------------
    void UIRPGTargetPic::setEvent()
    {
		
		IImage* img = getLayout()->getImage("head-pic");
		DYNAMIC_ASSERT(img);
		img->getWidget()->setMouseButtonDoubleClickEvent(onDoubleClickTargetHead);
		
	}
	//----------------------------------------------------------------------------------------
	Bool UIRPGTargetPic::setCharacterId(IdType id)
	{
		//mCharacterId = id;

		if (id == 0)
		{
			return false;
		}

		setTargetMp(mCharacterId);
		//setSp(mCharacterId);
		setTargetHp(mCharacterId);

		CPlayerCharacter* playerCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(id);
		DYNAMIC_ASSERT(playerCharacter);

		setTargetName(playerCharacter->getNormalName());
        
		///设置图像
		const ArtIconResCsvInfo* tempResInfo =ArtIconResCsv::getInstance().getIconArtResInfo(playerCharacter->getData()->charArtIcon);       
		DYNAMIC_ASSERT_LOG(tempResInfo,"tempResInfo == NULL!");
		if (tempResInfo != NULL)
		{
			IImage *headimg = getLayout()->getImage("head-large01");
			headimg->setItemGroup(tempResInfo->SmallGroupName);
			headimg->setItemResource(tempResInfo->SmallResName);
			headimg->setItemName(tempResInfo->SmallItemName);
		}
		setTargetLV(playerCharacter->getLevel());
		return true;
	}
	//----------------------------------------------------------------------------------------
	void UIRPGTargetPic::setTargetMp(PlayerCharacterIdType playerCharacterId)
	{
		if ( playerCharacterId != mCharacterId)
		  return;

		CPlayerCharacter* playerCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(playerCharacterId);
		DYNAMIC_ASSERT(playerCharacter);

		setTargetMp(playerCharacter);

	}
	//----------------------------------------------------------------------------------------
	void UIRPGTargetPic::setTargetSp(PlayerCharacterIdType playerCharacterId)
	{
		//IProgress* progress = getLayout()->getProgress("process_mp");
		//DYNAMIC_ASSERT(progress);
		//if (!progress)
		//{
		//	return;
		//}

		//progress->setProgressPosition(currSP/(1.f*maxSp));
	}
	//----------------------------------------------------------------------------------------
	void UIRPGTargetPic::setTargetHp(PlayerCharacterIdType playerCharacterId)
	{
		if ( playerCharacterId != mCharacterId)
			return;

		CPlayerCharacter* playerCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(playerCharacterId);
		DYNAMIC_ASSERT(playerCharacter);
		setTargetHp(playerCharacter);

	}
	//----------------------------------------------------------------------------------------
	void UIRPGTargetPic::setTargetLV( U32 lv )
	{
		Str16 tempLV(L"");
		MGStrOp::toString(lv,tempLV);
		IText* txtlv = getLayout()->getText("lvtext-large01");
		txtlv->getWidget()->setCaption(tempLV);
	}

	void UIRPGTargetPic::setTargetHp(CPlayerCharacter* playerCharacter)
	{
		IProgress* progress = getLayout()->getProgress("HP-large01");
		DYNAMIC_ASSERT(progress);

		Flt currHp = playerCharacter->getHp();
		Flt maxHp = playerCharacter->getMaxHp();

		progress->setProgressPosition( currHp/maxHp );

		Char16 tempMpMsg[32] = {0};
		swprintf_s(tempMpMsg, 32, L"%d/%d",(Int)currHp , (Int)maxHp);
		progress->getWidget()->setCaption(tempMpMsg);
	}

	void UIRPGTargetPic::setTargetSp(CPlayerCharacter* playerCharacter)
	{

	}

	void UIRPGTargetPic::setTargetMp(CPlayerCharacter* playerCharacter)
	{
		IProgress* progress = getLayout()->getProgress("MP-large01");
		DYNAMIC_ASSERT(progress);

		Flt currMp = playerCharacter->getMp();
		Flt maxMp = playerCharacter->getMaxMp();

		progress->setProgressPosition( currMp/maxMp );

		Char16 tempMpMsg[32] = {0};
		swprintf_s(tempMpMsg, 32, L"%d/%d",(Int)currMp , (Int)maxMp);
		progress->getWidget()->setCaption(tempMpMsg);
	}

	void UIRPGTargetPic::setTargetLV(CPlayerCharacter* playerCharacter)
	{
		U32 level = (U32)playerCharacter->getLevel();
		setTargetLV(level);
	}

	//----------------------------------------------------------------------------------------
	void UIRPGTargetPic::setTargetHead( UInt index )
	{
		IImage* img = getLayout()->getImage("img_head");
		DYNAMIC_ASSERT(img);
		//get....
		//img->setItemGroup()
		//img->setItemName()
	}
	//----------------------------------------------------------------------------------------
	void UIRPGTargetPic::setTargetName( Str16 name )
	{
		IText* text = getLayout()->getText("nametext-large01");
		DYNAMIC_ASSERT(text);
		if (!text)
		{
			return;
		}
		text->getWidget()->setCaption(name);
	}
	//----------------------------------------------------------------------------------------
	void UIRPGTargetPic::onDoubleClickTargetHead( void* widget )
	{
		/*DYNAMIC_ASSERT(widget);
		IdType id = CPlayer::getInstance().getActiveClan()->getMainGenrealID();
		SLGCameraOpCtrl::getInstance().focusPos(id);*/
	}


	void UIRPGTargetPic::update(Flt delta)
	{
	       if (this->isOpen())
	       {
			    Bool isNeedClose = false;
				//
				CSceneEntity* targetEntity =  CSceneManager::getInstance().getSceneEntity(mCharacterId,mCharacterType);
				if (targetEntity != NULL)
				{
                    if (!targetEntity->isInScreen())
                    {
                           isNeedClose = true;
                    }
					else
					{
                           //重新获取实体,更新显示数据
                           setTargetEntity(targetEntity);
					}
				}
				else
				{
                    isNeedClose= true;
				}
                if (isNeedClose)
                {
					this->clear();
					this->closeGui();
                }
	       }
	}

	
	//----------------------------------------------------------------------------------------
	void UIRPGTargetPic::setTargetEntity(CSceneEntity* entity)
	{
		DYNAMIC_ASSERT(entity);
		if (entity != NULL)
		{
			mTargetEntity  =   entity;
			mCharacterType =   entity->getType();
            mCharacterId   =   entity->getID();
			//名字，头像，等级，血条，蓝条更新
			if (mCharacterType == GOT_NPC)
			{ 
				Str strTemplateID = entity->getEntity()->getCustomAttr("CharID");
				Int templateID;
				if ( strTemplateID.empty() == false )
				{
					MGStrOp::toI32(strTemplateID.c_str(),templateID);
				} 
                const CharacterTempInfo* info = CharacterTemplate::getInstance().getCharacterTempInfo(templateID);
                if (info)
                {
                  Str16 name = info->getNpcSuiName()+info->getNpcName();
				  _setTextName(name);
                  
				  UInt imgIcon =info->getCharacterArtIconId();
				  const ArtIconResCsvInfo* tempResInfo =ArtIconResCsv::getInstance().getIconArtResInfo(imgIcon);       
				  DYNAMIC_ASSERT_LOG(tempResInfo,"tempResInfo == NULL!");
				  if (tempResInfo)
				  {
                      //rpg 下用的是圆形图片，统一用small里的数据
					  _setIconImage(tempResInfo->SmallGroupName,tempResInfo->SmallResName,tempResInfo->SmallItemName);
				  }
                  
				  U32 lv = info->getCharacterLevel();
				  Str16 tempLV(L"");
				  MGStrOp::toString(lv,tempLV);
				  _setTextLevel(tempLV);
                  
				  //NPC没有hp mp 暂时写死
				  _setProgressHp(1000.0f,1000.0f);
				  _setProgressMp(1000.0f,1000.0f);

                }
			}
			else if (mCharacterType == GOT_MONSTER || mCharacterType == GOT_PLAYERCHARACTER)
			{
				CCharacterSceneEntity* charSceneEntity =  dynamic_cast<CCharacterSceneEntity*>(entity);
				DYNAMIC_ASSERT_LOG(charSceneEntity,"error: charEntityData == NULL!");

				if (charSceneEntity)
				{  
					Str16 name = charSceneEntity->getDynamicData()->surName + charSceneEntity->getDynamicData()->mName; 
					_setTextName(name);

					UInt imgIcon =charSceneEntity->getDynamicData()->charArtIcon;
					const ArtIconResCsvInfo* tempResInfo =ArtIconResCsv::getInstance().getIconArtResInfo(imgIcon);       
					DYNAMIC_ASSERT_LOG(tempResInfo,"tempResInfo == NULL!");
					if (tempResInfo != NULL)
					{
						_setIconImage(tempResInfo->SmallGroupName,tempResInfo->SmallResName,tempResInfo->SmallItemName);
					}

					U32 lv = charSceneEntity->getDynamicData()->mLevel;
					Str16 tempLV(L"");
					MGStrOp::toString(lv,tempLV);
					_setTextLevel(tempLV);

					Flt currHp = charSceneEntity->getDynamicData()->hp;
					Flt maxHp = charSceneEntity->getDynamicData()->hpmax;
					_setProgressHp(currHp,maxHp);

					Flt currMp = charSceneEntity->getDynamicData()->mp;
					Flt maxMp = charSceneEntity->getDynamicData()->mpmax;
					_setProgressMp(currMp,maxMp);
				}
			}
			
		}	
	}
	//----------------------------------------------------------------------------------------
	void UIRPGTargetPic::clear()
	{

		IText* text = getLayout()->getText("name");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setCaption(L"");
		//
		IText* txtlv = getLayout()->getText("level");
		DYNAMIC_ASSERT(txtlv);
		txtlv->getWidget()->setCaption(L"");
		//
	}

    //----------------------------------------------------------------------------------------
	void UIRPGTargetPic::_setTextName( const Str16& name )
	{
		IText* text = getLayout()->getText("name");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setCaption(name);
	}
    //----------------------------------------------------------------------------------------
	void UIRPGTargetPic::_setTextLevel( const Str16& level )
	{
		IText* txtlv = getLayout()->getText("level");
		DYNAMIC_ASSERT(txtlv);
		txtlv->getWidget()->setCaption(level);
	}
	//----------------------------------------------------------------------------------------
	void UIRPGTargetPic::_setProgressHp( const Flt currHp,const Flt maxHp )
	{
		IProgress* progress = getLayout()->getProgress("HP");
		DYNAMIC_ASSERT(progress);
		progress->setProgressPosition( currHp/maxHp );

		Char16 tempMpMsg[32] = {0};
		swprintf_s(tempMpMsg, 32, L"%d/%d",(Int)currHp , (Int)maxHp);
		progress->getWidget()->setCaption(tempMpMsg);
	}
	//----------------------------------------------------------------------------------------
	void UIRPGTargetPic::_setProgressMp( const Flt currMp,const Flt maxMp )
	{

		IProgress* progress = getLayout()->getProgress("MP");
		DYNAMIC_ASSERT(progress);
		progress->setProgressPosition( currMp/maxMp );
        
		Char16 tempMpMsg[32] = {0};
		swprintf_s(tempMpMsg, 32, L"%d/%d",(Int)currMp , (Int)maxMp);
		progress->getWidget()->setCaption(tempMpMsg);
	}
	//----------------------------------------------------------------------------------------
	void UIRPGTargetPic::_setIconImage( const Str8& groupName,const Str8& ResourceName,const Str8& ItemName )
	{
		IImage* headimg = getLayout()->getImage("head-pic");
		DYNAMIC_ASSERT(headimg);
		headimg->setItemGroup(groupName);
		headimg->setItemResource(ResourceName);
		headimg->setItemName(ItemName);
	}
}