/******************************************************************************/
#ifndef _CLINEFLYSKILLEFFECT_H_
#define _CLINEFLYSKILLEFFECT_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CSkillEffect.h"

/******************************************************************************/

namespace MG
{   

    /******************************************************************************/
    //点技能特效
    /******************************************************************************/
    class CEmitterSkillEffect : public CSkillEffect
    {
		enum EmitterSkillEffectState
		{
			ESES_NULL,
			ESES_CREATEEFFECT,
			ESES_CHECKCOLLISION,
		};

    public:

		struct EffectEntityInfo
		{
			ISceneObject*		effectEntity;
			// 引擎特效实体最近次位置
			Vec3				effectEntityLastPos;

			EffectEntityInfo(){effectEntity = NULL;}
		};

		enum EmitType
		{
			ET_PARALLEL,		//平行发射
			ET_SCATTER,			//分散发射
		};

		enum FlyTrackType
		{
			FTT_LINE,				//直线
			FTT_GATHERED,			//聚集
			FTT_DIVERGENT,			//发散
			FTT_HELICAL,			//螺旋
		};

		CEmitterSkillEffect( CSkillObject* object );
		virtual ~CEmitterSkillEffect();


		/// 开始
		virtual void                	start();
		/// 结束
		virtual void                	end();
		/// 更新
		virtual void                	update( Flt delta );

		/// 设置开始的位置
		virtual void            		setStartPos( Vec3 pos );
		/// 设置开始的方向
		virtual void            		setStartDir( Vec3 dir );
		/// 设置距离
		virtual void            		setDistance( Flt dis );
		/// 设置散播角度
		virtual void					setScatterAngle( Flt angle );
		/// 设置发射仰角
		virtual void					setPitchAngle( Flt angle );
		/// 设置偏角
		virtual void					setYawAngle( Flt angle );
		/// 设置发射体数量
		virtual void					setEmitterNum( UInt num );
		///设置平行间的间隔
		virtual void					setEmitterInterval(UInt interval);
		/// 是否下坠
		virtual void					setIsParabola( Bool IsParabola );
		/// 设置发射类型
		virtual void					setEmitType( EmitType emitType);
		///设置飞行轨迹类型
		virtual void            		setFlyTrackType( FlyTrackType flyTrackType );
		///设置目标位置
		virtual void					setTargetPos( Vec3 pos );
		///设置是否穿刺
		virtual void					setIsPuncture( Bool isPuncture );

		virtual void					setMoveSpeed( Flt speed );

	protected:
		////////////////////////////////////////////////////////////////////////////////////////////////
		Bool							getIsCanHit( CCharacterSceneEntity* hitCharacterSceneEntity );

		////////////////////////////////////////////////////////////////////////////////////////////////
		void							createEffect( CCharacterSceneEntity* characterSceneEntity );

		void							checkCollision( CCharacterSceneEntity* characterSceneEntity );

		void							effectCollision( CCharacterSceneEntity* characterSceneEntity,  CCharacterSceneEntity* hitCharacterSceneEntity );

		////////////////////////////////////////////////////////////////////////////////////////////////

		//获得平行发射的起点和终点
		void							getParllelEmitStartPosAndEndPos( UInt index, UInt emitterNum, UInt emitterInterval, Vec3& startPos, Vec3& endPos );
		//获得分散发射的角度
		Flt								getScatterEmitAngle( UInt index, UInt emitterNum, Flt scatterAngle );

	protected:

		Vec3							mPos;
		Vec3							mDir;
		Vec3							mTargetPos;
		Flt								mDis;
		Flt								mScatterAngle;
		Flt								mPitchAngle;
		Flt								mYawAngle;
		UInt							mEmitterInterval;
		UInt							mEmitterNum;
		Bool							mIsParabola;
		EmitType						mEmitType;
		FlyTrackType					mFlyTrackType;
		Bool							mIsPuncture;
		Flt								mMoveSpeed;

		EmitterSkillEffectState			mState;

    private:

		std::vector<EffectEntityInfo*>	mEffectEntity;
		IdType							mMapId;
    };



}

/******************************************************************************/
#endif

