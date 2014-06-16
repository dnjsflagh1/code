/******************************************************************************/
#ifndef _ITEMDBPROCESSOR_H_
#define _ITEMDBPROCESSOR_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SClan.h"
#include "SPlayerCharacter.h"
#include "PlayerItem.h"
/******************************************************************************/

namespace MG
{
    class ItemDBProcessor
    {
    public:

        SINGLETON_INSTANCE(ItemDBProcessor);
        ItemDBProcessor();
        ~ItemDBProcessor();

        
        void        loadItemRecordInClan( SClanPtr& clanPtr, std::vector<ItemRecord>& itemList );
        void        loadItemRecordInPlayerCharacter( SPlayerCharacterPtr& clarPtr, std::vector<ItemRecord>& itemList );



    };
}
#endif