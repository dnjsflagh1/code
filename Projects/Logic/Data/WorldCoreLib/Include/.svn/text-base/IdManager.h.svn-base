/******************************************************************************/
#ifndef _ID_MANAGER_H_
#define _ID_MANAGER_H_
/******************************************************************************/
#include "WorldCorePreqs.h"

/******************************************************************************/

namespace MG
{
	class IdManager
	{
	public:
		IdManager();
		~IdManager();
		SINGLETON_INSTANCE(IdManager);

		//获取唯一的id
		U32		createId();

		//释放该id
		void	releaseId(U32 id);

	private:

		InterLocked	mLockID;
	};
}

#endif	//_ID_MANAGER_H_