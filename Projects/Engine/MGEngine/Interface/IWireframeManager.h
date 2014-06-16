/******************************************************************************/
#ifndef _IWIREFRAMEMANAGER_H_
#define _IWIREFRAMEMANAGER_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //�߿����
    /******************************************************************************/
    class IWireframeDecorator
    {
    public:
        // ����
        virtual void        rebuild() = NULL;;
        // ˢ��
        virtual void        refresh() = NULL;

        /// ���ô�ϸ 
        virtual void        setBoldSize(Flt size)  = NULL;
        /// �õ���ϸ
        virtual Flt         getBoldSize(void)  = NULL;

        /// ������ɫ 
        virtual void        setColour(Color colour)  = NULL;
        /// �õ���ɫ 
        virtual Color       getColour()  = NULL;

        /// ���ÿɼ���
        virtual void        setVisible(Bool visible) = NULL;
        /// �õ��ɼ���
        virtual Bool        getVisible() = NULL;

    };

    /******************************************************************************/
    //���߶���
    /******************************************************************************/
    class IPolyline
    {
    public:
        /// ����һ���ؼ��㵽�������������
        virtual void            addKeyPoint( Vec3 pos ) = NULL;
        /// �޸���������Ӧ�ؼ���λ��
        virtual void            setKeyPointPosition( Vec3 pos, Int index ) = NULL;
    };

    /******************************************************************************/
    //�����߿�װ����
    /******************************************************************************/
    class IPolylineWireframeDecorator : public IWireframeDecorator
    {
    public:
        /// �õ���װ�ε�Polyline
        virtual IPolyline*      getPolyline(void) = NULL;
    };

    /******************************************************************************/
    //��Ļ�����߿�װ����
    /******************************************************************************/
    class IScreenRectWireframeDecorator : public IWireframeDecorator
    {
    public:
        /// ��������
        virtual void            setRect(RectF rect,Bool isOnce=true) = NULL;
    };

    /******************************************************************************/
    //����Ȧ�߿�װ����
    /******************************************************************************/
    class ITerrainCircleDecorator : public IWireframeDecorator
    {
    public:

        /// ���ð뾶
        virtual void            setRadius(Flt radius) = NULL;
        /// ���������
        virtual void            setCenter(Vec3 pos) = NULL;

    };

	/******************************************************************************/
	//���η��߿�װ����
	/******************************************************************************/
	class ITerrainSquareDecorator : public IWireframeDecorator
	{
	public:

		/// ���ñ߳�
		virtual void            setSideLength(Flt length) = NULL;
		/// ���������
		virtual void            setCenter(Vec3 pos) = NULL;

	};

	/******************************************************************************/
	//�������߿�װ����
	/******************************************************************************/
	class ITerrainDiamondDecorator : public IWireframeDecorator
	{
	public:
		/// ���ñ߳�
		virtual void            setSideLength(Flt length) = NULL;
		/// ���������
		virtual void            setCenter(Vec3 pos) = NULL;
	};

    /******************************************************************************/
    //���������߿�װ����
    /******************************************************************************/
    class ITerrainGridsDecorator : public IWireframeDecorator
    {
    public:

    };

	/******************************************************************************/
	//��Ч�༭���ﳡ�������߿�װ����
	/******************************************************************************/
	class IEffectGridsDecorator : public IWireframeDecorator
	{
	public:

	};
    /******************************************************************************/
    //��Ϸ�߿����
    /******************************************************************************/
    class IWireframeManager 
    {
    public:

        /// ������Ļ�����߿�
        virtual IScreenRectWireframeDecorator*  createScreenRectWireframeDecorator( Str name ) = NULL;
        /// �õ���Ļ�����߿�
        virtual IScreenRectWireframeDecorator*  getScreenRectWireframeDecorator( Str name ) = NULL;
        /// ������Ļ�����߿�
        virtual void                            destroyScreenRectWireframeDecorator(IScreenRectWireframeDecorator* decorator) = NULL; 

        /// ���������߿�
        virtual IPolylineWireframeDecorator*    createPolylineWireframeDecorator( Str name ) = NULL;
        /// �õ������߿�
        virtual IPolylineWireframeDecorator*    getPolylineWireframeDecorator( Str name ) = NULL;
        /// ���������߿�
        virtual void                            destroyPolylineWireframeDecorator(IPolylineWireframeDecorator* decorator) = NULL; 

        /// ����Ȧ�߿�װ����
        virtual ITerrainCircleDecorator*        createTerrainCircleDecorator( Str name ) = NULL;
        /// �õ�Ȧ�߿�װ����
        virtual ITerrainCircleDecorator*        getTerrainCircleDecorator( Str name ) = NULL;
        /// ����Ȧ�߿�װ����
        virtual void                            destroyTerrainCircleDecorator(ITerrainCircleDecorator* decorator) = NULL; 

		/// �������߿�װ����
		virtual ITerrainSquareDecorator*        createTerrainSquareDecorator( Str name ) = NULL;
		/// �õ����߿�װ����
		virtual ITerrainSquareDecorator*        getTerrainSquareDecorator( Str name ) = NULL;
		/// ���ٷ��߿�װ����
		virtual void                            destroyTerrainSquareDecorator(ITerrainSquareDecorator* decorator) = NULL; 

		/// �������߿�װ����
		virtual ITerrainDiamondDecorator*        createTerrainDiamondDecorator( Str name ) = NULL;
		/// �õ����߿�װ����
		virtual ITerrainDiamondDecorator*        getTerrainDiamondDecorator( Str name ) = NULL;
		/// �������߿�װ����
		virtual void                            destroyTerrainDiamondDecorator(ITerrainDiamondDecorator* decorator) = NULL; 
    
        /// ���������߿�װ����
        virtual ITerrainGridsDecorator*         createTerrainGridsDecorator( Str name ) = NULL;
        /// �õ������߿�װ����
        virtual ITerrainGridsDecorator*         getTerrainGridsDecorator( Str name ) = NULL;
        /// ���������߿�װ����
        virtual void                            destroyTerrainGridsDecorator(ITerrainGridsDecorator* decorator) = NULL; 
		/// ��Ч���������߿�װ����
		virtual IEffectGridsDecorator*          createEffectGridsDecorator( Str name ) = NULL;
		/// �õ���Ч���������߿�װ����
		virtual IEffectGridsDecorator*          getEffectGridsDecorator( Str name ) = NULL;
		/// ������Ч���������߿�װ����
		virtual void                            destroyEffectGridsDecorator(IEffectGridsDecorator* decorator) = NULL; 
    };

}

/******************************************************************************/
#endif
