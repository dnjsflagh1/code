//********************************************************************************************************
#include "stdafx.h"
#include "TestNet.h"
#include "ClientMain.h"
#include "ClientNetApplyManager.h"
#include "TestNetPacketProcesser.h"
#include "CPlayer.h"
//********************************************************************************************************
namespace MG
{

	//--------------------------------------------------------------------
	TestNet::TestNet()
		:mIsAutoSend(false)
        ,mLastTime(0)
	{

	}
	//--------------------------------------------------------------------
	TestNet::~TestNet()
	{

	}
	//--------------------------------------------------------------------
	Bool TestNet::init()
	{
		return true;
	}
	//--------------------------------------------------------------------
	Bool TestNet::update( Flt delta )
	{
		IInput* input = ClientMain::getInstance().getEngine()->input();

		if ( input->isKeyPressed(KC_LMENU) && input->isShiftOn() )
		{
			mIsAutoSend = true;
		}
		
		if ( input->isKeyPressed(KC_RMENU) && input->isShiftOn() )
		{
			mIsAutoSend = false;
		}

        //手动发送
        if ( input->isKeyPressed(KC_S) && input->isShiftOn() )
        {
            timeSend();
        }

        //自动发送
		if ( mIsAutoSend )
		{
            mLastTime += delta;
            if ( mLastTime > 1 )
            {
                mLastTime = 0;

                for (UInt i=0; i<100; i++)
                {
                    timeSend();
                }
            }
		}

		return true;
	}

    //--------------------------------------------------------------------
    void TestNet::timeSend()
    {
        //send1();
        sendBaseTest();
    }

    //--------------------------------------------------------------------
    void TestNet::send1()
    {
        ////Str buff = "我是谁";
        //char buff[128] = {1,2,3,4};
        //ClientNetApplyManager::getInstance().sendLoginServerPacket(12,12,buff,sizeof(buff));
    }

    //--------------------------------------------------------------------
    void TestNet::sendBaseTest()
    {
        U64 accountID = CPlayer::getInstance().getAccountID();

        CPlayerCharacter* character = CPlayer::getInstance().getActiveClan()->getMainGenreal();
        if ( character )
        {
            U64 characterID = character->getID();
            TestNetPacketProcesser::getInstance().sendCFMBaseTestToFrontServer(accountID,characterID,1000);
            //TestNetPacketProcesser::getInstance().sendCFBaseTestToFrontServer(accountID,characterID);
        }
    }
    
}