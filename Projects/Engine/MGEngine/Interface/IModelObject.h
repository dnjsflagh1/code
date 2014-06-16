/******************************************************************************/
#ifndef _IMODELOBJECT_H_
#define _IMODELOBJECT_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "IShadow.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //ģ��Ч������
    /******************************************************************************/
    enum ModelEffectType
    {
        MET_NULL    = 0, 
    };

    /******************************************************************************/
    //ģ�Ͷ���
    /******************************************************************************/
    class IModelObject 
    {
    public:

        ////////////////////////////////////////////////////////////////////////////////////////////

        /// ��ȡ��ԴID
        virtual U32						getModelDeclarationID() = 0;
        ///	��ײ�е�size 
        virtual Vec3					getBoundingBoxSize() = 0;
        /// Ѱ·�뾶
        virtual Flt						getPatherRadius() = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////

        // ������ӰͶ������
        virtual void                    setShadowCastType(ShadowCasterType type) = 0;
        // �õ���ӰͶ������
        virtual ShadowCasterType        getShadowCastType() = 0;

        // �����Ƿ���ܶ�̬��Ӱ
        virtual void                    setDynamicShadowReceiveEnable(Bool enable) = 0;
        // �õ��Ƿ���ܶ�̬��Ӱ
        virtual Bool                    getDynamicShadowReceiveEnable() = 0;

        // �����Ƿ���ܾ�̬��Ӱ
        virtual void                    setStaticShadowReceiveEnable(Bool enable) = 0;
        // �õ��Ƿ���ܾ�̬��Ӱ
        virtual Bool                    getStaticShadowReceiveEnable() = 0;


        ////////////////////////////////////////////////////////////////////////////////////////////

        // �����Ƿ��ܱ�����
        virtual void                    setReflectEnable(Bool enable) = 0;
        // �õ��Ƿ��ܱ�����
        virtual Bool                    getReflectEnable() = 0;

        // �����Ƿ��ܱ�����
        virtual void                    setRefractEnable(Bool enable) = 0;
        // �õ��Ƿ��ܱ�����
        virtual Bool                    getRefractEnable() = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////

        /// �õ����������λ��
        virtual Vec3                    getBonePosition(CChar* boneName) = 0;
        /// �õ�����������λ��
        virtual Vec3                    getBoneWorldPosition(CChar* boneName) = 0;
		/// �õ���������Խ�λ��
		virtual Qua                     getBoneOrientation(CChar* boneName) = 0;
		/// �õ������������λ��
		virtual Qua                     getBoneWorldOrientation(CChar* boneName) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////

		/// ͨ��һ��ֵ��ȡ��������λ��
		virtual Vec3					getCenterPosition(Flt center = 0.0f, Bool isLocal = true) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////

        /// �õ��߶�
        virtual Flt                     getHeight() = 0;
        /// �õ����
        virtual Flt                     getWidth() = 0;


        ////////////////////////////////////////////////////////////////////////////////////////////

        /// ���ø���
        virtual void                    setHightLight(Flt shine, Bool useDirty=true) = 0;
        /// �����Է���
        virtual void                    setEmissive(Color color, Bool toAccessory = false) = 0;
		/// ����Է�����ɫ
		virtual Color					getEmissive() = 0;

    };

}

/******************************************************************************/
#endif
