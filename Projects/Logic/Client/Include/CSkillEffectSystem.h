/******************************************************************************/
#ifndef _CSKILLEFFECTSYSTEM_H_
#define _CSKILLEFFECTSYSTEM_H_
/******************************************************************************/
#include "ClientPreqs.h"
/******************************************************************************/

namespace MG
{   
    
    /******************************************************************************
	#	��Ϸ������Чϵͳ.

	#	�ڼ��ܵķ�������б����ɣ���Ϊ�ڽű������ɺ��ڴ���������.

	#	���ٷ�Ϊ2��
		1.�������ٺ�
		2.���ܽ������٣�ͨ���ɽű����ܶ����������.ͨ���ű�����effect:end() (���������ýű���Ч����Ϊ��)

	#	��Ϊ������Ч���ٵĻ���ע�����������Ҫ�ɶ�.

	#	���ӳ�ʱ����ͷţ��Ƚű���C++�����ͷ�֪ͨ�ײ������ɺ��
    ******************************************************************************/
    class CSkillEffectSystem
    {
    public:
        CSkillEffectSystem();
        virtual ~CSkillEffectSystem();
		//SINGLETON_INSTANCE(CSkillEffectSystem)

        /// ��ʼ��
        virtual Bool                    	initialize();
        /// ����ʼ��
        virtual Bool                    	uninitialize();
        /// ����
        virtual void                    	update( Flt delta );
        // ������м���
        virtual void                    	clear();
        // �����ܽ���ʱ
        virtual void                    	onSkillEnded( CSkillObject* skillObject );


        // ���ӵ���Ч
        virtual  CPointSkillEffect*			addPointEffect( CSkillObject* skillObject );
        // ���ӵ���Ч
        virtual CEmitterSkillEffect*		addEmitterSkillEffect( CSkillObject* skillObject );
		// ��Ŀ����Ч
		virtual CObjectSkillEffect*			addObjectSkillEffect( CSkillObject* skillObject );
		// ��˲����Ч
		virtual CInstantSkillEffect*		addInstantSkillEffect( CSkillObject* skillObject );
		// �������Ч
		virtual CSprintSkillEffect*			addSprintSkillEffect( CSkillObject* skillObject );

		virtual CGoUpAndDownSkillEffect*    addGoUpAndDownSkillEffect( CSkillObject* skillObject );

    protected:
		
  //      // ��������Ч
  //      virtual  CPointSkillEffect*       createPointEffect( SkillObject* skillObject ) = 0;
  //      // ����ֱ�߷�����Ч
  //      virtual CEmitterSkillEffect*     createLineFlyEffect( SkillObject* skillObject ) = 0;
		//// ����Ŀ����Ч
		//virtual CObjectSkillEffect*		createObjectEffect( SkillObject* skillObject ) = 0;
		//// ����˲����Ч
		//virtual CInstantSkillEffect*		createInstantEffect( SkillObject* skillObject ) = 0;
		//// ���������Ч
		//virtual CSprintSkillEffect*		createSprintEffect( SkillObject* skillObject ) = 0;

        
        // ������Ч�б�
        std::list< CSkillEffect* >			mSkillEffectList;
    };

}

/******************************************************************************/
#endif

