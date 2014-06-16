/******************************************************************************/
#ifndef _QUESTDBPROCESSOR_H_
#define _QUESTDBPROCESSOR_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SClan.h"
#include "ClanQuestObject.h"
/******************************************************************************/

namespace MG
{
    class QuestDBProcessor
    {
    public:

        SINGLETON_INSTANCE(QuestDBProcessor);
        QuestDBProcessor();
        ~QuestDBProcessor();


        void loadQuestInClan(   SClanPtr& clanPtr, 
                                std::vector<dbDoingClanQuestObject>& doingQuestData, 
                                std::vector<FinishedClanQuestObject>& finishedQuestData );

    };
}
#endif