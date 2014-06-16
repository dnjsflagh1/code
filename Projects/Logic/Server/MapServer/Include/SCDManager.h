//*********************************************************************************************************
#ifndef _SCD_MANAGER_H_
#define _SCD_MANAGER_H_
//*********************************************************************************************************
#include "MapServerPreqs.h"
#include "CDTimer.h"
//*********************************************************************************************************
namespace MG
{
	class SCDManager
	{
	public:
		SCDManager(CD_MASTER_TYPE type, SCharacter* parent = NULL);
		~SCDManager();

	public:

		//≥ı ºªØ
		void                    init();

	public:
		Bool                    checkCD(CD_MASTER_TYPE type, U32 cdid);
		void                    addCD(CD_MASTER_TYPE type, U32 cdid, U32 liveTime, U32 totalTime);
		void                    removeCD(CD_MASTER_TYPE type, U32 cdid);
		void                    removeGroupCD(CD_MASTER_TYPE type, U32 cdGroupId);

	private:
		void                    clear();

	private:
		CDTimer					mCDTimer;
		CD_MASTER_TYPE			mType;
		SCharacter*				mParent;
	};
}
//*********************************************************************************************************
#endif
//*********************************************************************************************************