/******************************************************************************/
#ifndef _IEDITORSYSTEM_H_
#define _IEDITORSYSTEM_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //��Ϸ�༭�ӿ�
    /******************************************************************************/
    class IEditorSystem
    {
    public:

        ///////////////////////////////////////////////////////////////////////////////////////////
        //����һ������
        virtual void                                            push( IEditorOperation* op ) = NULL; 
        //����һ������
        virtual void                                            pop() = NULL; 
        ///�õ���ˢ
        virtual IBrushSystem*                                   getBrushSystem() = NULL;

        ///////////////////////////////////////////////////////////////////////////////////////////

        ///�õ����θ߶����ӱ༭�ӿ�
        virtual ITerrainRaiseHeightOperationManager*            getTerrainRaiseHeightOperationManager() = NULL;
        ///�õ����θ߶Ƚ��ͱ༭�ӿ�
        virtual ITerrainLowerHeightOperationManager*            getTerrainLowerHeightOperationManager() = NULL;
        ///�õ����θ߶�ͳһ�༭�ӿ�
        virtual ITerrainUniformHeightOperationManager*          getTerrainUniformHeightOperationManager() = NULL;
        ///�õ����θ߶������༭�ӿ�
        virtual ITerrainNoiseHeightOperationManager*            getTerrainNoiseHeightOperationManager() = NULL;
        ///�õ����θ߶�ƽ���༭�ӿ�
        virtual ITerrainSmoothHeightOperationManager*           getTerrainSmoothHeightOperationManager() = NULL;

        ///////////////////////////////////////////////////////////////////////////////////////////

        ///�õ�������ͼ���ӱ༭�ӿ�
        virtual ITerrainAddTextureOperationManager*             getTerrainAddTextureOperationManager() = NULL;
        ///�õ�������ͼ���ͱ༭�ӿ�
        virtual ITerrainRemoveTextureOperationManager*          getTerrainRemoveTextureOperationManager() = NULL;
        ///�õ�������ͼͳһ�༭�ӿ�
        virtual ITerrainUniformTextureOperationManager*         getTerrainUniformTextureOOperationManager() = NULL;
        ///�õ�������ͼĨͿ�༭�ӿ�
        virtual ITerrainMopTextureOperationManager*             getTerrainMopTextureOperationManager() = NULL;
        ///�õ�������ͼģ���༭�ӿ�
        virtual ITerrainBlurTextureOperationManager*            getTerrainBlurTextureOperationManager() = NULL;


        ///////////////////////////////////////////////////////////////////////////////////////////

        ///�õ�����Tree�༭�ӿ�
        virtual ITerrainTreeOperationManager*			        getTerrainTreeOperationManager() = NULL;
        ///�õ�����Tree���ӱ༭�ӿ�
        virtual ITerrainAddTreeOperationManager*                getTerrainAddTreeOperationManager() = NULL;
        ///�õ�����Tree�Ƴ��༭�ӿ�
        virtual ITerrainRemoveTreeOperationManager*             getTerrainRemoveTreeOperationManager() = NULL;
        ///�õ�����Tree��ȷֲ��༭�ӿ�
        virtual ITerrainDefineTreeOperationManager*		        getTerrainDefineTreeOperationManager() = NULL;

        ///////////////////////////////////////////////////////////////////////////////////////////

        ///�õ������ϰ����ӱ༭�ӿ�
        virtual ITerrainAddRegionOperationManager*              getTerrainAddRegionOperationManager() = NULL;
        ///�õ������ϰ��Ƴ��༭�ӿ�
        virtual ITerrainRemoveRegionOperationManager*           getTerrainRemoveRegionOperationManager() = NULL;
    
        ///////////////////////////////////////////////////////////////////////////////////////////
        ///�õ�ˮ��ʾ�༭�ӿ�
        virtual ITerrainWaterShowOperationManager*               getTerrainWaterShowOperationManager() = NULL;
        ///�õ�ˮ���ر༭�ӿ�
        virtual ITerrainWaterHideOperationManager*               getTerrainWaterHideOperationManager() = NULL;


    };

}

/******************************************************************************/
#endif
