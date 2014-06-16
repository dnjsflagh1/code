//***********************************************************************************************************
#ifndef _H_HEADDESMANAGE_
#define _H_HEADDESMANAGE_
//***********************************************************************************************************
#include "ClientPreqs.h"
//***********************************************************************************************************
namespace  MG
{
    class HeadDesManage
    {
    public:
        HeadDesManage(){;}
        ~HeadDesManage();
        SINGLETON_INSTANCE(HeadDesManage);

    public:
        HeadDes*	createHeadDes(MG::CSceneEntity* pObj);
        void		destroyHeadDes(HeadDes* pHeadDes);

    protected:
        void		clear();

    private:
        std::vector<HeadDes*> mHeadDesList;
        
        std::list<HeadDes*> mHeadDesListWork;
        std::list<HeadDes*> mHeadDesListFree;
    };
}
//***********************************************************************************************************
#endif
//***********************************************************************************************************