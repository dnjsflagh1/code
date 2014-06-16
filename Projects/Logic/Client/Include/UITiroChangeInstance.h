//*************************************************************************************

#ifndef _UI_TIRO_CHANGE_INSTANCE_H_
#define _UI_TIRO_CHANGE_INSTANCE_H_

//*************************************************************************************

#include "ClientPreqs.h"
#include "UIObject.h"

//*************************************************************************************

namespace MG
{
	//-------------------------------------------------------------------------------
	struct UIInstanceInfo	//显示的UI信息
	{
		NetIdType			mapServerNetId;
		InstanceUIdType		instanceUId;
		RegionIdType		regionId;
		REGION_OBJ_TYPE		regionType;
		Int					curPlayerNum;		//当前人数
		Int					maxPlayerNum;		//最大人数
		std::wstring		instanceName;		//副本名字
		Bool				instanceCurrent;	//玩家当前所在服务器
		std::wstring		instanceState;		//服务器状态

		UIInstanceInfo()
			:mapServerNetId(0)
			,instanceUId(0)
			,regionId(0)
			,regionType(ROT_UNKNOWN)
			,curPlayerNum(0)
			,maxPlayerNum(0)
			,instanceCurrent(false)
		{

		}
	};

	//-------------------------------------------------------------------------------
	class  UITiroChangeInstance : public UIObject
	{
	public:
		UITiroChangeInstance();
		virtual ~UITiroChangeInstance();
		SINGLETON_INSTANCE(UITiroChangeInstance);

	public:
		virtual void setEvent();
		virtual Bool openGui();

	public:
		static void onClickTiroInstance(void* widget, Int index);		//选中一个副本
		static void onClickButtonConfirm(void* widget);		//确认， 发送换副本的请求
		static void onClickButtonCancel(void* widget);		//取消

	public:
		void		sendJumpTiroInstance(const UIInstanceInfo* instanceInfo);
		void		sendTiroList();


	public:
		void		addInstanceInfo(NetIdType mapServerNetId, UIInstanceInfo* info);
		void		clearInstanceInfo(NetIdType mapServerNetId);
		void		UIReFresh();

		void				setCurTiroInstanceInfo(UIInstanceInfo* instanceInfo);
		UIInstanceInfo*		getCurTiroInstanceInfo() const;
		
		InstanceListCsvInfo*	getTiroInstanceCsvInfo();

		std::wstring&		getTiroRegionName(RegionIdType tiroId);
	private:
		void testCreateTiro();			//for test
	private:
		std::map<NetIdType, std::vector<UIInstanceInfo>* >	mInstanceList;

		UIInstanceInfo*			mCurInstanceInfo;		//当前选中的信息
		InstanceListCsvInfo*	mTiroInstanceCsvInfo;

		RegionIdType			mTiroRegionId;
		std::wstring			mTiroRegionString;
	};
}

#endif	//_UI_TIRO_CHANGE_INSTANCE_H_