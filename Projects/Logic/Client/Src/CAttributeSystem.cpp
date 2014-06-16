/***********************************************************************************************************/
#include "stdafx.h"
#include "CAttributeSystem.h"
#include "CCharacter.h"
#include "CharacterList.h"
#include "AttributeInit.h"
#include "AttributeAppend.h"
/***********************************************************************************************************/
namespace MG
{
    //-----------------------------------------------------------------------------
#define ATTR_RAND_INDEX 3
#define LVADD_RAND_INDEX 4
    void CAttributeSystem::calBaseAttr(CCharacter* pCharacter)
    {
        AttributeSet* mCalAttrInfo = getCalAttrInfo();
		mCalAttrInfo->resetAllValue();

        //根据tempID加上附加值。
        const CharacterTempInfo* mCharacterTempInfo = pCharacter->getCharacterTempInfo();
        assert(mCharacterTempInfo);

		//初始化属性
        for (Int i=0; i<CHAR_ABILITYAPPEND_ID_NUM-1; i++)
        {
            Flt tempVal = 0;

            U32 id = mCharacterTempInfo->getCharacterAbilityAppendId(i);
            if ( 0 == id )
                continue;
            const AttributeInitInfo* pAAinfo = AttributeInit::getInstance().getAttributeInitInfo( id );
            DYNAMIC_ASSERT(pAAinfo);
			for ( Int j=0; j<APPENDATTR_NUM; j++ )
			{
				if ( 0 == pAAinfo->AppendAttrList[j].id )
					continue;
				//先判断类型，在选择计算方法。
				tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
				mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pAAinfo->AppendAttrList[j].value + tempVal );
			}
		}

		//附加属性
		U32 id = mCharacterTempInfo->getCharacterAbilityAppendId(CHAR_ABILITYAPPEND_ID_NUM-1);
		if ( id != 0 )
		{
			Flt tempVal = 0;

			const AttributeAppendInfo* pAttributeAppendInfo = AttributeAppend::getInstance().getAttributeAppendInfo(id);
			DYNAMIC_ASSERT(pAttributeAppendInfo);

			for ( Int j=0; j<APPENDATTR_NUM; j++ )
			{
				if ( 0 == pAttributeAppendInfo->AppendAttrList[j].id )
					continue;

				//先判断类型，在选择计算方法。
				tempVal =  mCalAttrInfo->getFanalValue( pAttributeAppendInfo->AppendAttrList[j].id );
				if ( pAttributeAppendInfo->AppendType == APPEND_TYPE_REAL )
				{	
					tempVal += pAttributeAppendInfo->AppendAttrList[j].value;
				}
				else
				{	
					tempVal += 
						pAttributeAppendInfo->AppendAttrList[j].value*pCharacter->getLevel()*PERMILLAGE_VALUE;
				}
				mCalAttrInfo->setFanalValue( pAttributeAppendInfo->AppendAttrList[j].id, tempVal );
			}
		}

		//随机属性
		{
			Flt tempVal = 0;
			const AttributeInitInfo* pAAinfo = NULL;

			//随机基础属性
			UInt randId = pCharacter->getDBAttrInitID();
			if ( 0 != randId )
			{
				pAAinfo = AttributeInit::getInstance().getAttributeInitInfo( randId );
				DYNAMIC_ASSERT(pAAinfo);
				for ( Int j=0; j<APPENDATTR_NUM; j++ )
				{
					if ( 0 == pAAinfo->AppendAttrList[j].id )
						continue;
					//先判断类型，在选择计算方法。
					tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
					mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pCharacter->getDBAttrInit(j) + tempVal );
				}
			}

			//随机附加属性
			UInt randAddId = pCharacter->getDBAttrLvlAddID();
			if ( 0 != randAddId )
			{
				pAAinfo = AttributeInit::getInstance().getAttributeInitInfo( randAddId );
				DYNAMIC_ASSERT(pAAinfo);
				for ( Int j=0; j<APPENDATTR_NUM; j++ )
				{
					if ( 0 == pAAinfo->AppendAttrList[j].id )
						continue;
					//先判断类型，在选择计算方法。
					tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
					mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pCharacter->getDBAttrLvlAdd(j) + tempVal );
				}
			}	
		}              

        ////在根据血脉加上附加值
        //const LineageInfo* pLginfo = LineageTemplate::getInstance().getAttrAppendInfo(lineageAppendAttrid);
        //assert(pLginfo);
        //if ( pLginfo->abilityGroupAppendId != 0 )
        //{
        //    const AttributeAppendInfo* pAAinfo = AttributeAppend::getInstance().getAttributeAppendInfo( pLginfo->abilityGroupAppendId );
        //    assert(pAAinfo);
        //    for ( Int j=0; j<APPENDATTR_NUM; j++ )
        //    {
        //        //先判断类型，在选择计算方法。
        //        Flt tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
        //        mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pAAinfo->AppendAttrList[j].value + tempVal );
        //    }
        //}

    }
    //-----------------------------------------------------------------------------
    void CAttributeSystem::calBaseAttr( const CharacterTempInfo* pInfo )
    {
		AttributeSet* mCalAttrInfo = getCalAttrInfo();
		mCalAttrInfo->resetAllValue();

		//根据tempID加上附加值。

		//初始化属性
		for (Int i=0; i<CHAR_ABILITYAPPEND_ID_NUM-1; i++)
		{
			Flt tempVal = 0;

			U32 id = pInfo->getCharacterAbilityAppendId(i);
			if ( id == 0 )
				continue;
			const AttributeInitInfo* pAAinfo = AttributeInit::getInstance().getAttributeInitInfo( id );
			DYNAMIC_ASSERT(pAAinfo);
			for ( Int j=0; j<APPENDATTR_NUM; j++ )
			{
				//先判断类型，在选择计算方法。
				tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
				mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pAAinfo->AppendAttrList[j].value + tempVal );
			}
		}

		//附加属性
		U32 id = pInfo->getCharacterAbilityAppendId(CHAR_ABILITYAPPEND_ID_NUM-1);
		if ( id != 0 )
		{
			Flt tempVal = 0;

			const AttributeAppendInfo* pAttributeAppendInfo = AttributeAppend::getInstance().getAttributeAppendInfo(id);
			DYNAMIC_ASSERT(pAttributeAppendInfo);

			for ( Int j=0; j<APPENDATTR_NUM; j++ )
			{
				//先判断类型，在选择计算方法。
				tempVal =  mCalAttrInfo->getFanalValue( pAttributeAppendInfo->AppendAttrList[j].id );
				mCalAttrInfo->setFanalValue( pAttributeAppendInfo->AppendAttrList[j].id, pAttributeAppendInfo->AppendAttrList[j].value + tempVal );
			}
		}
    }
	//-----------------------------------------------------------------------------
#undef  ATTR_RAND_INDEX
#undef LVADD_RAND_INDEX
    //-----------------------------------------------------------------------------
}