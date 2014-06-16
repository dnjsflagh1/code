/******************************************************************************/
#ifndef _SACTIONOBJECTMANAGER_H_
#define _SACTIONOBJECTMANAGER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "LinedState.h"
#include "ObjectPool.h"

/******************************************************************************/

namespace MG
{


	/******************************************************************************/
	// 实体组Action管理
	/******************************************************************************/
	class SActionObjectManager : public LinedStateObjectListener
	{
	public:
		SActionObjectManager();
		virtual ~SActionObjectManager();
		SINGLETON_INSTANCE(SActionObjectManager)

			void									revert();

		///////////////////////////////////////////////////////////////////////////////////

		SCharacterMoveToAction*						createSCharacterMoveToAction( SCharacter* character, Vec3 startMovePos, Vec3 moveToPos );
		void										destroySCharacterMoveToAction( SCharacterMoveToAction* action );

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		virtual void								onLinedStateLifeTimeOver(LinedStateObject* obj);

	protected:

		ObjectPool<SCharacterMoveToAction>          mSCharacterMoveToActionPool;

	};
}


#endif	