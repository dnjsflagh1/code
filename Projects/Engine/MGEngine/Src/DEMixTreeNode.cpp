//****************************************************************************************
#include "stdafx.h"
#include "DEMixTreeNode.h"
#include "GuiDelegateElementPool.h"
//****************************************************************************************
namespace MG
{
    DEMixTreeNode::DEMixTreeNode()
        :mpEGMixTreeNode(NULL)
    {

    }
    //------------------------------------------------------------------------------
    DEMixTreeNode::~DEMixTreeNode()
    {

    }
    //------------------------------------------------------------------------------
    MG::Bool DEMixTreeNode::setEGMixTreeNode( MyGUI::Widget* p )
    {
        DYNAMIC_ASSERT(p);

        mpEGMixTreeNode = p->castType<MyGUI::MixTreeNode>();

        DYNAMIC_ASSERT(mpEGMixTreeNode);

        setEGWidget(p);

        return true;
    }
    //------------------------------------------------------------------------------
    MG::UInt DEMixTreeNode::getChildNum()
    {
        DYNAMIC_ASSERT(mpEGMixTreeNode);

        return mpEGMixTreeNode->getChildNum();
    }
    //------------------------------------------------------------------------------
    IMixTreeNode* DEMixTreeNode::addChild(Bool isLeaf)
    {
        DYNAMIC_ASSERT(mpEGMixTreeNode);

        return GuiDgElmPool::getInstance().getDEMixTreeNode( mpEGMixTreeNode->addChild(isLeaf) );
    }
    //------------------------------------------------------------------------------
    void DEMixTreeNode::removeChild( IMixTreeNode* pNode )
    {
        DYNAMIC_ASSERT(mpEGMixTreeNode);

        mpEGMixTreeNode->removeChild(pNode->rowID(), pNode->rowName());
    }
    //------------------------------------------------------------------------------
    void DEMixTreeNode::removeChild( UInt nId )
    {
       DYNAMIC_ASSERT(mpEGMixTreeNode);

       mpEGMixTreeNode->removeChild(nId);
    }
    //------------------------------------------------------------------------------
    void DEMixTreeNode::removeChild( UInt nId, Str16 name )
    {
        DYNAMIC_ASSERT(mpEGMixTreeNode);

        mpEGMixTreeNode->removeChild(nId, name);
    }
    //------------------------------------------------------------------------------
    void DEMixTreeNode::removeChild( Str16 name )
    {
        DYNAMIC_ASSERT(mpEGMixTreeNode);

        mpEGMixTreeNode->removeChild(name);
    }
    //------------------------------------------------------------------------------
    IMixTreeNode* DEMixTreeNode::FindTreeNode( UInt nId )
    {
        DYNAMIC_ASSERT(mpEGMixTreeNode);

        return GuiDgElmPool::getInstance().getDEMixTreeNode( mpEGMixTreeNode->FindTreeNode(nId) );
    }
    //------------------------------------------------------------------------------
    IMixTreeNode* DEMixTreeNode::FindTreeNode( UInt nId, Str16 name )
    {
        DYNAMIC_ASSERT(mpEGMixTreeNode);

        return GuiDgElmPool::getInstance().getDEMixTreeNode( mpEGMixTreeNode->FindTreeNode(nId, name) );
    }
    //------------------------------------------------------------------------------
    IMixTreeNode* DEMixTreeNode::FindTreeNode( Str16 name )
    {
        DYNAMIC_ASSERT(mpEGMixTreeNode);

        return GuiDgElmPool::getInstance().getDEMixTreeNode( mpEGMixTreeNode->FindTreeNode(name) );
    }
    //------------------------------------------------------------------------------
    void DEMixTreeNode::addCell( ELM_TYPE type, Str16 caption, ColorI col )
    {
        DYNAMIC_ASSERT(mpEGMixTreeNode);

        mpEGMixTreeNode->addCell((MyGUI::ELM_TYPE)(int)type, caption, MyGUI::Colour(col.r, col.g, col.b, col.a));
    }
    //------------------------------------------------------------------------------
    void DEMixTreeNode::rowID( UInt id )
    {
        DYNAMIC_ASSERT(mpEGMixTreeNode);

        mpEGMixTreeNode->rowID(id);
    }
    //------------------------------------------------------------------------------
    MG::UInt DEMixTreeNode::rowID()
    {
        DYNAMIC_ASSERT(mpEGMixTreeNode);

        return mpEGMixTreeNode->rowID();
    }
    //------------------------------------------------------------------------------
    void DEMixTreeNode::rowName( Str16 name )
    {
        DYNAMIC_ASSERT(mpEGMixTreeNode);

        mpEGMixTreeNode->rowName(name);
    }
    //------------------------------------------------------------------------------
    MG::Str16 DEMixTreeNode::rowName()
    {
        DYNAMIC_ASSERT(mpEGMixTreeNode);

        return mpEGMixTreeNode->rowName();
    }
}