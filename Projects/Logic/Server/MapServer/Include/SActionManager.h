/******************************************************************************/
#ifndef _SACTIONMANAGER_H_
#define _SACTIONMANAGER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "LinedState.h"
#include "HeartBeatObject.h"

/******************************************************************************/

namespace MG
{


	/******************************************************************************/
	// 实体组Action管理
	/******************************************************************************/
	class SActionManager : public HeartBeatObject,  public LinedStateManager
	{
	public:
		SActionManager();
		virtual ~SActionManager();

	///////////////////////////////////////////////////////////////

		virtual void update();

	protected:
		Flt			mLastUpdateTime;
	};
}


#endif	