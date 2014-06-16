//*************************************************************************************
#include "stdafx.h"
#include "TemplateSimplePro.h"
//*************************************************************************************
namespace MG
{
	//--------------------------------------------------------------------------------
    void TemplateSimplePro::setEvent()
    {
        IImage* headImage = getLayout()->getImage("Image_Head");
        assert(headImage);
        headImage->getWidget()->setMouseButtonClickEvent(onMouseClickImagehead);
        headImage->getWidget()->setMouseButtonPressedEvent(onMouseReleaseImagehead);
        headImage->getWidget()->setToolTipsEvent(onTooltipsImagehead);
    }

	//--------------------------------------------------------------------------------
    void TemplateSimplePro::onMouseReleaseImagehead( void* widget, Int x, Int y, MouseCode mouseId )
    {

    }

	//--------------------------------------------------------------------------------
    void TemplateSimplePro::onTooltipsImagehead( void* widget, Bool isShow, Int x, Int y )
    {

    }

	//--------------------------------------------------------------------------------
    void TemplateSimplePro::onMouseClickImagehead( void* widget )
    {
        IImage* pMenu = (IImage*)widget;
        if ( pMenu )
        {
            pMenu->setTexture("simpleHead.png");
            TemplateSimplePro::getInstance().setClick();
        }
    }

	//--------------------------------------------------------------------------------
    void TemplateSimplePro::setHp()
    {
        /*IProgress* pProgressHP = getLayout()->getProgress("Progress_HP");
        assert(pProgressHP);
        size_t curHp = pProgressHP->getProgressPosition();
        if ( curHp >= 10000 )
            curHp = 1000;
        else
            curHp += 1000;
        pProgressHP->setProgressPosition( curHp );*/
    }

	//--------------------------------------------------------------------------------
    void TemplateSimplePro::setMp()
    {
        //IProgress* pProgressMP = getLayout()->getProgress("Progress_MP");
        //assert(pProgressMP);
        //size_t curMp = pProgressMP->getProgressPosition();
        //if ( curMp >= 10000 )
        //    curMp = 1000;
        //else
        //    curMp += 1000;
        //pProgressMP->setProgressPosition( curMp );
    }

	//--------------------------------------------------------------------------------
    void TemplateSimplePro::setLv()
    {
        IText* pTextlv = getLayout()->getText("Text_Lv");
        assert(pTextlv);
        std::wstring Lv = pTextlv->getWidget()->getCaption();
        int curLv = _wtoi( Lv.c_str() );
        if ( curLv >= 100 )
            curLv = 10;
        else
            curLv += 1;
        wchar_t temp[10] = L"";
        Lv.clear();
        Lv = _itow(curLv, temp, 10);
        pTextlv->getWidget()->setCaption(Lv);
    }

	//--------------------------------------------------------------------------------
    void TemplateSimplePro::setName()
    {
        IText* pTextName = getLayout()->getText("Text_name");
        assert(pTextName);
        std::wstring name = pTextName->getWidget()->getCaption();
        if (name.length() < 2)
        {   
            name = L"kitty";
            pTextName->getWidget()->setCaption(name);
        }
    }

	//--------------------------------------------------------------------------------
    void TemplateSimplePro::setClick()
    {
       setHp();
       setMp();
       setLv();
       setName();
    }
}