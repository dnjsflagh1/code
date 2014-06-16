//****************************************************************************************
#ifndef _H_DEMIXTREENODE_
#define _H_DEMIXTREENODE_
//****************************************************************************************
#include "IMixTree.h"
#include "DEWidget.h"
//****************************************************************************************
namespace MG
{
    class DEMixTreeNode : public IMixTreeNode, public DEWidget
    {
    public:
        DEMixTreeNode();
        ~DEMixTreeNode();

    public:
        //获得孩子的数量
        virtual UInt            getChildNum();
        //加孩子
        virtual IMixTreeNode*   addChild(Bool isLeaf);

        //删除某一个孩子
        virtual void            removeChild(IMixTreeNode* pNode);
        virtual void            removeChild(UInt nId);
        virtual void            removeChild(UInt nId, Str16 name);
        virtual void            removeChild(Str16 name);

        //找到孩子的指针
        virtual IMixTreeNode*   FindTreeNode(UInt nId);
        virtual IMixTreeNode*	FindTreeNode(UInt nId, Str16 name);
        virtual IMixTreeNode*	FindTreeNode(Str16 name);

        //加入到行的最后，设置cell的大小，并改变行的大小。
        virtual void            addCell(ELM_TYPE type, Str16 caption, ColorI col);

        //设置或获得行的属性
        virtual void            rowID(UInt id);
        virtual UInt            rowID();
        virtual void            rowName(Str16 name);
        virtual Str16           rowName();

    public:
        Bool            setEGMixTreeNode(MyGUI::Widget* p);
        MyGUI::Widget*  getEGMixTreeNode(){return mpEGMixTreeNode;}

    private:
        //引擎对象指针
        MyGUI::MixTreeNode*                                          mpEGMixTreeNode;
    };
}
//****************************************************************************************
#endif
//****************************************************************************************