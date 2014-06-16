//*****************************************************************************************
#ifndef _H_IMIXTREENODE_
#define _H_IMIXTREENODE_
//*****************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
//*****************************************************************************************
namespace MG
{
    class IMixTreeNode
    {
    public:
        //获得孩子的数量
        virtual UInt            getChildNum() = 0;
        //加孩子
        virtual IMixTreeNode*   addChild(Bool isLeaf) = 0;

        //删除某一个孩子
        virtual void            removeChild(IMixTreeNode* pNode) = 0;
        virtual void            removeChild(UInt nId) = 0;
        virtual void            removeChild(UInt nId, Str16 name) = 0;
        virtual void            removeChild(Str16 name) = 0;

        //找到孩子的指针
        virtual IMixTreeNode*   FindTreeNode(UInt nId) = 0;
        virtual IMixTreeNode*	FindTreeNode(UInt nId, Str16 name) = 0;
        virtual IMixTreeNode*	FindTreeNode(Str16 name) = 0;

        //加入到行的最后，设置cell的大小，并改变行的大小。
        virtual void            addCell(ELM_TYPE type, Str16 caption, ColorI col) = 0;

        //设置或获得行的属性
        virtual void            rowID(UInt id) = 0;
        virtual UInt            rowID() = 0;
        virtual void            rowName(Str16 name) = 0;
        virtual Str16           rowName() = 0;
    };
}
//*****************************************************************************************
#endif  //_H_IMIXTREENODE_
//*****************************************************************************************