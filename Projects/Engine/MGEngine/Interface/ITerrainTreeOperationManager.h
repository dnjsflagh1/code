/******************************************************************************/
#ifndef _ITERRAINTREEOPERATIONMANAGER_H_
#define _ITERRAINTREEOPERATIONMANAGER_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "IEditorOperation.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //��Ϸֲ�������ӿ�
    /******************************************************************************/
    class ITerrainTreeOperationManager : public IEditorOperationManager
    {
    public:

        //���ò������ID
        virtual U32		getOpModel() = NULL;

        //�õ��������ID
        virtual void	setOpModel(U32 modelID) = NULL;

		//����Tree����
		virtual void	setTreeType(U32 tType) = NULL;

		//��ȡTree����
		virtual U32		getTreeType() = NULL;

    };

    /******************************************************************************/
    //��Ϸֲ�����ӽӿ�
    /******************************************************************************/
    class ITerrainAddTreeOperationManager : public IEditorOperationManager
    {
    public:

        //�õ��ܶ�
        virtual Flt		getDensity() = NULL;

        //�����ܶ�
        virtual void	setDensity(Flt density) = NULL;

        //���ø���
        virtual Flt		getClumping() = NULL;

        //�õ�����
        virtual void	setClumping(Flt clumping) = NULL;

        //���ø߶ȱ仯��
        virtual void	setScaleVariable(Flt variable) = NULL;

        //�õ��߶ȱ仯��
        virtual Flt		getScaleVariable() = NULL;

        //���ø߶�
        virtual Flt		getScale() = NULL;

        //�õ��߶�
        virtual void	setScale(Flt scale) = NULL;

		//��ȡ�ݼ��
		virtual Flt		getGrassDistance() = NULL;

		//���òݼ��
		virtual void	setGrassDistance(Flt dis) = NULL;

		//��ȡ�����
		virtual Flt		getTreeDistance() = NULL;

		//���������
		virtual void	setTreeDistance(Flt dis) = NULL;

		//��ȡ��С�s�ű���
		virtual Flt		getMinScale() = NULL;

		//������С�s�ű���
		virtual void	setMinScale(Flt scale) = NULL;

		//��ȡ���s�ű���
		virtual Flt		getMaxScale() = NULL;

		//�������s�ű���
		virtual void	setMaxScale(Flt scale) = NULL;

		//��ȡ�Ƿ��������
		virtual bool	getAlign() = NULL;

		//�����Ƿ��������
		virtual void	setAlign(bool align) = NULL;

		//��ȡλ��ƫ�ưٷֱ�
		virtual Flt		getPositionOffset() = NULL;

		//����λ��ƫ�ưٷֱ�
		virtual void	setPositionOffset(Flt offset) = NULL;

		//��ȡ�ֲ���ʽ
		virtual U32		getDistribute() = NULL;

		//���÷ֲ���ʽ
		virtual void	setDistribute(U32 disType) = NULL;
		
    };

    /******************************************************************************/
    //��Ϸֲ���Ƴ��ӿ�
    /******************************************************************************/
    class ITerrainRemoveTreeOperationManager: public IEditorOperationManager
    {
    public:

    };
    /******************************************************************************/
    //ֲ������ˢ�ӿ�
    /******************************************************************************/
    class ITerrainDefineTreeOperationManager: public IEditorOperationManager
    {
    public:

        enum
        {
            /*@
            һ�β��������������Χ��������� 
            ѡ����Щ�����������������Ϊ����ѡ������������顣
            ��������Χ��û��������Լ�����һ�����Ρ�
            @*/
            DEFINE_BATCH_MODE_COMMON,

            /*@
            ����ѡ��������ڵ�����ȷ��������ڵ������顣
            @*/
            DEFINE_BATCH_MODE_REGION,

            /*@
            ������ѡ�е���������Ϊ��ָ���������顣
            @*/
            DEFINE_BATCH_MODE_SPECIALIZE,
        };

    public:

        //��������ָ��ģʽ
        virtual void	setMode( U32 mode ) = NULL;

        //��������ָ��ģʽ
        virtual U32		getMode() = NULL;

        //������������
        virtual void	setGroupName( const Str& group ) = NULL;

        //������������
        virtual Str		getGroupName() = NULL;

        //������������
        virtual void	lock(bool islock) = NULL;

        //������������
        virtual bool	isLocked() = NULL;

    };
}

/******************************************************************************/
#endif
