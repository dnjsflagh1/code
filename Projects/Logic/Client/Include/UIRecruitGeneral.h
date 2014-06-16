//***************************************************************************************************
#ifndef _H_UIRECRUITGENERAL_
#define _H_UIRECRUITGENERAL_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
#include "GeneralRecruitNetPacket.h"
//***************************************************************************************************
namespace MG
{
	struct RecruitGeneralInfo
	{
		U32							charTemplateId;
		U32							artIconId;			//ͷ��ID
		Str16						name;				//����
		Color						nameColor;			//������ɫ
		U32							age;				//��������
		Int							lifeSpan;			//����
		Str16						sex;				//�Ա�
		U32							str;				//����
		U32							gym;				//����
		U32							wit;				//��ı
		U32							affair;				//����

		Bool						hasRecruit;		//�Ƿ��ѱ���ļ
		Int							index;			//����ֵ ��������������

		RecruitGeneralInfo()
			:charTemplateId(0)
			,artIconId(0)
			,age(0)
			,lifeSpan(0)
			,str(0)
			,gym(0)
			,wit(0)
			,affair(0)
			,hasRecruit(false)
			,index(-1)
		{

		}

	};
	class UIRecruitGeneral  : public UIObject
	{
	public:
		UIRecruitGeneral();
		~UIRecruitGeneral();
		SINGLETON_INSTANCE(UIRecruitGeneral);

	public:
		virtual void	setEvent();
		virtual Bool    openGui();
		virtual void    update(Flt delta);
		virtual	void	restore();
		static  void    onEventUpdateBtn(void* widget);
		static  void    onEventRecruitBtn(void* widget);
	public:	
		void			clearRecruitGeneralList();
		bool			loadGeneralInfos(NetRandomGeneralInfo* data);
		void			UIFresh();

		void			UIClear();

		void			setGeneralRecruitId(U32 generalRecruitId);
		U32				getGeneralRecruitId() const;

		RecruitGeneralInfo*	getGeneralInfoByIndex(U32 index);
		std::map<Int, RecruitGeneralInfo>*		getGeneralList();

		Int				getRandPosition();
		void			resetRandPosition();
	private:
		void			test();
		static void		OnSendGeneralRecruit(void* arg);

		
	private:
		U32								mUpdateTime;				//ʣ��ˢ��ʱ��

		std::map<Int/*index*/, RecruitGeneralInfo> mRecruitGeneralList;		//�ӷ�������ȡ���з�װ

		U32				mGeneralRecruitId;							//��Ҫ�򿪵�����佫�б� id

		std::vector<Int/*index*/>		mPositionList;
		
		Int								mWantRecruitIndex;				//ѡ��Ҫ��ļ�佫��index

	};
}
//***************************************************************************************************
#endif
//***************************************************************************************************