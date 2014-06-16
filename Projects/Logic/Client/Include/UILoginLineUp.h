//*************************************************************************************
#ifndef _UILOGINLINEUP_H_
#define _UILOGINLINEUP_H_
//*************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*************************************************************************************
namespace MG
{
	
	
	enum LineUpType
	{
		line_up_type_busy_lc_account_login = 1,				//��¼Login�Ŷ�
		line_up_type_busy_lc_server_full,					//��������������
		line_up_type_busy_fc_account_login,					//�ʺŵ�¼FrontServer�Ŷ�
		line_up_type_busy_fc_create_clan,					//���������Ŷ�
		line_up_type_busy_fc_del_clan,						//ɾ�������Ŷ�
		line_up_type_busy_fc_create_character,				//������ɫ�Ŷ�
		line_up_type_busy_fc_join_game						//������Ϸ��ͼ�Ŷ�
	};
	class UILoginLineUp : public UIObject
		{
            
		public:
			UILoginLineUp(){;}
			~UILoginLineUp(){;}
			SINGLETON_INSTANCE(UILoginLineUp);
            //
			virtual void setEvent();
			virtual Bool openGui();
			virtual void restore();
			virtual void update(Flt delta);
			
            //
			static void onClickCancle(void* widget);

			void		openAccountLoginLsUi( I32 count );
			void		openAccountLoginFsUi( I32 count );
			void		openCreateClanUi( I32 count );
			void		openDelClanUi( I32 count );
			void		openCreateCharacterUi( I32 count );
			void		openJoinMapUi( I32 count );

		private:
			void handleClickCancle();
            void setTextVisible(const Str8& name,Bool isVisible);
			Bool isTextVisible(const Str8& name);

		public:
			void adjustUI(LineUpType lineUpType);
			void setRanKed(const Str16& ranKed);
			void setFullServerName();
            
		private:
			LineUpType mLineUpType;
			
		};


}

#endif