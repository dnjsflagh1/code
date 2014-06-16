//*****************************************************************************************
#ifndef _H_IMIXTREE_
#define _H_IMIXTREE_
//*****************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
#include "IMixTreeNode.h"
//*****************************************************************************************
namespace MG
{
    class IMixTree
    {
    public:
        virtual IWidget*            getWidget() = 0;
        //获得头节点
        virtual IMixTreeNode*       getHeadMixTreeNode() = 0;
        //获得竖型控件间的高度
        virtual UInt                getHeight() = 0;
        //当加入节点，删除节点时，重新排列属性控件
        virtual void                arrange() = 0;
        //获得当前选中的节点
        virtual IMixTreeNode*       getSelectNode() = 0;

    public:
        //设置点击叶子节点的回调函数
        virtual void                setClickLeafNode(PVOID_CALLBACK) = 0;
        
    };
}
//*****************************************************************************************
#endif  //_H_IMIXTREE_
//*****************************************************************************************