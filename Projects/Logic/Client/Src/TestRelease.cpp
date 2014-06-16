//********************************************************************************************************
#include "stdafx.h"
#include "TestRelease.h"
#include "ClientMain.h"
#include "SLGCameraOpCtrl.h"
#include "CampaignNetPacketProcesser.h"
#include "CPlayer.h"
//********************************************************************************************************
namespace MG
{

	//--------------------------------------------------------------------
	TestRelease::TestRelease()
	{
	}

	//--------------------------------------------------------------------
	TestRelease::~TestRelease()
	{

	}

	//--------------------------------------------------------------------
	Bool TestRelease::init()
	{
		return true;
	}

	//--------------------------------------------------------------------
	Bool TestRelease::update()
	{
		IInput* Input = ClientMain::getInstance().getEngine()->input();
		if ( !Input )
			return false;

		if ( Input->isAltOn() && Input->isCtrlOn() )
        {
            // 切换摄像机控制方式
            if ( Input->isKeyPressed(KC_F2) )
            {
                SLGCameraOpCtrl::getInstance().setTrackCamera( !SLGCameraOpCtrl::getInstance().isTrackCamera() );
                return true;
            }

            // 切换摄像机控制方式
            if ( Input->isKeyPressed(KC_F10) )
            {
                SLGCameraOpCtrl::getInstance().switchViewportLock();
                return true;
            }

            // 快速结束战役
            if ( Input->isKeyPressed(KC_E) )
            {
                CampaignNetPacketProcesser::getInstance().sendCampaignEndManual(CPlayer::getInstance().getMyCampaignId());
                return true;
            }
        }
	}
}
