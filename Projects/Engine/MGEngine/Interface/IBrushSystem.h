/******************************************************************************/
#ifndef _IBRUSHSYSTEM_H_
#define _IBRUSHSYSTEM_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //笔刷系统接口
    /******************************************************************************/
    class IBrushSystem
    {
    public:

        ///得到开始位置
        virtual void                    setStartPos(Vec3 pos) = NULL;
        ///设置结束位置
        virtual Vec3                    getStartPos() = NULL;

        ///得到结束位置
        virtual void                    setEndPos(Vec3 pos) = NULL;
        ///设置结束位置
        virtual Vec3                    getEndPos() = NULL;

        ///得到大小
        virtual Flt                     getSize() = NULL;
        ///设置大小
        virtual void                    setSize( Flt size ) = NULL;

        ///设置是否可见
        virtual void                    setFacadeVisible(Bool visible)  = NULL;

        ///得到速度
        virtual Flt                     getSpeed() = NULL;
        ///设置速度
        virtual void                    setSpeed( Flt speed ) = NULL;

		///得到当前贴图索引
		virtual Int                     getActiveTextureLayerIndex( ) = NULL;
		///设置当前贴图索引
		virtual void                    setActiveTextureLayerIndex( Int index ) = NULL;

        ///得到当前静态物体索引
        virtual Int                     getActiveBatchEntityLayerIndex( ) = NULL;
        ///设置当前静态物体索引
        virtual void                    setActiveBatchEntityLayerIndex( Int index ) = NULL;

        /// 得到圆形画笔设置
        virtual IBrushCircleShape*      getBrushCircleShape() = NULL;
        /// 得到矩形画笔设置
        virtual IBrushRectShape*        getBrushRectShape() = NULL;
        /// 得到菱形画笔设置
        virtual IBrushRhombusShape*     getBrushRhombusShape() = NULL;
        /// 设置活动的画笔形状
        virtual void                    setActiveShape(IBrushShape* shape) = NULL;


        /// 得到笔刷喷枪类型接口
        virtual IBrushAirStyle*         getBrushAirStyle() = NULL;
        /// 得到笔刷画笔类型接口
        virtual IBrushPaintStyle*       getBrushPaintStyle() = NULL;
        /// 得到笔刷噪音类型接口
        virtual IBrushNoiseStyle*       getBrushNoiseStyle() = NULL;
        /// 得到笔刷碎片类型接口
        virtual IBrushFractalStyle*     getBrushFractalStyle() = NULL;
        /// 设置活动的类型
        virtual void                    setActiveStyle(IBrushStyle* style) = NULL;
    };
}

/******************************************************************************/
#endif
