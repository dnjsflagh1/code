/***********************************************************************************************************/
#include "stdafx.h"
#include "CAttributeSystem.h"
#include "CCharacter.h"
#include "CharacterList.h"
#include "AttributeAppend.h"
/***********************************************************************************************************/
namespace MG
{
    //-----------------------------------------------------------------------------
#define ATTR_RAND_INDEX 3
#define LVADD_RAND_INDEX 4
    void CAttributeSystem::calBaseAttr(CCharacter* pCharacter)
    {
        //AttributeSet* mCalAttrInfo = getCalAttrInfo();

        //�ӽ�ɫ��ȡ�����ԣ��������Ա���
       /* mCalAttrInfo->setFanalValue( ATTR_ID_LevelBase, (Flt)pCharacter->getLevel() );
        mCalAttrInfo->setFanalValue( ATTR_ID_Hp, (Flt)pCharacter->getHp());
        mCalAttrInfo->setFanalValue( ATTR_ID_Mp, (Flt)pCharacter->getMp());
        mCalAttrInfo->setFanalValue( ATTR_ID_Sp, (Flt)pCharacter->getSp());
        mCalAttrInfo->setFanalValue( ATTR_ID_Awake, (Flt)pCharacter->getLineageNum());*/

        //����tempID���ϸ���ֵ��
        //const CharacterTempInfo* mCharacterTempInfo = pCharacter->getCharacterTempInfo();
        //assert(mCharacterTempInfo);
        //for (Int i=0; i<CHAR_ABILITYAPPEND_ID_NUM; i++)
        //{
        //    U32 id = mCharacterTempInfo->getCharacterAbilityAppendId(i);
        //    if ( id == 0 )
        //        break;
        //    const AttributeAppendInfo* pAAinfo = AttributeAppend::getInstance().getAttributeAppendInfo( id );
        //    assert(pAAinfo);

        //    
        //    for ( Int j=0; j<APPENDATTR_NUM; j++ )
        //    {
        //        //���ж����ͣ���ѡ����㷽����
        //        Flt tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
        //        mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pAAinfo->AppendAttrList[j].value + tempVal );
        //    }

        //}

        ////�ڸ���Ѫ�����ϸ���ֵ
        //const LineageInfo* pLginfo = LineageTemplate::getInstance().getAttrAppendInfo(lineageAppendAttrid);
        //assert(pLginfo);
        //if ( pLginfo->abilityGroupAppendId != 0 )
        //{
        //    const AttributeAppendInfo* pAAinfo = AttributeAppend::getInstance().getAttributeAppendInfo( pLginfo->abilityGroupAppendId );
        //    assert(pAAinfo);
        //    for ( Int j=0; j<APPENDATTR_NUM; j++ )
        //    {
        //        //���ж����ͣ���ѡ����㷽����
        //        Flt tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
        //        mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pAAinfo->AppendAttrList[j].value + tempVal );
        //    }
        //}

    }
    //-----------------------------------------------------------------------------
#undef  ATTR_RAND_INDEX
#undef LVADD_RAND_INDEX
    //-----------------------------------------------------------------------------
}