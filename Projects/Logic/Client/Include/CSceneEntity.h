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

        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [主要方法]
        //×××××××××××××××××××××××××××××××××××××××××××××××××

        // 更新
        virtual void            update( Flt delta );

        // 初始化
        virtual void            initialize();
        // 反初始化
        virtual void            unInitialize();
        
        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [基本属性]
        //×××××××××××××××××××××××××××××××××××××××××××××××××
        
		// 是否在屏幕中
		virtual Bool            isInScreen();
		// 换模型
		virtual IEntity*        reloadEntity(U32 modelID);
        // 得到实体对象
        virtual IEntity*        getEntity() {return mEntity;};
        // 获得骨骼的位置
        virtual Vec3            getEntityBonePos( Str boneName );
		// 得到世界坐标
		virtual Bool            getWorldPos( Vec3& worldPos );
		// 得到屏幕坐标
		virtual Bool            getScreenPos( Vec2& screenPos, Vec3 offset );
		// 头顶信息是否显示
		virtual void			setHeadDesVisible( bool visible );
		// 获取了头顶面指针
		virtual HeadDes*		getHeadDes() { return mHeadDes; };

        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [实体行为]
        //×××××××××××××××××××××××××××××××××××××××××××××××××

        // 停止所有主要Action
        virtual void            stopAllMainAction();
		
        //---------------------------------------------------------------------------------------

        // 开始移动行为
		virtual void            doMoveToAction(Vec3 destination, Flt startTime, Bool isBlockCheck = true, ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_DYNAMIC );
        virtual void            doMoveToAction(Vec3 startPos, Vec3 destination, Flt startTime, Bool isBlockCheck = true, ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_DYNAMIC );

        // 停止移动行为
		virtual void            stopMoveToAction();

		virtual void			setIsWaitMoveToAction( Bool isWait );
        // 得到移动行为
        CCSEntityLineMoveAcion* getActiveMoveToAction();

        //---------------------------------------------------------------------------------------

        // 开始播放特效行为,允许同时存在不同的粒子特效
        void                    doPlayParticleEffectAction(Str effectName, Vec3 relativePos, Str bindBoneName = "");
        // 停止播放特效行为
        void                    stopPlayParticleEffectAction(Str effectName);
        
        //---------------------------------------------------------------------------------------

        // 开始交互行为
        void                    doRequestInteractAction(CCharacterSceneEntity* obj);
        // 停止交互行为
        void                    stopRequestInteractAction();
        
        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [动画]
        //×××××××××××××××××××××××××××××××××××××××××××××××××
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