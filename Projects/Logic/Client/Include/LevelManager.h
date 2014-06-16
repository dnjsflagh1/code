//*********************************************************************************************************
#ifndef _H_LEVEL_MANAGER_
#define _H_LEVEL_MANAGER_
//*********************************************************************************************************
#include "ClientPreqs.h"
//*********************************************************************************************************
namespace MG
{
	class LevelManager
	{
	public:
		LevelManager(){;}
		~LevelManager(){;}
		SINGLETON_INSTANCE(LevelManager);

	public:
		void		addExp(CCharacter* pCCharacter, Byte expType, U32 expNum);

	protected:
	private:
		void		getLevelAndCurExp(CCharacter* pCCharacter, Byte expType, U32& level, U32& curExp);
		void		setExp(CCharacter* pCCharacter, Byte expType, U32 expNum);
	};
}
//*********************************************************************************************************
#endif
//*********************************************************************************************************