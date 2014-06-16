//******************************************************************************************
#ifndef _QUESTTEXT_H_
#define _QUESTTEXT_H_
//******************************************************************************************
namespace MG
{

#define QUEST_NAME_MAX_LEN		16
#define QUEST_NAMEADD_MAX_LEN	4
#define QUEST_DESC_MAX_LEN		64
#define QUEST_DIALG_MAX_LEN		128
#define QUEST_VALUE_MAX_LEN		64


	//-----------------------------------------------------------------------
	//对应策划文档QuestText一条记录
	struct QuestTextInfo
	{
		U32					id;
		Str16				name;				//任务名
		Str16				nameAdd;			//任务附加名
		Str16				desc;				//任务描述
		Str16				acceptText;			//接收任务对话文字
		Str16				submitText;			//提交任务对话文字
		Str16				submitTextUnFinish;	//提交任务未完成对话文字
		Str16				submitTextFail;		//提交任务失败对话文字
		Str16				destNpcText;		//任务目标Ncp的对话文字
		Str16				valueText1;			//任务目标1的描述文字
		Str16				valueText2;			//任务目标2的描述文字	
		Str16				valueText3;			//任务目标3的描述文字
		Str16				valueText4;			//任务目标4的描述文字
		

		QuestTextInfo()
		{
			id = 0;
			name.reserve(QUEST_NAME_MAX_LEN);		
			nameAdd.reserve(QUEST_NAMEADD_MAX_LEN);			
			desc.reserve(QUEST_DESC_MAX_LEN);				
			acceptText.reserve(QUEST_DIALG_MAX_LEN);			
			submitText.reserve(QUEST_DIALG_MAX_LEN);
			submitTextUnFinish.reserve(QUEST_DIALG_MAX_LEN);
			destNpcText.reserve(QUEST_DIALG_MAX_LEN);		
			valueText1.reserve(QUEST_VALUE_MAX_LEN);			
			valueText2.reserve(QUEST_VALUE_MAX_LEN);				
			valueText3.reserve(QUEST_VALUE_MAX_LEN);			
			valueText4.reserve(QUEST_VALUE_MAX_LEN);
			submitTextFail.reserve(QUEST_VALUE_MAX_LEN);
		}
	};
	enum
	{
		questtextinfoid,
		questtextinfonote,
		questtextinfoname,				
		questtextinfonameadd,	
		questtextinfodesc,			
		questtextinfoaccepttext,			
		questtextinfosubmittext,			
		questtextinfosubmittextunfinish,
		questtextinfosubmittextfail,
		questtextinfodestnpctext,	
		questtextinfovaluetext1,			
		questtextinfovaluetext2,			
		questtextinfovaluetext3,			
		questtextinfovaluetext4,
		
	};
	//-----------------------------------------------------------------------
	//对应策划文档QuestText表
	class QuestTextInfos                       
	{
	public:
		QuestTextInfos();
		~QuestTextInfos();
		SINGLETON_INSTANCE(QuestTextInfos);

	public:
		// MG_CN_MODIFY
		///加载 QuestText.csv 
		Bool                            load(Str16 fileName, IMGExternalPackManager* packManager = NULL);

		//根据ID获得  QuestTextInfo
		QuestTextInfo*					getQuestTextInfo(U32 id);

	protected:
		void                            clear();

	private:
		std::map<U32, QuestTextInfo*>	mQuestTextInfoMap;

	};
}
#endif