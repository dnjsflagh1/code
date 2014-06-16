/******************************************************************************/
#ifndef _SAIMANAGER_H_
#define _SAIMANAGER_H_
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
	class SAIManager : public HeartBeatObject,  public LinedStateManager
	{
	public:
		SAIManager();
		virtual ~SAIManager();

		///////////////////////////////////////////////////////////////

		virtual void update();

	protected:
		Flt			mLastUpdateTime;
	};
}


#endif	