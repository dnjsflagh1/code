//******************************************************************************************
#ifndef _QUESTVALUECHANGE_H_
#define _QUESTVALUECHANGE_H_
//******************************************************************************************
namespace MG
{
	enum CHANGE_TYPE
	{
		CHANGE_TYPE_NULL,								//������
		CHANGE_TYPE_RECIVE_THEN_FINISHED		= 1,	//���ܼ����
		CHANGE_TYPE_TALK_TO_NPC					= 2,	//��ĳһNpc�Ի�
		CHANGE_TYPE_KILL_MONSTER				= 3,	//ɱ��ĳһ����
		CHANGE_TYPE_KILLMONSTER_AND_GETITEM		= 4,	//ɱ��ĳһ������ĳһ��Ʒ
		CHANGE_TYPE_GET_ITEM					= 5,	//���ĳһ��Ʒ
		CHANGE_TYPE_GET_GENERAL					= 6,	//���ĳһ����
		CHANGE_TYPE_PLAY_TIME				    = 7,    //����һ����Ϸʱ��
		CHANGE_TYPE_LEAVE_MAP					= 8,	//�뿪ĳһ��ͼ
		CHANGE_TYPE_GET_ARMY					= 9,	//���ĳһ����
		CHANGE_TYPE_CREATE_BUILDING				= 10,	//����ĳһ����
		CHANGE_TYPE_CALL_MONSTER				= 11,	//�ٻ�ĳһ����
		CHANGE_TYPE_DESTORY_BUILDING			= 12,	//�ݻ�ĳһ����
		CHANGE_TYPE_WIN_ARMY					= 13,	//����ĳһ����
		CHANGE_TYPE_CLAN_LEVEL_CHANGE			= 14,	//����ȼ��仯
		CHANGE_TYPE_MAIN_GENERAL_LEVEL_CHANGE	= 15,	//�����ȼ��仯
		CHANGE_TYPE_USE_ITEM				    = 16,	//ʹ��ĳһ��Ʒ

	};
	enum VALUECHANGE_TYPE	
	{   
		VALUECHANGE_TYPE_1,	//�����¼��changeValue1
		VALUECHANGE_TYPE_2,	//...
		VALUECHANGE_TYPE_3,
		VALUECHANGE_TYPE_4,
	};
	//-----------------------------------------------------------------------
	//��Ӧ�߻��ĵ�QuestValueChangeһ����¼
	struct QuestValueChangeInfo
	{
		U32					id;				//����Ŀ��id
		U32					groupId;		//����Ŀ�����id
		CHANGE_TYPE			type;			//����Ŀ�������
		U32					param1;			//����Ŀ��Ĳ���1
		U32					param2;			//����Ŀ��Ĳ���2
		U32					param3;			//����Ŀ��Ĳ���3
		U32					param4;			//����Ŀ��Ĳ���4
		VALUECHANGE_TYPE	valueChangeType;//��Ӧ�����valueChange����
		I32					valueChangeNum;	//����valueChange�ı�ֵ
		QuestValueChangeInfo()
		{
			id = 0;				
			groupId = 0;		
			type = CHANGE_TYPE_NULL;			
			param1 = 0;			
			param2 = 0;	
			param3 = 0;			
			param4 = 0;	
			valueChangeType = VALUECHANGE_TYPE_1;
			valueChangeNum = 0;	
		}
	};
	enum
	{
		questvaluechangeinfoid,			
		questvaluechangeinfogroupid = 2,	//filter Note field
		questvaluechangeinfotype,			
		questvaluechangeinfoparam1,		
		questvaluechangeinfoparam2,
		questvaluechangeinfoparam3,		
		questvaluechangeinfoparam4,
		questvaluechangeinfovaluechangetype,
		questvaluechangeinfovaluechangenum,
	};
	//-----------------------------------------------------------------------
	//��Ӧ�߻��ĵ�QuestValueChange��
	class IMGExternalPackManager;

	class QuestValueChangeInfos                       
	{
	public:
		QuestValueChangeInfos();
		~QuestValueChangeInfos();
		SINGLETON_INSTANCE(QuestValueChangeInfos);

	public:
		// MG_CN_MODIFY
		///���� QuestValueChange.csv 
		Bool								load(Str16 fileName, IMGExternalPackManager* packManager = NULL);

		//����ID���  QuestValueChangeInfo
		QuestValueChangeInfo*				getQuestValueChangeInfo(U32 id);
		Int									getQuestValueChangeInfoByGroupId(U32 groupId,std::vector<QuestValueChangeInfo*>& changeValues);

	protected:
		void								clear();

	private:
		std::map<U32, QuestValueChangeInfo*>			mQuestValueChangeInfoMap;

	};
}
#endif