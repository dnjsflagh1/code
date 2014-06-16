
/******************************************************************************/
#ifndef _S_CAMPAIGNMANAGER_H_
#define _S_CAMPAIGNMANAGER_H_
/******************************************************************************/

#include "MapServerPreqs.h"


/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // SCampaignManager
    /******************************************************************************/
    class SCampaignInRegionManager
    {
    public:
        SCampaignInRegionManager();
        ~SCampaignInRegionManager();
        SINGLETON_INSTANCE(SCampaignInRegionManager);
      
	public:
		// ´´½¨ Ïú»ÙSCampaign 
        void    createCampaign( );
        

       
    };
}

#endif	//