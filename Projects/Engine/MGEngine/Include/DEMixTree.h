//****************************************************************************************
#ifndef _H_DEMIXTREE_
#define _H_DEMIXTREE_
//****************************************************************************************
#include "DEWidget.h"
#include "IMixTree.h"
//****************************************************************************************
namespace MG
{
    class DEMixTree : public IMixTree, public DEWidget
    {
    public:
        DEMixTree();
        virtual ~DEMixTree();

    public:
        virtual IWidget*            getWidget();
        //获得头节点
        virtual IMixTreeNode*       getHeadMixTreeNode();
        //获得竖型控件间的高度
        virtual UInt                getHeight();
        //当加入节点，删除节点时，重新排列属性控件
        virtual void                arrange();
        //获得当前选中的节点
        virtual IMixTreeNode*       getSelectNode();

    public:
        //设置点击叶子节点的回调函数
        virtual void                setClickLeafNode(PVOID_CALLBACK func);

    public:
        Bool                        setEGMixTree(MyGUI::Widget* p);
        MyGUI::Widget*              getEGMixTree(){return mpEGMixTree;}

    protected:
        //引擎事件
        void                        notifyMouseButtonClick(MyGUI::MixTree* p);
        
    protected:
        //记录引擎对象和对应的回调函数，当引擎的回调响应时可找到client的回调函数
        static std::map<MyGUI::MixTree*, PVOID_CALLBACK>                mMapClickCallBack;

    private:
        MyGUI::MixTree*             mpEGMixTree;

    };
}
//****************************************************************************************
#endif
//****************************************************************************************