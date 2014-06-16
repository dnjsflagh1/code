//*****************************************************************************************************
#include "stdafx.h"
#include "CPlayerCharacter.h"
#include "CSkillOwnManager.h"
#include "SkillInfoList.h"
#include "CSkillObject.h"
#include "ClientMain.h"
#include "UISkillTips.h"
#include "CGameMessageConfig.h"
//#include "AttributeSystem.h"
#include "AttributeFormula.h"
#include "AttributePara.h"
//*****************************************************************************************************
namespace MG
{
	const Str16 GMCONFIG_KEEYNAME = L"skilltips";
    
	//----------------------------------------------------------------------------------------
	UISkillTips::UISkillTips()
		:mSelectSkillInfo(NULL),mCurrentCharacter(NULL)
	{

	}
	//----------------------------------------------------------------------------------------
	void UISkillTips::openSkillTips(IconInfo* picon,CoordI coord,CCharacter* character)
	{
		mSelectSkillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(picon->tempID);
		if (character)
		{
			mCurrentCharacter = character;
		}
		else
			mCurrentCharacter = NULL;

		setSkillTipsInfo(coord);
		openGui();

	}
	//----------------------------------------------------------------------------------------
	#define  item_tips_space 5
	void UISkillTips::setSkillTipsInfo( CoordI coord )
	{
		U32 height = item_tips_space;

		clearAllItems();
		setSkillNameAndLevel(height);
		setSkillKindNameAndType(height);
		setSkillSpend(height);
		setSkillTimeDelay(height);
		setSkillActionTime(height);
		setSkillDescribe(height);

		//设置tips的位置
		setTipsCoord(height, coord);
	}
	//----------------------------------------------------------------------------------------
	void UISkillTips::setSkillNameAndLevel( U32& height )
	{
		//name
		Str16 tempName;
		Color tempColor(0/255.f, 255/255.f, 0/255.f, 1.f);
		//SkillInfo *skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(mSelectSkillData->skillId);
		tempName = mSelectSkillInfo->skillInfo->name;
		//设置属性和控件的大小，位置
		U32 length = ClientMain::getInstance().getGui()->getLengthStr(tempName);
		U32 fontHeight = ClientMain::getInstance().getGui()->getHeightChar();
		IText* pText = getLayout()->getText("text_name");
		pText->getWidget()->setCaption(tempName);
		pText->setTextColour(tempColor);
		CoordI tempCoord = pText->getWidget()->getCoord();
		tempCoord.left = item_tips_space;
		tempCoord.top = height;
		//tempCoord.width = length;
		tempCoord.height = fontHeight;
		pText->getWidget()->setCoord(tempCoord);

        //level
		Char16 tempNameLevel[30] = {0};
		SkillBaseInfo* baseInfo = mSelectSkillInfo->skillInfo;
		Int tempLevel = baseInfo->skillLevel;
		if (tempLevel != 0)
		{
			Str16 preStr = CGameMessageConfig::getInstance().getStr(GMCONFIG_KEEYNAME,L"skilllevel",L"");
			swprintf_s(tempNameLevel,30,preStr.c_str(),tempLevel);
		
			//MGStrOp::sprintf((Char16*)tempNameLevel,30,(Char16*)preStr.c_str(),tempLevel);
			//设置属性和控件的大小，位置
			length = ClientMain::getInstance().getGui()->getLengthStr(tempNameLevel);
			//U32 fontHeight = ClientMain::getInstance().getGui()->getHeightChar();
			IText* pTextLevel = getLayout()->getText("text_level");

			CoordI tempLevelCoord = pTextLevel->getWidget()->getCoord();
			tempLevelCoord.left = item_tips_space + tempCoord.left + tempCoord.width;
			tempLevelCoord.top = height;
			//tempLevelCoord.width = length;
			tempLevelCoord.height = fontHeight;

			pTextLevel->getWidget()->setCoord(tempLevelCoord);
			pTextLevel->getWidget()->setCaption(tempNameLevel);
		    pTextLevel->setTextColour(tempColor);

		}
		
		//更新高度
		height += tempCoord.height;



	}
	
