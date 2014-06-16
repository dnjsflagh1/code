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
            // �л���������Ʒ�ʽ
            if ( Input->isKeyPressed(KC_F2) )
            {
                SLGCameraOpCtrl::getInstance().setTrackCamera( !SLGCameraOpCtrl::getInstance().isTrackCamera() );
                return true;
            }

            // �л���������Ʒ�ʽ
            if ( Input->isKeyPressed(KC_F10) )
            {
                SLGCameraOpCtrl::getInstance().switchViewportLock();
                return true;
            }

            // ���ٽ���ս��
            if ( Input->isKeyPressed(KC_E) )
            {
                CampaignNetPacketProcesser::getInstance().sendCampaignEndManual(CPlayer::getInstance().getMyCampaignId());
                return true;
            }
        }
	}
}
