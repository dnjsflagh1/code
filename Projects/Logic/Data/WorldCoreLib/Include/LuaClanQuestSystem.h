/******************************************************************************/
#ifndef _LUACLANQUESTSYSTEM_H_
#define _LUACLANQUESTSYSTEM_H_
/******************************************************************************/

#include "WorldCorePreqs.h"

/******************************************************************************/


namespace MG
{
	/******************************************************************************/
	//��Ϸ���ܽű�ϵͳ
	/******************************************************************************/
	class LuaClanQuestSystem
	{
	public:
		LuaClanQuestSystem();
		virtual ~LuaClanQuestSystem();

		/// ��ʼ��
		virtual Bool    initialize(LuaManager* luaMgr, Str filePath);
		/// ����ʼ��
		virtual Bool    uninitialize();

		/// �õ�Lua�������
		LuaManager*     getLuaManager(){return mLuaMgr;};

        
	protected:

		/// ����Lua�ļ�
		Bool            loadLuaFile(Str filePath);

		/// ע���Lua��ط���
		virtual void    registerLua() = 0;

	protected:
        // �ű��������
		LuaManager*		mLuaMgr;
	};

}

/******************************************************************************/
#endif

