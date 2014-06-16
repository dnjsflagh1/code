/******************************************************************************/
#include "stdafx.h"
#include "CreateCampaginState.h"
#include "CClientNew.h"
/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------------
	CreateCampaginState::CreateCampaginState( CClient* ower )
		:BaseState(ower)
	{
		mClassName = "CreateCampaginState";
	}
	//--------------------------------------------------------------------------------
	CreateCampaginState::~CreateCampaginState()
	{

	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::onNetEvent( INetEvent* netEvent )
	{

	}

	//--------------------------------------------------------------------------------
	void CreateCampaginState::connectLoginServer()
	{
		
	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::connectFrontServer()
	{

	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::accountLoginLoginServer()
	{

	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::accountLoginFrontServer()
	{

	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::accountLogin()
	{

	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::joinGame()
	{

	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::autoJoinGame()
	{

	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::createClan()
	{

	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::createCharacter()
	{

	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::closeNet()
	{
		addMessage(out_info,"state：【CreateCampaginState】  op：closeNet desc：关闭网络中");
		//mOwer->setState(mOwer->getCloseState());
		//mOwer->stateNetClose();
	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::randMove()
	{

	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::createTroop()
	{

	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::sendDataToLoginServer(U32 size)
	{

	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::sendDataToFrontServer(U32 size)
	{
		if (hasParentState())
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【CreateCampaginState】  op：testSendDataToFrontServer desc：调用出错");
		}
		else
		{
			mOwer->stateTestSendDataToFrontServer(size);
			addMessage(out_info,"state：【CreateCampaginState】  op：testSendDataToLoginServer desc:  desc：发送数据到Front");
		}
	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::testSkill()
	{

	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::createCampagin()
	{

	}
	//--------------------------------------------------------------------------------
	void CreateCampaginState::jumpMap()
	{

	}
	//--------------------------------------------------------------------------------
	std::string& CreateCampaginState::getClassName()
	{
		return mClassName;
	}

};
/******************************************************************************/
