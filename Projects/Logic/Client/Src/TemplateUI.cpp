//***************************************************************************************
#include "stdafx.h"
#include "TemplateUI.h"
#include "ClientMain.h"
//***************************************************************************************
namespace MG
{

	//--------------------------------------------------------------------------------
    TemplateUI::TemplateUI()
        :mIndex(0)
    {

    }

    //----------------------------------------------------------------------------
    TemplateUI::~TemplateUI()
    {

    }

    //----------------------------------------------------------------------------
    void TemplateUI::setEvent()
    {
         IButton* tempbtn1 = getLayout()->getButton("Button1");
         tempbtn1->getWidget()->setMouseButtonClickEvent( onClickButton1 );

    }

	//--------------------------------------------------------------------------------
    void TemplateUI::onClickButton1( void* widget )
    {
        DYNAMIC_ASSERT(widget) ;

        TemplateUI::getInstance().addCDEvent();
    }

	//--------------------------------------------------------------------------------
    void TemplateUI::onClickButton2( void* widget )
    {
        DYNAMIC_ASSERT(widget) ;

        TemplateUI::getInstance().addNode();
    }

	//--------------------------------------------------------------------------------
    void TemplateUI::onClickWindowClose( void* widget )
    {
       IForm* pMenu = (IForm*)widget;
       if (pMenu)
       {
           pMenu->getWidget()->setVisible(false);
       }
    }

	//--------------------------------------------------------------------------------
    void TemplateUI::onSelectAcceptEvent( void* widget )
    {
       IEdit* pMenu = (IEdit*)widget;
       if (pMenu)
       {
           std::wstring content = pMenu->getWidget()->getCaption();
           if ( content == L"" )
               return;
           pMenu->setCaption(L"");
           TemplateUI::getInstance().insertText(content);
       }
    }

	//--------------------------------------------------------------------------------
    void TemplateUI::onPressText( void* widget, int x, int y, MouseCode id )
    {
       IText* pMenu = (IText*)widget;
       if (pMenu)
       {
           pMenu->getWidget()->setCaption(L"hudie");
       }
    }

	//--------------------------------------------------------------------------------
    void TemplateUI::onReleaseImage( void* widget, int x, int y, MouseCode id )
    {
       IImage* pMenu = (IImage*)widget;
       if (pMenu)
       {
           pMenu->setTexture("Crystal_Clear_Butterfly.png");
       }
    }

