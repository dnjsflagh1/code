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
    //��ˢ԰��״�ӿ�
    /******************************************************************************/
    class BrushCircleShape : public IBrushCircleShape
    {
    public:
        SINGLETON_INSTANCE(BrushCircleShape)
        BrushCircleShape();
        virtual ~BrushCircleShape();
        
    protected:
        
        // �Ƿ�����Ч��λ��
        virtual Bool    isValidPos( Vec2 pos, Vec2& margin );
		// ����һ����Ч�ķ�Χ
		virtual Flt		getValidRange( Vec2 pos );
        //// �õ��յ���Ӱ��ϵ��[0 .. 1]
        //virtual Flt     getIntensity( Vec2 pos );
    };

    /******************************************************************************/
    //��ˢ����״�ӿ�
    /******************************************************************************/
    class BrushRectShape : public IBrushRectShape
    {
    public:
        SINGLETON_INSTANCE(BrushRectShape)
        BrushRectShape();
        virtual ~BrushRectShape();

    protected:
        
        // �Ƿ�����Ч��λ��
        virtual Bool    isValidPos( Vec2 pos, Vec2& margin );
		// ����һ����Ч�ķ�Χ
		virtual Flt		getValidRange( Vec2 pos );

    };

    /******************************************************************************/
    //��ˢ����״�ӿ�
    /******************************************************************************/
    class BrushRhombusShape : public IBrushRhombusShape
    {
    public:
        SINGLETON_INSTANCE(BrushRhombusShape)
        BrushRhombusShape();
        virtual ~BrushRhombusShape();

    protected:
        
        // �Ƿ�����Ч��λ��
        virtual Bool    isValidPos( Vec2 pos, Vec2& margin );
		// ����һ����Ч�ķ�Χ
		virtual Flt		getValidRange( Vec2 pos );
    };
}

/******************************************************************************/

#endif

