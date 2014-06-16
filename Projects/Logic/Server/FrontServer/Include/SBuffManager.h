//************************************************************************************************
#ifndef _H_SBUFFMANAGER_
#define _H_SBUFFMANAGER_
//************************************************************************************************
#include "FrontServerPreqs.h"
#include "BuffData.h"
//************************************************************************************************
namespace MG
{
	class SBuffManager
	{
	private:
		typedef std::map<UInt, BuffData>	MapBuffData;	
		typedef std::map<PlayerCharacterIdType, MapBuffData> MapCharacterBuff;

	public:
		SBuffManager();
		~SBuffManager(){;}

	public:
		//�����Լ��ĸ���
		void	setParent(SClan* pSClan);
		//�����µ�buff����buff����
		void	updateBuff(PlayerCharacterIdType id, UInt timeUse, UInt curAddNum, UInt buffId);
		//��DB����Buff��
		void	sendBuffToMapServer();
		//��ɫ�Ƴ�ɾ��Buff��
		void	deleteBuffByPlayerCharacterId(PlayerCharacterIdType id);
		//�����Ƴ�
		void	clear();
		MapCharacterBuff&	getMapCharacterBuff(){return mMapCharacterBuff;}

	protected:
	
		MapCharacterBuff				mMapCharacterBuff;

		SClan* mpParent;

	};
}
//************************************************************************************************
#endif
//************************************************************************************************