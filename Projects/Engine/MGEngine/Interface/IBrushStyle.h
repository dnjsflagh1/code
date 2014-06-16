/******************************************************************************/
#ifndef _IBRUSHSTYLE_H_
#define _IBRUSHSTYLE_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //笔刷类型接口
    /******************************************************************************/
    class IBrushStyle
    {
    public:
        
        // 是否是有效的位置
        virtual Bool    isValidPos( Vec2 pos ) { return false; };
        // 得到收到的影响系数[0 .. 1]
        virtual Flt     getIntensity( Vec2 pos ) { return 0; };
    };

    /******************************************************************************/
    //笔刷喷枪类型接口
    /******************************************************************************/
    class IBrushAirStyle : public IBrushStyle
    {
    public:

		///得到衰减
		virtual Flt     getAttenuation() { return 0; };
		///设置衰减
		virtual void    setAttenuation(Flt att) {};
    };

    /******************************************************************************/
    //笔刷画笔类型接口
    /******************************************************************************/
    class IBrushPaintStyle : public IBrushStyle
    {
    public:

    };

    /******************************************************************************/
    //笔刷噪音类型接口
    /******************************************************************************/
    class IBrushNoiseStyle : public IBrushStyle
    {
    public:

		// 是否是有效的位置
		virtual Bool    isValidPos( Vec2 pos ) { return false; };

		// 得到收到的影响系数[0 .. 1]
		virtual Flt     getIntensity( Vec2 pos ) { return 0; };

		///得到变化度
		virtual Flt     getVariable() { return 0; } ;

		///设置变化度
		virtual void    setVariable(Flt variable) {}; 

		///得到分辨率
		virtual Flt		getResolution() { return 0; };

		///得到变化度
		virtual void	setResolution(U32 size) {};
    };

    /******************************************************************************/
    //笔刷碎片类型接口
    /******************************************************************************/
    class IBrushFractalStyle : public IBrushStyle
    {
    public:

    };
}

/******************************************************************************/
#endif
