/******************************************************************************/
#ifndef _SLUACLANQUESTSYSTEM_H_
#define _SLUACLANQUESTSYSTEM_H_
/******************************************************************************/

#include "LuaClanQuestSystem.h"
#include "FrontServerPreqs.h"
/******************************************************************************/


namespace MG
{
	/******************************************************************************/
	//��Ϸ��������ű�ϵͳ
	/******************************************************************************/
	class SLuaClanQuestSystem : public LuaClanQuestSystem
	{
	public:
		SLuaClanQuestSystem();
		virtual ~SLuaClanQuestSystem();
		SINGLETON_INSTANCE(SLuaClanQuestSystem)

		/// �õ�Lua�������
		LuaManager*     getLuaManager(){return mLuaMgr;};

		/// C++ ���� Lua�Ľӿ�
        Bool            execAcceptQuestScript(SClan* clan,ClanQuestObject* clanQuestObj);
        Bool            execSubbmitQuestScript(SClan* clan,ClanQuestObject* clanQuestObj);
		
	protected:
		/// ע���Lua��ط���
		virtual void     registerLua();

	};

}

/******************************************************************************/
#endif

