//*********************************************************************************************************
#ifndef _H_LEVEL_MANAGER_
#define _H_LEVEL_MANAGER_
//*********************************************************************************************************
#include "FrontServerPreqs.h"
//*********************************************************************************************************
namespace MG
{
	class LevelManager
	{
	public:
		LevelManager(){;}
		~LevelManager(){;}

	public:
		Bool		addExp(SCharacter* pCCharacter, Byte expType, U32 expNum, Bool& isUp);
		void		getLevelAndCurExp(SCharacter* pCCharacter, Byte expType, U32& level, U32& curExp);

	protected:
	private:
		
		void		setExp(SCharacter* pCCharacter, Byte expType, U32 expNum);
	};
}
//*********************************************************************************************************
#endif
//*********************************************************************************************************