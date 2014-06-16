/******************************************************************************/
#ifndef _CLUASKILLSYSTEM_H_
#define _CLUASKILLSYSTEM_H_
/******************************************************************************/

#include "LuaSkillSystem.h"
#include "CSkillObject.h"

/******************************************************************************/


namespace MG
{
	/******************************************************************************/
	//��Ϸ���ܽű�ϵͳ
	/******************************************************************************/
	class CLuaSkillSystem : public LuaSkillSystem
	{
	public:
		CLuaSkillSystem();
		virtual ~CLuaSkillSystem();
		SINGLETON_INSTANCE(CLuaSkillSystem)

		/// �ͻ��˵��ã�ִ�п�ʼ�������ܽű����ɷ�������Ϣ����
		void							execClientStartClantScript(CSkillObject* skillObject);
		/// �ͻ��˵��ã�ִ���������ܼ�ʱ�ű�����ʱ��������
		void							execClientUpdateClantScript(CSkillObject* skillObject, Flt time);
		/// �ͻ��˵��ã�ִ�н����������ܽű����ɷ�������Ϣ����
		void							execClientEndClantScript(CSkillObject* skillObject);
		
		/// �ͻ��˵��ã�ִ�м���ǰ�ÿ�ʼ�ű����ɷ�������Ϣ����
		void							execClientStartFrontScript(CSkillObject* skillObject);
		/// �ͻ��˵��ã�ִ�м���ǰ�ÿ�ʼ�ű����ɷ�������Ϣ����
		void							execClientEndFrontScript(CSkillObject* skillObject);
		/// �ͻ��˵��ã�ִ�м��ܺ��ý����ű�����ʱ��������
		void							execClientStartBehindScript(CSkillObject* skillObject);
		/// �ͻ��˵��ã�ִ�м��ܺ��ý����ű�����ʱ��������
		void							execClientEndBehindScript(CSkillObject* skillObject);
		/// �ͻ��˵��ã�ִ�п�ʼ�ͷż��ܽű����ɷ�������Ϣ����
		void							execClientStartInjectScript(CSkillObject* skillObject);
		/// �ͻ��˵��ã�ִ���ͷż��ܼ�ʱ�ű�����ʱ��������
		void							execClientUpdateInjectScript(CSkillObject* skillObject, Flt time);
		/// �ͻ��˵��ã�ִ�н������ܼ�ʱ�ű�����ʱ��������
		void							execClientEndInjectScript(CSkillObject* skillObject);


        /// �ͻ��˵��� �� ִ�п�ʼ������ײӰ��ű�
        void							execClientCollisionAffectScript(CCharacterSceneEntity* affecter, UInt addecterTotal, CSkillObject* skillObject, CSkillEffect* skillEffect);

	protected:
		virtual void					registerLua();

	};

}

/******************************************************************************/
#endif

