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
	//��Ӧ�߻��ĵ�QuestTextһ����¼
	struct QuestTextInfo
	{
		U32					id;
		Str16				name;				//������
		Str16				nameAdd;			//���񸽼���
		Str16				desc;				//��������
		Str16				acceptText;			//��������Ի�����
		Str16				submitText;			//�ύ����Ի�����
		Str16				submitTextUnFinish;	//�ύ����δ��ɶԻ�����
		Str16				submitTextFail;		//�ύ����ʧ�ܶԻ�����
		Str16				destNpcText;		//����Ŀ��Ncp�ĶԻ�����
		Str16				valueText1;			//����Ŀ��1����������
		Str16				valueText2;			//����Ŀ��2����������	
		Str16				valueText3;			//����Ŀ��3����������
		Str16				valueText4;			//����Ŀ��4����������
		

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
	//��Ӧ�߻��ĵ�QuestText��
	class QuestTextInfos                       
	{
	public:
		QuestTextInfos();
		~QuestTextInfos();
		SINGLETON_INSTANCE(QuestTextInfos);

	public:
		// MG_CN_MODIFY
		///���� QuestText.csv 
		Bool                            load(Str16 fileName, IMGExternalPackManager* packManager = NULL);

		//����ID���  QuestTextInfo
		QuestTextInfo*					getQuestTextInfo(U32 id);

	protected:
		void                            clear();

	private:
		std::map<U32, QuestTextInfo*>	mQuestTextInfoMap;

	};
}
#endif