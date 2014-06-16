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
    //游戏地形高度升高操作管理
    /******************************************************************************/
    class TerrainRaiseHeightOperationManager : public ITerrainRaiseHeightOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainRaiseHeightOperationManager)
        TerrainRaiseHeightOperationManager();
        virtual ~TerrainRaiseHeightOperationManager();

        ///得到幅度
        virtual Flt                     getAmplitude() ;
        ///设置幅度
        virtual void                    setAmplitude(Flt amp) ;
		///得到水的幅度
		virtual Flt						getWaterAmplitude();
		///设置水的幅度
		virtual void					setWaterAmplitude(Flt amp);

        ///创建一个操作
        virtual IEditorOperation*       createOneOperation();

    protected:

        Flt mAmp;

		Flt mWaterAmp;

    };
    
    /******************************************************************************/
    //游戏地形高度降低操作管理
    /******************************************************************************/
    class TerrainLowerHeightOperationManager : public ITerrainLowerHeightOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainLowerHeightOperationManager)
        TerrainLowerHeightOperationManager();
        virtual ~TerrainLowerHeightOperationManager();

        ///得到幅度
        virtual Flt                     getAmplitude() ;
        ///设置幅度
        virtual void                    setAmplitude(Flt amp) ;
		///得到水的幅度
		virtual Flt						getWaterAmplitude();
		///设置水的幅度
		virtual void					setWaterAmplitude(Flt amp);
        ///创建一个操作
        virtual IEditorOperation*       createOneOperation( );

    protected:

        Flt mAmp;

		Flt mWaterAmp;

    };

    /******************************************************************************/
    //地形高度统一操作管理
    /******************************************************************************/
    class TerrainUniformHeightOperationManager : public ITerrainUniformHeightOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainUniformHeightOperationManager)
        TerrainUniformHeightOperationManager();
        virtual ~TerrainUniformHeightOperationManager();

        ///得到幅度
        virtual Flt                     getAmplitude() ;
        ///设置幅度
        virtual void                    setAmplitude(Flt amp) ;
		///设置水的高度
		virtual void					setGroundHeight( Flt height ) { mGroundHeight = height; }
		///得到水的设置高度
		virtual Flt						getGroundHeight() { return mGroundHeight; };
		///设置水的高度
		virtual void					setWaterHeight( Flt height ) { mWaterHeight = height; }
		///得到水的设置高度
		virtual Flt						getWaterHeight() { return mWaterHeight; };
		///锁定水的高度值, 给外界的UI使用
		virtual void					lock(bool islock) { mLocked = islock; };
		///是否锁定水的高度，给UI使用
		virtual bool					isLocked() { return mLocked; }

        ///创建一个操作
        virtual IEditorOperation*       createOneOperation( );

    protected:

		//地形操作幅度
        Flt		mAmp;

		//是否锁定值
		bool	mLocked;

		//水的目标高度
		Flt		mWaterHeight;

		//陆地的目标高度
		Flt		mGroundHeight;
    };

    /******************************************************************************/
    //地形高度噪音操作管理
    /******************************************************************************/
    class TerrainNoiseHeightOperationManager : public ITerrainNoiseHeightOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainNoiseHeightOperationManager)
        TerrainNoiseHeightOperationManager();
        virtual ~TerrainNoiseHeightOperationManager();

        ///得到幅度
        virtual Flt                     getAmplitude() ;
        ///设置幅度
        virtual void                    setAmplitude(Flt amp) ;

        ///创建一个操作
        virtual IEditorOperation*       createOneOperation( );

    protected:

        Flt mAmp;

    };

    /******************************************************************************/
    //地形高度平滑操作管理
    /******************************************************************************/
    class TerrainSmoothHeightOperationManager : public ITerrainSmoothHeightOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainSmoothHeightOperationManager)
        TerrainSmoothHeightOperationManager();
        virtual ~TerrainSmoothHeightOperationManager();

        ///得到幅度
        virtual Flt                     getAmplitude() ;
        ///设置幅度
        virtual void                    setAmplitude(Flt amp) ;

        ///创建一个操作
        virtual IEditorOperation*       createOneOperation( );

    protected:

        Flt mAmp;

    };
}

/******************************************************************************/

#endif

