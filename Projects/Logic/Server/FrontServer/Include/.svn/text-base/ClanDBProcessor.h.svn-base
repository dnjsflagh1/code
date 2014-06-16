/******************************************************************************/
#ifndef _CLANDBPROCESSOR_H_
#define _CLANDBPROCESSOR_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SPlayer.h"
/******************************************************************************/

namespace MG
{
    class ClanDBProcessor
    {
    public:

        SINGLETON_INSTANCE(ClanDBProcessor);
        ClanDBProcessor();
        ~ClanDBProcessor();


        void    loadAndCreateAllClanInPlayer( SPlayerPtr& playerPtr );
		Bool	insertClanDataInfo(const ClanData* _clandata);
        
		Bool	updateClanDataInfo(const ClanData* _clandata);
    };
}
#endif