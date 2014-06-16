/******************************************************************************/
#ifndef _SSKILLOBJECT_H_
#define _SSKILLOBJECT_H_
/******************************************************************************/
#include "MapServerPreqs.h"
#include "SkillObject.h"
/******************************************************************************/
namespace MG
{

	class SSkillObject: public SkillObject
	{
    public:
        SSkillObject( SCharacter* owner );
        virtual ~SSkillObject();

		virtual void								update( Flt delta );

    protected:

		virtual void								onSkillStartClant();

		virtual void								onSkillUpdateClant( Flt delta );

		virtual void								onSkillEndClant();

		virtual void                				onSkillClantFinished();

		virtual void								onSkillStartInject();

		virtual void								onSkillUpdateInject( Flt delta );

		virtual void								onSkillEndInject();

		virtual void                				onSkillInjectFinished();


		///////////////////////////////////////////////////////////////////

		//ִ�м��ܿ�ʼ�����߼�
		virtual void								execServerSkillStartClantLogic();

		//ִ�м�������Update�߼�
		virtual void								execServerSkillClantUpdateLogic();

		//ִ�м��ܽ��������߼�
		virtual void								execServerSkillEndClantLogic();

		//ִ�м��������ű�
		virtual void								execServerSkillStartClantScript();

		//ִ�м�������Update�ű�
		virtual void								execServerSkillClantUpdateScript();

		//ִ�м��ܽ��������ű�
		virtual void								execServerSkillEndClantScript();

		///////////////////////////////////////////////////////////////////

		//ִ�м��ܷ����߼�
		virtual void								execServerSkillStartInjectLogic();

		//ִ�м��ܷ���Update�߼�
		virtual void								execServerSkillInjectUpdateLogic();

		//ִ�м��ܽ��������߼�
		virtual void								execServerSkillEndInjectLogic();

		//ִ�м��ܷ���ű�
		virtual void								execServerSkillStartInjectScript();

		//ִ�м��ܷ���Update�ű�
		virtual void								execServerSkillInjectUpdateScript();

		//ִ�м��ܽ�������ű�
		virtual void								execServerSkillEndInjectScript();


		///////////////////////////////////////////////////////////////////

	private:
		Flt             							mLastTime;
		SCharacter*									mOwner;
		Bool										mIsExecScript;
	};
}

#endif