//******************************************************************************************
#ifndef _DIALOGUEVASSAL_H_
#define _DIALOGUEVASSAL_H_
//******************************************************************************************
#include "GameFilePreqs.h"
namespace MG
{

		#define NPC_DIALOG_FUNCTION_ID_COUNT 8
		
		
		///对应策划文档DialogueVassal一条记录
		struct DialogueVassalInfo
		{
			U32					id;				//id
			U32					diaType;		//对话目标类型
			U32                 diaObjectId;    //对话目标ID
			U32					fuctionId[NPC_DIALOG_FUNCTION_ID_COUNT];          //功能数组

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
			///加载 DialogueVassal.csv 
			Bool                        load(Str16 fileName, IMGExternalPackManager* packManager = NULL);

			///根据ID获得  DialogueVassalInfo
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