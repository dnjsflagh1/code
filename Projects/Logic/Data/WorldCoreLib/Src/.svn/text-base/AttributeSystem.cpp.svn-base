//******************************************************************************************
#include "stdafx.h"
#include "AttributeSystem.h"
#include "LineageTemplate.h"
#include "AttributeAppend.h"
#include "AttributeFormula.h"
#include "AttributeList.h"
#include "AttributePara.h"
//******************************************************************************************
namespace MG
{
    //******************************************************************************************
    AttributeSystem::AttributeSystem()
    {

    }
    //---------------------------------------------------------------------------------
    AttributeSystem::~AttributeSystem()
    {

    }
	//---------------------------------------------------------------------------------
	void AttributeSystem::print()
	{
		mCalAttrInfo.print();
	}
    //---------------------------------------------------------------------------------
    void AttributeSystem::calFinalAttr(CHAR_FORMULA_TYPE type, CharacterData* pCharacterData)
    {
        mCalAttrInfo.calFanalAttr(type, pCharacterData);              
    }
    //---------------------------------------------------------------------------------
    AttributeSet* AttributeSystem::getCalAttrInfo()
    {
        return &mCalAttrInfo;
    }
    //---------------------------------------------------------------------------------
    Int AttributeSystem::addValue(U32 id, Int num)
    {
        return (Int)mCalAttrInfo.addValue(id, num);
    }
    //---------------------------------------------------------------------------------
    Flt AttributeSystem::getFanalValue( U32 attrId )
    {
        return  mCalAttrInfo.getFanalValue(attrId) ;
    }
    //---------------------------------------------------------------------------------
    void AttributeSystem::setFanalValue( U32 attrId, Flt value )
    {
        mCalAttrInfo.setFanalValue(attrId, value);
    }
    //---------------------------------------------------------------
	void AttributeSystem::calRelateAttr( U32 attrId, Flt value, CHAR_FORMULA_TYPE type, CharacterData* pCharacterData )
	{
		//先改变自己。
		mCalAttrInfo.addValue(attrId, value);

		//获得属性信息。
		const AttrInfo* pAttrInfo = AttributeList::getInstance().getAttrInfo((ATTR_ID)attrId);
		DYNAMIC_ASSERT(pAttrInfo);

		//同分组id计算。
		std::vector<AttrInfo*>* tempReckonAttrInfo = AttributeList::getInstance().getVectorAttrInfoByGroupId(pAttrInfo->groupId);
		DYNAMIC_ASSERT(tempReckonAttrInfo);
		calRelateAttr(tempReckonAttrInfo, type, pCharacterData);

		//同类型type计算
		if ( pAttrInfo->useType == ATTR_USE_TYPE_TALENT )
		{
			std::vector<AttrInfo*>* tempUseTypeAttrInfo = AttributeList::getInstance().getVectorAttrInfoByUseType(ATTR_USE_TYPE_FIGHT);
			DYNAMIC_ASSERT(tempUseTypeAttrInfo);
			calRelateAttr(tempUseTypeAttrInfo, type, pCharacterData);
		}

	}
	//---------------------------------------------------------------------------------
	void AttributeSystem::calRelateAttr( std::vector<AttrInfo*>* tempVectorAttrInfo, CHAR_FORMULA_TYPE type, CharacterData* pCharacterData )
	{
		const AttrParaInfo* pParaInfo = NULL;
		std::vector<AttrInfo*>::iterator reckonFront = tempVectorAttrInfo->begin();
		std::vector<AttrInfo*>::iterator reckonBack = tempVectorAttrInfo->end();
		while (reckonFront != reckonBack)
		{
			if ( (*reckonFront)->formulaParaID[type] == 0 )
			{  
				reckonFront++;
			  	continue;
			}

			pParaInfo = AttributePara::getInstance().getAttrParaInfo( (*reckonFront)->formulaParaID[type] );
			assert(pParaInfo);

			setFanalValue((*reckonFront)->attrId, 
					AttributeFormula::getInstance().calValue(
					&mCalAttrInfo,
					pCharacterData,
					pParaInfo->para, pParaInfo->attrID, pParaInfo->FormulaId
					)
				);

			++reckonFront;
		}
	}
	//---------------------------------------------------------------------------------
	MG::Int AttributeSystem::getShieldByType( STATUS_ABSORBTYPE type )
	{
		DYNAMIC_ASSERT(type>STATUS_ABSORBTYPE_NULL  &&  type<STATUS_ABSORBTYPE_MAX);
		return (Int)mCalAttrInfo.getFanalValue(Attr_ID_shield_FIGHT+type-1);
	}
	//---------------------------------------------------------------------------------
	void AttributeSystem::setShieldByType( STATUS_ABSORBTYPE type, Int val )
	{
		DYNAMIC_ASSERT(type>STATUS_ABSORBTYPE_NULL  &&  type<STATUS_ABSORBTYPE_MAX);
		mCalAttrInfo.setFanalValue(Attr_ID_shield_FIGHT+type-1, (Flt)val);
	}
	//---------------------------------------------------------------------------------
	void AttributeSystem::addShieldByType( STATUS_ABSORBTYPE type, Int val )
	{
		DYNAMIC_ASSERT(type>STATUS_ABSORBTYPE_NULL  &&  type<STATUS_ABSORBTYPE_MAX);
		mCalAttrInfo.setFanalValue(
			Attr_ID_shield_FIGHT+type-1,
			mCalAttrInfo.getFanalValue(Attr_ID_shield_FIGHT+type-1)+(Flt)val
			);
	}

}