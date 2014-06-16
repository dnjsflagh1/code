//******************************************************************************************
#include "stdafx.h"
#include "AttributeSet.h"
////#include "PlayerCharacter.h"
#include "AttributePara.h"
#include "AttributeFormula.h"
//******************************************************************************************
namespace MG
{
    AttributeSet::AttributeSet()
    {
        memset(mAttrfinalList, 0, sizeof(mAttrfinalList));
    }
    //---------------------------------------------------------------------------------
    AttributeSet::~AttributeSet()
    {

    }
    //---------------------------------------------------------------------------------
    Flt AttributeSet::getFanalValue( U32 id ) const
    {
        if ( id <= 0  ||  id >= ATTR_ID_COUNT_MAX )
        {  
            return 0.f;   
        }

        return mAttrfinalList[id];  
    }
    //---------------------------------------------------------------------------------
    void AttributeSet::setFanalValue( U32 id, Flt value )
    {
        if (id <= 0  ||  id >= ATTR_ID_COUNT_MAX)
        {  
            return ;   
        }

        const AttrInfo* tempAttrInfo = AttributeList::getInstance().getAttrInfo((ATTR_ID)id);
        assert(tempAttrInfo);

        mAttrfinalList[id] = value;

        if ( tempAttrInfo->minValue != tempAttrInfo->maxValue )
        {
            if ( mAttrfinalList[id] < tempAttrInfo->minValue )
                mAttrfinalList[id] = (Flt)tempAttrInfo->minValue;
            else if ( mAttrfinalList[id] > tempAttrInfo->maxValue )
                mAttrfinalList[id] = (Flt)tempAttrInfo->maxValue;
        }

    }
    //---------------------------------------------------------------------------------
    void AttributeSet::calFanalAttr(CHAR_FORMULA_TYPE type, CharacterData* pCharacterData)
    {
        const AttrInfo* pInfo = NULL;
        const AttrParaInfo* pParaInfo = NULL;
        for (U32 i=ATTR_ID_NULL+1; i<ATTR_ID_MAX; i++)
        {
            pInfo = AttributeList::getInstance().getAttrInfo((ATTR_ID)i);
            assert(pInfo);

            if ( pInfo->formulaParaID[type] == 0 )
                continue;
            
            pParaInfo = AttributePara::getInstance().getAttrParaInfo( pInfo->formulaParaID[type] );
            assert(pParaInfo);
            
            const AttributeSet* pTempAttrSet = this;
            setFanalValue(
				i, 
				AttributeFormula::getInstance().calValue(
						pTempAttrSet, 
						pCharacterData,
						pParaInfo->para, 
						pParaInfo->attrID, 
						pParaInfo->FormulaId
					)
				) ;

        }
    }
    //---------------------------------------------------------------------------------
    MG::Flt AttributeSet::addValue( U32 id, Flt value )
    {
        if (id <= 0  ||  id >= ATTR_ID_COUNT_MAX)
        {  
            return 0.f;   
        }

        const AttrInfo* tempAttrInfo = AttributeList::getInstance().getAttrInfo((ATTR_ID)id);
        assert(tempAttrInfo);

        mAttrfinalList[id] += value;

        if ( tempAttrInfo->minValue != tempAttrInfo->maxValue )
        {
            if ( mAttrfinalList[id] < tempAttrInfo->minValue )
                mAttrfinalList[id] = (Flt)tempAttrInfo->minValue;
            else if ( mAttrfinalList[id] > tempAttrInfo->maxValue )
                mAttrfinalList[id] = (Flt)tempAttrInfo->maxValue;
        }

        return mAttrfinalList[id];
    }
	//---------------------------------------------------------------------------------
	void AttributeSet::resetAllValue()
	{
		memset(mAttrfinalList, 0, sizeof(mAttrfinalList));
	}

	void AttributeSet::print()
	{
		LogSystem::getInstance().log(out_sys,"\n属性打印 开始\n");
		
		for (Int i=0; i<ATTR_ID_COUNT_MAX; ++i)
		{
			if (mAttrfinalList[i] != 0)
			{
				LogSystem::getInstance().log(out_sys,"[%d]: %f\n", i, mAttrfinalList[i]);
			}
		}

		LogSystem::getInstance().log(out_sys,"\n属性打印 结束\n");
	}
}                       