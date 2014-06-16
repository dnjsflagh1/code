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
        //���ͷ�ڵ�
        virtual IMixTreeNode*       getHeadMixTreeNode();
        //������Ϳؼ���ĸ߶�
        virtual UInt                getHeight();
        //������ڵ㣬ɾ���ڵ�ʱ�������������Կؼ�
        virtual void                arrange();
        //��õ�ǰѡ�еĽڵ�
        virtual IMixTreeNode*       getSelectNode();

    public:
        //���õ��Ҷ�ӽڵ�Ļص�����
        virtual void                setClickLeafNode(PVOID_CALLBACK func);

    public:
        Bool                        setEGMixTree(MyGUI::Widget* p);
        MyGUI::Widget*              getEGMixTree(){return mpEGMixTree;}

    protected:
        //�����¼�
        void                        notifyMouseButtonClick(MyGUI::MixTree* p);
        
    protected:
        //��¼�������Ͷ�Ӧ�Ļص�������������Ļص���Ӧʱ���ҵ�client�Ļص�����
        static std::map<MyGUI::MixTree*, PVOID_CALLBACK>                mMapClickCallBack;

    private:
        MyGUI::MixTree*             mpEGMixTree;

    };
}
//****************************************************************************************
#endif
//****************************************************************************************