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
    //������ͼ���ӱ༭�ӿ�
    /******************************************************************************/
    class ITerrainAddTextureOperationManager : public IEditorOperationManager
    {
    public:
        ///�õ�����
        virtual Flt     getAmplitude() = NULL;
        ///���÷���
        virtual void    setAmplitude(Flt amp) = NULL;



    };

    /******************************************************************************/
    //������ͼ���ͱ༭�ӿ�
    /******************************************************************************/
    class ITerrainRemoveTextureOperationManager: public IEditorOperationManager
    {
    public:
        ///�õ�����
        virtual Flt     getAmplitude() = NULL;
        ///���÷���
        virtual void    setAmplitude(Flt amp) = NULL;

    };


    /******************************************************************************/
    //������ͼͳһ�༭�ӿ�
    /******************************************************************************/
    class ITerrainUniformTextureOperationManager: public IEditorOperationManager
    {
    public:
        ///�õ�����
        virtual Flt     getAmplitude() = NULL;
        ///���÷���
        virtual void    setAmplitude(Flt amp) = NULL;

    };


    /******************************************************************************/
    //������ͼĨͿ�༭�ӿ�
    /******************************************************************************/
    class ITerrainMopTextureOperationManager: public IEditorOperationManager
    {
    public:
        ///�õ�����
        virtual Flt     getAmplitude() = NULL;
        ///���÷���
        virtual void    setAmplitude(Flt amp) = NULL;

    };

    /******************************************************************************/
    //������ͼģ���༭�ӿ�
    /******************************************************************************/
    class ITerrainBlurTextureOperationManager: public IEditorOperationManager
    {
    public:
        ///�õ�����
        virtual Flt     getAmplitude() = NULL;
        ///���÷���
        virtual void    setAmplitude(Flt amp) = NULL;

    };
}

/******************************************************************************/
#endif
