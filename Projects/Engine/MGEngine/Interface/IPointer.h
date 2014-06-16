//************************************************************************************************
#ifndef _H_IPOINTER_
#define _H_IPOINTER_
//************************************************************************************************
#include "MGEngineInterfacePreqs.h"
//************************************************************************************************
namespace MG
{
    class IPointer
    {
    public:
		//����״̬�������
		virtual void					setPointer(Str8 name, MGPOINTER_LEVEL level = MGPOINTER_LEVEL_LOW) = 0;
        /** Reset to default pointer */
        virtual void                    resetToDefaultPointer() = 0;
        //������ͼƬ������ͼƬ��Ϊ���ͼƬ
        virtual void                    setImage(Str8 resName, Str8 groupName, Str8 itemName, IAny any, int num = 1) = 0;
        //��ø�����Ϣ��
        virtual IAny*                   getAnyData() = 0;
        //���һ���������¼�����
        virtual void                    setDropEvent(PVOID_CALLBACK func) = 0;
		//������ʾ����
		virtual void					setVisible( bool visible ) = 0;

    };
}

//************************************************************************************************
#endif
//************************************************************************************************