/******************************************************************************/
#ifndef _CSKILLOBJECT_H_
#define _CSKILLOBJECT_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "SkillObject.h"
#include "CSkillEffectSystem.h"
/******************************************************************************/
namespace MG
{

    /******************************************************************************

		# �ͻ��˼��ܶ���

		# ���糡����������ʾ���ֵļ��ܶ��󣬰�����������������Ч��

		# lua�ӿ�

			@ startClant()(������֪ͨ����). 
			  �е���Lua_ExecClientStartClantScript�ű�.
			@ onClantFinished()(�������м�ʱ����).�����յ��µ�Clantʱ����ã�
			  �е���Lua_ExecClientEndClantScript�ű�.
			@ startInject()(������֪ͨ����).
			  �е���Lua_ExecClientStartInjectScript�ű�.
			@ onInjectFinished()(�������м�ʱ����).�����յ��µ�Injectʱ����ã�
			  �е���Lua_ExecClientEndInjectScript�ű�.

		# Clant��Inject����ǰ�������PrepareUseSkill(���Ƴ���ǰ���SkillObject)

		# ������ɫ��ʱ��

    ******************************************************************************/
    class CSkillObject : public SkillObject
    {
    public:
        CSkillObject( CCharacterSceneEntity* owner );
        virtual ~CSkillObject();

    public:
        //�õ�֧����
        //virtual CCharacterSceneEntity*      getCharacterEntity();

    public:

		///////////////////////////////////////////////////////////////////

		//�Ƿ�ִ�нű�
		void								setIsExecScript( Bool isExecScript );

		Bool								getIsExecScript();

		///////////////////////////////////////////////////////////////////

		virtual void						startInject( Bool isUpdate  = false  );

		///////////////////////////////////////////////////////////////////

		Bool								getIsEndBehind();

		///////////////////////////////////////////////////////////////////


		CCharacterSceneEntity*				getOwner();

		///////////////////////////////////////////////////////////////////

    protected:

		///////////////////////////////////////////////////////////////////

		virtual void						onSkillFinished();

		virtual void						onSkillEnd();

		///////////////////////////////////////////////////////////////////

		//skill������ʼ
		virtual void						onSkillStartClant();
		//skill����Update
		virtual void						onSkillUpdateClant( Flt delta );
		//skill��������
		virtual void						onSkillEndClant();
		//skill�������
		virtual void                   		onSkillClantFinished();
		//skill����ǰ�ÿ�ʼ
		virtual	void						onSkillStartFront();
		//skill����ǰ�ý���
		virtual	void						onSkillEndFront();
		//skill���俪ʼ
		virtual void						onSkillStartInject();
		//skill����Update
		virtual void						onSkillUpdateInject( Flt delta );
		//skill�������
		virtual void						onSkillEndInject();
		//skill�������
		virtual void                   		onSkillInjectFinished();
		//skill���ÿ�ʼ
		virtual void                        onSkillStartBehind();
		//skill���ý���
		virtual void                        onSkillEndBehind();

		///////////////////////////////////////////////////////////////////

		//ִ�м��ܿ�ʼ�����߼�
		virtual void						execClientSkillStartClantLogic();

		//ִ�м�������Update�߼�
		virtual void						execClientSkillClantUpdateLogic();

		//ִ�м��ܽ��������߼�
		virtual void						execClientSkillEndClantLogic();

		//ִ�м��������ű�
		virtual void						execClientSkillStartClantScript();

		//ִ�м�������Update�ű�
		virtual void						execClientSkillClantUpdateScript();

		//ִ�м��ܽ��������ű�
		virtual void						execClientSkillEndClantScript();

		///////////////////////////////////////////////////////////////////

		//ִ�м���ǰ�ÿ�ʼ�߼�
		virtual void						execClientSkillStartFrontLogic();

		//ִ�м���ǰ�ý����߼�
		virtual void						execClientSkillEndFrontLogic();

		//ִ�м���ǰ�ÿ�ʼ�ű�
		virtual void						execClientSkillStartFrontScript();

		//ִ�м���ǰ�ý����ű�
		virtual void						execClientSkillEndFrontScript();

		////////////////////////////////////////////////////////////////////

		//ִ�м��ܽ������ÿ�ʼ�߼�
		virtual void						execClientSkillStartBehindLogic();

		//ִ�м��ܽ������ý����߼�
		virtual void						execClientSkillEndBehindLogic();

		//ִ�м��ܺ��ÿ�ʼ�ű�
		virtual void						execClientSkillStartBehindScript();

		//ִ�м��ܺ��ý����ű�
		virtual void						execClientSkillEndBehindScript();

		///////////////////////////////////////////////////////////////////

		//ִ�м��ܷ����߼�
		virtual void						execClientSkillStartInjectLogic();

		//ִ�м��ܷ���Update�߼�
		virtual void						execClientSkillInjectUpdateLogic();

		//ִ�м��ܽ��������߼�
		virtual void						execClientSkillEndInjectLogic();

		//ִ�м��ܷ���ű�
		virtual void						execClientSkillStartInjectScript();

		//ִ�м��ܷ���Update�ű�
		virtual void						execClientSkillInjectUpdateScript();

		//ִ�м��ܽ�������ű�
		virtual void						execClientSkillEndInjectScript();


		///////////////////////////////////////////////////////////////////

	protected:

		CCharacterSceneEntity*				mOwner;
		Bool								mIsExecScript;
		Bool								mIsEndBehind;
    };
}

#endif