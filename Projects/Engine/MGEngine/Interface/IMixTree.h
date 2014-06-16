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
        //���ͷ�ڵ�
        virtual IMixTreeNode*       getHeadMixTreeNode() = 0;
        //������Ϳؼ���ĸ߶�
        virtual UInt                getHeight() = 0;
        //������ڵ㣬ɾ���ڵ�ʱ�������������Կؼ�
        virtual void                arrange() = 0;
        //��õ�ǰѡ�еĽڵ�
        virtual IMixTreeNode*       getSelectNode() = 0;

    public:
        //���õ��Ҷ�ӽڵ�Ļص�����
        virtual void                setClickLeafNode(PVOID_CALLBACK) = 0;
        
    };
}
//*****************************************************************************************
#endif  //_H_IMIXTREE_
//*****************************************************************************************