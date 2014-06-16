/******************************************************************************/
#ifndef _BRUSHSYSTEM_H_
#define _BRUSHSYSTEM_H_
/******************************************************************************/

#include "IBrushSystem.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //游戏编辑主接口
    /******************************************************************************/
    class BrushSystem : public IBrushSystem
    {
    public:
        SINGLETON_INSTANCE(BrushSystem)
        BrushSystem();
        virtual ~BrushSystem();

        ///得到开始位置
        virtual void                    setStartPos(Vec3 pos);
        ///设置结束位置
        virtual Vec3                    getStartPos();


        ///得到结束位置
        virtual void                    setEndPos(Vec3 pos);
        ///设置结束位置
        virtual Vec3                    getEndPos();

        ///得到大小
        virtual Flt                     getSize();
        ///设置大小
        virtual void                    setSize( Flt size ) ;

        ///设置是否可见
        virtual void                    setFacadeVisible(Bool visible);

        ///得到速度
        virtual Flt                     getSpeed() ;
        ///设置速度
        virtual void                    setSpeed( Flt speed ) ;

		///得到当前贴图索引
		virtual Int                     getActiveTextureLayerIndex( );
		///设置当前贴图索引
		virtual void                    setActiveTextureLayerIndex( Int index );

        ///得到当前静态物体索引
        virtual Int                     getActiveBatchEntityLayerIndex( );
        ///设置当前静态物体索引
        virtual void                    setActiveBatchEntityLayerIndex( Int index );

        /// 得到圆形画笔设置
        virtual IBrushCircleShape*      getBrushCircleShape() ;
        /// 得到矩形画笔设置
        virtual IBrushRectShape*        getBrushRectShape() ;
        /// 得到菱形画笔设置
        virtual IBrushRhombusShape*     getBrushRhombusShape() ;
        /// 设置活动的画笔形状
        virtual void                    setActiveShape(IBrushShape* shape);
        /// 得到活动的画笔形状
        virtual IBrushShape*            getActiveShape();

        /// 得到笔刷喷枪类型接口
        virtual IBrushAirStyle*         getBrushAirStyle() ;
        /// 得到笔刷画笔类型接口
        virtual IBrushPaintStyle*       getBrushPaintStyle();
        /// 得到笔刷噪音类型接口
        virtual IBrushNoiseStyle*       getBrushNoiseStyle() ;
        /// 得到笔刷碎片类型接口
        virtual IBrushFractalStyle*     getBrushFractalStyle() ;
        /// 设置活动的类型
        virtual void                    setActiveStyle(IBrushStyle* style) ;
        /// 得到活动的类型
        virtual IBrushStyle*            getActiveStyle();

    public:

		/// 获得受影响的大致范围， 之后还是需要通过特定的笔刷， 去判断范围内的每个顶点是否有效
                Ogre::Rect              getActiveRect();

    protected:
        
        //外观名字
        static const  Str  FACADE_NAME;
        //笔刷开始位置
        Vec3            mStartPos;
        //笔刷结束位置
        Vec3            mEndPos;

        //笔刷大小
        Flt             mSize;

        //笔刷速度
        Flt             mSpeed;

		//当前贴图索引
		Int				mActiveTextureLayerIndex;

        //当前静态实体层
        Int             mActiveBatchEntityLayerIndex;
        
        IBrushShape*    mActiveBrushShape;
        IBrushStyle*    mActiveBrushStyle; 
    };
    
}

/******************************************************************************/

#endif

