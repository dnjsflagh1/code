//********************************************************************************************************
#include "stdafx.h"
#include "TestEffect.h"
#include "ClientMain.h"
#include "LuaSkillSystem.h"
#include "CPlayerCharacterEntity.h"
#include "CPlayer.h"
#include "GameNetPacket.h"
#include "SkillNetPacketProcesser.h"
#include "ClientNetApplyManager.h"
#include "CSceneManager.h"
#include "UIManage.h"
#include "IEffectEntity.h"
//********************************************************************************************************
namespace MG
{

    //--------------------------------------------------------------------
    TestEffect::TestEffect()
    {
        mEntity = NULL;
    }

    //--------------------------------------------------------------------
    TestEffect::~TestEffect()
    {

    }

    //--------------------------------------------------------------------
    Bool TestEffect::init()
    {
        return true;
    }

    //--------------------------------------------------------------------
    Bool TestEffect::update()
    {
		//FUNDETECTION(__MG_FUNC__);
        if(ClientMain::getInstance().getEngine()->input()->isAltOn())
        {
     //       if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_G ))
     //       {
     //           if ( mEntity == NULL )
     //           {
     //               //mEntity = CSceneManager::getInstance().getEngineScene()->createEffectEntity("Examples/Smoke");
     //               //mEntity2 = CSceneManager::getInstance().getEngineScene()->createEffectEntity("jjj_fire");

     //               //mEntity2->getSceneNode()->setPosition( Vec3(0,350,0) );

					////mEntity = CSceneManager::getInstance().getEngineScene()->createEffectEntity("jjj_fire");

					////mEntity->getSceneNode()->setPosition( Vec3(0,350,0) );
					////mEntity->getSceneNode()->setScale( Vec3(1000,1000,1000) );
     //           }
     //       }

            if ( ClientMain::getInstance().getEngine()->input()->isMousePressed(MB_Left) )
            {
                if ( mEntity )
                {            // 分配处理鼠标左健地面事件
                    Vec3 pos;
                    if ( ClientMain::getInstance().getScene()->getTerrainManager()->getMouseRayIntersection(pos) )
                        mEntity->getSceneNode()->setPosition( pos + Vec3(0,20,0));
                }
            }
        }

        return true;
    }
}