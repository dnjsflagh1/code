/******************************************************************************/
#ifndef _IBRUSHSYSTEM_H_
#define _IBRUSHSYSTEM_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //��ˢϵͳ�ӿ�
    /******************************************************************************/
    class IBrushSystem
    {
    public:

        ///�õ���ʼλ��
        virtual void                    setStartPos(Vec3 pos) = NULL;
        ///���ý���λ��
        virtual Vec3                    getStartPos() = NULL;

        ///�õ�����λ��
        virtual void                    setEndPos(Vec3 pos) = NULL;
        ///���ý���λ��
        virtual Vec3                    getEndPos() = NULL;

        ///�õ���С
        virtual Flt                     getSize() = NULL;
        ///���ô�С
        virtual void                    setSize( Flt size ) = NULL;

        ///�����Ƿ�ɼ�
        virtual void                    setFacadeVisible(Bool visible)  = NULL;

        ///�õ��ٶ�
        virtual Flt                     getSpeed() = NULL;
        ///�����ٶ�
        virtual void                    setSpeed( Flt speed ) = NULL;

		///�õ���ǰ��ͼ����
		virtual Int                     getActiveTextureLayerIndex( ) = NULL;
		///���õ�ǰ��ͼ����
		virtual void                    setActiveTextureLayerIndex( Int index ) = NULL;

        ///�õ���ǰ��̬��������
        virtual Int                     getActiveBatchEntityLayerIndex( ) = NULL;
        ///���õ�ǰ��̬��������
        virtual void                    setActiveBatchEntityLayerIndex( Int index ) = NULL;

        /// �õ�Բ�λ�������
        virtual IBrushCircleShape*      getBrushCircleShape() = NULL;
        /// �õ����λ�������
        virtual IBrushRectShape*        getBrushRectShape() = NULL;
        /// �õ����λ�������
        virtual IBrushRhombusShape*     getBrushRhombusShape() = NULL;
        /// ���û�Ļ�����״
        virtual void                    setActiveShape(IBrushShape* shape) = NULL;


        /// �õ���ˢ��ǹ���ͽӿ�
        virtual IBrushAirStyle*         getBrushAirStyle() = NULL;
        /// �õ���ˢ�������ͽӿ�
        virtual IBrushPaintStyle*       getBrushPaintStyle() = NULL;
        /// �õ���ˢ�������ͽӿ�
        virtual IBrushNoiseStyle*       getBrushNoiseStyle() = NULL;
        /// �õ���ˢ��Ƭ���ͽӿ�
        virtual IBrushFractalStyle*     getBrushFractalStyle() = NULL;
        /// ���û������
        virtual void                    setActiveStyle(IBrushStyle* style) = NULL;
    };
}

/******************************************************************************/
#endif
