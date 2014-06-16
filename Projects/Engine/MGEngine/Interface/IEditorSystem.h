/******************************************************************************/
#ifndef _IEDITORSYSTEM_H_
#define _IEDITORSYSTEM_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //游戏编辑接口
    /******************************************************************************/
    class IEditorSystem
    {
    public:

        ///////////////////////////////////////////////////////////////////////////////////////////
        //增加一个操作
        virtual void                                            push( IEditorOperation* op ) = NULL; 
        //回退一个操作
        virtual void                                            pop() = NULL; 
        ///得到笔刷
        virtual IBrushSystem*                                   getBrushSystem() = NULL;

        ///////////////////////////////////////////////////////////////////////////////////////////

        ///得到地形高度增加编辑接口
        virtual ITerrainRaiseHeightOperationManager*            getTerrainRaiseHeightOperationManager() = NULL;
        ///得到地形高度降低编辑接口
        virtual ITerrainLowerHeightOperationManager*            getTerrainLowerHeightOperationManager() = NULL;
        ///得到地形高度统一编辑接口
        virtual ITerrainUniformHeightOperationManager*          getTerrainUniformHeightOperationManager() = NULL;
        ///得到地形高度噪音编辑接口
        virtual ITerrainNoiseHeightOperationManager*            getTerrainNoiseHeightOperationManager() = NULL;
        ///得到地形高度平滑编辑接口
        virtual ITerrainSmoothHeightOperationManager*           getTerrainSmoothHeightOperationManager() = NULL;

        ///////////////////////////////////////////////////////////////////////////////////////////

        ///得到地形贴图增加编辑接口
        virtual ITerrainAddTextureOperationManager*             getTerrainAddTextureOperationManager() = NULL;
        ///得到地形贴图降低编辑接口
        virtual ITerrainRemoveTextureOperationManager*          getTerrainRemoveTextureOperationManager() = NULL;
        ///得到地形贴图统一编辑接口
        virtual ITerrainUniformTextureOperationManager*         getTerrainUniformTextureOOperationManager() = NULL;
        ///得到地形贴图抹涂编辑接口
        virtual ITerrainMopTextureOperationManager*             getTerrainMopTextureOperationManager() = NULL;
        ///得到地形贴图模糊编辑接口
        virtual ITerrainBlurTextureOperationManager*            getTerrainBlurTextureOperationManager() = NULL;


        ///////////////////////////////////////////////////////////////////////////////////////////

        ///得到地形Tree编辑接口
        virtual ITerrainTreeOperationManager*			        getTerrainTreeOperationManager() = NULL;
        ///得到地形Tree增加编辑接口
        virtual ITerrainAddTreeOperationManager*                getTerrainAddTreeOperationManager() = NULL;
        ///得到地形Tree移除编辑接口
        virtual ITerrainRemoveTreeOperationManager*             getTerrainRemoveTreeOperationManager() = NULL;
        ///得到地形Tree噪度分布编辑接口
        virtual ITerrainDefineTreeOperationManager*		        getTerrainDefineTreeOperationManager() = NULL;

        ///////////////////////////////////////////////////////////////////////////////////////////

        ///得到地形障碍增加编辑接口
        virtual ITerrainAddRegionOperationManager*              getTerrainAddRegionOperationManager() = NULL;
        ///得到地形障碍移除编辑接口
        virtual ITerrainRemoveRegionOperationManager*           getTerrainRemoveRegionOperationManager() = NULL;
    
        ///////////////////////////////////////////////////////////////////////////////////////////
        ///得到水显示编辑接口
        virtual ITerrainWaterShowOperationManager*               getTerrainWaterShowOperationManager() = NULL;
        ///得到水隐藏编辑接口
        virtual ITerrainWaterHideOperationManager*               getTerrainWaterHideOperationManager() = NULL;


    };

}

/******************************************************************************/
#endif
