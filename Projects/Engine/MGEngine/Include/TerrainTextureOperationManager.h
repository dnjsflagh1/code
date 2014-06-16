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
    //������ͼ���ӱ༭�ӿ�
    /******************************************************************************/
    class TerrainAddTextureOperationManager : public ITerrainAddTextureOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainAddTextureOperationManager)
        TerrainAddTextureOperationManager();
        virtual ~TerrainAddTextureOperationManager();

        ///�õ�����
        virtual Flt     getAmplitude();
        ///���÷���
        virtual void    setAmplitude(Flt amp);

        ///����һ������
        virtual IEditorOperation*       createOneOperation();

    protected:

        Flt mAmp;
    };

    /******************************************************************************/
    //������ͼ���ͱ༭�ӿ�
    /******************************************************************************/
    class TerrainRemoveTextureOperationManager: public ITerrainRemoveTextureOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainRemoveTextureOperationManager)
        TerrainRemoveTextureOperationManager();
        virtual ~TerrainRemoveTextureOperationManager();

        ///�õ�����
        virtual Flt     getAmplitude();
        ///���÷���
        virtual void    setAmplitude(Flt amp);

        ///����һ������
        virtual IEditorOperation*       createOneOperation();

    protected:

        Flt mAmp;

    };


    /******************************************************************************/
    //������ͼͳһ�༭�ӿ�
    /******************************************************************************/
    class TerrainUniformTextureOperationManager: public ITerrainUniformTextureOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainUniformTextureOperationManager)
        TerrainUniformTextureOperationManager();
        virtual ~TerrainUniformTextureOperationManager();

        ///�õ�����
        virtual Flt     getAmplitude();
        ///���÷���
        virtual void    setAmplitude(Flt amp);

        ///����һ������
        virtual IEditorOperation*       createOneOperation();

    protected:

        Flt mAmp;

    };


    /******************************************************************************/
    //������ͼĨͿ�༭�ӿ�
    /******************************************************************************/
    class TerrainMopTextureOperationManager: public ITerrainMopTextureOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainMopTextureOperationManager)
        TerrainMopTextureOperationManager();
        virtual ~TerrainMopTextureOperationManager();

        ///�õ�����
        virtual Flt     getAmplitude();
        ///���÷���
        virtual void    setAmplitude(Flt amp);

        ///����һ������
        virtual IEditorOperation*       createOneOperation();

    protected:

        Flt mAmp;


    };

    /******************************************************************************/
    //������ͼģ���༭�ӿ�
    /******************************************************************************/
    class TerrainBlurTextureOperationManager: public ITerrainBlurTextureOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainBlurTextureOperationManager)
        TerrainBlurTextureOperationManager();
        virtual ~TerrainBlurTextureOperationManager();

        ///�õ�����
        virtual Flt     getAmplitude();
        ///���÷���
        virtual void    setAmplitude(Flt amp);

        ///����һ������
        virtual IEditorOperation*       createOneOperation();

    protected:

        Flt mAmp;

    };

}

/******************************************************************************/

#endif

