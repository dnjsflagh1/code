/******************************************************************************/
#ifndef _LUASKILLSYSTEM_H_
#define _LUASKILLSYSTEM_H_
/******************************************************************************/

#include "WorldCorePreqs.h"

/******************************************************************************/


namespace MG
{
	/******************************************************************************/
	//��Ϸ���ܽű�ϵͳ
	/******************************************************************************/
	class LuaSkillSystem
	{
	public:
		LuaSkillSystem();
		virtual ~LuaSkillSystem();
		//SINGLETON_INSTANCE(LuaSkillSystem)

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

		/// ���ؼ��ܻ�����Ϣ
		Bool			loadSkillBaseInfo();

	private:

		// �õ�һ�����ֵı�
		void			getNumberListFromTable( Int tableIndex, Str name, std::vector<U32>& list );
		// �õ�һ�����ֵı�
		void			getNumberMapFromTable( Int tableIndex, Str name, std::map<IdType,UInt>& map  );

	protected:

        // �ű��������
		LuaManager*		mLuaMgr;

	};

}

/******************************************************************************/
#endif

