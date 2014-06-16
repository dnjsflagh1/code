//****************************************************************************************
#ifndef _H_GUIDELEGATEELEMENTPOOL_754893_
#define _H_GUIDELEGATEELEMENTPOOL_754893_
//****************************************************************************************
#include "DEWidget.h"
#include "DEButton.h"
#include "DEForm.h"
#include "DEEdit.h"
#include "DEImage.h"
#include "DEText.h"
#include "DEProgress.h"
#include "DEViewScroll.h"
#include "DEList.h"
#include "DETab.h"
#include "DETabItem.h"
#include "DECombobox.h"
#include "DEMixTree.h"
#include "DEMixTreeNode.h"
#include "DERollingText.h"
#include "DEMixList.h"
#include "DEMixListRow.h"
#include "DEHScroll.h"
#include "DEVScroll.h"
#include "DETimeText.h"
//****************************************************************************************
class MyGUI::Widget;
//****************************************************************************************
namespace MG
{
    class GuiDgElmPool
    {
    public:
        GuiDgElmPool();
        ~GuiDgElmPool();
        
        SINGLETON_INSTANCE(GuiDgElmPool);

    public:
        DEWidget* getDEWidget(MyGUI::Widget* p);
        DEButton* getDEButton(MyGUI::Widget* p);
        DEEdit* getDEEdit(MyGUI::Widget* p);
        DEForm* getDEForm(MyGUI::Widget* p);
        DEImage* getDEImage(MyGUI::Widget* p);
        DEProgress* getDEProgress(MyGUI::Widget* p);
        DEText* getDEText(MyGUI::Widget* p);
        DEViewScroll* getDEViewScroll(MyGUI::Widget* p);
        DEList* getDEList(MyGUI::Widget* p);
        DETab* getDETab(MyGUI::Widget* p);
        DETabItem* getDETabItem(MyGUI::Widget* p);
        DEComboBox* getDEComboBox(MyGUI::Widget* p);
        DEMixTree* getDEMixTree(MyGUI::Widget* p);
        DEMixTreeNode* getDEMixTreeNode(MyGUI::Widget* p);
        DERollingText* getDERollingText(MyGUI::Widget* p);
        DEMixList* getDEMixList(MyGUI::Widget* p);
        DEMixListRow* getDEMixListRow(MyGUI::Widget* p);
		DEHScroll*	geDEHScroll(MyGUI::Widget* p);
		DEVScroll*	geDEVScroll(MyGUI::Widget* p);
		DETimeText* getDETimeText(MyGUI::Widget* p);

    protected:
        std::vector<DEWidget*> mVectorDEWidget;
        DEButton mDEButton;
        DEEdit mDEEdit;
        DEForm mDEForm;
        DEImage mDEImage;
        DEProgress mDEProgress;
        DEText mDEText;
        DEViewScroll mDEViewScroll;
        DEList mDEList;
        DETab mDETab;
        DETabItem mDETabItem;
        DEComboBox mDEComboBox;
        DEMixTree mDEMixTree;
        std::vector<DEMixTreeNode*> mVectorDEMixTreeNode;
        DERollingText mDERollingText;
        DEMixList mDEMixList;
        std::vector<DEMixListRow*> mVectorDEMixListRow;
		DEHScroll mDEHScroll;
		DEVScroll mDEVScroll;
		DETimeText mDETimeText;

        //最后一次使用节点的索引值，树节点最多10个。
        UInt    mCurTreeNodeIndex;
        UInt    mCurWidgetIndex;
        UInt    mCurMixListRowIndex;
    };
}

//****************************************************************************************
#endif
//****************************************************************************************