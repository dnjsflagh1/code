//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: RelationCsvBase.h
//        Author: yuanlinhu
//          Date: 2012-3-6
//          Time: 15:00
//   Description: 
//			ȡ����Relation�� �ṩ ��������
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-6      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _RELATION_CSV_BASE_H_
#define _RELATION_CSV_BASE_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{

	//*************************************************************************************************//
	//��Ӧ CSV���ÿ���ֶ�
	//*************************************************************************************************//
	enum RelationCsvBaseRow
	{
		RCB_RelationId = 0,			//��ϵ����id,��������������
		RCB_MapId,					//���¶�Ӧ�����������ĵ�ͼid
		RCB_ArtName,				//�����������ͣ���¼�����Ķ�Ӧid ��EntityName��
		RCB_GameDataId,				//�����������ͣ���¼�߻�ָ���Ķ�Ӧ����id

		RCB_Max,
	};

	//*************************************************************************************************//
	//������ͼ��ϵ��Ϣ
	//*************************************************************************************************//
	struct RelationInfo
	{
		RelationIdType		relationId;
		MapIdType			mapId;
		Str16				artName;
		GameObjectIdType	gameDataId;
	};

	//--------------------------------------------------------------------------
	class RelationCsvBase
	{
	public:
		RelationCsvBase();
		~RelationCsvBase();
		// MG_CN_MODIFY
		Bool				load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);

		RelationInfo*		getRelationInfoByGameDataId(const GameObjectIdType gameObjectId);

	private:
		SimpleMapDataSetManager<RelationIdType, RelationInfo>		mRelationList;
	};
}

#endif	//_RELATION_CSV_BASE_H_