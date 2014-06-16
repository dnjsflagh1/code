//****************************************************************************************
#include "stdafx.h"
#include "DEMixTree.h"
#include "GuiDelegateElementPool.h"
//****************************************************************************************
namespace MG
{
    std::map<MyGUI::MixTree*, PVOID_CALLBACK>                DEMixTree::mMapClickCallBack;

    DEMixTree::DEMixTree()
        :mpEGMixTree(NULL)
    {

    }
    //------------------------------------------------------------------------------
    DEMixTree::~DEMixTree()
    {

    }
    //------------------------------------------------------------------------------
    IWidget* DEMixTree::getWidget()
    {
        DYNAMIC_ASSERT(mpEGMixTree);

        setEGWidget(mpEGMixTree);

        return this;
    }
    //------------------------------------------------------------------------------
    IMixTreeNode* DEMixTree::getHeadMixTreeNode()
    {
        DYNAMIC_ASSERT(mpEGMixTree);

        return GuiDgElmPool::getInstance().getDEMixTreeNode( (*mpEGMixTree)() );
    }
    //------------------------------------------------------------------------------
    MG::UInt DEMixTree::getHeight()
    {
        DYNAMIC_ASSERT(mpEGMixTree);

        return mpEGMixTree->getHeight();
    }
    //------------------------------------------------------------------------------
    void DEMixTree::arrange()
    {
        DYNAMIC_ASSERT(mpEGMixTree);

        mpEGMixTree->arrange();
    }
    //------------------------------------------------------------------------------
    IMixTreeNode* DEMixTree::getSelectNode()
    {
        DYNAMIC_ASSERT(mpEGMixTree);

        MyGUI::MixTreeNode* tempNode = mpEGMixTree->getSelectNode();
        if ( tempNode )
            return GuiDgElmPool::getInstance().getDEMixTreeNode( tempNode );
        else
            return NULL;
    }
    //------------------------------------------------------------------------------
    void DEMixTree::setClickLeafNode( PVOID_CALLBACK func )
    {
        DYNAMIC_ASSERT(mpEGMixTree);

        mMapClickCallBack[mpEGMixTree] = func;
        mpEGMixTree->mEventRowClick = MyGUI::newDelegate(this, &DEMixTree::notifyMouseButtonClick);
    }
    //------------------------------------------------------------------------------
    void DEMixTree::notifyMouseButtonClick( MyGUI::MixTree* p )
    {
        DYNAMIC_ASSERT(p);

        mpEGMixTree = p->castType<MyGUI::MixTree>();

        DYNAMIC_ASSERT(mpEGMixTree);

        setEGWidget(p);
        (mMapClickCallBack[mpEGMixTree])(this);
    }
    //------------------------------------------------------------------------------
    MG::Bool DEMixTree::setEGMixTree( MyGUI::Widget* p )
    {
        DYNAMIC_ASSERT(p);

        mpEGMixTree = p->castType<MyGUI::MixTree>();

        DYNAMIC_ASSERT(mpEGMixTree);

        setEGWidget(p);

        return true;
    }

    
}