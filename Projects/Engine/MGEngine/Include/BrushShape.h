/******************************************************************************/
#ifndef _BRUSHSHAPE_H_
#define _BRUSHSHAPE_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IBrushShape.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //笔刷园形状接口
    /******************************************************************************/
    class BrushCircleShape : public IBrushCircleShape
    {
    public:
        SINGLETON_INSTANCE(BrushCircleShape)
        BrushCircleShape();
        virtual ~BrushCircleShape();
        
    protected:
        
        // 是否是有效的位置
        virtual Bool    isValidPos( Vec2 pos, Vec2& margin );
		// 返回一个有效的范围
		virtual Flt		getValidRange( Vec2 pos );
        //// 得到收到的影响系数[0 .. 1]
        //virtual Flt     getIntensity( Vec2 pos );
    };

    /******************************************************************************/
    //笔刷矩形状接口
    /******************************************************************************/
    class BrushRectShape : public IBrushRectShape
    {
    public:
        SINGLETON_INSTANCE(BrushRectShape)
        BrushRectShape();
        virtual ~BrushRectShape();

    protected:
        
        // 是否是有效的位置
        virtual Bool    isValidPos( Vec2 pos, Vec2& margin );
		// 返回一个有效的范围
		virtual Flt		getValidRange( Vec2 pos );

    };

    /******************************************************************************/
    //笔刷菱形状接口
    /******************************************************************************/
    class BrushRhombusShape : public IBrushRhombusShape
    {
    public:
        SINGLETON_INSTANCE(BrushRhombusShape)
        BrushRhombusShape();
        virtual ~BrushRhombusShape();

    protected:
        
        // 是否是有效的位置
        virtual Bool    isValidPos( Vec2 pos, Vec2& margin );
		// 返回一个有效的范围
		virtual Flt		getValidRange( Vec2 pos );
    };
}

/******************************************************************************/

#endif

