//********************************************************************************************************
#include "stdafx.h"
#include "TestManager.h"
#include "TestUI.h"
#include "TestNet.h"
#include "TestSkill.h"
#include "TestEffect.h"
#include "TestScene.h"
#include "TestAttr.h"
#include "TestRelease.h"
//********************************************************************************************************
namespace MG
{
    //--------------------------------------------------------------------
    TestManager::TestManager()
    {

    }
    //--------------------------------------------------------------------
    TestManager::~TestManager()
    {

    }
    //--------------------------------------------------------------------
    Bool TestManager::init()
    {
#ifdef _DEBUG
		//FUNDETECTION(__MG_FUNC__);
        TestUI::getInstance().init();
		TestNet::getInstance().init();
		TestSkill::getInstance().init();
		TestEffect::getInstance().init();
		TestScene::getInstance().init();
       // TestAttr::getInstance().init();
#endif
		TestRelease::getInstance().init();
        return true;
    }
    //--------------------------------------------------------------------
    Bool TestManager::update( Flt delta )
    {
#ifdef _DEBUG
		//FUNDETECTION(__MG_FUNC__);
		TestUI::getInstance().update();
		TestNet::getInstance().update( delta );
		TestSkill::getInstance().update();
		TestEffect::getInstance().update();
		TestScene::getInstance().update();
        //TestAttr::getInstance().update(delta);
#endif
		TestRelease::getInstance().update();
        return true;
    }
}