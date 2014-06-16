
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
#ifndef _CQUEST_PLAYERCHARACTER_H_
#define _CQUEST_PLAYERCHARACTER_H_

/******************************************************************************/
#include "QuestPlayerCharacter.h"
#include "ClientPreqs.h"
/******************************************************************************/


namespace MG
{
	class CQuestPlayerCharacter : public QuestPlayerCharacter
	{
	public:
		CQuestPlayerCharacter(Clan* clan);
		~CQuestPlayerCharacter();

		virtual Bool	addQuest(Int questID);
		virtual Bool	submitQuest(Int questID);
		virtual Bool	giveupQuest(Int questID);
	};

}


#endif	//_CQUEST_PLAYERCHARACTER_H_