	//----------------------------------------------------------------------------------------
	void UISkillTips::setSkillKindNameAndType( U32& height )
	{
		//kindname
		Str16 tempName;
		Color tempColor(230/255.f, 200/255.f, 50/255.f, 1.f);
       // SkillInfo *skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(mSelectSkillData->skillId);
		tempName = mSelectSkillInfo->skillInfo->kindName;
		//设置属性和控件的大小，位置
		U32 length = ClientMain::getInstance().getGui()->getLengthStr(tempName);
		U32 fontHeight = ClientMain::getInstance().getGui()->getHeightChar();
		IText* pText = getLayout()->getText("text_kindname");
		pText->getWidget()->setCaption(tempName);
		pText->setTextColour(tempColor);
		CoordI tempCoord = pText->getWidget()->getCoord();
		tempCoord.left = item_tips_space;
		tempCoord.top = height;
		//tempCoord.width = length;
		tempCoord.height = fontHeight;
		pText->getWidget()->setCoord(tempCoord);

		//type
		Str16 tempSkillType;
        Int showType = mSelectSkillInfo->skillShowType;
		Char16 showTypeName[30] = {0};
		swprintf_s(showTypeName,30,L"showtype%d",showType);
		tempSkillType = CGameMessageConfig::getInstance().getStr(GMCONFIG_KEEYNAME,Str16(showTypeName),L"");

		//设置属性和控件的大小，位置
		length = ClientMain::getInstance().getGui()->getLengthStr(tempSkillType);
		IText* pTextType = getLayout()->getText("text_type");

		CoordI tempTypeCoord = pTextType->getWidget()->getCoord();
		tempTypeCoord.left = item_tips_space + tempCoord.left + tempCoord.width;
		tempTypeCoord.top = height;
		//tempTypeCoord.width = length;
		tempTypeCoord.height = fontHeight;

		pTextType->getWidget()->setCoord(tempTypeCoord);
		pTextType->getWidget()->setCaption(tempSkillType);
		pTextType->setTextColour(tempColor);
		//更新高度
		height += tempCoord.height;

		
	}
	
	//----------------------------------------------------------------------------------------
	void UISkillTips::setSkillSpend( U32& height )
	{
		if (!mCurrentCharacter)
		{
			return;
		}
		if ( mCurrentCharacter->getType() != GOT_PLAYERCHARACTER )
			return;

		Str16 tempName;
		Color tempColor(255/255.f, 255/255.f, 255/255.f, 1.f);
		//SkillInfo *skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(mSelectSkillData->skillId); 
		if (mSelectSkillInfo->skillShowType == SKILL_SHOW_TYPE_ONE)
		{
			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)mSelectSkillInfo->skillInfo;
			UInt spendFormula =  initiativeSkillBasicInfo->formulaParameterId2;
			if ( spendFormula == 0)
			    return;
			AttributeSet* pMasterAttributeSet = mCurrentCharacter->getAttributeSet();
			const AttrParaInfo* pAttrParaInfo = NULL;
			pAttrParaInfo =  AttributePara::getInstance().getAttrParaInfo(spendFormula);
			DYNAMIC_ASSERT(pAttrParaInfo);
			Flt tempValue = AttributeFormula::getInstance().calValue( pMasterAttributeSet, mCurrentCharacter->getCharacterData(), pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId );
			Int spendType = initiativeSkillBasicInfo->spendType;
			Char16 spendTypeStr[30] = {0};
			swprintf_s(spendTypeStr,30,L"skillspend%d",spendType);
			tempName = CGameMessageConfig::getInstance().getStr(GMCONFIG_KEEYNAME,Str16(spendTypeStr),L"");
			Char16 showName[50] = {0};
			swprintf_s(showName,50,tempName.c_str(),static_cast<Int>(tempValue));
			//设置属性和控件的大小，位置
			U32 length = ClientMain::getInstance().getGui()->getLengthStr(showName);
			U32 fontHeight = ClientMain::getInstance().getGui()->getHeightChar();
			IText* pText = getLayout()->getText("text_spend");
			pText->getWidget()->setCaption(showName);
			pText->setTextColour(tempColor);
			CoordI tempCoord = pText->getWidget()->getCoord();
			tempCoord.left = item_tips_space;
			tempCoord.top = height;
			//tempCoord.width = length;
			tempCoord.height = fontHeight;
			pText->getWidget()->setCoord(tempCoord);

			//更新高度
			height += tempCoord.height;


		}


