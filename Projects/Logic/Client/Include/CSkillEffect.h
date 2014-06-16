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
    //��Ϸ������Ч
    /******************************************************************************/
    class CSkillEffect : public CLuaReference
    {
    public:
        //����״̬
        enum SkillEffectState
        {
            SES_NONE,
            SES_START,
            SES_END,
        };
        
        CSkillEffect( CSkillObject* object );
        virtual ~CSkillEffect();

        /// ��ʼ
        virtual void                start();
        /// ����
        virtual void                end();
        /// ����
        virtual void                update( Flt delta );
        /// �õ�����״̬
        virtual SkillEffectState    getState();
        /// �Ƿ����ڸü���
        virtual Bool                isBelongSkill( CSkillObject* object );

    public:
        
        /// ������Ч
        virtual void                setEffect( UInt effectFileId );

        /// �Ƿ���������ܽ���ʱ
        virtual Bool                isEndOnSkillEned();
        /// �Ƿ���������ܽ���ʱ
        virtual void                setIsEndOnSkillEned( Bool isEnded);

        /// �����Ƿ�����ײ
        virtual void                setCollisionCheck( Bool isCheckCollsion );
        /// �Ƿ�����ײ
        virtual Bool                getCollisionCheck();
        
        /// �õ�����ID
        virtual IdType              getSkillID();
        /// �õ�ʹ���߱��
        virtual IdType              getUserID();
        /// �õ�ʹ��������
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
 //   //�㼼����Ч
 //   /******************************************************************************/
 //   class  CPointSkillEffect : public CSkillEffect
 //   {
 //   public:
 //        CPointSkillEffect( SkillObject* object );
 //       virtual ~ CPointSkillEffect();

 //       /// ����λ��
 //       virtual void            setPos( Vec3 pos );
	//	virtual void			setHight( UInt hight);
	//	virtual void			setDurationTime( Flt time );
	//	virtual void			setRadius( UInt radius );
	//	virtual void			setAffectIntervalTime( Flt time );

 //   protected:
 //       Vec3					mPos;       //�����ͷŵ�λ��
	//	UInt					mHight;	
	//	Flt						mDurationTime;
	//	//UInt					mRadius;
	//	Flt						mAffectIntervalTime;
 //   };
 //   
 //   /******************************************************************************/
 //   //ֱ�߷��м�����Ч
 //   /******************************************************************************/
 //   class CEmitterSkillEffect : public CSkillEffect
 //   {
 //   public:
	//	enum EmitType
	//	{
	//		ET_PARALLEL,		//ƽ�з���
	//		ET_SCATTER,			//��ɢ����
	//	};

	//	enum FlyTrackType
	//	{
	//		FTT_LINE,				//ֱ��
	//		FTT_GATHERED,			//�ۼ�
	//		FTT_DIVERGENT,			//��ɢ
	//		FTT_HELICAL,			//����
	//	};

 //       CEmitterSkillEffect( SkillObject* object );
 //       virtual ~CEmitterSkillEffect();

 //       /// ���ÿ�ʼ��λ��
 //       virtual void            setStartPos( Vec3 pos );
 //       /// ���ÿ�ʼ�ķ���
 //       virtual void            setStartDir( Vec3 dir );
 //       /// ���þ���
 //       virtual void            setDistance( Flt dis );
	//	 /// ����ɢ���Ƕ�
	//	virtual void			setScatterAngle( Flt angle );
	//	 /// ���÷�������
	//	virtual void			setPitchAngle( Flt angle );
	//	/// ����ƫ��
	//	virtual void			setYawAngle( Flt angle );
	//	 /// ���÷���������
	//	virtual void			setEmitterNum( UInt num );
	//	///����ƽ�м�ļ��
	//	virtual void			setEmitterInterval(UInt interval);
	//	/// �Ƿ���׹
	//	virtual void			setIsParabola( Bool IsParabola );
	//	/// ���÷�������
	//	virtual void			setEmitType( EmitType emitType);
	//	///���÷��й켣����
	//	virtual void            setFlyTrackType( FlyTrackType flyTrackType );
	//	///����Ŀ��λ��
	//	virtual void			setTargetPos( Vec3 pos );
	//	///�����Ƿ񴩴�
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
	////Ŀ�꼼����Ч
	///******************************************************************************/

	//class CObjectSkillEffect : public CSkillEffect
	//{
	//public:

	//	CObjectSkillEffect( SkillObject* object );
	//	virtual ~CObjectSkillEffect();

	//	/// ���ÿ�ʼ��λ��
	//	virtual void            setStartPos( Vec3 pos );
	//	/// ���þ���
	//	virtual void            setDistance( Flt dis );
	//	/// �Ƿ���׹
	//	virtual void			setIsParabola( Bool IsParabola );
	//	///����Ŀ��id
	//	virtual void			setTargetID( IdType id );
	//	///����Ŀ������
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
	////˲��������Ч
	///******************************************************************************/

	//class CInstantSkillEffect : public CSkillEffect
	//{
	//public:

	//	CInstantSkillEffect( SkillObject* object );
	//	virtual ~CInstantSkillEffect();

	//	/// ���ÿ�ʼ��λ��
	//	virtual void            setPos( Vec3 pos );
	//	/// ������Ч
	//	//virtual void			setPlayTotalTime( Flt time );
	//	///����Ŀ��id
	//	virtual void			setTargetID( IdType id );
	//	///����Ŀ������
	//	virtual void			setTargetType( GAMEOBJ_TYPE type );

	//protected:
	//	Vec3					mPos;
	//	//Flt						mPlayTotalTime;
	//	IdType					mTargetId;
	//	GAMEOBJ_TYPE			mTargetType;
	//};

	///******************************************************************************/
	////��̼�����Ч
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
	////�����չ�����
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

