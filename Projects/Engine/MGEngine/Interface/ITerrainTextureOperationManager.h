/******************************************************************************/
#ifndef _ITERRAINTEXTUREOPERATIONMANAGER_H_
#define _ITERRAINTEXTUREOPERATIONMANAGER_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "IEditorOperation.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //地形贴图增加编辑接口
    /******************************************************************************/
    class ITerrainAddTextureOperationManager : public IEditorOperationManager
    {
    public:
        ///得到幅度
        virtual Flt     getAmplitude() = NULL;
        ///设置幅度
        virtual void    setAmplitude(Flt amp) = NULL;



    };

    /******************************************************************************/
    //地形贴图降低编辑接口
    /******************************************************************************/
    class ITerrainRemoveTextureOperationManager: public IEditorOperationManager
    {
    public:
        ///得到幅度
        virtual Flt     getAmplitude() = NULL;
        ///设置幅度
        virtual void    setAmplitude(Flt amp) = NULL;

    };


    /******************************************************************************/
    //地形贴图统一编辑接口
    /******************************************************************************/
    class ITerrainUniformTextureOperationManager: public IEditorOperationManager
    {
    public:
        ///得到幅度
        virtual Flt     getAmplitude() = NULL;
        ///设置幅度
        virtual void    setAmplitude(Flt amp) = NULL;

    };


    /******************************************************************************/
    //地形贴图抹涂编辑接口
    /******************************************************************************/
    class ITerrainMopTextureOperationManager: public IEditorOperationManager
    {
    public:
        ///得到幅度
        virtual Flt     getAmplitude() = NULL;
        ///设置幅度
        virtual void    setAmplitude(Flt amp) = NULL;

    };

    /******************************************************************************/
    //地形贴图模糊编辑接口
    /******************************************************************************/
    class ITerrainBlurTextureOperationManager: public IEditorOperationManager
    {
    public:
        ///得到幅度
        virtual Flt     getAmplitude() = NULL;
        ///设置幅度
        virtual void    setAmplitude(Flt amp) = NULL;

    };
}

/******************************************************************************/
#endif
