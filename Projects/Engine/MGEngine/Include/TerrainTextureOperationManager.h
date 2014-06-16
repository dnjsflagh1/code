/******************************************************************************/
#ifndef _TERRAINTEXTUREOPERATIONMANAGER_H_
#define _TERRAINTEXTUREOPERATIONMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrainTextureOperationManager.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //地形贴图增加编辑接口
    /******************************************************************************/
    class TerrainAddTextureOperationManager : public ITerrainAddTextureOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainAddTextureOperationManager)
        TerrainAddTextureOperationManager();
        virtual ~TerrainAddTextureOperationManager();

        ///得到幅度
        virtual Flt     getAmplitude();
        ///设置幅度
        virtual void    setAmplitude(Flt amp);

        ///创建一个操作
        virtual IEditorOperation*       createOneOperation();

    protected:

        Flt mAmp;
    };

    /******************************************************************************/
    //地形贴图降低编辑接口
    /******************************************************************************/
    class TerrainRemoveTextureOperationManager: public ITerrainRemoveTextureOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainRemoveTextureOperationManager)
        TerrainRemoveTextureOperationManager();
        virtual ~TerrainRemoveTextureOperationManager();

        ///得到幅度
        virtual Flt     getAmplitude();
        ///设置幅度
        virtual void    setAmplitude(Flt amp);

        ///创建一个操作
        virtual IEditorOperation*       createOneOperation();

    protected:

        Flt mAmp;

    };


    /******************************************************************************/
    //地形贴图统一编辑接口
    /******************************************************************************/
    class TerrainUniformTextureOperationManager: public ITerrainUniformTextureOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainUniformTextureOperationManager)
        TerrainUniformTextureOperationManager();
        virtual ~TerrainUniformTextureOperationManager();

        ///得到幅度
        virtual Flt     getAmplitude();
        ///设置幅度
        virtual void    setAmplitude(Flt amp);

        ///创建一个操作
        virtual IEditorOperation*       createOneOperation();

    protected:

        Flt mAmp;

    };


    /******************************************************************************/
    //地形贴图抹涂编辑接口
    /******************************************************************************/
    class TerrainMopTextureOperationManager: public ITerrainMopTextureOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainMopTextureOperationManager)
        TerrainMopTextureOperationManager();
        virtual ~TerrainMopTextureOperationManager();

        ///得到幅度
        virtual Flt     getAmplitude();
        ///设置幅度
        virtual void    setAmplitude(Flt amp);

        ///创建一个操作
        virtual IEditorOperation*       createOneOperation();

    protected:

        Flt mAmp;


    };

    /******************************************************************************/
    //地形贴图模糊编辑接口
    /******************************************************************************/
    class TerrainBlurTextureOperationManager: public ITerrainBlurTextureOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainBlurTextureOperationManager)
        TerrainBlurTextureOperationManager();
        virtual ~TerrainBlurTextureOperationManager();

        ///得到幅度
        virtual Flt     getAmplitude();
        ///设置幅度
        virtual void    setAmplitude(Flt amp);

        ///创建一个操作
        virtual IEditorOperation*       createOneOperation();

    protected:

        Flt mAmp;

    };

}

/******************************************************************************/

#endif