		//skillInfo
	}
	//----------------------------------------------------------------------------------------
	void UISkillTips::setSkillTimeDelay( U32& height )
	{
		//SkillInfo *skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(mSelectSkillData->skillId);
		if (mSelectSkillInfo->skillShowType == SKILL_SHOW_TYPE_ONE)
		{
		    Color tempColor(0/255.f, 255/255.f, 255/255.f, 1.f);
			Char16 tempSkillTimeDelay[30];
			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)mSelectSkillInfo->skillInfo;
			UInt timedelay = initiativeSkillBasicInfo->ownerTimepieceDelay;
            Flt  timedelayFlt = timedelay/10.f;
			Int	 timedelayInt = static_cast<Int>(timedelayFlt);
			Str16 preStr = CGameMessageConfig::getInstance().getStr(GMCONFIG_KEEYNAME,L"skilltimedelay",L"");
			swprintf_s(tempSkillTimeDelay,30,preStr.c_str(),timedelayInt);
			//设置属性和控件的大小，位置
			U32 length = ClientMain::getInstance().getGui()->getLengthStr(tempSkillTimeDelay);
			U32 fontHeight = ClientMain::getInstance().getGui()->getHeightChar();
			IText* pText = getLayout()->getText("text_timedelay");
			pText->getWidget()->setCaption(tempSkillTimeDelay);
			pText->setTextColour(tempColor);
			CoordI tempCoord = pText->getWidget()->getCoord();
			tempCoord.left = item_tips_space;
			tempCoord.top = height;
			//tempCoord.width = length;
			tempCoord.height = fontHeight;
			pText->getWidget()->setCoord(tempCoord);

			//更新高度
			height += tempCoord.height;


		}
		

	}
	//----------------------------------------------------------------------------------------
	void UISkillTips::setSkillActionTime( U32& height )
	{
		//Str16 tempName;
		//SkillInfo *skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(mSelectSkillData->skillId);
		if (mSelectSkillInfo->skillShowType == SKILL_SHOW_TYPE_ONE)
		{
			Color tempColor(0/255.f, 255/255.f, 255/255.f, 1.f);
			Char16 tempSkillActionTime[30];
			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)mSelectSkillInfo->skillInfo;
			UInt actiontime= initiativeSkillBasicInfo->actionTime;
			Flt  actiontimeFlt = actiontime/10.f;
			Int	 actiontimeInt = static_cast<Int>(actiontimeFlt);
			Str16 preStr = CGameMessageConfig::getInstance().getStr(GMCONFIG_KEEYNAME,L"skillactiontime",L"");
			swprintf_s(tempSkillActionTime,30,preStr.c_str(),actiontimeInt);
			//设置属性和控件的大小，位置
			U32 length = ClientMain::getInstance().getGui()->getLengthStr(tempSkillActionTime);
			U32 fontHeight = ClientMain::getInstance().getGui()->getHeightChar();
			IText* pText = getLayout()->getText("text_actiontime");
			pText->getWidget()->setCaption(tempSkillActionTime);
			pText->setTextColour(tempColor);
			CoordI tempCoord = pText->getWidget()->getCoord();
			tempCoord.left = item_tips_space;
			tempCoord.top = height;
			//tempCoord.width = length;
			tempCoord.height = fontHeight;
			pText->getWidget()->setCoord(tempCoord);

			//更新高度
			height += tempCoord.height;

		}

	}
	//----------------------------------------------------------------------------------------
	void UISkillTips::setSkillDescribe( U32& height )
	{
		Str16 tempName;
		Color tempColor(255/255.f, 250/255.f, 210/255.f, 1.f);
		//SkillInfo *skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(mSelectSkillData->skillId); 
		tempName = mSelectSkillInfo->skillInfo->text;
		
		
		//获取显示最大宽度
		IWidget* pWidget = getLayout()->getWidget("text_describe");
		CoordI tempCoord = pWidget->getCoord();
		tempCoord.left = item_tips_space;
		tempCoord.top = height;

		Int maxWidth =tempCoord.width;
		//设置属性和控件的大小，位置
	    U32 fontHeight = ClientMain::getInstance().getGui()->getHeightStrAddBreak(tempName,maxWidth);
		U32 length = ClientMain::getInstance().getGui()->getLengthStr(tempName);
		IText* pText = getLayout()->getText("text_describe");
		pText->getWidget()->setCaption(tempName);
		pText->setTextColour(tempColor);
		
		tempCoord.height = fontHeight;
		pText->getWidget()->setCoord(tempCoord);
		
		//更新高度
		height += tempCoord.height;
		
	}
	//----------------------------------------------------------------------------------------
	MG::Bool UISkillTips::closeGui()
	{
		mSelectSkillInfo = NULL;
		return UIObject::closeGui();

	}
	//----------------------------------------------------------------------------------------
	void UISkillTips::setTipsCoord( U32 height, CoordI coord )
	{
		IWidget* pWidget = getLayout()->getWidget(MAIN_WIDGET);
		CoordI curCoord = pWidget->getCoord();
		curCoord.height = height + item_tips_space;

		U32 curScreenWidth =  ClientMain::getInstance().getEngine()->display()->getWidth();


		//默认位置为右上角
		if ( curCoord.width + coord.left + coord.width > curScreenWidth )
			curCoord.left = coord.left - curCoord.width;
		else
			curCoord.left = coord.left + coord.width;

		if ( coord.top - curCoord.height < 0 )
			curCoord.top = coord.top + coord.height;
		else
			curCoord.top = coord.top - curCoord.height;

		pWidget->setCoord(curCoord);


	}
	//----------------------------------------------------------------------------------------
	void UISkillTips::clearAllItems()
	{
		//
       IText* pText = getLayout()->getText("text_name");
	   DYNAMIC_ASSERT(pText);
	   pText->getWidget()->setCaption(L"");
	   IText* pTextLevel = getLayout()->getText("text_level");
	   DYNAMIC_ASSERT(pTextLevel);
	   pTextLevel->getWidget()->setCaption(L"");
       
	   //
	   pText = getLayout()->getText("text_kindname");
	   DYNAMIC_ASSERT(pText);
	   pText->getWidget()->setCaption(L"");
	   IText* pTextType = getLayout()->getText("text_type");
	   DYNAMIC_ASSERT(pTextType);
	   pTextType->getWidget()->setCaption(L"");
	   
	   //
	  pText = getLayout()->getText("text_spend");
	  DYNAMIC_ASSERT(pText);
	  pText->getWidget()->setCaption(L"");

	  //
	  pText = getLayout()->getText("text_timedelay");
	  DYNAMIC_ASSERT(pText);
	  pText->getWidget()->setCaption(L"");

	  //
	  pText = getLayout()->getText("text_actiontime");
	  DYNAMIC_ASSERT(pText);
	  pText->getWidget()->setCaption(L"");

	  //
	 pText = getLayout()->getText("text_describe");
	 DYNAMIC_ASSERT(pText);
	 pText->getWidget()->setCaption(L"");

        
	}

}