//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: GeneralRandomCsv.h
//        Author: yuanlinhu
//          Date: 2012-11-17
//          Time: 10:45
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-11-17      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _GENERAL_RANDOM_CSV_H_
#define _GENERAL_RANDOM_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{


	//*************************************************************************************************//
	//������Ҫ��ö��
	//*************************************************************************************************//


	//*************************************************************************************************//
	//��������ʵ����Ϣ
	//*************************************************************************************************//
	struct GeneralRandomCsvInfo
	{
		U32 GeneralRandomId;
		U32 GeneralGroupID;
		U32 CharacterTemplateId;
		U32 GeneralRandomNum;
		U32 AbilityInit1;
		U32 AbilityInit2;
		Int	LifeSpanRandom;

		GeneralRandomCsvInfo()
			:GeneralRandomId(0)
			,GeneralGroupID(0)
			,CharacterTemplateId(0)
			,GeneralRandomNum(0)
			,AbilityInit1(0)
			,AbilityInit2(0)
			,LifeSpanRandom(0)
		{
		}
	};

	//*************************************************************************************************//
	class GeneralRandomCsv
	{
		//*************************************************************************************************//
		//��Ӧ CSV���ÿ���ֶ�
		//*************************************************************************************************//
		enum GeneralRandomCsvRow
		{
			GeneralRandomCsvRow_GeneralRandomId,
			GeneralRandomCsvRow_Notes,
			GeneralRandomCsvRow_GeneralGroupID,						//�����������ID
			GeneralRandomCsvRow_CharacterTemplateId,				//��ɫģ��ID
			GeneralRandomCsvRow_GeneralRandomNum,					//���������ļ��Բ������ֵ
			GeneralRandomCsvRow_AbilityInit1,						//�����ʼ����ID1
			GeneralRandomCsvRow_AbilityInit2,						//�����ʼ����ID2
			GeneralRandomCsvRow_CharacterSkillId1,					//���ܷ���ID1
			GeneralRandomCsvRow_CharacterSkillId2,					//���ܷ���ID2
			GeneralRandomCsvRow_CharacterArtIconGroupId,			//�����ɫͷ�����ID
			GeneralRandomCsvRow_CharacterArtModelGroupId,			//�����ɫģ�ͷ���ID
			GeneralRandomCsvRow_LifeSpanRandom,						//��������
			GeneralRandomCsvRow_GeneralRandomPrice,					//������ļ����Ҫ�Ļ��ѵ���Ʒ
			GeneralRandomCsvRow_GeneralRandomAmount,				//������ļ������Ʒ������
			GeneralRandomCsvRow_Max
		};

	public:
		GeneralRandomCsv();
		~GeneralRandomCsv();
		SINGLETON_INSTANCE(GeneralRandomCsv);

		Bool									load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		GeneralRandomCsvInfo*					getInfoById(U32 id);
		std::vector<const GeneralRandomCsvInfo*>*		getRandomListByGeneralGroupId(U32 GeneralGroupId);
		std::map<U32, GeneralRandomCsvInfo*>*	getList();

	private:
		SimpleMapDataSetManager<U32, GeneralRandomCsvInfo>							mGeneralRandomList;
		std::map<U32/*GeneralGroupID*/, std::vector<const GeneralRandomCsvInfo*> >	mGeneralRandomByGroupId;
	};
}

#endif	//_GENERAL_RECRUIT_CSV_H_
