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
    //��ˢ��ǹ���ͽӿ�
    /******************************************************************************/
    class BrushAirStyle : public IBrushAirStyle
    {
    public:
        SINGLETON_INSTANCE(BrushAirStyle)
        BrushAirStyle();
        virtual ~BrushAirStyle();

    protected:

        // �Ƿ�����Ч��λ��
        virtual Bool    isValidPos( Vec2 pos );

        // �õ��յ���Ӱ��ϵ��[0 .. 1]
        virtual Flt     getIntensity( Vec2 pos );

		///�õ�˥��
		virtual Flt     getAttenuation();

		///����˥��
		virtual void    setAttenuation(Flt atten);

	protected:

		Flt				mAtten;

    };

    /******************************************************************************/
    //��ˢ�������ͽӿ�
    /******************************************************************************/
    class BrushPaintStyle : public IBrushPaintStyle
    {
    public:
        SINGLETON_INSTANCE(BrushPaintStyle)
        BrushPaintStyle();
        virtual ~BrushPaintStyle();

    protected:

        // �Ƿ�����Ч��λ��
        virtual Bool    isValidPos( Vec2 pos );

        // �õ��յ���Ӱ��ϵ��[0 .. 1]
        virtual Flt     getIntensity( Vec2 pos );

    };

    /******************************************************************************/
    //��ˢ�������ͽӿ�
    /******************************************************************************/
    class BrushNoiseStyle : public IBrushNoiseStyle
    {
    public:
        SINGLETON_INSTANCE(BrushNoiseStyle)
        BrushNoiseStyle();
        virtual ~BrushNoiseStyle();

    protected:

        // �Ƿ�����Ч��λ��
        virtual Bool    isValidPos( Vec2 pos );

        // �õ��յ���Ӱ��ϵ��[0 .. 1]
        virtual Flt     getIntensity( Vec2 pos );

		///�õ��仯��
		virtual Flt     getVariable();

		///���ñ仯��
		virtual void    setVariable(Flt variable); 

		///�õ��ֱ���
		virtual Flt		getResolution();

		///�õ��仯��
		virtual void	setResolution(U32 size);

	private:

		///����������¼������ͼ
				void	drawFilterTexture();
		///���������������ͼ�Ĵ�С
				void	resizeFilterTexture();
	protected:

		///����������ڴ泤��
		static  Flt		FILTER_TEX_MAX_SIZE;
		// ���ɹ�������
		U8*				m_pFilterTexData;
		// �����������Ч���
		U32				m_nFilterTexWidth;
		// �����������Ч�߶�
		U32				m_nFilterTexHeight;
		// �仯��, �仯��ԽС�� ����Խƽ��
		Flt				m_fVariable;

    };

    /******************************************************************************/
    //��ˢ��Ƭ���ͽӿ�
    /******************************************************************************/
    class BrushFractalStyle : public IBrushFractalStyle
    {
    public:
        SINGLETON_INSTANCE(BrushFractalStyle)
        BrushFractalStyle();
        virtual ~BrushFractalStyle();

    protected:
        
        // �Ƿ�����Ч��λ��
        virtual Bool    isValidPos( Vec2 pos );

        // �õ��յ���Ӱ��ϵ��[0 .. 1]
        virtual Flt     getIntensity( Vec2 pos );

    };
}

/******************************************************************************/

#endif

