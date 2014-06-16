//****************************************************************************************
#include "stdafx.h"
#include "GuiDelegateElementPool.h"
//****************************************************************************************
#define WIDGET_NUM_MAX 10
//****************************************************************************************
namespace MG
{
    
    GuiDgElmPool::GuiDgElmPool()
        :mCurTreeNodeIndex(0)
        ,mCurWidgetIndex(0)
    {

    }
    //----------------------------------------------------------------------------------
    GuiDgElmPool::~GuiDgElmPool()
    {
        {
            std::vector<DEMixTreeNode*>::iterator front = mVectorDEMixTreeNode.begin();
            std::vector<DEMixTreeNode*>::iterator back = mVectorDEMixTreeNode.end();
            while (front != back)
            {
                delete *front;

                ++front;
            }
            mVectorDEMixTreeNode.clear();
        }
        //----------------------------------------------------------------------------
        {
            std::vector<DEWidget*>::iterator front = mVectorDEWidget.begin();
            std::vector<DEWidget*>::iterator back = mVectorDEWidget.end();
            while (front != back)
            {
                delete *front;

                ++front;
            }
            mVectorDEWidget.clear();
        }
        //----------------------------------------------------------------------------
        {
            std::vector<DEMixListRow*>::iterator front = mVectorDEMixListRow.begin();
            std::vector<DEMixListRow*>::iterator back = mVectorDEMixListRow.end();
            while (front != back)
            {
                delete *front;

                ++front;
            }
            mVectorDEMixListRow.clear();
        }
    }
    //----------------------------------------------------------------------------------
    DEWidget* GuiDgElmPool::getDEWidget( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;

        DEWidget* tempWidget = NULL;
        if ( mVectorDEWidget.size() < WIDGET_NUM_MAX )
        {
            tempWidget = new DEWidget;
            mVectorDEWidget.push_back(tempWidget); 
        }
        else
        {
            if (mCurWidgetIndex >= WIDGET_NUM_MAX)
            {
                mCurWidgetIndex = 0;
            }
            tempWidget = mVectorDEWidget[mCurWidgetIndex];
        }

        tempWidget->setEGWidget(p);
        ++mCurWidgetIndex;

        return tempWidget;
    }
    //----------------------------------------------------------------------------------
    DEButton* GuiDgElmPool::getDEButton( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;
        mDEButton.setEGButton(p);
        return &mDEButton;
    }
    //----------------------------------------------------------------------------------
    DEEdit* GuiDgElmPool::getDEEdit( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;
        mDEEdit.setEGEdit(p);
        return &mDEEdit;
    }
    //----------------------------------------------------------------------------------
    DEForm* GuiDgElmPool::getDEForm( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;

        mDEForm.setEGForm(p);
        return &mDEForm;
    }
    //----------------------------------------------------------------------------------
    DEImage* GuiDgElmPool::getDEImage( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;

        mDEImage.setEGImage(p);
        return &mDEImage;
    }
    //----------------------------------------------------------------------------------
    DEProgress* GuiDgElmPool::getDEProgress( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;

        mDEProgress.setEGProgress(p);
        return &mDEProgress;
    }
    //----------------------------------------------------------------------------------
    DEText* GuiDgElmPool::getDEText( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;

        mDEText.setEGText(p);
        return &mDEText;
    }
    //----------------------------------------------------------------------------------
    DEViewScroll* GuiDgElmPool::getDEViewScroll( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;

        mDEViewScroll.setEGViewScroll(p);
        return &mDEViewScroll;
    }
    //----------------------------------------------------------------------------------
    DEList* GuiDgElmPool::getDEList( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;

        mDEList.setEGList(p);
        return &mDEList;
    }
    //----------------------------------------------------------------------------------
    DETab* GuiDgElmPool::getDETab( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;

        mDETab.setEGTab(p);
        return &mDETab;
    }
    //----------------------------------------------------------------------------------
    DETabItem* GuiDgElmPool::getDETabItem( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;

        mDETabItem.setEGTabItem(p);
        return &mDETabItem;
    }
    //----------------------------------------------------------------------------------
    DEComboBox* GuiDgElmPool::getDEComboBox( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;

        mDEComboBox.setEGComboBox(p);
        return &mDEComboBox;
    }
    //----------------------------------------------------------------------------------
    DEMixTree* GuiDgElmPool::getDEMixTree( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;

        mDEMixTree.setEGMixTree(p);

        return &mDEMixTree;
    }
    //----------------------------------------------------------------------------------
    DEMixTreeNode* GuiDgElmPool::getDEMixTreeNode( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;
        
        DEMixTreeNode* tempNode = NULL;
        if ( mVectorDEMixTreeNode.size() < WIDGET_NUM_MAX )
        {
            tempNode = new DEMixTreeNode;
            mVectorDEMixTreeNode.push_back(tempNode); 
        }
        else
        {
            if (mCurTreeNodeIndex >= WIDGET_NUM_MAX)
            {
                mCurTreeNodeIndex = 0;
            }
            tempNode = mVectorDEMixTreeNode[mCurTreeNodeIndex];
        }

        tempNode->setEGMixTreeNode(p);
        ++mCurTreeNodeIndex;

        return tempNode;
    }
    //----------------------------------------------------------------------------------
    DERollingText* GuiDgElmPool::getDERollingText( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;

        mDERollingText.setEGRollingText(p);

        return &mDERollingText;
    }
    //----------------------------------------------------------------------------------
    DEMixList* GuiDgElmPool::getDEMixList( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;

        mDEMixList.setEGMixList(p);

        return &mDEMixList;
    }
    //----------------------------------------------------------------------------------
    DEMixListRow* GuiDgElmPool::getDEMixListRow( MyGUI::Widget* p )
    {
        if ( p == NULL )
            return NULL;

        DEMixListRow* tempNode = NULL;
        if ( mVectorDEMixListRow.size() < WIDGET_NUM_MAX )
        {
            tempNode = new DEMixListRow;
            mVectorDEMixListRow.push_back(tempNode); 
        }
        else
        {
            if (mCurMixListRowIndex >= WIDGET_NUM_MAX)
            {
                mCurMixListRowIndex = 0;
            }
            tempNode = mVectorDEMixListRow[mCurMixListRowIndex];
        }

        tempNode->setEGMixListRow(p);
        ++mCurMixListRowIndex;

        return tempNode;
    }
	//----------------------------------------------------------------------------------
	DEHScroll* GuiDgElmPool::geDEHScroll( MyGUI::Widget* p )
	{
		if ( p == NULL )
			return NULL;

		mDEHScroll.setEGHScroll(p);

		return &mDEHScroll;
	}
	//----------------------------------------------------------------------------------
	DEVScroll* GuiDgElmPool::geDEVScroll( MyGUI::Widget* p )
	{
		if ( p == NULL )
			return NULL;

		mDEVScroll.setEGVScroll(p);

		return &mDEVScroll;
	}
	//----------------------------------------------------------------------------------
	DETimeText* GuiDgElmPool::getDETimeText( MyGUI::Widget* p )
	{
		if ( p == NULL )
			return NULL;

		mDETimeText.setEGTimeText(p);

		return &mDETimeText;
	}
}
