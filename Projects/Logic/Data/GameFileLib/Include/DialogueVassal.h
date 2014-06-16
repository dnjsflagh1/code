//******************************************************************************************
#ifndef _DIALOGUEVASSAL_H_
#define _DIALOGUEVASSAL_H_
//******************************************************************************************
#include "GameFilePreqs.h"
namespace MG
{

		#define NPC_DIALOG_FUNCTION_ID_COUNT 8
		
		
		///��Ӧ�߻��ĵ�DialogueVassalһ����¼
		struct DialogueVassalInfo
		{
			U32					id;				//id
			U32					diaType;		//�Ի�Ŀ������
			U32                 diaObjectId;    //�Ի�Ŀ��ID
			U32					fuctionId[NPC_DIALOG_FUNCTION_ID_COUNT];          //��������

			DialogueVassalInfo():id(0),diaType(0),diaObjectId(0)
			{
				for (Int i = 0; i < NPC_DIALOG_FUNCTION_ID_COUNT; i++)
				{
					fuctionId[i] = 0;
				}
			}
		};


		class DialogueVassal
		{

		public:
			DialogueVassal();
			~DialogueVassal();
			SINGLETON_INSTANCE(DialogueVassal);
            
			enum
			{
				dialogueVassalId,
				note,
				dialogueType,
				dialogueObjectId,
				fuctionListId1,
				fuctionListId2,
				fuctionListId3,
				fuctionListId4,
				fuctionListId5,
				fuctionListId6,
				fuctionListId7,
				fuctionListId8
			};

		public:
			// MG_CN_MODIFY
			///���� DialogueVassal.csv 
			Bool                        load(Str16 fileName, IMGExternalPackManager* packManager = NULL);

			///����ID���  DialogueVassalInfo
			DialogueVassalInfo*			getDialogueVassalInfo(U32 id);
			DialogueVassalInfo*			getDialogueVassalInfobyObjectId(U32 id);

		protected:
			void                            clear();

		private:
			std::map<U32, DialogueVassalInfo*> mDialogueVassalInfoMap;


		};
}
//
#endif