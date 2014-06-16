/******************************************************************************/
#ifndef _ITERRAINHEIGHTOPERATIONMANAGER_H_
#define _ITERRAINHEIGHTOPERATIONMANAGER_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "IEditorOperation.h"
#include "ITerrain.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //��Ϸ���θ߶����ӽӿ�
    /******************************************************************************/
    class ITerrainHeightOperationManager : public IEditorOperationManager
    {
    public:
        ITerrainHeightOperationManager()
            :mTerrainSurfaceType(TST_GROUND)
        {
        }
        /// ���ò����ر�����
        void                    setTerrainSurfaceType( TerrainSurfaceType type ){mTerrainSurfaceType=type;};
        /// �õ������ر�����
        TerrainSurfaceType      getTerrainSurfaceType(){return mTerrainSurfaceType;};

    protected:

        TerrainSurfaceType mTerrainSurfaceType;
    };



    /******************************************************************************/
    //��Ϸ���θ߶����ӽӿ�
    /******************************************************************************/
    class ITerrainRaiseHeightOperationManager : public ITerrainHeightOperationManager
    {
    public:
        ///�õ�����
        virtual Flt     getAmplitude() = NULL;
        ///���÷���
        virtual void    setAmplitude(Flt amp) = NULL;
		///�õ�����
		virtual Flt     getWaterAmplitude() = NULL;
		///���÷���
		virtual void    setWaterAmplitude(Flt amp) = NULL;
    };

    /******************************************************************************/
    //��Ϸ���θ߶ȼ��ٽӿ�
    /******************************************************************************/
    class ITerrainLowerHeightOperationManager: public ITerrainHeightOperationManager
    {
    public:
        ///�õ�����
        virtual Flt     getAmplitude() = NULL;
        ///���÷���
        virtual void    setAmplitude(Flt amp) = NULL;
		///�õ�����
		virtual Flt     getWaterAmplitude() = NULL;
		///���÷���
		virtual void    setWaterAmplitude(Flt amp) = NULL;
    };

    /******************************************************************************/
    //���θ߶�ͳһ�༭�ӿ�
    /******************************************************************************/
    class ITerrainUniformHeightOperationManager: public ITerrainHeightOperationManager
    {
    public:

		virtual void	setWaterHeight( Flt height ) = NULL;
		///�õ�ˮ�����ø߶�
		virtual Flt		getWaterHeight() = NULL;
		///����ˮ�ĸ߶�ֵ, ������UIʹ��
		virtual void	lock(bool islock) = NULL;
		///�Ƿ�����ˮ�ĸ߶ȣ���UIʹ��
		virtual bool	isLocked() = NULL;
    };

    /******************************************************************************/
    //���θ߶������༭�ӿ�
    /******************************************************************************/
    class ITerrainNoiseHeightOperationManager: public ITerrainHeightOperationManager
    {
    public:
		///�õ�����
		virtual Flt     getAmplitude() = NULL;
		///���÷���
		virtual void    setAmplitude(Flt amp) = NULL;
    };

    /******************************************************************************/
    //���θ߶�ƽ���༭�ӿ�
    /******************************************************************************/
    class ITerrainSmoothHeightOperationManager: public ITerrainHeightOperationManager
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
