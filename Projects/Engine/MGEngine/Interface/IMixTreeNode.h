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
        //��ú��ӵ�����
        virtual UInt            getChildNum() = 0;
        //�Ӻ���
        virtual IMixTreeNode*   addChild(Bool isLeaf) = 0;

        //ɾ��ĳһ������
        virtual void            removeChild(IMixTreeNode* pNode) = 0;
        virtual void            removeChild(UInt nId) = 0;
        virtual void            removeChild(UInt nId, Str16 name) = 0;
        virtual void            removeChild(Str16 name) = 0;

        //�ҵ����ӵ�ָ��
        virtual IMixTreeNode*   FindTreeNode(UInt nId) = 0;
        virtual IMixTreeNode*	FindTreeNode(UInt nId, Str16 name) = 0;
        virtual IMixTreeNode*	FindTreeNode(Str16 name) = 0;

        //���뵽�е��������cell�Ĵ�С�����ı��еĴ�С��
        virtual void            addCell(ELM_TYPE type, Str16 caption, ColorI col) = 0;

        //���û����е�����
        virtual void            rowID(UInt id) = 0;
        virtual UInt            rowID() = 0;
        virtual void            rowName(Str16 name) = 0;
        virtual Str16           rowName() = 0;
    };
}
//*****************************************************************************************
#endif  //_H_IMIXTREENODE_
//*****************************************************************************************