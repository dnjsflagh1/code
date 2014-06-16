/******************************************************************************/
#ifndef _SKILLOBJECT_H_
#define _SKILLOBJECT_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
#include "WorldCoreDefine.h"
#include "CLuaBinder.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //����״̬
    /******************************************************************************/
    enum SkillState
    {
        SKILLSTATE_NONE = 0,
        SKILLSTATE_CLANT,   //�����׶�
        SKILLSTATE_INJECT,  //����׶�
    };

	enum SkillPhases
	{
		SKILLPHASES_NONE = 0,

		SKILLPHASES_START,   //������ʼ�׶�
		SKILLPHASES_UPDATE,
		SKILLPHASES_END,
	};

    /******************************************************************************/
    //���ܲ�������
    /******************************************************************************/
    enum SkillOpType
    {
        SKILLOPTYPE_NONE        = 0,    //������
        SKILLOPTYPE_PASSIVITY   = 1,    //����
		SKILLOPTYPE_EMITTER		= 2,
		//SKILLOPTYPE_INSTANT     = 2,    //˲��
        SKILLOPTYPE_POINT       = 3,    //�㹥��
        SKILLOPTYPE_OBJECT      = 4,    //����Ŀ��
    };
		
    enum STRATEGY_TYPE
    {
        ST_NONE     = 0,    //������
		ST_GENERAL  = 1,
        ST_METHOD   = 2,    //ս��
        ST_PLAN     = 3,    //�Ʋ�
        ST_ARMY     = 4,    //����
        ST_POLITICS = 5,    //����
    };


    enum AFFECT_TYPE
    {
        AT_NONE         = 0,    //������
        AT_SYSTEM       = 1,    //ϵͳ
        AT_NORMAL       = 2,    //һ��
        AT_BENEFICIAL   = 3,    //����
        AT_HARMFUL      = 4,    //����
    };

    /******************************************************************************/
    //���ܶ���
    //��������������ع��ܽӿڣ��ͻ��˺ͷ���˷ֱ�̳�ʵ�ָ��Զ�Ӧ�Ĺ��ܽӿ�
    /******************************************************************************/
    class SkillObject : public CLuaReference
	{
	public:
		SkillObject();
		SkillObject( GAMEOBJ_TYPE ownerType, GameObjectIdType ownerId, UInt ownerIndex );
		virtual ~SkillObject();

    public:
        //�õ�������������
		virtual  SkillInfo*					getSkillInfo();

		virtual  void						setSkillInfo( SkillInfo* skillInfo );

		/////////////////////////////////////////////////////////////////////////////////////////
        //����Ŀ�꣬һ�����ڷ���ָ������ļ��ܣ�SkillOpType = SKILLOPTYPE_POINT
        void								setTargetPosition(Vec3 pos);
        //�õ�Ŀ��
        Vec3								getTargetPosition();

        //����Ŀ�꣬һ�����ڷ�������Ŀ��ļ��ܣ�SkillOpType = SKILLOPTYPE_OBJECT
        void								setTargetObject(GAMEOBJ_TYPE targetType, IdType targetId, Int targetIndex = -1);
        //�õ�Ŀ��
        GAMEOBJ_TYPE						getTargetObjectType();
        //�õ�Ŀ��		
        IdType								getTargetObjectID();

		UInt								getTargetObjectIndex();

		/////////////////////////////////////////////////////////////////////////////////////////
        //���²���
		virtual void						update( Flt delta );

        //ֹͣʹ�ü���
        virtual void						stopUse();
        
		/////////////////////////////////////////////////////////////////////////////////////////

		//�Ƿ�����������
		virtual Bool						isClanting();
        //��ʼ�������� //isCheckTiming:�Ƿ������������ʱ��
        virtual void						startClant( Bool isUpdate = false );

		/////////////////////////////////////////////////////////////////////////////////////////
		//�Ƿ����ͷż���
		virtual Bool						isInjecting();
        //��ʼ�ͷż���
        virtual void						startInject( Bool isUpdate = false );

        //�Ƿ�ȫ�����
                Bool                		isFinished(){ return mIsFinished;};
	public:
		GameObjectIdType					getOwnerID();

		GAMEOBJ_TYPE						getOwnerType();

		UInt								getOwnerIndex();

		//PlayerIdType						getPlayerID();

    protected:
		//skill��ʼʹ��
		virtual void						onSkillStart();
		//skillUpdate
		virtual void						onSkillUpdate( Flt delta );
		//skillʹ�ý���
		virtual void						onSkillEnd();
		//skill���ʹ��
		virtual void						onSkillFinished();
		//skill������ʼ
		virtual void						onSkillStartClant() = 0;
		//skill����Update
		virtual void						onSkillUpdateClant( Flt delta ) = 0;
		//skill��������
		virtual void						onSkillEndClant() = 0;
		//skill�������
		virtual void                		onSkillClantFinished() = 0;
		//skill���俪ʼ
		virtual void						onSkillStartInject() = 0;
		//skill����Update
		virtual void						onSkillUpdateInject( Flt delta ) = 0;
		//skill�������
		virtual void						onSkillEndInject() = 0;
		//skill�������
		virtual void                		onSkillInjectFinished() = 0;

	
		/////////////////////////////////////////////////////////////////////////////////////////

		void								setUpdateTime( Flt time );

		void								setStopUpdateTime( Flt time );

		/////////////////////////////////////////////////////////////////////////////////////////

	protected:

		SkillState							mState;

		SkillPhases							mPhases;

		// ����Ŀ��λ��
		Vec3								mTargetPosition;

		// ����Ŀ�����
		GAMEOBJ_TYPE    					mTargetObjectType;
		IdType          					mTargetObjectID;
		Int									mTargetObjectIndex;

		// �Ƿ���ʱ��
		Bool								mIsUpdate;

		// ����ʱ��
		Flt            						mCurrTiming;
		// ��ʱ��
		Flt            						mTotalTiming;
		// �Ƿ��ʱȫ�����
		Bool								mIsFinished;

		GameObjectIdType					mOwnerId;
		UInt								mOwnerIndex;
		GAMEOBJ_TYPE						mOwnerType;

		//���ܻ�������
		SkillInfo*							mSkillInfo;

		Flt									mUpdateTime;

		Flt									mPauseUpdateTime;
	
	};
}

#endif