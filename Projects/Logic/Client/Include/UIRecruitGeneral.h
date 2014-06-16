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
		U32							artIconId;			//头像ID
		Str16						name;				//姓名
		Color						nameColor;			//姓名颜色
		U32							age;				//出生年龄
		Int							lifeSpan;			//寿命
		Str16						sex;				//性别
		U32							str;				//力量
		U32							gym;				//技巧
		U32							wit;				//智谋
		U32							affair;				//政务

		Bool						hasRecruit;		//是否已被招募
		Int							index;			//索引值 服务器传过来的

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
		U32								mUpdateTime;				//剩余刷新时间

		std::map<Int/*index*/, RecruitGeneralInfo> mRecruitGeneralList;		//从服务器获取进行封装

		U32				mGeneralRecruitId;							//需要打开的随机武将列表 id

		std::vector<Int/*index*/>		mPositionList;
		
		Int								mWantRecruitIndex;				//选择要招募武将的index

	};
}
//***************************************************************************************************
#endif
//***************************************************************************************************