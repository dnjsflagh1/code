//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: ArtMapResCsv.h
//        Author: yuanlinhu
//          Date: 2012-3-6
//          Time: 11:27
//   Description: 
//			��ȡ ArtMapRes.csv ��
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-6      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _ART_MAP_RES_CSV_H_
#define _ART_MAP_RES_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"
#include "MapListCsv.h"

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//
	//��Ӧ CSV���ÿ���ֶ�
	//*************************************************************************************************//
	enum ArtMapResCsvRow
	{
		AMR_ArtMapResId		= 0,
		AMR_ArtMapResNote,
		AMR_Name,
		AMR_AdvanceType,
		AMR_UseType,
		AMR_ResPackId,
		AMR_BaseFilePath,
		AMR_RPGCamSetID,
		AMR_RPGRadarID,
		AMR_SLGCamSetID,
		AMR_SLGRadarID,
		
		AMR_Max,
	};

	//*************************************************************************************************//
	//������ͼ��Դ��Ϣ
	//*************************************************************************************************//
	struct ArtMapResCsvInfo
	{
		ArtMapResIdType		artMapResId;		//��ͼ��Դ�ĵ���Id
		Str16				name;				//��ͼ��Դ������
		//...
		Str16				BaseFilePath;		//����������ͼ��ͼ�ļ���·����128����ĸ�ͷ���

		MapType				mapType;			//��ͼ����
		U32					rpgCameraId;		//RPG�����ID
		U32					rpgRadarId;			//RPG�����ID
		U32					slgCameraId;		//SLG�����ID	
		U32					slgRadarId;			//SLGС��ͼID
	};

	//--------------------------------------------------------------------------
	class ArtMapResCsv
	{
	public:
		ArtMapResCsv();
		~ArtMapResCsv();
		SINGLETON_INSTANCE(ArtMapResCsv);
		// MG_CN_MODIFY
		Bool	load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);

		ArtMapResCsvInfo*				getArtMapResInfoById(ArtMapResIdType id);
		
		const ArtMapResCsvInfo*			getArtMapResInfoByIndex(I32 order);

	private:

		SimpleMapDataSetManager<ArtMapResIdType, ArtMapResCsvInfo>		mArtMapResList;
	};
}

#endif	//_ART_MAP_RES_CSV_H_