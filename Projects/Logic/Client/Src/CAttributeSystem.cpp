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

        //����tempID���ϸ���ֵ��
        const CharacterTempInfo* mCharacterTempInfo = pCharacter->getCharacterTempInfo();
        assert(mCharacterTempInfo);

		//��ʼ������
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
				//���ж����ͣ���ѡ����㷽����
				tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
				mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pAAinfo->AppendAttrList[j].value + tempVal );
			}
		}

		//��������
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

				//���ж����ͣ���ѡ����㷽����
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

		//�������
		{
			Flt tempVal = 0;
			const AttributeInitInfo* pAAinfo = NULL;

			//�����������
			UInt randId = pCharacter->getDBAttrInitID();
			if ( 0 != randId )
			{
				pAAinfo = AttributeInit::getInstance().getAttributeInitInfo( randId );
				DYNAMIC_ASSERT(pAAinfo);
				for ( Int j=0; j<APPENDATTR_NUM; j++ )
				{
					if ( 0 == pAAinfo->AppendAttrList[j].id )
						continue;
					//���ж����ͣ���ѡ����㷽����
					tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
					mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pCharacter->getDBAttrInit(j) + tempVal );
				}
			}

			//�����������
			UInt randAddId = pCharacter->getDBAttrLvlAddID();
			if ( 0 != randAddId )
			{
				pAAinfo = AttributeInit::getInstance().getAttributeInitInfo( randAddId );
				DYNAMIC_ASSERT(pAAinfo);
				for ( Int j=0; j<APPENDATTR_NUM; j++ )
				{
					if ( 0 == pAAinfo->AppendAttrList[j].id )
						continue;
					//���ж����ͣ���ѡ����㷽����
					tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
					mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pCharacter->getDBAttrLvlAdd(j) + tempVal );
				}
			}	
		}              

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
    void CAttributeSystem::calBaseAttr( const CharacterTempInfo* pInfo )
    {
		AttributeSet* mCalAttrInfo = getCalAttrInfo();
		mCalAttrInfo->resetAllValue();

		//����tempID���ϸ���ֵ��

		//��ʼ������
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
				//���ж����ͣ���ѡ����㷽����
				tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
				mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pAAinfo->AppendAttrList[j].value + tempVal );
			}
		}

		//��������
		U32 id = pInfo->getCharacterAbilityAppendId(CHAR_ABILITYAPPEND_ID_NUM-1);
		if ( id != 0 )
		{
			Flt tempVal = 0;

			const AttributeAppendInfo* pAttributeAppendInfo = AttributeAppend::getInstance().getAttributeAppendInfo(id);
			DYNAMIC_ASSERT(pAttributeAppendInfo);

			for ( Int j=0; j<APPENDATTR_NUM; j++ )
			{
				//���ж����ͣ���ѡ����㷽����
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