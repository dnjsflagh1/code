/******************************************************************************/
#ifndef _WIREFRAMEMANAGER_H_
#define _WIREFRAMEMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IWireframeManager.h"
#include "PolylineWireframeDecorator.h"
#include "ScreenRectWireframeDecorator.h"
#include "TerrainCircleDecorator.h"
#include "TerrainSquareDecorator.h"
#include "TerrainDiamondDecorator.h"
#include "TerrainGridsDecorator.h"
#include "EffectGridsDecorator.h"

/******************************************************************************/
namespace MG
{

    /**
    -----------------------------------------------------------------------------
    线框管理器
    -----------------------------------------------------------------------------
    */
    class WireframeManager : public IWireframeManager
    {
    public:

        WireframeManager(Scene* scene);
        virtual ~WireframeManager();

        /// 更新
        void    update( Real delta );
        /// 清除
        void    clear( );

    public:

        ///////////////////////////////////////////////////////////////////////////

        /// 创建屏幕矩形线框
        virtual IScreenRectWireframeDecorator*  createScreenRectWireframeDecorator( Str name ) ;
        /// 得到屏幕矩形线框
        virtual IScreenRectWireframeDecorator*  getScreenRectWireframeDecorator( Str name ) ;
        /// 销毁屏幕矩形线框
        virtual void                            destroyScreenRectWireframeDecorator(IScreenRectWireframeDecorator* decorator) ; 
        /// 销毁所有的矩形线框
        void                                    destroyAllScreenRectWireframeDecorator();

        ///////////////////////////////////////////////////////////////////////////

        /// 创建折线线框
        virtual IPolylineWireframeDecorator*    createPolylineWireframeDecorator( Str name ) ;
        /// 得到折线线框
        virtual IPolylineWireframeDecorator*    getPolylineWireframeDecorator( Str name ) ;
        /// 销毁折线线框
        virtual void                            destroyPolylineWireframeDecorator(IPolylineWireframeDecorator* decorator) ; 
        /// 销毁所有的矩形线框
                void                            destroyAllPolylineWireframeDecorator();

        ///////////////////////////////////////////////////////////////////////////


        /// 创建圈线框装饰者
        virtual ITerrainCircleDecorator*        createTerrainCircleDecorator( Str name ) ;
        /// 得到圈线框装饰者
        virtual ITerrainCircleDecorator*        getTerrainCircleDecorator( Str name ) ;
        /// 销毁圈线框装饰者
        virtual void                            destroyTerrainCircleDecorator(ITerrainCircleDecorator* decorator) ; 
        /// 销毁所有的圈线框装饰者
                void                            destroyAllTerrainCircleDecorator();

        /// 创建方线框装饰者
        virtual ITerrainSquareDecorator*        createTerrainSquareDecorator( Str name ) ;
        /// 得到方线框装饰者
        virtual ITerrainSquareDecorator*        getTerrainSquareDecorator( Str name ) ;
        /// 销毁方线框装饰者
        virtual void                            destroyTerrainSquareDecorator(ITerrainSquareDecorator* decorator) ; 
        /// 销毁所有的方线框装饰者
                void                            destroyAllTerrainSquareDecorator();

        /// 创建菱线框装饰者
        virtual ITerrainDiamondDecorator*        createTerrainDiamondDecorator( Str name ) ;
        /// 得到菱线框装饰者
        virtual ITerrainDiamondDecorator*        getTerrainDiamondDecorator( Str name ) ;
        /// 销毁菱线框装饰者
        virtual void                            destroyTerrainDiamondDecorator(ITerrainDiamondDecorator* decorator) ; 
        /// 销毁所有的菱线框装饰者
                void                            destroyAllTerrainDiamondDecorator();

                ///////////////////////////////////////////////////////////////////////////

        /// 创建网格线框装饰者
        virtual ITerrainGridsDecorator*         createTerrainGridsDecorator( Str name ) ;
        /// 得到网格线框装饰者
        virtual ITerrainGridsDecorator*         getTerrainGridsDecorator( Str name ) ;
        /// 销毁网格线框装饰者
        virtual void                            destroyTerrainGridsDecorator(ITerrainGridsDecorator* decorator) ; 
        /// 销毁所有的圈线框装饰者
                void                            destroyAllTerrainGridsDecorator();

		/// 特效场景网格线框装饰者
		virtual IEffectGridsDecorator*          createEffectGridsDecorator( Str name );
		/// 得到特效场景网格线框装饰者
		virtual IEffectGridsDecorator*          getEffectGridsDecorator( Str name );
		/// 销毁特效场景网格线框装饰者
		virtual void                            destroyEffectGridsDecorator(IEffectGridsDecorator* decorator); 
		/// 销毁所有的圈线框装饰者
				void                            destroyAllEffectGridsDecorator();


        ////////////////////////////////////////////////////////////////////////

        /// 渲染事件
         virtual    void                        postFindVisibleObjects(Ogre::SceneManager* source, 
                                                Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport* v);

    private:

        ////////////////////////////////////////////////////////////////////////
        /// 所属Scene
        Scene* mScene;

        ////////////////////////////////////////////////////////////////////////
        /// 折线对象列表
        NameGenerator mPolylineWireframeDecoratorNameGenerator;
        std::map<String, PolylineWireframeDecorator*> mPolylineWireframeDecorators;

        ////////////////////////////////////////////////////////////////////////
        /// 屏幕矩形线框对象列表
        NameGenerator mScreenRectWireframeDecoratorNameGenerator;
        std::map<String, ScreenRectWireframeDecorator*> mScreenRectWireframeDecorators;

        ////////////////////////////////////////////////////////////////////////
        /// 屏幕圈线框装饰者对象列表
        NameGenerator mTerrainCircleDecoratorNameGenerator;
        std::map<String, TerrainCircleDecorator*> mTerrainCircleDecorator;

		////////////////////////////////////////////////////////////////////////
		/// 屏幕方线框装饰者对象列表
		NameGenerator mTerrainSquareDecoratorNameGenerator;
		std::map<String, TerrainSquareDecorator*> mTerrainSquareDecorator;

		////////////////////////////////////////////////////////////////////////
		/// 屏幕菱线框装饰者对象列表
		NameGenerator mTerrainDiamondDecoratorNameGenerator;
		std::map<String, TerrainDiamondDecorator*> mTerrainDiamondDecorator;

        ////////////////////////////////////////////////////////////////////////
        /// 屏幕圈线框装饰者对象列表
        NameGenerator mTerrainGridsDecoratorNameGenerator;
        std::map<String, TerrainGridsDecorator*> mTerrainGridsDecorator;

		////////////////////////////////////////////////////////////////////////
		/// 特效场景网格对象
		NameGenerator mEffectGridsDecoratorNameGenerator;
		std::map<String, EffectGridDecorator*> mEffectGridsDecorator;
    };

}

/******************************************************************************/

#endif