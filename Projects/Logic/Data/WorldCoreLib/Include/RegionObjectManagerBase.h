//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\Game\WorldCoreLib\Include\WorldManagerNew.h
//        Author: yuanlinhu
//          Date: 2012-3-12
//          Time: 13:46
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-12      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _WORLD_MANAGER_NEW_H_
#define _WORLD_MANAGER_NEW_H_
/******************************************************************************/

#include "WorldCorePreqs.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//����������,��������
	/******************************************************************************/
	class RegionObjectManagerBase
	{
	public:
		RegionObjectManagerBase(){};
		virtual ~RegionObjectManagerBase(){};

		Bool				loadCsvAndCreateRegion();


		virtual		Bool	loadCsv()																	= NULL;

		virtual		Bool	hasMapDistributionObj(MapDistributionIdType mapDistributionId)				= NULL;
		virtual		Bool	hasPlaceObj(PlaceIdType placeId)											= NULL;
		virtual		Bool	hasTiroInstanceObj(InstanceIdType instanceId)								= NULL;
		virtual		Bool	hasPveInstanceObj(InstanceIdType instanceId)								= NULL;
		virtual		Bool	hasHomeInstanceObj(InstanceIdType instanceId)								= NULL;

		virtual		void	createMapDistributionObj(MapDistributionCsvInfo* mapDistributionCsvInfo)	= NULL;
		virtual		void	createPlaceObj(PlaceListCsvInfo* placeInfo)									= NULL;
		virtual		void	createTiroInstanceObj(InstanceListCsvInfo* instanceInfo)					= NULL;
		virtual		void	createPveInstanceObj(InstanceListCsvInfo* instanceInfo)						= NULL;
		virtual		void	createHomeInstanceObj(InstanceListCsvInfo* instanceInfo)					= NULL;
		
		
	private:
		void				createAllMapDistribution();	//�������ݣ�, ͨ�� MapDistributionCsv ����  
		void				createAllPlace();			//ͨ�� PlaceListCsv ����
		void				createAllTiroInstance();	//���� ����(InstanceNewList.csv ��)�ȸ���
		void				createAllPVEInstance();		//���� pve(InstancePvEList.csv ��) �ȸ���
		void				createAllHomeInstance();	//���� pve(InstanceHomeList.csv ��) �ȸ���
	};
}

#endif	//_WORLD_MANAGER_NEW_H_	