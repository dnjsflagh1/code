/******************************************************************************/
#ifndef _PLACEDB_H_
#define _PLACEDB_H_
/******************************************************************************/
#define  PLACE_TABLE_NAME	"place_info"
#include "CommonGameDefine.h"
//#include "PlaceObject.h"

/******************************************************************************/
#if 0
namespace MG
{
	class PlaceDBOp
	{
	public:
		static Bool checkOrCreatePlaceTable(DBDriver& driver);
		static Bool checkPlace(DBDriver& driver, Char8* sql);
		static Bool createOrUpdatePlaceDB(DBDriver& driver, PlaceObject_OldVersion& placeDB);
		static Bool loadPlaceFromDB(DBDriver& driver, PlaceObject_OldVersion& placeDB);
		static Bool loadAllPlaceFromDB(DBDriver& driver, WorldManager_OldVersion* worldMgr);

		//�˺�������ר�ú��� ����CenterServer�������ݿ��ͼ��Ϣ
		//���ã� ����ͼ���ݣ��ĵ�����Ҫ�������ݿ�ĵ�ͼ���ݣ��������ݿ�
		static Bool createDbRecordByMemory(DBDriver& driver, PlaceObject_OldVersion& placeDB);
	};
}

#endif
#endif