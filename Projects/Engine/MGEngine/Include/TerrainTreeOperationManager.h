/******************************************************************************/
#ifndef _TERRAINTREEOPERATIONMANAGER_H_
#define _TERRAINTREEOPERATIONMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrainTreeOperationManager.h"

/******************************************************************************/
namespace MG
{


    class TerrainTreeOperationManager : public ITerrainTreeOperationManager
    {
	public:
		enum TreeType
		{
			TREE,
			GRASS
		};
    public:
        SINGLETON_INSTANCE(TerrainTreeOperationManager)
        TerrainTreeOperationManager();
        virtual ~TerrainTreeOperationManager();

        ///����һ������
        IEditorOperation*    createOneOperation(){ return NULL; };

    public:

        //���ò������ID
        U32		getOpModel();

        //�õ��������ID
        void	setOpModel(U32 modelID);

		//����Tree����
		void	setTreeType(U32 tType);

		//��ȡTree����
		U32		getTreeType();

    protected:

        //���������ID
        U32		mOpModelID;
		//������
		U32		mTreeType;
    };


    /******************************************************************************/
    //��ϷTREE����ʵ��ӿ�
    /******************************************************************************/
    class TerrainAddTreeOperationManager : public ITerrainAddTreeOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainAddTreeOperationManager)
        TerrainAddTreeOperationManager();
        virtual ~TerrainAddTreeOperationManager();

        ///����һ������
        virtual IEditorOperation*   createOneOperation();

    public:

        //�õ��ܶ�
        Flt		getDensity();

        //�����ܶ�
        void	setDensity(Flt density);

        //���þۺ�
        Flt		getClumping();

        //�õ��ۺ�
        void	setClumping(Flt clumping);

        //���ø߶�
        Flt		getScale();

        //�õ��߶�
        void	setScale(Flt scale);

        //���ø߶ȱ仯��
        Flt		getScaleVariable();

        //�õ��߶ȱ仯��
        void	setScaleVariable(Flt variable);

		//��ȡ�Ƿ��������
		bool	getAlign();

		//�����Ƿ��������
		void	setAlign(bool align);

		//��ȡ�ݼ��
		Flt		getGrassDistance();

		//���òݼ��
		void	setGrassDistance(Flt dis);

		//��ȡ�����
		Flt		getTreeDistance();

		//���������
		void	setTreeDistance(Flt dis);

		//��ȡ��С�s�ű���
		Flt		getMinScale();

		//������С�s�ű���
		void	setMinScale(Flt scale);

		//��ȡ���s�ű���
		Flt		getMaxScale();

		//�������s�ű���
		void	setMaxScale(Flt scale);

		//��ȡλ��ƫ�ưٷֱ�
		Flt		getPositionOffset();

		//����λ��ƫ�ưٷֱ�
		void	setPositionOffset(Flt offset);

		//��ȡ�ֲ���ʽ
		U32		getDistribute();

		//���÷ֲ���ʽ
		void	setDistribute(U32 disType);

    protected:

        //�ܶ�
        Flt		mDensity;
        //�ۺ�
        Flt		mClumping;
        //��ȡ�߶ȱ仯
        Flt		mScale;
        //�߶ȱ仯��
        Flt		mScaleVariable;
		//�Ƿ��������
		Flt		mAlign;
		//λ��ƫ�ưٷֱ�
		Flt mPositionOffset;
		//�ݼ���
		Flt		mGrassDistance;
		//�����
		Flt		mTreeDistance;
		//��С���ű���
		Flt		mMinScale;
		//������ű���
		Flt		mMaxScale;
		//�ֲ���ʽ
		U32		mDistributeType;
    };


    /******************************************************************************/
    //��ϷTREE�Ƴ�ʵ��ӿ�
    /******************************************************************************/
    class TerrainRemoveTreeOperationManager : public ITerrainRemoveTreeOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainRemoveTreeOperationManager)
        TerrainRemoveTreeOperationManager();
        virtual ~TerrainRemoveTreeOperationManager();

        ///����һ������
        virtual IEditorOperation*       createOneOperation( );
    };

    /******************************************************************************/
    //��ϷTREEˢʵ��ӿ�
    /******************************************************************************/
    class TerrainDefineTreeOperationManager: public ITerrainDefineTreeOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainDefineTreeOperationManager)
        TerrainDefineTreeOperationManager();
        virtual ~TerrainDefineTreeOperationManager();

        ///����һ������
        virtual IEditorOperation*       createOneOperation( );

    public:

        virtual void	setMode( U32 mode ) { mDefineMode = mode; }

        virtual U32		getMode() { return mDefineMode; };

        virtual void	setGroupName( const Str& group ) { mDefineGroup = group; }

        virtual Str		getGroupName() { return mDefineGroup; };

        virtual void	lock(bool islock) { mLocked = islock; };

        virtual bool	isLocked() { return mLocked; }

    protected:

        //�������εķ�ʽ
        U32				mDefineMode;

        //�������ε�����
        Str				mDefineGroup;

        //������������
        bool			mLocked;
    };
}

/******************************************************************************/

#endif

