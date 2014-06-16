/******************************************************************************/
#ifndef _SLUASKILLSYSTEM_H_
#define _SLUASKILLSYSTEM_H_
/******************************************************************************/
#include "MapServerPreqs.h"
#include "LuaSkillSystem.h"
/******************************************************************************/


namespace MG
{
	/******************************************************************************/
	//��Ϸ���ܽű�ϵͳ
	/******************************************************************************/
	class SLuaSkillSystem : public LuaSkillSystem
	{
	public:
		SLuaSkillSystem();
		virtual ~SLuaSkillSystem();
		SINGLETON_INSTANCE(SLuaSkillSystem)

		/// C++ ���� Lua�Ľӿ�

        /// ���������� �� ִ�п�ʼ������ײӰ��ű�
		void            execServerCollisionAffectScript(SCharacter* Injecter, SCharacter* affecter, UInt affecterTotal, IdType skillID );
        
	protected:
		/// ע���Lua��ط���
		void            registerLua();

	};

}

/******************************************************************************/
#endif

