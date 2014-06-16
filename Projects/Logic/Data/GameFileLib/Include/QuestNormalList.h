//******************************************************************************************
#ifndef _QUESTNORMALLIST_H_
#define _QUESTNORMALLIST_H_
//******************************************************************************************
#include "ClanQuestInfoBase.h"
//******************************************************************************************
namespace MG
{

	//-----------------------------------------------------------------------
	//对应策划文档QuestNormalList一条记录
	enum CYCLE_TYPE
	{
		CYCLE_TYPE_NULL,		//无意义
		CYCLE_TYPE_ONCE,		//一次任务
		CYCLE_TYPE_PER_HOUR,	//每小时
		CYCLE_TYPE_PER_DAY,		//每日
		CYCLE_TYPE_PER_WEEK,	//每周
		
	};
	struct QuestNormalInfo : public ClanQuestInfoBase
	{
		U32					id;					//普通任务的id
		CYCLE_TYPE			cycleType;			//循环类型
		U32					textId;				//任务文本id

		U32					acceptNpcId;		//接任务Npc模版id		做注释用（与functionDialgue表对应）
		U32					submitNpcId;		//交任务Npc模版id		做注释用（与functionDialgue表对应）

		U32					clanJudgeId;		//氏族要求id
		U32					characterJudgeId;	//角色要求id

		U32					valueChangeGroupId;	//任务目标的组id

		I32					valueSuccess[MAX_CLAN_QUEST_VALUE_COUNT];		//任务成功判断值1


		I32					valueFail[MAX_CLAN_QUEST_VALUE_COUNT];			//任务失败判断值


		U32					giveStateId;		//给予的状态id
		U32					giveStateNum;		//给予的状态的叠加数
		U32					giveItemId;			//给予氏族的物品id
		Str8				giveScript;			//接收任务给予的脚本

		U32					delStateId;			//完成任务删除的状态id
		U32					delItemGroupId;		//完成任务删除物品的分组id
		Str8				delScript;			//完成任务给予的脚本
		U32					itemGroupId;		//完成任务奖励物品的分组id
		QuestNormalInfo()
		{
			id = 0;					
			cycleType = CYCLE_TYPE_NULL;
			textId = 0;

			acceptNpcId = 0;
			submitNpcId = 0;

			clanJudgeId = 0;
			characterJudgeId = 0;

			valueChangeGroupId = 0;

			valueSuccess[0] = 0;
			valueSuccess[1] = 0;
			valueSuccess[2] = 0;
			valueSuccess[3] = 0;

			valueFail[0] = 0;
			valueFail[2] = 0;
			valueFail[3] = 0;	
			valueFail[4] = 0;

			giveStateId = 0;
			giveStateNum = 0;	
			giveItemId = 0;
			delStateId = 0;
			delItemGroupId = 0;
			itemGroupId = 0;
			giveScript.reserve(QUEST_SCRIPT_NAME_MAX_LEN);
			delScript.reserve(QUEST_SCRIPT_NAME_MAX_LEN);
		}
		// 接口
		//---------------------------------------------------------------------
		virtual QuestTextInfo*	getTextInfo();
		virtual	Str8&			getAcceptScript();
		virtual	Str8&			getSubmitScript();
		virtual	CYCLE_TYPE		getQuestCycleType();
		virtual	Int				getValue(Bool success,Int index);
		virtual	Int				getValueChangeGroupInfo(std::vector<QuestValueChangeInfo*>& changeValues);
		virtual U32             getItemGroupId();
		virtual U32             getItemDelGroupId();
		virtual U32             getclanJudgeId();
		virtual U32             getcharacterJudgeId();

	};
	enum
	{
		questnormalinfoid,
		questnormalinfonote,
		questnormalinfocycletype,
		questnormalinfotextid,

		questnormalinfoacceptnpcid,
		questnormalinfosubmitnpcid,

		questnormalinfoclanjudgeid,
		questnormalinfocharacterjudgeid,

		questnormalinfovaluechangegroupid,

		questnormalinfovaluesuccess1,
		questnormalinfovaluesuccess2,
		questnormalinfovaluesuccess3,
		questnormalinfovaluesuccess4,

		questnormalinfovaluefail1,
		questnormalinfovaluefail2,
		questnormalinfovaluefail3,	
		questnormalinfovaluefail4,

		questnormalinfogivestateid,
		questnormalinfogivestatenum,	
		questnormalinfogiveitemid,
		questnormalinfogivescript,
		questnormalinfodelstateid,
		questnormalinfodelitemgroupid,
		questnormalinfodelscript,
		questnormalinfoitemgroupid,
	};
	//-----------------------------------------------------------------------
	//对应策划文档QuestNormalList表
	class QuestNormalInfos                       
	{
	public:
		QuestNormalInfos();
		~QuestNormalInfos();
		SINGLETON_INSTANCE(QuestNormalInfos);

	public:
		// MG_CN_MODIFY
		///加载 QuestNormalList.csv 
		Bool								load(Str16 fileName, IMGExternalPackManager* packManager = NULL);

		//根据ID获得  QuestNormalInfo
		QuestNormalInfo*					getQuestNormalInfo(U32 id);

	protected:
		void								clear();

	private:
		std::map<U32, QuestNormalInfo*>		mQuestNormalInfoMap;

	};
}
#endif