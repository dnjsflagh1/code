/******************************************************************************/
#ifndef _WIREFRAMEMANAGER_H_
#define _WIREFRAMEMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IWireframeManager.h"
#include "PolylineWireframeDecorator.h"
#include "ScreenRectWireframeDecorator.h"
#include "TerrainCircleDecorator.h"
#include "TerrainSquareDecorator.h"
#include "TerrainDiamondDecorator.h"
#include "TerrainGridsDecorator.h"
#include "EffectGridsDecorator.h"

/******************************************************************************/
namespace MG
{

    /**
    -----------------------------------------------------------------------------
    �߿������
    -----------------------------------------------------------------------------
    */
    class WireframeManager : public IWireframeManager
    {
    public:

        WireframeManager(Scene* scene);
        virtual ~WireframeManager();

        /// ����
        void    update( Real delta );
        /// ���
        void    clear( );

    public:

        ///////////////////////////////////////////////////////////////////////////

        /// ������Ļ�����߿�
        virtual IScreenRectWireframeDecorator*  createScreenRectWireframeDecorator( Str name ) ;
        /// �õ���Ļ�����߿�
        virtual IScreenRectWireframeDecorator*  getScreenRectWireframeDecorator( Str name ) ;
        /// ������Ļ�����߿�
        virtual void                            destroyScreenRectWireframeDecorator(IScreenRectWireframeDecorator* decorator) ; 
        /// �������еľ����߿�
        void                                    destroyAllScreenRectWireframeDecorator();

        ///////////////////////////////////////////////////////////////////////////

        /// ���������߿�
        virtual IPolylineWireframeDecorator*    createPolylineWireframeDecorator( Str name ) ;
        /// �õ������߿�
        virtual IPolylineWireframeDecorator*    getPolylineWireframeDecorator( Str name ) ;
        /// ���������߿�
        virtual void                            destroyPolylineWireframeDecorator(IPolylineWireframeDecorator* decorator) ; 
        /// �������еľ����߿�
                void                            destroyAllPolylineWireframeDecorator();

        ///////////////////////////////////////////////////////////////////////////


        /// ����Ȧ�߿�װ����
        virtual ITerrainCircleDecorator*        createTerrainCircleDecorator( Str name ) ;
        /// �õ�Ȧ�߿�װ����
        virtual ITerrainCircleDecorator*        getTerrainCircleDecorator( Str name ) ;
        /// ����Ȧ�߿�װ����
        virtual void                            destroyTerrainCircleDecorator(ITerrainCircleDecorator* decorator) ; 
        /// �������е�Ȧ�߿�װ����
                void                            destroyAllTerrainCircleDecorator();

        /// �������߿�װ����
        virtual ITerrainSquareDecorator*        createTerrainSquareDecorator( Str name ) ;
        /// �õ����߿�װ����
        virtual ITerrainSquareDecorator*        getTerrainSquareDecorator( Str name ) ;
        /// ���ٷ��߿�װ����
        virtual void                            destroyTerrainSquareDecorator(ITerrainSquareDecorator* decorator) ; 
        /// �������еķ��߿�װ����
                void                            destroyAllTerrainSquareDecorator();

        /// �������߿�װ����
        virtual ITerrainDiamondDecorator*        createTerrainDiamondDecorator( Str name ) ;
        /// �õ����߿�װ����
        virtual ITerrainDiamondDecorator*        getTerrainDiamondDecorator( Str name ) ;
        /// �������߿�װ����
        virtual void                            destroyTerrainDiamondDecorator(ITerrainDiamondDecorator* decorator) ; 
        /// �������е����߿�װ����
                void                            destroyAllTerrainDiamondDecorator();

                ///////////////////////////////////////////////////////////////////////////

        /// ���������߿�װ����
        virtual ITerrainGridsDecorator*         createTerrainGridsDecorator( Str name ) ;
        /// �õ������߿�װ����
        virtual ITerrainGridsDecorator*         getTerrainGridsDecorator( Str name ) ;
        /// ���������߿�װ����
        virtual void                            destroyTerrainGridsDecorator(ITerrainGridsDecorator* decorator) ; 
        /// �������е�Ȧ�߿�װ����
                void                            destroyAllTerrainGridsDecorator();

		/// ��Ч���������߿�װ����
		virtual IEffectGridsDecorator*          createEffectGridsDecorator( Str name );
		/// �õ���Ч���������߿�װ����
		virtual IEffectGridsDecorator*          getEffectGridsDecorator( Str name );
		/// ������Ч���������߿�װ����
		virtual void                            destroyEffectGridsDecorator(IEffectGridsDecorator* decorator); 
		/// �������е�Ȧ�߿�װ����
				void                            destroyAllEffectGridsDecorator();


        ////////////////////////////////////////////////////////////////////////

        /// ��Ⱦ�¼�
         virtual    void                        postFindVisibleObjects(Ogre::SceneManager* source, 
                                                Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport* v);

    private:

        ////////////////////////////////////////////////////////////////////////
        /// ����Scene
        Scene* mScene;

        ////////////////////////////////////////////////////////////////////////
        /// ���߶����б�
        NameGenerator mPolylineWireframeDecoratorNameGenerator;
        std::map<String, PolylineWireframeDecorator*> mPolylineWireframeDecorators;

        ////////////////////////////////////////////////////////////////////////
        /// ��Ļ�����߿�����б�
        NameGenerator mScreenRectWireframeDecoratorNameGenerator;
        std::map<String, ScreenRectWireframeDecorator*> mScreenRectWireframeDecorators;

        ////////////////////////////////////////////////////////////////////////
        /// ��ĻȦ�߿�װ���߶����б�
        NameGenerator mTerrainCircleDecoratorNameGenerator;
        std::map<String, TerrainCircleDecorator*> mTerrainCircleDecorator;

		////////////////////////////////////////////////////////////////////////
		/// ��Ļ���߿�װ���߶����б�
		NameGenerator mTerrainSquareDecoratorNameGenerator;
		std::map<String, TerrainSquareDecorator*> mTerrainSquareDecorator;

		////////////////////////////////////////////////////////////////////////
		/// ��Ļ���߿�װ���߶����б�
		NameGenerator mTerrainDiamondDecoratorNameGenerator;
		std::map<String, TerrainDiamondDecorator*> mTerrainDiamondDecorator;

        ////////////////////////////////////////////////////////////////////////
        /// ��ĻȦ�߿�װ���߶����б�
        NameGenerator mTerrainGridsDecoratorNameGenerator;
        std::map<String, TerrainGridsDecorator*> mTerrainGridsDecorator;

		////////////////////////////////////////////////////////////////////////
		/// ��Ч�����������
		NameGenerator mEffectGridsDecoratorNameGenerator;
		std::map<String, EffectGridDecorator*> mEffectGridsDecorator;
    };

}

/******************************************************************************/

#endif