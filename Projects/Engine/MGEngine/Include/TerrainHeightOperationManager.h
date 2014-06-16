/******************************************************************************/
#ifndef _TERRAINHEIGHTOPERATIONMANAGER_H_
#define _TERRAINHEIGHTOPERATIONMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrainHeightOperationManager.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //��Ϸ���θ߶����߲�������
    /******************************************************************************/
    class TerrainRaiseHeightOperationManager : public ITerrainRaiseHeightOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainRaiseHeightOperationManager)
        TerrainRaiseHeightOperationManager();
        virtual ~TerrainRaiseHeightOperationManager();

        ///�õ�����
        virtual Flt                     getAmplitude() ;
        ///���÷���
        virtual void                    setAmplitude(Flt amp) ;
		///�õ�ˮ�ķ���
		virtual Flt						getWaterAmplitude();
		///����ˮ�ķ���
		virtual void					setWaterAmplitude(Flt amp);

        ///����һ������
        virtual IEditorOperation*       createOneOperation();

    protected:

        Flt mAmp;

		Flt mWaterAmp;

    };
    
    /******************************************************************************/
    //��Ϸ���θ߶Ƚ��Ͳ�������
    /******************************************************************************/
    class TerrainLowerHeightOperationManager : public ITerrainLowerHeightOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainLowerHeightOperationManager)
        TerrainLowerHeightOperationManager();
        virtual ~TerrainLowerHeightOperationManager();

        ///�õ�����
        virtual Flt                     getAmplitude() ;
        ///���÷���
        virtual void                    setAmplitude(Flt amp) ;
		///�õ�ˮ�ķ���
		virtual Flt						getWaterAmplitude();
		///����ˮ�ķ���
		virtual void					setWaterAmplitude(Flt amp);
        ///����һ������
        virtual IEditorOperation*       createOneOperation( );

    protected:

        Flt mAmp;

		Flt mWaterAmp;

    };

    /******************************************************************************/
    //���θ߶�ͳһ��������
    /******************************************************************************/
    class TerrainUniformHeightOperationManager : public ITerrainUniformHeightOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainUniformHeightOperationManager)
        TerrainUniformHeightOperationManager();
        virtual ~TerrainUniformHeightOperationManager();

        ///�õ�����
        virtual Flt                     getAmplitude() ;
        ///���÷���
        virtual void                    setAmplitude(Flt amp) ;
		///����ˮ�ĸ߶�
		virtual void					setGroundHeight( Flt height ) { mGroundHeight = height; }
		///�õ�ˮ�����ø߶�
		virtual Flt						getGroundHeight() { return mGroundHeight; };
		///����ˮ�ĸ߶�
		virtual void					setWaterHeight( Flt height ) { mWaterHeight = height; }
		///�õ�ˮ�����ø߶�
		virtual Flt						getWaterHeight() { return mWaterHeight; };
		///����ˮ�ĸ߶�ֵ, ������UIʹ��
		virtual void					lock(bool islock) { mLocked = islock; };
		///�Ƿ�����ˮ�ĸ߶ȣ���UIʹ��
		virtual bool					isLocked() { return mLocked; }

        ///����һ������
        virtual IEditorOperation*       createOneOperation( );

    protected:

		//���β�������
        Flt		mAmp;

		//�Ƿ�����ֵ
		bool	mLocked;

		//ˮ��Ŀ��߶�
		Flt		mWaterHeight;

		//½�ص�Ŀ��߶�
		Flt		mGroundHeight;
    };

    /******************************************************************************/
    //���θ߶�������������
    /******************************************************************************/
    class TerrainNoiseHeightOperationManager : public ITerrainNoiseHeightOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainNoiseHeightOperationManager)
        TerrainNoiseHeightOperationManager();
        virtual ~TerrainNoiseHeightOperationManager();

        ///�õ�����
        virtual Flt                     getAmplitude() ;
        ///���÷���
        virtual void                    setAmplitude(Flt amp) ;

        ///����һ������
        virtual IEditorOperation*       createOneOperation( );

    protected:

        Flt mAmp;

    };

    /******************************************************************************/
    //���θ߶�ƽ����������
    /******************************************************************************/
    class TerrainSmoothHeightOperationManager : public ITerrainSmoothHeightOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainSmoothHeightOperationManager)
        TerrainSmoothHeightOperationManager();
        virtual ~TerrainSmoothHeightOperationManager();

        ///�õ�����
        virtual Flt                     getAmplitude() ;
        ///���÷���
        virtual void                    setAmplitude(Flt amp) ;

        ///����һ������
        virtual IEditorOperation*       createOneOperation( );

    protected:

        Flt mAmp;

    };
}

/******************************************************************************/

#endif

