/******************************************************************************/
#ifndef _IWIREFRAMEMANAGER_H_
#define _IWIREFRAMEMANAGER_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //线框对象
    /******************************************************************************/
    class IWireframeDecorator
    {
    public:
        // 构造
        virtual void        rebuild() = NULL;;
        // 刷新
        virtual void        refresh() = NULL;

        /// 设置粗细 
        virtual void        setBoldSize(Flt size)  = NULL;
        /// 得到粗细
        virtual Flt         getBoldSize(void)  = NULL;

        /// 设置颜色 
        virtual void        setColour(Color colour)  = NULL;
        /// 得到颜色 
        virtual Color       getColour()  = NULL;

        /// 设置可见度
        virtual void        setVisible(Bool visible) = NULL;
        /// 得到可见度
        virtual Bool        getVisible() = NULL;

    };

    /******************************************************************************/
    //折线对象
    /******************************************************************************/
    class IPolyline
    {
    public:
        /// 加入一个关键点到折线中最后个点后
        virtual void            addKeyPoint( Vec3 pos ) = NULL;
        /// 修改折线中相应关键点位置
        virtual void            setKeyPointPosition( Vec3 pos, Int index ) = NULL;
    };

    /******************************************************************************/
    //折线线框装饰者
    /******************************************************************************/
    class IPolylineWireframeDecorator : public IWireframeDecorator
    {
    public:
        /// 得到被装饰的Polyline
        virtual IPolyline*      getPolyline(void) = NULL;
    };

    /******************************************************************************/
    //屏幕矩形线框装饰者
    /******************************************************************************/
    class IScreenRectWireframeDecorator : public IWireframeDecorator
    {
    public:
        /// 设置区域
        virtual void            setRect(RectF rect,Bool isOnce=true) = NULL;
    };

    /******************************************************************************/
    //地形圈线框装饰者
    /******************************************************************************/
    class ITerrainCircleDecorator : public IWireframeDecorator
    {
    public:

        /// 设置半径
        virtual void            setRadius(Flt radius) = NULL;
        /// 设置坐标点
        virtual void            setCenter(Vec3 pos) = NULL;

    };

	/******************************************************************************/
	//地形方线框装饰者
	/******************************************************************************/
	class ITerrainSquareDecorator : public IWireframeDecorator
	{
	public:

		/// 设置边长
		virtual void            setSideLength(Flt length) = NULL;
		/// 设置坐标点
		virtual void            setCenter(Vec3 pos) = NULL;

	};

	/******************************************************************************/
	//地形菱线框装饰者
	/******************************************************************************/
	class ITerrainDiamondDecorator : public IWireframeDecorator
	{
	public:
		/// 设置边长
		virtual void            setSideLength(Flt length) = NULL;
		/// 设置坐标点
		virtual void            setCenter(Vec3 pos) = NULL;
	};

    /******************************************************************************/
    //地形网格线框装饰者
    /******************************************************************************/
    class ITerrainGridsDecorator : public IWireframeDecorator
    {
    public:

    };

	/******************************************************************************/
	//特效编辑器里场景网格线框装饰者
	/******************************************************************************/
	class IEffectGridsDecorator : public IWireframeDecorator
	{
	public:

	};
    /******************************************************************************/
    //游戏线框管理
    /******************************************************************************/
    class IWireframeManager 
    {
    public:

        /// 创建屏幕矩形线框
        virtual IScreenRectWireframeDecorator*  createScreenRectWireframeDecorator( Str name ) = NULL;
        /// 得到屏幕矩形线框
        virtual IScreenRectWireframeDecorator*  getScreenRectWireframeDecorator( Str name ) = NULL;
        /// 销毁屏幕矩形线框
        virtual void                            destroyScreenRectWireframeDecorator(IScreenRectWireframeDecorator* decorator) = NULL; 

        /// 创建折线线框
        virtual IPolylineWireframeDecorator*    createPolylineWireframeDecorator( Str name ) = NULL;
        /// 得到折线线框
        virtual IPolylineWireframeDecorator*    getPolylineWireframeDecorator( Str name ) = NULL;
        /// 销毁折线线框
        virtual void                            destroyPolylineWireframeDecorator(IPolylineWireframeDecorator* decorator) = NULL; 

        /// 创建圈线框装饰者
        virtual ITerrainCircleDecorator*        createTerrainCircleDecorator( Str name ) = NULL;
        /// 得到圈线框装饰者
        virtual ITerrainCircleDecorator*        getTerrainCircleDecorator( Str name ) = NULL;
        /// 销毁圈线框装饰者
        virtual void                            destroyTerrainCircleDecorator(ITerrainCircleDecorator* decorator) = NULL; 

		/// 创建方线框装饰者
		virtual ITerrainSquareDecorator*        createTerrainSquareDecorator( Str name ) = NULL;
		/// 得到方线框装饰者
		virtual ITerrainSquareDecorator*        getTerrainSquareDecorator( Str name ) = NULL;
		/// 销毁方线框装饰者
		virtual void                            destroyTerrainSquareDecorator(ITerrainSquareDecorator* decorator) = NULL; 

		/// 创建菱线框装饰者
		virtual ITerrainDiamondDecorator*        createTerrainDiamondDecorator( Str name ) = NULL;
		/// 得到菱线框装饰者
		virtual ITerrainDiamondDecorator*        getTerrainDiamondDecorator( Str name ) = NULL;
		/// 销毁菱线框装饰者
		virtual void                            destroyTerrainDiamondDecorator(ITerrainDiamondDecorator* decorator) = NULL; 
    
        /// 创建网格线框装饰者
        virtual ITerrainGridsDecorator*         createTerrainGridsDecorator( Str name ) = NULL;
        /// 得到网格线框装饰者
        virtual ITerrainGridsDecorator*         getTerrainGridsDecorator( Str name ) = NULL;
        /// 销毁网格线框装饰者
        virtual void                            destroyTerrainGridsDecorator(ITerrainGridsDecorator* decorator) = NULL; 
		/// 特效场景网格线框装饰者
		virtual IEffectGridsDecorator*          createEffectGridsDecorator( Str name ) = NULL;
		/// 得到特效场景网格线框装饰者
		virtual IEffectGridsDecorator*          getEffectGridsDecorator( Str name ) = NULL;
		/// 销毁特效场景网格线框装饰者
		virtual void                            destroyEffectGridsDecorator(IEffectGridsDecorator* decorator) = NULL; 
    };

}

/******************************************************************************/
#endif
