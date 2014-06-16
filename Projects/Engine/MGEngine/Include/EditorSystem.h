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
    //游戏编辑主接口
    /******************************************************************************/
    class EditorSystem : public IEditorSystem
    {
    public:
        SINGLETON_INSTANCE(EditorSystem)
        EditorSystem();
        virtual ~EditorSystem();

        /////////////////////////////////////////////////////////////////////////////////////////////

        //增加一个操作
        virtual void                                            push( IEditorOperation* op ) ; 
        //回退一个操作
        virtual void                                            pop(); 

        /////////////////////////////////////////////////////////////////////////////////////////////

        ///得到笔刷
        virtual IBrushSystem*                                   getBrushSystem() ;


        /////////////////////////////////////////////////////////////////////////////////////////////

        ///得到地形高度增加编辑接口
        virtual ITerrainRaiseHeightOperationManager*            getTerrainRaiseHeightOperationManager();
        ///得到地形高度降低编辑接口
        virtual ITerrainLowerHeightOperationManager*            getTerrainLowerHeightOperationManager();
        ///得到地形高度统一编辑接口
        virtual ITerrainUniformHeightOperationManager*          getTerrainUniformHeightOperationManager();
        ///得到地形高度噪音编辑接口
        virtual ITerrainNoiseHeightOperationManager*            getTerrainNoiseHeightOperationManager();
        ///得到地形高度平滑编辑接口
        virtual ITerrainSmoothHeightOperationManager*           getTerrainSmoothHeightOperationManager();

        /////////////////////////////////////////////////////////////////////////////////////////////

        ///得到地形贴图增加编辑接口
        virtual ITerrainAddTextureOperationManager*             getTerrainAddTextureOperationManager();
        ///得到地形贴图降低编辑接口
        virtual ITerrainRemoveTextureOperationManager*          getTerrainRemoveTextureOperationManager();
        ///得到地形贴图统一编辑接口
        virtual ITerrainUniformTextureOperationManager*         getTerrainUniformTextureOOperationManager();
        ///得到地形贴图抹涂编辑接口
        virtual ITerrainMopTextureOperationManager*             getTerrainMopTextureOperationManager();
        ///得到地形贴图模糊编辑接口
        virtual ITerrainBlurTextureOperationManager*            getTerrainBlurTextureOperationManager();

        /////////////////////////////////////////////////////////////////////////////////////////////

        ///得到地形Tree编辑接口
        virtual ITerrainTreeOperationManager*			        getTerrainTreeOperationManager();
        ///得到地形Tree增加编辑接口
        virtual ITerrainAddTreeOperationManager*                getTerrainAddTreeOperationManager();
        ///得到地形Tree移除编辑接口
        virtual ITerrainRemoveTreeOperationManager*             getTerrainRemoveTreeOperationManager();
        ///得到地形Tree噪度分布编辑接口
        virtual ITerrainDefineTreeOperationManager*		        getTerrainDefineTreeOperationManager();

        /////////////////////////////////////////////////////////////////////////////////////////////

        ///得到地形障碍增加编辑接口
        virtual ITerrainAddRegionOperationManager*               getTerrainAddRegionOperationManager() ;
        ///得到地形障碍移除编辑接口
        virtual ITerrainRemoveRegionOperationManager*            getTerrainRemoveRegionOperationManager() ;

        /////////////////////////////////////////////////////////////////////////////////////////////

        ///得到水显示编辑接口
        virtual ITerrainWaterShowOperationManager*               getTerrainWaterShowOperationManager() ;
        ///得到水隐藏编辑接口
        virtual ITerrainWaterHideOperationManager*               getTerrainWaterHideOperationManager() ;


    protected:
        
        //清空操作列表
        void                                                    clearOperationList();

    private:

        std::deque<IEditorOperation*>   mEditorOperationList;
        UInt                            mMaxOperationMemeryCount;
    };

}

/******************************************************************************/

#endif

