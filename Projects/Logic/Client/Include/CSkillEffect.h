/******************************************************************************/
#ifndef _CSKILLEFFECT_H_
#define _CSKILLEFFECT_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
#include "CLuaBinder.h"

/******************************************************************************/

namespace MG
{   
    /******************************************************************************/
    //游戏技能特效
    /******************************************************************************/
    class CSkillEffect : public CLuaReference
    {
    public:
        //技能状态
        enum SkillEffectState
        {
            SES_NONE,
            SES_START,
            SES_END,
        };
        
        CSkillEffect( CSkillObject* object );
        virtual ~CSkillEffect();

        /// 开始
        virtual void                start();
        /// 结束
        virtual void                end();
        /// 更新
        virtual void                update( Flt delta );
        /// 得到技能状态
        virtual SkillEffectState    getState();
        /// 是否属于该技能
        virtual Bool                isBelongSkill( CSkillObject* object );

    public:
        
        /// 设置特效
        virtual void                setEffect( UInt effectFileId );

        /// 是否结束当技能结束时
        virtual Bool                isEndOnSkillEned();
        /// 是否结束当技能结束时
        virtual void                setIsEndOnSkillEned( Bool isEnded);

        /// 设置是否检测碰撞
        virtual void                setCollisionCheck( Bool isCheckCollsion );
        /// 是否检测碰撞
        virtual Bool                getCollisionCheck();
        
        /// 得到技能ID
        virtual IdType              getSkillID();
        /// 得到使用者编号
        virtual IdType              getUserID();
        /// 得到使用者类型
        virtual GAMEOBJ_TYPE        getUserType();

		virtual CSkillObject*		getSkillObject();
        
    protected:

		CSkillObject*				mSkillObject; 
        Bool                		mIsCheckCollsion;
        UInt                		mEffectFileId;
        SkillEffectState    		mSkillEffectState;
        Bool                		mIsEndOnSkillEned;
    };

 //   /******************************************************************************/
 //   //点技能特效
 //   /******************************************************************************/
 //   class  CPointSkillEffect : public CSkillEffect
 //   {
 //   public:
 //        CPointSkillEffect( SkillObject* object );
 //       virtual ~ CPointSkillEffect();

 //       /// 设置位置
 //       virtual void            setPos( Vec3 pos );
	//	virtual void			setHight( UInt hight);
	//	virtual void			setDurationTime( Flt time );
	//	virtual void			setRadius( UInt radius );
	//	virtual void			setAffectIntervalTime( Flt time );

 //   protected:
 //       Vec3					mPos;       //技能释放的位置
	//	UInt					mHight;	
	//	Flt						mDurationTime;
	//	//UInt					mRadius;
	//	Flt						mAffectIntervalTime;
 //   };
 //   
 //   /******************************************************************************/
 //   //直线飞行技能特效
 //   /******************************************************************************/
 //   class CEmitterSkillEffect : public CSkillEffect
 //   {
 //   public:
	//	enum EmitType
	//	{
	//		ET_PARALLEL,		//平行发射
	//		ET_SCATTER,			//分散发射
	//	};

	//	enum FlyTrackType
	//	{
	//		FTT_LINE,				//直线
	//		FTT_GATHERED,			//聚集
	//		FTT_DIVERGENT,			//发散
	//		FTT_HELICAL,			//螺旋
	//	};

 //       CEmitterSkillEffect( SkillObject* object );
 //       virtual ~CEmitterSkillEffect();

 //       /// 设置开始的位置
 //       virtual void            setStartPos( Vec3 pos );
 //       /// 设置开始的方向
 //       virtual void            setStartDir( Vec3 dir );
 //       /// 设置距离
 //       virtual void            setDistance( Flt dis );
	//	 /// 设置散播角度
	//	virtual void			setScatterAngle( Flt angle );
	//	 /// 设置发射仰角
	//	virtual void			setPitchAngle( Flt angle );
	//	/// 设置偏角
	//	virtual void			setYawAngle( Flt angle );
	//	 /// 设置发射体数量
	//	virtual void			setEmitterNum( UInt num );
	//	///设置平行间的间隔
	//	virtual void			setEmitterInterval(UInt interval);
	//	/// 是否下坠
	//	virtual void			setIsParabola( Bool IsParabola );
	//	/// 设置发射类型
	//	virtual void			setEmitType( EmitType emitType);
	//	///设置飞行轨迹类型
	//	virtual void            setFlyTrackType( FlyTrackType flyTrackType );
	//	///设置目标位置
	//	virtual void			setTargetPos( Vec3 pos );
	//	///设置是否穿刺
	//	virtual void			setIsPuncture( Bool isPuncture );

