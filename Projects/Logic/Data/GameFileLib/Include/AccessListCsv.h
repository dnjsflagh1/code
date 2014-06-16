//********************************************************************************************************************
#ifndef _H_ACCESS_LIST_
#define _H_ACCESS_LIST_
//********************************************************************************************************************
#include "GameFilePreqs.h"
//********************************************************************************************************************
namespace MG
{
    //Ӣ����	������	        ��;����
    //AccessId	��·ID	        ��·��id
    //RoadName	��·����	    ��·���������ƣ�16��������
    //Type	    ��·����	    ��·ʹ�ö�������ͣ���Ϊ����1����ͨ·�����Ӻͽ�ɫ����ͨ�У�������2������ר��·������3����ɫר��·
    //PlaceAId	A�ص�ID	        ��·һ�˵ص��PlaceId
    //PlaceBId	B�ص�ID	        ��·��һ�˵ص��PlaceId
    //MapId	    ����id	        ����սʱѡ�õĸ�����ͼid

    struct AccessInfo 
    {
        U32             AccessId    ;
        Str16           RoadName    ;
        ACCESS_TYPE     Type	    ;
        U32             PlaceAId    ;
        U32             PlaceBId    ;
        U32             MapId	    ;
    };
    //------------------------------------------------------------------------------------
    class AccessListCsv
    {
    public:
        AccessListCsv(){;}
        ~AccessListCsv();
        SINGLETON_INSTANCE(AccessListCsv);

    public:
		// MG_CN_MODIFY
        //����place�ڵ���
        Bool                        load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        //���place�ڵ���Ϣ
        const AccessInfo*           getAccessInfo( U32 accessId );
        //���place�ڵ���Ϣ
        Bool                        getAccessInfo( U32 accessId, const AccessInfo*& info );
        //���place�����нڵ㡣
        std::map<U32, AccessInfo*>* getMapAccessInfo(){return &mMapAccessInfo;}

    protected:
        void                        clear();

    private:
        std::map<U32, AccessInfo*>  mMapAccessInfo;

    };
}
//********************************************************************************************************************
#endif
//********************************************************************************************************************