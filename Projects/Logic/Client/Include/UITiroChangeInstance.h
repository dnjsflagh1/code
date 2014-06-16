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
	struct UIInstanceInfo	//��ʾ��UI��Ϣ
	{
		NetIdType			mapServerNetId;
		InstanceUIdType		instanceUId;
		RegionIdType		regionId;
		REGION_OBJ_TYPE		regionType;
		Int					curPlayerNum;		//��ǰ����
		Int					maxPlayerNum;		//�������
		std::wstring		instanceName;		//��������
		Bool				instanceCurrent;	//��ҵ�ǰ���ڷ�����
		std::wstring		instanceState;		//������״̬

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
		static void onClickTiroInstance(void* widget, Int index);		//ѡ��һ������
		static void onClickButtonConfirm(void* widget);		//ȷ�ϣ� ���ͻ�����������
		static void onClickButtonCancel(void* widget);		//ȡ��

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

		UIInstanceInfo*			mCurInstanceInfo;		//��ǰѡ�е���Ϣ
		InstanceListCsvInfo*	mTiroInstanceCsvInfo;

		RegionIdType			mTiroRegionId;
		std::wstring			mTiroRegionString;
	};
}

#endif	//_UI_TIRO_CHANGE_INSTANCE_H_