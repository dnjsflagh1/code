/******************************************************************************/
#ifndef _PLAYERCHARACTERDBPROCESSOR_H_
#define _PLAYERCHARACTERDBPROCESSOR_H_
/******************************************************************************/
#include "FrontServerPreqs.h"
#include "SPlayer.h"
/******************************************************************************/

namespace MG
{
    class PlayerCharacterDBProcessor
    {
    public:

        SINGLETON_INSTANCE(PlayerCharacterDBProcessor);
        PlayerCharacterDBProcessor();
        ~PlayerCharacterDBProcessor();


        void    loadAndCreateAllPlayerCharacterInPlayer( SPlayerPtr& playerPtr );

		Bool	insertGenrealDataInfo(const PlayerCharacterData* _PlayerCharacterData);
    };
}
#endif