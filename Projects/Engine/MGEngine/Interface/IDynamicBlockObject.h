/******************************************************************************/
#ifndef _IDYNAMICBLOCKOBJECT_H_
#define _IDYNAMICBLOCKOBJECT_H_
/******************************************************************************/
#include "MGEngineInterfacePreqs.h"
/******************************************************************************/

namespace MG
{

    class IDynamicBlockObject
    {
    public:

        // �õ���������
        virtual ISceneObject*               getSceneObject() = 0;

        // ������Ч��
        virtual void						setEnable(Bool enable) = 0;
        // �Ƿ���Ч��
        virtual Bool						getEnable() = 0;

        // �Ƿ���ʾ�ϰ�
		virtual void						setShowBlock(Bool enable) = 0;

        // �����Ƿ�Ӱ�쾲̬�ϰ�
        virtual void						setStaticBlockEnable(Bool enable) = 0;

        // �����Ƿ��ǽ����ϰ�
        virtual void						setStructureMode(Bool enable) = 0;

        // �õ���̬��ײ�������С
        virtual Int							getStaticBlockGridDiameter() = 0;
        // ���ö���뾶����
		virtual void						setObjectRadius( Flt objectRadius ) = 0;

        // �õ�����İ뾶
		virtual Flt							getObjectRadius() = 0;

        // ˢ���µ��ϰ���
		virtual void			       		refreshBlock( Vec3 oldPos, Vec3 newPos ) = 0;

        // �õ���ռ�Ķ�̬�ϰ������б�
        virtual void                        getCurrLocationDynamicBlockIndexList( std::map<UInt, UInt>& list ) = 0;

        // �ж��Ƿ�������ռ�Ķ�̬�ϰ�����
        virtual Bool                        isBelongCurrLocationDynamicBlockIndex( UInt index ) = 0;

        // �ж��Ƿ�������ռ�ľ�̬�ϰ�����
        virtual Bool                        isBelongCurrLocationStaticBlockIndex( UInt index ) = 0;

  //      // ����������ײ�ϰ�������
		//virtual void						setCollideBlockIndex( UInt index ) = 0;
  //      // �õ�������ײ�ϰ�������
  //      virtual UInt						getCollideBlockIndex() = 0;

		virtual IDynamicBlockObject*		getCollideBlockObject() = 0;

		virtual void						setCollideBlockObject( IDynamicBlockObject* collideBlockObject ) = 0;

		virtual RectF						getBlockRect() = 0;
    };
}

/******************************************************************************/
#endif