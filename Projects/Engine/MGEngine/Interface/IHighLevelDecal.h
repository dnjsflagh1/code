/******************************************************************************/
#ifndef _IHIGHLEVELDECAL_H_
#define _IHIGHLEVELDECAL_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //���������ӿ�
    /******************************************************************************/
    class IHighLevelDecal
    {
    public:

        /// ����λ��
        virtual void                    setPosition(Vec3& pos) = 0;
        /// �õ�λ��
        virtual Vec3&                   getPosition() = 0;
        
        /// ���ô�С
        virtual void                    setSize(Flt size) = 0;
        /// �õ���С
        virtual Flt                     getSize() = 0;
        
		/// ���÷���
		virtual void					setNormal(Vec3& normal) = 0;
		/// �õ�����
		virtual Vec3&					getNormal() = 0;

        /// ���ÿɼ���
        virtual void                    setVisible(Bool visible) = 0;
    };
    
    /******************************************************************************/
    //����������
    /******************************************************************************/
    class IHighLevelDecalSet
    {
    public:

        /// �õ������ӿ�
        virtual IHighLevelDecal*        getDecal(UInt index) = 0;
        /// �õ���������
        virtual UInt                    getDecalNum() = 0;

		virtual void					update( Flt delta ) = 0;
    };



}

/******************************************************************************/
#endif
