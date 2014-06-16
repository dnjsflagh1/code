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
		//设置自己的父亲
		void	setParent(SClan* pSClan);
		//处理新的buff或者buff消亡
		void	updateBuff(PlayerCharacterIdType id, UInt timeUse, UInt curAddNum, UInt buffId);
		//从DB加载Buff。
		void	sendBuffToMapServer();
		//角色移除删除Buff。
		void	deleteBuffByPlayerCharacterId(PlayerCharacterIdType id);
		//氏族推出
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