//***********************************************************************************************************
#include "stdafx.h"
#include "HeadDes.h"
#include "HeadDesManage.h"
//***********************************************************************************************************
namespace MG
{
    HeadDesManage::~HeadDesManage()
    {
        clear();
    }
    //----------------------------------------------------------------------------------
    HeadDes* HeadDesManage::createHeadDes(CSceneEntity* pObj)
    {
        HeadDes* tempDes = NULL;
        if ( mHeadDesListFree.size() > 0 )
        {
            tempDes = mHeadDesListFree.front();
            tempDes->resetParent(pObj);

            mHeadDesListFree.pop_front();
            mHeadDesListWork.push_back(tempDes);  
        }
        else
        {
            tempDes = new HeadDes(pObj);
            assert(tempDes);
            mHeadDesList.push_back(tempDes);
            mHeadDesListWork.push_back(tempDes);
        }

        return tempDes;
    }
    //----------------------------------------------------------------------------------
    void HeadDesManage::destroyHeadDes( HeadDes* pHeadDes )
    {
        std::list<HeadDes*>::iterator iter = mHeadDesListWork.begin();
        while ( mHeadDesListWork.end() != iter )
        {
            if ( (*iter) == pHeadDes )
            {
                mHeadDesListWork.erase(iter);
                mHeadDesListFree.push_back(pHeadDes);

                pHeadDes->closeDes();
                return;
            }
            ++iter;
        }

		DYNAMIC_ASSERT(0);
    }
    //----------------------------------------------------------------------------------
    void HeadDesManage::clear()
    {
        mHeadDesListFree.clear();
        mHeadDesListWork.clear();

        while ( mHeadDesList.begin() != mHeadDesList.end() )
        {
            delete ( *mHeadDesList.begin() );
            mHeadDesList.erase( mHeadDesList.begin() ) ;
        }

        mHeadDesList.clear();
    }
}