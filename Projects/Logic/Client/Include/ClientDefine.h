/******************************************************************************/
#ifndef _CLIENTDEFINE_H_
#define _CLIENTDEFINE_H_
/******************************************************************************/

#include "LinedState.h"

/******************************************************************************/
//��Ϸ�߼���
/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	enum CampaignResult
	{
		CampaignResult_Init,

		CampaignResult_Win,
		CampaignResult_Lose,

		CampaignResult_Max
	};


    /******************************************************************************/
    //��ϷĻ��
    /******************************************************************************/
    class IScreen : public LinedStateObject
    {
    public:

        IScreen( Str name ):LinedStateObject(name){};

        // ����ʼ���س���
        virtual void    onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) = 0;
        // ���������س���
        virtual void    onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) = 0;
        /// ��ж�س���
        virtual void    onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) = 0;

    };

    /******************************************************************************/
    //��Ϸ��������
    /******************************************************************************/
    class IOpCtrl
    {
    public:

        //��������
        virtual void    update( Flt delta ) = 0;
        //������ԭ
        virtual void    revert(){};

        // ����ʼ���س���
        virtual void    onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) {};
        // ���������س���
        virtual void    onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) {};
        /// ��ж�س���
        virtual void    onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) {};

    };

}


/******************************************************************************/
#endif

