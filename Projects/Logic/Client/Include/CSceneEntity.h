/******************************************************************************/
#ifndef _CSCENEENTITY_H_
#define _CSCENEENTITY_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CSceneObject.h"
#include "CommonGameDefine.h"
#include "ISceneNodeAction.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //CSceneEntity
    /******************************************************************************/

    class CSceneEntity : public CSceneObject
    {
    public:

        CSceneEntity(IEntity* entity, GAMEOBJ_TYPE type, GAMEOBJ_QUERY_TYPE queryType, SceneObjectData* dynamicData);
        virtual ~CSceneEntity();
        
    public:

        //��������������������������������������������������������������������������������������������������
        //  [��Ҫ����]
        //��������������������������������������������������������������������������������������������������

        // ����
        virtual void            update( Flt delta );

        // ��ʼ��
        virtual void            initialize();
        // ����ʼ��
        virtual void            unInitialize();
        
        //��������������������������������������������������������������������������������������������������
        //  [��������]
        //��������������������������������������������������������������������������������������������������
        
		// �Ƿ�����Ļ��
		virtual Bool            isInScreen();
		// ��ģ��
		virtual IEntity*        reloadEntity(U32 modelID);
        // �õ�ʵ�����
        virtual IEntity*        getEntity() {return mEntity;};
        // ��ù�����λ��
        virtual Vec3            getEntityBonePos( Str boneName );
		// �õ���������
		virtual Bool            getWorldPos( Vec3& worldPos );
		// �õ���Ļ����
		virtual Bool            getScreenPos( Vec2& screenPos, Vec3 offset );
		// ͷ����Ϣ�Ƿ���ʾ
		virtual void			setHeadDesVisible( bool visible );
		// ��ȡ��ͷ����ָ��
		virtual HeadDes*		getHeadDes() { return mHeadDes; };

        //��������������������������������������������������������������������������������������������������
        //  [ʵ����Ϊ]
        //��������������������������������������������������������������������������������������������������

        // ֹͣ������ҪAction
        virtual void            stopAllMainAction();
		
        //---------------------------------------------------------------------------------------

        // ��ʼ�ƶ���Ϊ
		virtual void            doMoveToAction(Vec3 destination, Flt startTime, Bool isBlockCheck = true, ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_DYNAMIC );
        virtual void            doMoveToAction(Vec3 startPos, Vec3 destination, Flt startTime, Bool isBlockCheck = true, ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_DYNAMIC );

        // ֹͣ�ƶ���Ϊ
		virtual void            stopMoveToAction();

		virtual void			setIsWaitMoveToAction( Bool isWait );
        // �õ��ƶ���Ϊ
        CCSEntityLineMoveAcion* getActiveMoveToAction();

        //---------------------------------------------------------------------------------------

        // ��ʼ������Ч��Ϊ,����ͬʱ���ڲ�ͬ��������Ч
        void                    doPlayParticleEffectAction(Str effectName, Vec3 relativePos, Str bindBoneName = "");
        // ֹͣ������Ч��Ϊ
        void                    stopPlayParticleEffectAction(Str effectName);
        
        //---------------------------------------------------------------------------------------

        // ��ʼ������Ϊ
        void                    doRequestInteractAction(CCharacterSceneEntity* obj);
        // ֹͣ������Ϊ
        void                    stopRequestInteractAction();
        
        //��������������������������������������������������������������������������������������������������
        //  [����]
        //��������������������������������������������������������������������������������������������������
		virtual void			applyActionGroup() {}

		virtual void            setIdleAnimation( Str animName, Bool isIdle, Bool isPlay = false );

		virtual void            setFreezeLastFrame( Str aniName, Bool isFreeze );

        virtual void            playAnimation(Str animName,  
                                              Bool randomTimePlaye = true, 
                                              Bool isLoop=false, 
                                              Bool isLastFrameStop = false, 
                                              Bool isReset = true );

        virtual	void            stopAnimation(Str animName); 

        virtual	void            stopAllAnimation(); 

		virtual Bool            isPlayAnimation(Str animName);

		virtual Flt             getAnimationLength(Str animName);

		virtual Bool            isRiding() { return false; }

		virtual void            setBattleState(Bool isBattle) {}

		virtual Bool            isBattleState() { return false; }

	protected:

		virtual	void            setActionGroup( U32 actionGroup, Bool isRide );

		virtual void            getActionGroup( Str& weaponAction, Str& rideAction );
        
    protected:

        IEntity*    mEntity;

        HeadDes*    mHeadDes;
    };
}
/******************************************************************************/
#endif // CSceneEntity
/******************************************************************************/