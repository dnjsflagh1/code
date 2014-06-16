/******************************************************************************/
#ifndef _IDECAL_H_
#define _IDECAL_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	// ��������
	/******************************************************************************/
	enum IDecalType
	{
		DT_SIMPLE,
		DT_HIGHLEVEL,
	};
	

	/******************************************************************************/
	//�����ӿ�
	/******************************************************************************/
	class IDecal
	{
	public:

		/// �õ�����
		virtual IDecalType				getType() = 0; 

		/// ����λ��
		virtual void                    setPosition(Vec3& pos) = 0;
		/// �õ�λ��
		virtual Vec3&                   getPosition() = 0;
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
	class IDecalSet
	{
	public:

		/// �õ������ӿ�
		virtual IDecal*					getDecal(UInt index) = 0;
		/// �õ���������
		virtual UInt                    getDecalNum() = 0;
		/// ���ô�С
		virtual void					setSize(int size) = 0;
		/// ��ȡ��С
		virtual int						getSize() = 0;
		/// ��������
		virtual void					update(Flt delta) = 0;

		virtual void					preRendering() = 0;

		virtual void					postRendering() = 0;
	};



}

/******************************************************************************/
#endif
