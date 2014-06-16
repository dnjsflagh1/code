//***********************************************************************************************************
#include "stdafx.h"
#include "UICommon.h"
#include "HeadDes.h"
#include "ClientMain.h"
#include "CSceneManager.h"
#include "CharacterList.h"
#include "ItemTemplate.h"
#include "CPlayer.h"
#include "ArtIconResCsv.h"
#include "CCharacterSceneEntity.h"
#include "CPlayerCharacterEntity.h"
#include "COrdinaryBuildingEntity.h"
#include "CNpcEntity.h"
#include "CBuildingEntity.h"
#include "CTroopEntity.h"
#include "CItemEntity.h"
#include "ItemData.h"
#include "CMonsterEntity.h"
#include "MonsterData.h"
#include "CRegionManager.h"
#include "CPlaceObject.h"
//***********************************************************************************************************
#define  CORRECT_HEIGHT   1.1
//***********************************************************************************************************
namespace MG
{
    HeadDes::HeadDes( CSceneEntity* pParent )
        :mParent(pParent)
		,mBackImg(NULL)			
		,mCharacterSpeakImg(NULL)	
		,mFlagImg(NULL)			
		,mCharacterSpeakEdit(NULL)	
		,mOptionalText(NULL)		
		,mName(NULL)				
		,mHpProcess(NULL)			
		,mInit(false)				
		,mCharacterTempInfo(NULL)
		,mItemIempInfo(NULL)
		,mIsPressTab(false)
		,mIsTemplateCharacter(false)
		,mIsVisible(true)
    {

    }
    //------------------------------------------------------------------------------------
    HeadDes::~HeadDes()
    {
        //clear();
    }
    //------------------------------------------------------------------------------------
    void HeadDes::update()
    {
		if ( !mInit || !mIsVisible )
			return;

		hide();

		if ( calBasePoint() == false )
			return;

		////检测Tab键是否按下，设置血条的显示
		//if( ClientMain::getInstance().getEngine()->input()->isKeyHolded( KC_TAB ) )
		//{
		//	mIsPressTab = true;
		//	if ( mHpProcess )
		//		mHpProcess->getWidget()->setVisible(true);
		//}
		//else
		//{
		//	mIsPressTab = false;
		//	if ( mHpProcess )
		//		mHpProcess->getWidget()->setVisible(false);
		//}

		if ( mIsTemplateCharacter )
		{
			if ( mParent->getType() == GOT_PLAYERCHARACTER ) 
			{
				updateTemplateCharacter();
			}
		}
		else
		{
			//更新对象的描述信息
			if ( mParent->getType() == GOT_PLAYERCHARACTER ) 
			{
				updatePlayerCharacter();
			}
			else if (mParent->getType() == GOT_NPC)
			{
				updateNpc();
			}
			else if ( mParent->getType() == GOT_TROOP )
			{
				//updateTroop();
			}
			else if (mParent->getType() == GOT_ITEM)
			{
				//
				updateItem();
			}
			else if (mParent->getType() == GOT_MONSTER)
			{
				//
				updateMonster();
			}
			else if (mParent->getType() == GOT_ORDINARY_BUILDING)
			{
				updateRotPlace();
			}
		}

		
    }
    //------------------------------------------------------------------------------------
    void HeadDes::init()
    {
        ///显示最大时间 当前消耗时间
        mCharacterSpeakMaxTime = 5 * 1000;
        mCharacterSpeakCurrTime = mCharacterSpeakMaxTime;

        ///基点
        mBasePoint = Vec2(0,0);

		GAMEOBJ_TYPE type = mParent->getType();      
		
        switch (type)
        {
        case GOT_PLAYERCHARACTER:
            {
                if ( mCharacterTempInfo == NULL )
                    mCharacterTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo( ( (CCharacterSceneEntity*)mParent )->getDynamicData()->mCharacterTemplateID );
                DYNAMIC_ASSERT(mCharacterTempInfo);
                CPlayerCharacterEntity* pCharEntity = dynamic_cast<CPlayerCharacterEntity*>(mParent);
				DYNAMIC_ASSERT(pCharEntity);
                initName(type,pCharEntity->getDynamicData()->surName + pCharEntity->getDynamicData()->mName );   //名字 和 姓
                initOptional(mCharacterTempInfo);
                initHeadFlag();
                initSpeak(mCharacterTempInfo);
                initHp();
            }
        	break;
        case GOT_TROOP:
            {
                //if ( mCharacterTempInfo == NULL )
                    //mCharacterTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo( ( (CTroopObject*)mParent )->getBaseData()->mCharacterTemplateID );
                //DYNAMIC_ASSERT(mCharacterTempInfo);
                //initName(type, mCharacterTempInfo->getCharacterSurName());
				//军队暂时不要血条。
                //initHp();
            }
            break;
        case GOT_NPC:
            {
                if ( mCharacterTempInfo == NULL )
                {  
                    Str strTemplateID = mParent->getEntity()->getCustomAttr("CharID");
                    Int templateID;
                    if ( strTemplateID.empty() == false )
                    {
                        MGStrOp::toI32(strTemplateID.c_str(),templateID);
                    } 
                    mCharacterTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(templateID);
                }
                if ( mCharacterTempInfo )
                {
                    initName(type,mCharacterTempInfo->getNpcSuiName() + mCharacterTempInfo->getNpcName());
                    initOptional(mCharacterTempInfo);
                    initHeadFlag();
                    initSpeak(mCharacterTempInfo);
                }
                else
                    return;
            }
            break;
        case GOT_ITEM:
            {   
				CItemEntity* pItemEntity = dynamic_cast<CItemEntity*>(mParent);
				if (mItemIempInfo == NULL)
				{
					mItemIempInfo = ItemTemplate::getInstance().getItemInfo(pItemEntity->getDynamicData()->mItemTemplateId);
					DYNAMIC_ASSERT_LOG(mItemIempInfo,"mItemIempInfo == NULL");
					if (mItemIempInfo == NULL)
					{
						return;
					}
				}
				if (mItemIempInfo)
				{
					initName(type,mParent->getName());
					initHeadFlag();
				}
                
            }
            break;
			
        case GOT_MONSTER:
            { 
				CMonsterEntity* pMonsterEntity = dynamic_cast<CMonsterEntity*>(mParent);
				if (mCharacterTempInfo == NULL)
				{
					mCharacterTempInfo =CharacterTemplate::getInstance().getCharacterTempInfo(pMonsterEntity->getDynamicData()->mCharacterTemplateID);
					DYNAMIC_ASSERT_LOG(mCharacterTempInfo,"mItemIempInfo == NULL");
					if (mCharacterTempInfo == NULL)
					{
						return;
					}
				}
				if (mCharacterTempInfo)
				{
					Str16 strLevel;
					MGStrOp::toString(mCharacterTempInfo->getCharacterLevel(),strLevel);
					//名字(等级)
					initName(type,mCharacterTempInfo->getMonsterSuiName() + mCharacterTempInfo->getMonsterName() 
						+ L"("+ strLevel + L"级)");
					initHeadFlag();
				}
                
            }
            break;
		case GOT_ORDINARY_BUILDING:
			{

				 COrdinaryBuildingEntity* ordinaryBuildingEntity = dynamic_cast<COrdinaryBuildingEntity*>(mParent);
                 if (ordinaryBuildingEntity)
                 {
                       if (ordinaryBuildingEntity->getDynamicData()->buildingType == OBLT_PLACE)
                       {
						   Str strPlaceID = mParent->getEntity()->getCustomAttr("PlaceID");
						   Int temPlaceID;
						   if ( strPlaceID.empty() == false && strPlaceID.length() > 0 )
						   {
							   MGStrOp::toI32(strPlaceID.c_str(),temPlaceID);

							   CRegionObject* regionObj = CRegionManager::getInstance().getRegionObjectById(ROT_PLACE,temPlaceID);
							  // DYNAMIC_ASSERT_LOG(regionObj,"error: regionObj == NULL!");
							   if (regionObj)
							   {  
								   CPlaceObject* placeObj   = dynamic_cast<CPlaceObject*>(regionObj);
								   Str16 name = placeObj->getPlaceData()->getPlaceListCsvInfo()->placeName + 
									   placeObj->getPlaceData()->getPlaceListCsvInfo()->placeTitle;
								   initName(type,name);
								   initHeadFlag();
							   }
						   }
                       }
                 }
				
			}
			break;
        }

        mInit = true;
		
    }
    //------------------------------------------------------------------------------------
    void HeadDes::clear()
    {
		if ( mBackImg )
			ClientMain::getInstance().getGui()->destroyImage(mBackImg);
		if ( mCharacterSpeakImg )
			ClientMain::getInstance().getGui()->destroyImage(mCharacterSpeakImg);
		if ( mFlagImg )
			ClientMain::getInstance().getGui()->destroyImage(mFlagImg);
		if ( mCharacterSpeakEdit )
			ClientMain::getInstance().getGui()->destroyEdit(mCharacterSpeakEdit);
		if ( mName )
			ClientMain::getInstance().getGui()->destroyText(mName);
		if ( mOptionalText )
			ClientMain::getInstance().getGui()->destroyText(mOptionalText);
		if ( mHpProcess )
			ClientMain::getInstance().getGui()->destroyProgress(mHpProcess);
    }
	//------------------------------------------------------------------------------------
	void HeadDes::updateTemplateCharacter()
	{
		///设置图标
		Vec2 flagImgPos;
		if ( mFlagImg )
		{
			flagImgPos.x = mBasePoint.x - mFlagImgSize.x / 2;
			flagImgPos.y = mBasePoint.y - mOptionalTextSize.y - mNameTextSize.y - mFlagImgSize.y;
			mFlagImg->getWidget()->setPosition(flagImgPos);
			mFlagImg->getWidget()->setVisible(true);
		}
	}
	//------------------------------------------------------------------------------------
    void HeadDes::updatePlayerCharacter()
    {
        CPlayerCharacterEntity* entity = (CPlayerCharacterEntity*)mParent;
        
		///计算血条位置
		Vec2 hpProcessPos;
		if ( mHpProcess )
		{
			hpProcessPos.x = mBasePoint.x - mHpProcessSize.x / 2;
			hpProcessPos.y = mBasePoint.y - mHpProcessSize.y;
			mHpProcess->getWidget()->setPosition(hpProcessPos);

			Flt maxHp = entity->getHpMax();
			Flt currHp = entity->getHp();

			mHpProcess->setProgressPosition(currHp/maxHp/*(1.f*maxHp)*/);
			mHpProcess->getWidget()->setVisible(true);
		}
		//角色的描述内容
		///计算可选文字位置
		Vec2 optionalTextPos;

		if ( mOptionalText )
		{
			if (mCurrType == HEADDES_OPTIONALTEXT_TYPE_NULL )
			{
				mOptionalText->getWidget()->setVisible(false);
			}
			else
			{
				optionalTextPos.x = mBasePoint.x - mOptionalTextSize.x / 2;
				optionalTextPos.y = mBasePoint.y - mHpProcessSize.y - mOptionalTextSize.y;
				mOptionalText->getWidget()->setPosition(optionalTextPos);

				mOptionalText->getWidget()->setVisible(true);
			}
		}
		
		///计算名字位置
		Vec2 nameTextPos;
		if ( mName )
		{
			nameTextPos.x = mBasePoint.x - mNameTextSize.x / 2;
			nameTextPos.y = mBasePoint.y - mHpProcessSize.y - mOptionalTextSize.y - mNameTextSize.y;
			mName->getWidget()->setPosition(nameTextPos);
			mName->getWidget()->setVisible(true);
		}
		//mFlagImg->getWidget()->setVisible(false);
		//static U64 startTime = 0;
		//if (mCharacterSpeakCurrTime == 0)
		//{
		//	mCharacterSpeakCurrTime = 1;
		//	startTime = MGTimeOp::getCurrTick();
		//	mBackImg->getWidget()->setVisible(true);
		//	mCharacterSpeakImg->getWidget()->setVisible(true);
		//	mCharacterSpeakEdit->getWidget()->setVisible(true);
		//}
 
		//if (mCharacterSpeakCurrTime >= mCharacterSpeakMaxTime)
		//{
		//	mBackImg->getWidget()->setVisible(false);
		//	mCharacterSpeakImg->getWidget()->setVisible(false);
		//	mCharacterSpeakEdit->getWidget()->setVisible(false);
		//}
		//else
		//{
		//	U64 currTime = MGTimeOp::getCurrTick();
		//	mCharacterSpeakCurrTime += (currTime - startTime);
		//	startTime = currTime;
		//}

		//Vec2 backImgPos;
		//backImgPos.x = mBasePoint.x - (mSpeakEditSize.x + mSpeakImageSize.x) / 2;
		//backImgPos.y = mBasePoint.y - mHpProcessSize.y - mOptionalTextSize.y - mNameTextSize.y - mBackImgSize.y;
		//mBackImg->getWidget()->setPosition(backImgPos);
		//Vec2 characterSpeakImgPos;
		//characterSpeakImgPos.x = backImgPos.x;
		//characterSpeakImgPos.y = backImgPos.y + 0.5 * (mBackImgSize.y - mSpeakImageSize.y);
		//mCharacterSpeakImg->getWidget()->setPosition(characterSpeakImgPos);

		//Vec2 characterSpeakEditPos;
		//characterSpeakEditPos.x = backImgPos.x + mSpeakImageSize.x;
		//characterSpeakEditPos.y = backImgPos.y + 1;
		//mCharacterSpeakEdit->getWidget()->setPosition(characterSpeakEditPos);

    }
    //------------------------------------------------------------------------------------
    void HeadDes::resetParent( CSceneEntity* pParent )
    {
        mParent = pParent;
    }
	//------------------------------------------------------------------------------------
	void HeadDes::setVisible( bool visible )
	{
		if (mBackImg)
		{
			mBackImg->getWidget()->setVisible(visible);
		}
		if (mCharacterSpeakImg)
		{
			mCharacterSpeakImg->getWidget()->setVisible(visible);
		}
		if (mFlagImg)
		{
			mFlagImg->getWidget()->setVisible(visible);
		}
		if (mCharacterSpeakEdit)
		{
			mCharacterSpeakEdit->getWidget()->setVisible(visible);
		}
		if (mName)
		{
			mName->getWidget()->setVisible(visible);
		}
		if (mOptionalText)
		{
			mOptionalText->getWidget()->setVisible(visible);
		}
		if (mHpProcess)
		{
			mHpProcess->getWidget()->setVisible(visible);
		}

		mIsVisible = visible;
	}
	//------------------------------------------------------------------------------------
	void HeadDes::hide()
	{
		if (mBackImg)
		{
			mBackImg->getWidget()->setVisible(false);
		}
		if (mCharacterSpeakImg)
		{
			mCharacterSpeakImg->getWidget()->setVisible(false);
		}
		if (mFlagImg)
		{
			mFlagImg->getWidget()->setVisible(false);
		}
		if (mCharacterSpeakEdit)
		{
			mCharacterSpeakEdit->getWidget()->setVisible(false);
		}
		if (mName)
		{
			mName->getWidget()->setVisible(false);
		}
		if (mOptionalText)
		{
			mOptionalText->getWidget()->setVisible(false);
		}
		if (mHpProcess)
		{
			mHpProcess->getWidget()->setVisible(false);
		}
	}
	//------------------------------------------------------------------------------------
    void HeadDes::closeDes()
    {
		hide();
		
		mInit = false;
        mCharacterTempInfo = NULL;
		mItemIempInfo      = NULL;
		
    }
	//------------------------------------------------------------------------------------
	void HeadDes::setBackImg( UInt id )
	{
		const ArtIconResCsvInfo* iconInfo = ArtIconResCsv::getInstance().getIconArtResInfo(id);
		if (mBackImg && iconInfo)
		{
			mBackImg->setItemResource(iconInfo->ResName);
			mBackImg->setItemGroup(iconInfo->GroupName);
			mBackImg->setItemName(iconInfo->ItemName);
		}
		else
		{
			mBackImg->setItemResource("pic_Icon7");
			mBackImg->setItemGroup("Icons");
			mBackImg->setItemName("1");
		}
	}	
	//------------------------------------------------------------------------------------
	void HeadDes::setSpeakImg( UInt id )
	{
		if (!mCharacterSpeakImg)
		{
			return;
		}
		const ArtIconResCsvInfo* iconInfo = ArtIconResCsv::getInstance().getIconArtResInfo(id);
		if (iconInfo)
		{
			mCharacterSpeakImg->setItemResource(iconInfo->ResName);
			mCharacterSpeakImg->setItemGroup(iconInfo->GroupName);
			mCharacterSpeakImg->setItemName(iconInfo->ItemName);
		}
		else
		{
			mCharacterSpeakImg->setItemResource("pic_person_head");
			mCharacterSpeakImg->setItemGroup("Icons");
			mCharacterSpeakImg->setItemName("male");
		}		

	}
	//------------------------------------------------------------------------------------
	void HeadDes::setSpeakContent( Str16& content )
	{
		if (!mCharacterSpeakEdit)
		{
			return;
		}
		
		Str16 temp = content;
		Int lineCount = 1;
		Int size = temp.size();
		U32 len = 0;
		Str16 tempChar = L"";
		Int i = 0;
		for (; i < size; i++)
		{
			tempChar = temp.at(i);
			len += ClientMain::getInstance().getGui()->getLengthStr(tempChar);
			if (len > mSpeakEditSize.x - 10)
			{
				if (lineCount >= 3)
				{
					break;
				}
				len = 0;
				temp.insert(i,L"\n");
				lineCount++;
				i++;
			}
		}
		mCharacterSpeakEdit->getWidget()->setCaption(temp.substr(0,i - 1));
		mCharacterSpeakCurrTime = 0;
		mCharacterSpeakMaxTime = mCharacterSpeakMaxTime;

	}
	//------------------------------------------------------------------------------------
	void HeadDes::setMaxSpeakTime( U32 time )
	{
		mCharacterSpeakMaxTime = time;
	}
	//------------------------------------------------------------------------------------
	void HeadDes::setFlagImg( UInt id )
	{
		if (!mFlagImg)
		{
			return;
		}
		const ArtIconResCsvInfo* iconInfo = ArtIconResCsv::getInstance().getIconArtResInfo(id);
		if (iconInfo)
		{
			mFlagImg->setItemResource(iconInfo->ResName);
			mFlagImg->setItemGroup(iconInfo->GroupName);
			mFlagImg->setItemName(iconInfo->ItemName);
		}
		else
		{
			mFlagImg->setItemResource("");
			mFlagImg->setItemGroup("");
			mFlagImg->setItemName("");
		}	
	}
	//------------------------------------------------------------------------------------
	void HeadDes::setOptionalTextType( HEADDES_OPTIONALTEXT_TYPE type )
	{
		mCurrType = type;
		U32 len = 0;
		Str16 temp;
		if (mCurrType == HEADDES_OPTIONALTEXT_TYPE_TITEL)
		{
			if ( mCharacterTempInfo )
            {
                temp = mCharacterTempInfo->getCharacterTitle();
                len = ClientMain::getInstance().getGui()->getLengthStr(temp);
                mOptionalTextSize.x = len + 1;
            }	
		}
		else if (mCurrType == HEADDES_OPTIONALTEXT_TYPE_TIPS)
		{
			if ( mCharacterTempInfo )
            {
                temp = mCharacterTempInfo->getCharacterTips();
                len = ClientMain::getInstance().getGui()->getLengthStr(temp);
                mOptionalTextSize.x = len + 1;
            }
		}
		mOptionalText->getWidget()->setCaption(temp);
		mOptionalText->getWidget()->setSize(mOptionalTextSize);
	}
	//------------------------------------------------------------------------------------
	void HeadDes::setOptionalText( Str16& content )
	{
		//只有一行 截断处理
		Str16 temp = content;
		Int size = temp.size();
		U32 len = 0;
		Str16 tempChar = L"";
		Int i = 0;
		for (; i < size; i++)
		{
			tempChar = temp.at(i);
			len += ClientMain::getInstance().getGui()->getLengthStr(tempChar);
			if (len > mOptionalTextSize.x - 10)
			{
				break;
			}
		}
		mOptionalText->getWidget()->setCaption(temp.substr(0,i - 1));
		
	}
	//------------------------------------------------------------------------------------
	void HeadDes::setHeight( Flt height )
	{
		mHeightAboveParent = height+CORRECT_HEIGHT;
	}
	//------------------------------------------------------------------------------------
	void HeadDes::updateNpc()
	{
		///计算可选文字位置
		Vec2 optionalTextPos;
		if ( mOptionalText )
		{
			if (mCurrType == HEADDES_OPTIONALTEXT_TYPE_NULL)
			{
				mOptionalText->getWidget()->setVisible(false);
			}
			else
			{
				optionalTextPos.x = mBasePoint.x - mOptionalTextSize.x / 2;
				optionalTextPos.y = mBasePoint.y - mOptionalTextSize.y;
				mOptionalText->getWidget()->setPosition(optionalTextPos);
				mOptionalText->getWidget()->setVisible(true);
			}
		}

		///计算名字位置
		Vec2 nameTextPos;
		if ( mName )
		{
			nameTextPos.x = mBasePoint.x - mNameTextSize.x / 2;
			nameTextPos.y = mBasePoint.y - mOptionalTextSize.y - mNameTextSize.y;
			mName->getWidget()->setPosition(nameTextPos);
			mName->getWidget()->setVisible(true);
		}

		///设置图标
		Vec2 flagImgPos;
		if ( mFlagImg )
		{
			flagImgPos.x = mBasePoint.x - mFlagImgSize.x / 2;
			flagImgPos.y = mBasePoint.y - mOptionalTextSize.y - mNameTextSize.y - mFlagImgSize.y;
			mFlagImg->getWidget()->setPosition(flagImgPos);
			mFlagImg->getWidget()->setVisible(true);
		}
		
	}
    //------------------------------------------------------------------------------------
    void HeadDes::updateBattleBuild()
    {
        CBuildingEntity* entity = (CBuildingEntity*)mParent;

        ///计算血条位置
        Vec2 hpProcessPos;
        //hpProcessPos.x = mBasePoint.x - mHpProcessSize.x / 2;
        //hpProcessPos.y = mBasePoint.y - mHpProcessSize.y;
        //mHpProcess->getWidget()->setPosition(hpProcessPos);

        //Int maxHp = 100/*(dynamic_cast<Character*>(mParent))->getFanalValue(ATTR_ID_HpMax)*/;
        //Int currHp = entity->getDynamicData()->hp;

        //mHpProcess->setProgressPosition(currHp/(1.f*maxHp));

		if ( mOptionalText )
		{
			if (mCurrType == HEADDES_OPTIONALTEXT_TYPE_NULL)
			{
				mOptionalText->getWidget()->setVisible(false);
			}
			else
			{
				mOptionalText->getWidget()->setVisible(true);
			}
		}

        ///计算名字位置
        Vec2 nameTextPos;
		if ( mName )
		{
			nameTextPos.x = mBasePoint.x - mNameTextSize.x / 2;
			nameTextPos.y = mBasePoint.y - mHpProcessSize.y - mNameTextSize.y;
			mName->getWidget()->setPosition(nameTextPos);
			mName->getWidget()->setVisible(true);
		} 
    }
    //------------------------------------------------------------------------------------
    void HeadDes::initName(GAMEOBJ_TYPE type, Str16 name)
    {

		 mNameTextSize = Vec2(100, 14);
        ///设置目标名字
        if (!mName)
        {
            mName = ClientMain::getInstance().getGui()->getText(NULL,CoordI(0, 0, 0, 0), L"");
        }
        if (type == GOT_PLAYERCHARACTER)
        {

            mName->setTextColour(Color(4,2,34,255));
        }
        else if (type == GOT_NPC)
        {  
			//NPC统一显示绿色
            mName->setTextColour(COLOR_GREEN);
        }
        else if (type == GOT_BUILDING)
        { 
            mName->setTextColour(Color(36,15,0,255));
        }
		else if (type == GOT_ITEM)
		{
			U32 rank = 0;
			Color tempColor(1.f, 1.f, 1.f, 1.f);
			//计算名字的长度
			U32 length = ClientMain::getInstance().getGui()->getLengthStr(name);
			mNameTextSize.x = length;
           //分品质显示颜色
           if (mItemIempInfo)
           {
             rank = mItemIempInfo->getItemBaseRank();
			 switch (rank)
			 {
			 case ITEM_RANK_WHITE:
				 tempColor = /*Color(1.f, 0.f, 0.f,1.f);*/COLOR_WHITE;
				 break;
			 case ITEM_RANK_GREEN:
				 tempColor = /*Color(0.f, 1.f, 0.f, 1.f)*/COLOR_GREEN;
				 break;
			 case ITEM_RANK_BLUE:
				 tempColor = /*Color(0.f, 0.f, 1.f, 0.f);*/COLOR_BLUE;
				 break;
			 case ITEM_RANK_PURPLE:
				 tempColor = /*Color(175/255.f, 0.f, 1.f, 1.f);*/COLOR_PURPLE;
				 break;
			 default:
				 DYNAMIC_ASSERT(0);
				 break;
			 }

           }
		   mName->setTextColour(tempColor);
		}
		else if (type == GOT_MONSTER)
		{
		   Byte nameColorType = mCharacterTempInfo->getMonsterNameColorType();
		   Color tempColor(1.f, 1.f, 1.f, 1.f);
		   //主动  红色
		   if (nameColorType == 1)
		   {
                tempColor = COLOR_RED;
		   }
		   //被动  黄色
		   else if (nameColorType == 2)
		   {
			   tempColor = COLOR_YELLOW;
		   }
           mName->setTextColour(tempColor);
		}
		else if (type == GOT_ORDINARY_BUILDING)
		{
           mName->setTextColour(COLOR_GREEN);
		}

        mName->getWidget()->setCaption(name);
        mName->getWidget()->setSize(mNameTextSize);
		mName->setTextAlign(MGAlign::Center);
        mName->getWidget()->setVisible(true);
    }
    //------------------------------------------------------------------------------------
    void HeadDes::initSpeak(const CharacterTempInfo*& charTemp)
    {
        ///设置喊话界面
        if (!mBackImg)
        {
            mBackImg = ClientMain::getInstance().getGui()->getImage( CoordI(0, 0, 0, 0), "");
        }
        if (!mCharacterSpeakImg)
        {
            mCharacterSpeakImg = ClientMain::getInstance().getGui()->getImage(CoordI(0, 0, 0, 0), "");
        }
        if (!mCharacterSpeakEdit)
        {
            mCharacterSpeakEdit = ClientMain::getInstance().getGui()->getEdit(NULL, CoordI(0, 0, 0, 0), L"");
        }
        mSpeakImageSize = Vec2(30,30);
        mSpeakEditSize = Vec2(184,56);
        mBackImgSize = Vec2(224,56);
        mBackImg->getWidget()->setAlpha(0.3);
        mBackImg->getWidget()->setSize(mBackImgSize);
        mCharacterSpeakEdit->setEditStatic(true);
        mCharacterSpeakEdit->setEditMultiLine(true);
        mCharacterSpeakEdit->getWidget()->setSize(mSpeakEditSize);
        mCharacterSpeakImg->getWidget()->setSize(mSpeakImageSize);
        setBackImg(0);
        setSpeakImg(charTemp->getCharacterArtIconId());
        mCharacterSpeakEdit->setTextAlign(MGAlign::Center);
        mBackImg->getWidget()->setVisible(false);
        mCharacterSpeakImg->getWidget()->setVisible(false);
        mCharacterSpeakEdit->getWidget()->setVisible(false);
        mBackImg->getWidget()->setVisible(false);
    }
    //------------------------------------------------------------------------------------
    void HeadDes::initHeadFlag()
    {
        ///头顶标记
        if (!mFlagImg)
        {
            mFlagImg = ClientMain::getInstance().getGui()->getImage(CoordI(0, 0, 0, 0), "");
        }	
        mFlagImgSize = Vec2(40,40);
        mFlagImg->getWidget()->setSize(mFlagImgSize);
        mFlagImg->getWidget()->setVisible(true);
        setFlagImg(0);
    }
    //------------------------------------------------------------------------------------
    void HeadDes::initHp()
    {
        if (!mHpProcess)
        {
            mHpProcess = ClientMain::getInstance().getGui()->getProgress(CoordI(0, 0, 0, 0), 100,100);
            mHpProcess->setTexture("Main_Area_HpMp", "Larges", "HP");
        }	
        mHpProcessSize = Vec2(50,6);
        mHpProcess->getWidget()->setSize(mHpProcessSize);
        mHpProcess->getWidget()->setVisible(true);
    }
    //------------------------------------------------------------------------------------
    void HeadDes::initOptional(const CharacterTempInfo*& charTemp)
    {
        ///玩家自选内容  
        if (!mOptionalText)
        {
            mOptionalText = ClientMain::getInstance().getGui()->getText(NULL, CoordI(0, 0, 0, 0), L"");
        }	
        mCurrType = HEADDES_OPTIONALTEXT_TYPE_TITEL;
        mOptionalTextSize = Vec2(140, 14);
        mOptionalText->setTextAlign(MGAlign::Center);
        mOptionalText->getWidget()->setCaption(charTemp->getCharacterTitle());
        U32 len = ClientMain::getInstance().getGui()->getLengthStr(charTemp->getCharacterTitle());
        mOptionalTextSize.x = len + 1;
        mOptionalText->getWidget()->setSize(mOptionalTextSize);
        mOptionalText->setTextAlign(MGAlign::Center);
        mOptionalText->getWidget()->setVisible(true);
    }
    //------------------------------------------------------------------------------------
    Bool HeadDes::calBasePoint()
    {
		Vec2 screenPos;
		IDisplay* display = ClientMain::getInstance().getEngine()->display();

		mIsInScreen = mParent->getScreenPos( screenPos, Vec3(0,mHeightAboveParent,0) );
		
		if ( mIsInScreen )
		{
			///计算基点位置
			mBasePoint.x = UInt(screenPos.x * display->getWidth());
			mBasePoint.y = UInt(screenPos.y * display->getHeight());
		}

		return mIsInScreen;
    }
    //------------------------------------------------------------------------------------
    void HeadDes::updateTroop()
    {
        CTroopEntity* entity = (CTroopEntity*)mParent;

        ///计算血条位置
        static Vec2 hpProcessPos;
        //hpProcessPos.x = mBasePoint.x - mHpProcessSize.x / 2;
        //hpProcessPos.y = mBasePoint.y - mHpProcessSize.y;
        //mHpProcess->getWidget()->setPosition(hpProcessPos);

        //Int maxHp = 100;
        //Int currHp = entity->getDynamicData()->hp;

        //mHpProcess->setProgressPosition(currHp/(1.f*maxHp));
		if ( mHpProcess )
		{
			mHpProcess->getWidget()->setVisible(true);
		}
    }
	//------------------------------------------------------------------------------------
	void HeadDes::updateItem()
	{  
		///计算名字位置
		if (mName != NULL)
		{
			Vec2 nameTextPos;
			nameTextPos.x = mBasePoint.x - mNameTextSize.x / 2;
			nameTextPos.y = mBasePoint.y - mOptionalTextSize.y - mNameTextSize.y;
			mName->getWidget()->setPosition(nameTextPos);
			mName->getWidget()->setVisible(true);
		}
	}
	//------------------------------------------------------------------------------------
	void HeadDes::updateMonster()
	{
		///计算名字位置
		if (mName != NULL)
		{
			Vec2 nameTextPos;
			nameTextPos.x = mBasePoint.x - mNameTextSize.x / 2;
			nameTextPos.y = mBasePoint.y - mOptionalTextSize.y - mNameTextSize.y;
			mName->getWidget()->setPosition(nameTextPos);
			mName->getWidget()->setVisible(true);
		}
	}
	//------------------------------------------------------------------------------------
	void HeadDes::updateRotPlace()
	{
       if (mName != NULL)
       {
		   Vec2 nameTextPos;
		   nameTextPos.x = mBasePoint.x - mNameTextSize.x / 2;
		   nameTextPos.y = mBasePoint.y - mOptionalTextSize.y - mNameTextSize.y;
		   mName->getWidget()->setPosition(nameTextPos);
		   mName->getWidget()->setVisible(true);
       }
	}
	//------------------------------------------------------------------------------------
}