	//--------------------------------------------------------------------------------
    void TemplateUI::insertText( std::wstring text )
    {
       IEdit* tempedit2 = getLayout()->getEdit("Edit2");
       if (tempedit2)
       {
           tempedit2->addText(text+L"\n");
       }
    }
    //--------------------------------------------------------------------------------
    void TemplateUI::onClickButton3( void* widget )
    {
        DYNAMIC_ASSERT(widget);

        TemplateUI::getInstance().addLeaf();
    }
    //--------------------------------------------------------------------------------
    void TemplateUI::onClickButton4( void* widget )
    {
        DYNAMIC_ASSERT(widget);

        TemplateUI::getInstance().deleteLeaf();
    }
    //--------------------------------------------------------------------------------
    void TemplateUI::onClickTreeNode( void* widget )
    {
        DYNAMIC_ASSERT(widget);

        TemplateUI::getInstance().showNodeInfo();
    }
    //--------------------------------------------------------------------------------
    void TemplateUI::addNode()
    {
        IMixTree* mixtree = getLayout()->getMixTree("mixtree");
        IMixTreeNode* head = mixtree->getHeadMixTreeNode();
        IMixTreeNode* node = head->addChild(false);

        Char16 name[32] = L"";
        swprintf_s(name, 32, L"节点%d", mIndex);

        node->addCell(ET_IMAGE, L"", ColorI(0, 0, 0, 0));
        node->addCell(ET_TEXT, name, ColorI(0, 0, 0, 0));
        node->rowID(mIndex++);
        node->rowName(name);

        IMixTreeNode* leaf = node->addChild(true);

        swprintf_s(name, 32, L"叶子%d", mIndex);

        leaf->addCell(ET_TEXT, name, ColorI(0, 0, 0, 0));
        leaf->rowID(mIndex++);
        leaf->rowName(name);


        mixtree->arrange();
    }
    //--------------------------------------------------------------------------------
    void TemplateUI::deleteNode()
    {
        IMixTree* mixtree = getLayout()->getMixTree("mixtree");
        IMixTreeNode* head = mixtree->getHeadMixTreeNode();
        IMixTreeNode* node = mixtree->getSelectNode();

        if ( node == NULL )
            return;

        head->removeChild(node);

        mixtree->arrange();
    }
    //--------------------------------------------------------------------------------
    void TemplateUI::addLeaf()
    {
        IMixTree* mixtree = getLayout()->getMixTree("mixtree");
        IMixTreeNode* node = mixtree->getSelectNode();

        if ( node == NULL )
            return;

        IMixTreeNode* leaf = node->addChild(true);

        Char16 name[32] = L"";
        swprintf_s(name, 32, L"叶子%d", mIndex);

        leaf->addCell(ET_TEXT, name, ColorI(0, 0, 0, 0));
        leaf->rowID(mIndex++);
        leaf->rowName(name);

        mixtree->arrange();
    }
    //--------------------------------------------------------------------------------
    void TemplateUI::deleteLeaf()
    {
        IMixTree* mixtree = getLayout()->getMixTree("mixtree");
        IMixTreeNode* head = mixtree->getHeadMixTreeNode();
        IMixTreeNode* node = mixtree->getSelectNode();

        if ( node == NULL )
            return;

        head->removeChild(node);

        mixtree->arrange();
    }
    //--------------------------------------------------------------------------------
    void TemplateUI::showNodeInfo()
    {
        IMixTree* mixtree = getLayout()->getMixTree("mixtree");
        IMixTreeNode* node = mixtree->getSelectNode();

        if ( node == NULL )
            return;

        IText* tempText = getLayout()->getText("Text1");
        tempText->getWidget()->setCaption( node->rowName() );
    }
    //--------------------------------------------------------------------------------
    void TemplateUI::onClickMixlist( void* widget, int index )
    {
        TemplateUI::getInstance().showNodeInfo();
    }
    //--------------------------------------------------------------------------------
    void TemplateUI::update()
    {
        /*if ( ClientMain::getInstance().getEngine()->input()->isKeyReleased(KeyCode::KC_TAB) )
        {
            IWidget* pEdit1 = getLayout()->getWidget("Edit1");
            IWidget* pEdit3 = getLayout()->getWidget("Edit3");
            if ( pEdit1->isKeyFocus() )
            {
                pEdit3->setKeyFocus(true);
            }
            else 
            {
                pEdit1->setKeyFocus(true);
            }
        }
		*/
    }
    //--------------------------------------------------------------------------------
    void TemplateUI::onClickMixListCheckBox( void* widget )
    {
        IWidget* pWidget = (IWidget*)widget;
        if ( pWidget->getButton()->getStateCheck() )
            pWidget->getButton()->setStateCheck(false);
        else
            pWidget->getButton()->setStateCheck(true);
    }
	//--------------------------------------------------------------------------------
	void TemplateUI::onCDEvent( void* widget, int timeouttime )
	{
		TemplateUI::getInstance().setCDEvent(timeouttime);
	}
	//--------------------------------------------------------------------------------
	void TemplateUI::setCDEvent( int timeouttime )
	{
		ITimeText* pITimeText = getLayout()->getTimeText("11test");
		pITimeText->getWidget()->setVisible(false);

		IText* pText = getLayout()->getText("cdevent");
		pText->getWidget()->setCaption(L"12345");

		openImageCD(timeouttime);
		
	}
	//--------------------------------------------------------------------------------
	void TemplateUI::addCDEvent()
	{
		ITimeText* pITimeText = getLayout()->getTimeText("11test");
		pITimeText->setCoolDownTime(30*1000);
		pITimeText->setEventTimeOut(onCDEvent, 10*1000, 0);
	}
	//--------------------------------------------------------------------------------
	void TemplateUI::openImageCD( int timeouttime )
	{
		IImage* pImage = getLayout()->getImage("imagetTest");
		pImage->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_ONCE, timeouttime, timeouttime);
		pImage->setFrameChangeEvent(onImageCDEvent);
	}
	//--------------------------------------------------------------------------------
	void TemplateUI::onImageCDEvent( void* widget, int lastFrame )
	{	
		int a =0;
		int b=0;
		int c;
		c = a+b;
	}
}
