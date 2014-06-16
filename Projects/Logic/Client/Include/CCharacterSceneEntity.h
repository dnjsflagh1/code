/******************************************************************************/
#ifndef _H_CCHARACTER_SCENE_ENTITY_
#define _H_CCHARACTER_SCENE_ENTITY_
/******************************************************************************/
#include "ClientPreqs.h"
#include "GameObject.h"
#include "CharacterSceneEntity.h"
#include "CSceneEntity.h"
#include "CSceneObject.h"
/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //CCharacterSceneEntity
    /******************************************************************************/

    class CCharacterSceneEntity : public CSceneEntity, public CharacterSceneEntity
    {
    public:
        CCharacterSceneEntity(IEntity* entity, GAMEOBJ_TYPE type, GAMEOBJ_QUERY_TYPE queryType, CharacterEntityData* dynamicData);
        virtual ~CCharacterSceneEntity();

    public:

    //��������������������������������������������������������������������������������������������������
    //  [��Ҫ����]
    //��������������������������������������������������������������������������������������������������
        // ��ʼ��
        virtual void				        initialize();
        // ����ʼ��
        virtual void				        unInitialize();
        // ����
        virtual void				        update( Flt delta );

        /// �õ�����ʹ�ù�����
        CSkillUseManager*	                getSkillUseManager(){return mSkillUseManager;};

    //��������������������������������������������������������������������������������������������������
    //  [��������]
    //��������������������������������������������������������������������������������������������������

        // �õ���������
        //CharacterData*				        getBaseData();
        
        // �õ���̬����
        CharacterEntityData*				getDynamicData();

    //��������������������������������������������������������������������������������������������������
    //  [ʵ����Ϊ]
    //��������������������������������������������������������������������������������������������������

        // ֹͣ������ҪAction
        virtual void                        stopAllMainAction();
		
		// ����ս��״ͼ�� ��ƽ״̬
		virtual void						setBattleState(Bool battleState, Bool isPlayIdle = false );

        //---------------------------------------------------------------------------------------

        // ��ʼ������Ϊ
        void                                doDieAction();
        // ֹͣ������Ϊ
        void                                stopDieAction();

		void								setIsMoving(Bool isMoving);
		Bool								getIsMoving();


        //---------------------------------------------------------------------------------------

        // ��ʼ����������Ϊ
        void                                doClantSkillAcion(IdType skillid);
        // ֹͣ����������Ϊ
        void                                stopClantSkillAcion();

		//---------------------------------------------------------------------------------------
		void								addEffect(UInt effectFileId, Bool isAutoDestroy = true );

		void								endEffect(UInt effectFileId);

        //---------------------------------------------------------------------------------------

        // ��ʼ�ͷż�����Ϊ
        void                                doInjectSkillAction(IdType skillid);
        void                                doInjectSkillAction(IdType skillid, Vec3 target);
        void                                doInjectSkillAction(IdType skillid, GAMEOBJ_TYPE targetType, IdType targetId);
        // ֹͣ�ͷż�����Ϊ
        void                                stopInjectSkillAction();

        //---------------------------------------------------------------------------------------

		void								setAIEnable( Bool enable );

		//---------------------------------------------------------------------------------------

		void								setAIController( Bool enable );

		//---------------------------------------------------------------------------------------
	//��������������������������������������������������������������������������������������������������
	// [characterentitydata]
	//��������������������������������������������������������������������������������������������������
		void								setHp(Int val);
		void								setMp(Int val);
		void								setSp(Int val);
		void								setHpMax(Int val);
		void								setMpMax(Int val);
		void								setSpMax(Int val);
		Int									getHp();
		Int									getMp();
		Int									getSp();
		Int									getHpMax();
		Int									getMpMax();
		Int									getSpMax();

    //��������������������������������������������������������������������������������������������������
    //  [ͷ����]
    //��������������������������������������������������������������������������������������������������

        // ��ʾ��Ѫ
        void                                showReduceHP(UInt num);
        // ��ʾ��Ѫ
        void                                showRecoverHP(UInt num);

		virtual void						setPos(Vec3 pos);
		virtual void						setDir(Vec3 dir);

		virtual Vec3						getPos(Bool isIgnoreHeight = true);
		virtual Vec3						getDir();

		void								setIsCanMove(Bool isCanMove);
		Bool								getIsCanMove();

		void								die();

	public:
		//״̬������������
		CBuffManager*						getCBuffManager();
		///////////////////////////////////////////////////////////////////////////////////////////

		//�õ���ɫģ��ָ��
		const CharacterTempInfo*            getCharacterTempInfo();
		void								setCharacterTempInfo();

		//״̬������������

		///////////////////////////////////////////////////////////////////////////////////////////
		const FightAIGroup*					getFightAIGroup();

		const BaseAIGroup*					getBaseAIGroup();

		///////////////////////////////////////////////////////////////////////////////////////////

		void								addFightAITriggerCount( UInt fightAIId );

		UInt								getFightAITriggerCount( UInt fightAIId );

		void								clearFightAITriggerCount();

	public:

		CAIController*						getAIController();
		//FightManager*						getFightManager();

		///////////////////////////////////////////////////////////////////////////////////////////
		

    protected:

		CBuffManager*						mpCBuffManager;

        CSkillUseManager*					mSkillUseManager;
		//FightManager*						mFightManager;
		//��ɫģ����Ϣ
		const CharacterTempInfo*			mCharacterTempInfo;

		const BaseAIGroup*					mBaseAIGroup;
		const FightAIGroup*					mFightAIGroup;

		CAIController*						mAIController;

		std::map<UInt, UInt>				mFightAITriggerCountList;

		Bool								mIsMoving;
		Bool								mIsCanMove;

		IEffectComponent*					mEffectComponent;
        Str     						    mEffectName;
		UInt								mEffectFileId;
    };
}
/******************************************************************************/
#endif // _H_CCHARACTER_SCENE_ENTITY_
/******************************************************************************/