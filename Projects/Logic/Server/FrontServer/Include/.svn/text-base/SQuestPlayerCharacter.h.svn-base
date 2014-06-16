
//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: SQuestManager.h
//        Author: yuanlinhu
//          Date: 2011-9-22
//          Time: 10:34
//   Description:
//			和玩家绑定的任务相关信息
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2011-9-22      add
//////////////////////////////////////////////////////////////
#ifndef _SQUEST_PLAYERCHARACTER_H_
#define _SQUEST_PLAYERCHARACTER_H_

/******************************************************************************/
#include "FrontServerPreqs.h"
/******************************************************************************/


namespace MG
{
	class SQuestPlayerCharacter : public QuestPlayerCharacter
	{
	public:
		SQuestPlayerCharacter(Clan* clan);
		~SQuestPlayerCharacter();

		virtual Bool	addQuest(Int questID);
		virtual Bool	submitQuest(Int questID);
		virtual Bool	giveupQuest(Int questID);

	//private:
	//	SClan*	getSClan();
	};

}


#endif	//_SQUEST_PLAYERCHARACTER_H_