	//	virtual void			setMoveSpeed( Flt speed );


 //   protected:

 //       Vec3					mPos;
 //       Vec3					mDir;
	//	Vec3					mTargetPos;
 //       Flt						mDis;
	//	Flt						mScatterAngle;
	//	Flt						mPitchAngle;
	//	Flt						mYawAngle;
	//	UInt					mEmitterInterval;
	//	UInt					mEmitterNum;
	//	Bool					mIsParabola;
	//	EmitType				mEmitType;
	//	FlyTrackType			mFlyTrackType;
	//	Bool					mIsPuncture;
	//	Flt						mMoveSpeed;
 //   };

	///******************************************************************************/
	////目标技能特效
	///******************************************************************************/

	//class CObjectSkillEffect : public CSkillEffect
	//{
	//public:

	//	CObjectSkillEffect( SkillObject* object );
	//	virtual ~CObjectSkillEffect();

	//	/// 设置开始的位置
	//	virtual void            setStartPos( Vec3 pos );
	//	/// 设置距离
	//	virtual void            setDistance( Flt dis );
	//	/// 是否下坠
	//	virtual void			setIsParabola( Bool IsParabola );
	//	///设置目标id
	//	virtual void			setTargetID( IdType id );
	//	///设置目标类型
	//	virtual void			setTargetType( GAMEOBJ_TYPE type );

	//	virtual void			setMoveSpeed( Flt speed );

	//protected:
	//	Vec3					mPos;
	//	Vec3					mDir;
	//	Flt						mDis;
	//	Bool					mIsParabola;
	//	IdType					mTargetId;
	//	GAMEOBJ_TYPE			mTargetType;
	//	Flt						mMoveSpeed;

	//};


	///******************************************************************************/
	////瞬发技能特效
	///******************************************************************************/

	//class CInstantSkillEffect : public CSkillEffect
	//{
	//public:

	//	CInstantSkillEffect( SkillObject* object );
	//	virtual ~CInstantSkillEffect();

	//	/// 设置开始的位置
	//	virtual void            setPos( Vec3 pos );
	//	/// 设置特效
	//	//virtual void			setPlayTotalTime( Flt time );
	//	///设置目标id
	//	virtual void			setTargetID( IdType id );
	//	///设置目标类型
	//	virtual void			setTargetType( GAMEOBJ_TYPE type );

	//protected:
	//	Vec3					mPos;
	//	//Flt						mPlayTotalTime;
	//	IdType					mTargetId;
	//	GAMEOBJ_TYPE			mTargetType;
	//};

	///******************************************************************************/
	////冲刺技能特效
	///******************************************************************************/

	//class CSprintSkillEffect : public CSkillEffect
	//{
	//public:
	//	CSprintSkillEffect( SkillObject* object );
	//	virtual ~CSprintSkillEffect();

	//	virtual void			setPos( Vec3 pos );
	//	virtual void			setDis( UInt dis);

	//protected:
	//	Vec3					mPos;
	//	Vec3					mStartPos;
	//	UInt					mDis;
	//};

	///******************************************************************************/
	////军队普攻技能
	///******************************************************************************/

	//class CTroopGeneralAttack : public CSkillEffect
	//{
	//public:
	//	CTroopGeneralAttack( SkillObject* object );
	//	virtual ~CTroopGeneralAttack();

	//	virtual void			setAttackNum( UInt attackNum );
	//	virtual void			setAttackRadius( UInt attackRadius );
	//	virtual void			setSurroundRadius( UInt surroundRadius );

	//protected:
	//	UInt					mAttackNum;
	//	UInt					mAttackRadius;
	//	UInt					mSurroundRadius;
	//};

}

/******************************************************************************/
#endif

