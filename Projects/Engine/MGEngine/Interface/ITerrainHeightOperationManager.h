/******************************************************************************/
#ifndef _ITERRAINHEIGHTOPERATIONMANAGER_H_
#define _ITERRAINHEIGHTOPERATIONMANAGER_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "IEditorOperation.h"
#include "ITerrain.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //游戏地形高度增加接口
    /******************************************************************************/
    class ITerrainHeightOperationManager : public IEditorOperationManager
    {
    public:
        ITerrainHeightOperationManager()
            :mTerrainSurfaceType(TST_GROUND)
        {
        }
        /// 设置操作地表类型
        void                    setTerrainSurfaceType( TerrainSurfaceType type ){mTerrainSurfaceType=type;};
        /// 得到操作地表类型
        TerrainSurfaceType      getTerrainSurfaceType(){return mTerrainSurfaceType;};

    protected:

        TerrainSurfaceType mTerrainSurfaceType;
    };



    /******************************************************************************/
    //游戏地形高度增加接口
    /******************************************************************************/
    class ITerrainRaiseHeightOperationManager : public ITerrainHeightOperationManager
    {
    public:
        ///得到幅度
        virtual Flt     getAmplitude() = NULL;
        ///设置幅度
        virtual void    setAmplitude(Flt amp) = NULL;
		///得到幅度
		virtual Flt     getWaterAmplitude() = NULL;
		///设置幅度
		virtual void    setWaterAmplitude(Flt amp) = NULL;
    };

    /******************************************************************************/
    //游戏地形高度减少接口
    /******************************************************************************/
    class ITerrainLowerHeightOperationManager: public ITerrainHeightOperationManager
    {
    public:
        ///得到幅度
        virtual Flt     getAmplitude() = NULL;
        ///设置幅度
        virtual void    setAmplitude(Flt amp) = NULL;
		///得到幅度
		virtual Flt     getWaterAmplitude() = NULL;
		///设置幅度
		virtual void    setWaterAmplitude(Flt amp) = NULL;
    };

    /******************************************************************************/
    //地形高度统一编辑接口
    /******************************************************************************/
    class ITerrainUniformHeightOperationManager: public ITerrainHeightOperationManager
    {
    public:

		virtual void	setWaterHeight( Flt height ) = NULL;
		///得到水的设置高度
		virtual Flt		getWaterHeight() = NULL;
		///锁定水的高度值, 给外界的UI使用
		virtual void	lock(bool islock) = NULL;
		///是否锁定水的高度，给UI使用
		virtual bool	isLocked() = NULL;
    };

    /******************************************************************************/
    //地形高度噪音编辑接口
    /******************************************************************************/
    class ITerrainNoiseHeightOperationManager: public ITerrainHeightOperationManager
    {
    public:
		///得到幅度
		virtual Flt     getAmplitude() = NULL;
		///设置幅度
		virtual void    setAmplitude(Flt amp) = NULL;
    };

    /******************************************************************************/
    //地形高度平滑编辑接口
    /******************************************************************************/
    class ITerrainSmoothHeightOperationManager: public ITerrainHeightOperationManager
    {
	public:
		///得到幅度
		virtual Flt     getAmplitude() = NULL;
		///设置幅度
		virtual void    setAmplitude(Flt amp) = NULL;
    };
}

/******************************************************************************/
#endif
