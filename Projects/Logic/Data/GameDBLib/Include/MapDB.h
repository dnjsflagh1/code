/******************************************************************************/
#ifndef _MAPDBOP_H_
#define _MAPDBOP_H_
/******************************************************************************/
#define  MAP_TABLE_NAME	"map_info"
#include "CommonGameDefine.h"
//#include "MapObject.h"
/******************************************************************************/

#if 0
namespace MG
{
	class MapDbOp
	{
	public:
		static Bool checkOrCreateMapTable(DBDriver& driver);
		static Bool checkMap(DBDriver& driver, Char8* sql);
		static Bool createOrUpdateMapDB(DBDriver& driver, MapObject_OldVersion& mapDB);
		static Bool loadMapFromDB(DBDriver& driver, MapObject_OldVersion& mapDB);
		static Bool loadAllMapFromDB(DBDriver& driver, WorldManager_OldVersion* worldMgr);
		
		//�˺�������ר�ú��� ����CenterServer�������ݿ��ͼ��Ϣ
		//���ã� ����ͼ���ݣ��ĵ�����Ҫ�������ݿ�ĵ�ͼ���ݣ��������ݿ�
		static Bool createDbRecordByMemory(DBDriver& driver, MapObject_OldVersion& mapDB);
	};
}
#endif

#endif