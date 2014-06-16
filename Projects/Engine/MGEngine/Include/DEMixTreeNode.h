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
        //��ú��ӵ�����
        virtual UInt            getChildNum();
        //�Ӻ���
        virtual IMixTreeNode*   addChild(Bool isLeaf);

        //ɾ��ĳһ������
        virtual void            removeChild(IMixTreeNode* pNode);
        virtual void            removeChild(UInt nId);
        virtual void            removeChild(UInt nId, Str16 name);
        virtual void            removeChild(Str16 name);

        //�ҵ����ӵ�ָ��
        virtual IMixTreeNode*   FindTreeNode(UInt nId);
        virtual IMixTreeNode*	FindTreeNode(UInt nId, Str16 name);
        virtual IMixTreeNode*	FindTreeNode(Str16 name);

        //���뵽�е��������cell�Ĵ�С�����ı��еĴ�С��
        virtual void            addCell(ELM_TYPE type, Str16 caption, ColorI col);

        //���û����е�����
        virtual void            rowID(UInt id);
        virtual UInt            rowID();
        virtual void            rowName(Str16 name);
        virtual Str16           rowName();

    public:
        Bool            setEGMixTreeNode(MyGUI::Widget* p);
        MyGUI::Widget*  getEGMixTreeNode(){return mpEGMixTreeNode;}

    private:
        //�������ָ��
        MyGUI::MixTreeNode*                                          mpEGMixTreeNode;
    };
}
//****************************************************************************************
#endif
//****************************************************************************************