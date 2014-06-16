/******************************************************************************/
#ifndef _BRUSHSTYLE_H_
#define _BRUSHSTYLE_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IBrushStyle.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //笔刷喷枪类型接口
    /******************************************************************************/
    class BrushAirStyle : public IBrushAirStyle
    {
    public:
        SINGLETON_INSTANCE(BrushAirStyle)
        BrushAirStyle();
        virtual ~BrushAirStyle();

    protected:

        // 是否是有效的位置
        virtual Bool    isValidPos( Vec2 pos );

        // 得到收到的影响系数[0 .. 1]
        virtual Flt     getIntensity( Vec2 pos );

		///得到衰减
		virtual Flt     getAttenuation();

		///设置衰减
		virtual void    setAttenuation(Flt atten);

	protected:

		Flt				mAtten;

    };

    /******************************************************************************/
    //笔刷画笔类型接口
    /******************************************************************************/
    class BrushPaintStyle : public IBrushPaintStyle
    {
    public:
        SINGLETON_INSTANCE(BrushPaintStyle)
        BrushPaintStyle();
        virtual ~BrushPaintStyle();

    protected:

        // 是否是有效的位置
        virtual Bool    isValidPos( Vec2 pos );

        // 得到收到的影响系数[0 .. 1]
        virtual Flt     getIntensity( Vec2 pos );

    };

    /******************************************************************************/
    //笔刷噪音类型接口
    /******************************************************************************/
    class BrushNoiseStyle : public IBrushNoiseStyle
    {
    public:
        SINGLETON_INSTANCE(BrushNoiseStyle)
        BrushNoiseStyle();
        virtual ~BrushNoiseStyle();

    protected:

        // 是否是有效的位置
        virtual Bool    isValidPos( Vec2 pos );

        // 得到收到的影响系数[0 .. 1]
        virtual Flt     getIntensity( Vec2 pos );

		///得到变化度
		virtual Flt     getVariable();

		///设置变化度
		virtual void    setVariable(Flt variable); 

		///得到分辨率
		virtual Flt		getResolution();

		///得到变化度
		virtual void	setResolution(U32 size);

	private:

		///根据噪度重新计算过滤图
				void	drawFilterTexture();
		///重新设置这个过滤图的大小
				void	resizeFilterTexture();
	protected:

		///过滤纹理的内存长宽
		static  Flt		FILTER_TEX_MAX_SIZE;
		// 生成过滤纹理
		U8*				m_pFilterTexData;
		// 过滤纹理的有效宽度
		U32				m_nFilterTexWidth;
		// 过滤纹理的有效高度
		U32				m_nFilterTexHeight;
		// 变化度, 变化度越小， 波形越平缓
		Flt				m_fVariable;

    };

    /******************************************************************************/
    //笔刷碎片类型接口
    /******************************************************************************/
    class BrushFractalStyle : public IBrushFractalStyle
    {
    public:
        SINGLETON_INSTANCE(BrushFractalStyle)
        BrushFractalStyle();
        virtual ~BrushFractalStyle();

    protected:
        
        // 是否是有效的位置
        virtual Bool    isValidPos( Vec2 pos );

        // 得到收到的影响系数[0 .. 1]
        virtual Flt     getIntensity( Vec2 pos );

    };
}

/******************************************************************************/

#endif

