//***************************************************************************************************
#ifndef _UI_CHANGE_RECRUIT_H_
#define _UI_CHANGE_RECRUIT_H_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
#include "GeneralRecruitNetPacket.h"
//***************************************************************************************************
namespace MG
{

	class UIChangeRecruit  : public UIObject
	{
	public:
		UIChangeRecruit();
		~UIChangeRecruit();
		SINGLETON_INSTANCE(UIChangeRecruit);

	public:
		virtual void	setEvent();
		virtual Bool    openGui();
		virtual	void	restore();

	public:
		static void onEventConfirmBtn(void* widget);
		static void onClickGeneralInfo(void* widget, Int index);

	public:
		void UIFresh();

	public:	//��ļ���佫
		void								clearRecruitGeneralList();
		void								loadRecruitGeneralInfo(NetRecuitGeneralInfo* generalInfo);
		std::map<U64, CPlayerCharacter*>*	getRecruitGeneralList();
	
		void		setSelectGeneralId(U64 generalId);
		U64			getSelectGeneralId() const;

	private:
		//����ļ���佫�б�
		std::map<U64, CPlayerCharacter*>	mRecruitGeneralList;


		U64									mSelectGeneralId;
	};
}

//***************************************************************************************************
#endif	//_UI_CHANGE_RECRUIT_H_
//***************************************************************************************************