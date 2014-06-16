/******************************************************************************/
#ifndef _EDITORSYSTEM_H_
#define _EDITORSYSTEM_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IEditorSystem.h"
/******************************************************************************/
namespace MG
{


    /******************************************************************************/
    //��Ϸ�༭���ӿ�
    /******************************************************************************/
    class EditorSystem : public IEditorSystem
    {
    public:
        SINGLETON_INSTANCE(EditorSystem)
        EditorSystem();
        virtual ~EditorSystem();

        /////////////////////////////////////////////////////////////////////////////////////////////

        //����һ������
        virtual void                                            push( IEditorOperation* op ) ; 
        //����һ������
        virtual void                                            pop(); 

        /////////////////////////////////////////////////////////////////////////////////////////////

        ///�õ���ˢ
        virtual IBrushSystem*                                   getBrushSystem() ;


        /////////////////////////////////////////////////////////////////////////////////////////////

        ///�õ����θ߶����ӱ༭�ӿ�
        virtual ITerrainRaiseHeightOperationManager*            getTerrainRaiseHeightOperationManager();
        ///�õ����θ߶Ƚ��ͱ༭�ӿ�
        virtual ITerrainLowerHeightOperationManager*            getTerrainLowerHeightOperationManager();
        ///�õ����θ߶�ͳһ�༭�ӿ�
        virtual ITerrainUniformHeightOperationManager*          getTerrainUniformHeightOperationManager();
        ///�õ����θ߶������༭�ӿ�
        virtual ITerrainNoiseHeightOperationManager*            getTerrainNoiseHeightOperationManager();
        ///�õ����θ߶�ƽ���༭�ӿ�
        virtual ITerrainSmoothHeightOperationManager*           getTerrainSmoothHeightOperationManager();

        /////////////////////////////////////////////////////////////////////////////////////////////

        ///�õ�������ͼ���ӱ༭�ӿ�
        virtual ITerrainAddTextureOperationManager*             getTerrainAddTextureOperationManager();
        ///�õ�������ͼ���ͱ༭�ӿ�
        virtual ITerrainRemoveTextureOperationManager*          getTerrainRemoveTextureOperationManager();
        ///�õ�������ͼͳһ�༭�ӿ�
        virtual ITerrainUniformTextureOperationManager*         getTerrainUniformTextureOOperationManager();
        ///�õ�������ͼĨͿ�༭�ӿ�
        virtual ITerrainMopTextureOperationManager*             getTerrainMopTextureOperationManager();
        ///�õ�������ͼģ���༭�ӿ�
        virtual ITerrainBlurTextureOperationManager*            getTerrainBlurTextureOperationManager();

        /////////////////////////////////////////////////////////////////////////////////////////////

        ///�õ�����Tree�༭�ӿ�
        virtual ITerrainTreeOperationManager*			        getTerrainTreeOperationManager();
        ///�õ�����Tree���ӱ༭�ӿ�
        virtual ITerrainAddTreeOperationManager*                getTerrainAddTreeOperationManager();
        ///�õ�����Tree�Ƴ��༭�ӿ�
        virtual ITerrainRemoveTreeOperationManager*             getTerrainRemoveTreeOperationManager();
        ///�õ�����Tree��ȷֲ��༭�ӿ�
        virtual ITerrainDefineTreeOperationManager*		        getTerrainDefineTreeOperationManager();

        /////////////////////////////////////////////////////////////////////////////////////////////

        ///�õ������ϰ����ӱ༭�ӿ�
        virtual ITerrainAddRegionOperationManager*               getTerrainAddRegionOperationManager() ;
        ///�õ������ϰ��Ƴ��༭�ӿ�
        virtual ITerrainRemoveRegionOperationManager*            getTerrainRemoveRegionOperationManager() ;

        /////////////////////////////////////////////////////////////////////////////////////////////

        ///�õ�ˮ��ʾ�༭�ӿ�
        virtual ITerrainWaterShowOperationManager*               getTerrainWaterShowOperationManager() ;
        ///�õ�ˮ���ر༭�ӿ�
        virtual ITerrainWaterHideOperationManager*               getTerrainWaterHideOperationManager() ;


    protected:
        
        //��ղ����б�
        void                                                    clearOperationList();

    private:

        std::deque<IEditorOperation*>   mEditorOperationList;
        UInt                            mMaxOperationMemeryCount;
    };

}

/******************************************************************************/

#endif

