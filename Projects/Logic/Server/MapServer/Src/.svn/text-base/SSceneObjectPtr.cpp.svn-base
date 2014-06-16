/******************************************************************************/

#include "stdafx.h"
#include "SSceneObjectPtr.h"
#include "SSceneObjectFactory.h"
#include "SSceneObject.h"
#include "SGameObjectFactory.h"
#include "SThirdPartCharacter.h"
#include "SMonster.h"
#include "SCamp.h"
#include "SBuilding.h"


/******************************************************************************/

namespace MG
{
    
    //-----------------------------------------------------------------------------
    void SSceneObjectPtr::destroy(void)
    {
        mFactory->destroySceneObject( getPointer() );
    }

}	//namespace MG