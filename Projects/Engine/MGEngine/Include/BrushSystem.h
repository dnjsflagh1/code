/******************************************************************************/
#ifndef _BRUSHSYSTEM_H_
#define _BRUSHSYSTEM_H_
/******************************************************************************/

#include "IBrushSystem.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //��Ϸ�༭���ӿ�
    /******************************************************************************/
    class BrushSystem : public IBrushSystem
    {
    public:
        SINGLETON_INSTANCE(BrushSystem)
        BrushSystem();
        virtual ~BrushSystem();

        ///�õ���ʼλ��
        virtual void                    setStartPos(Vec3 pos);
        ///���ý���λ��
        virtual Vec3                    getStartPos();


        ///�õ�����λ��
        virtual void                    setEndPos(Vec3 pos);
        ///���ý���λ��
        virtual Vec3                    getEndPos();

        ///�õ���С
        virtual Flt                     getSize();
        ///���ô�С
        virtual void                    setSize( Flt size ) ;

        ///�����Ƿ�ɼ�
        virtual void                    setFacadeVisible(Bool visible);

        ///�õ��ٶ�
        virtual Flt                     getSpeed() ;
        ///�����ٶ�
        virtual void                    setSpeed( Flt speed ) ;

		///�õ���ǰ��ͼ����
		virtual Int                     getActiveTextureLayerIndex( );
		///���õ�ǰ��ͼ����
		virtual void                    setActiveTextureLayerIndex( Int index );

        ///�õ���ǰ��̬��������
        virtual Int                     getActiveBatchEntityLayerIndex( );
        ///���õ�ǰ��̬��������
        virtual void                    setActiveBatchEntityLayerIndex( Int index );

        /// �õ�Բ�λ�������
        virtual IBrushCircleShape*      getBrushCircleShape() ;
        /// �õ����λ�������
        virtual IBrushRectShape*        getBrushRectShape() ;
        /// �õ����λ�������
        virtual IBrushRhombusShape*     getBrushRhombusShape() ;
        /// ���û�Ļ�����״
        virtual void                    setActiveShape(IBrushShape* shape);
        /// �õ���Ļ�����״
        virtual IBrushShape*            getActiveShape();

        /// �õ���ˢ��ǹ���ͽӿ�
        virtual IBrushAirStyle*         getBrushAirStyle() ;
        /// �õ���ˢ�������ͽӿ�
        virtual IBrushPaintStyle*       getBrushPaintStyle();
        /// �õ���ˢ�������ͽӿ�
        virtual IBrushNoiseStyle*       getBrushNoiseStyle() ;
        /// �õ���ˢ��Ƭ���ͽӿ�
        virtual IBrushFractalStyle*     getBrushFractalStyle() ;
        /// ���û������
        virtual void                    setActiveStyle(IBrushStyle* style) ;
        /// �õ��������
        virtual IBrushStyle*            getActiveStyle();

    public:

		/// �����Ӱ��Ĵ��·�Χ�� ֮������Ҫͨ���ض��ı�ˢ�� ȥ�жϷ�Χ�ڵ�ÿ�������Ƿ���Ч
                Ogre::Rect              getActiveRect();

    protected:
        
        //�������
        static const  Str  FACADE_NAME;
        //��ˢ��ʼλ��
        Vec3            mStartPos;
        //��ˢ����λ��
        Vec3            mEndPos;

        //��ˢ��С
        Flt             mSize;

        //��ˢ�ٶ�
        Flt             mSpeed;

		//��ǰ��ͼ����
		Int				mActiveTextureLayerIndex;

        //��ǰ��̬ʵ���
        Int             mActiveBatchEntityLayerIndex;
        
        IBrushShape*    mActiveBrushShape;
        IBrushStyle*    mActiveBrushStyle; 
    };
    
}

/******************************************************************************/

#endif

