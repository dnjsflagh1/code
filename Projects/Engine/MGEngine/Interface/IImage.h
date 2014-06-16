//**********************************************************************************************************
#ifndef _H_IMAGE_75758943_
#define _H_IMAGE_75758943_
//**********************************************************************************************************
#include "IWidget.h"
//**********************************************************************************************************
//��̬ͼƬ�ӿ�
namespace MG
{
    class IImage
    {
    public:
        virtual IWidget*    getWidget() = 0;
        //����texture
        virtual void        setTexture(const Str8& name) = 0;
        virtual void        setTexture(const std::string& _name, const std::string& _group, const std::string& _item) = 0;
        //����texture����Դ��
        virtual bool		setItemResource(const std::string& _name) = 0;
        //����ȡ�Ǹ�Ⱥ����Դ
        virtual void		setItemGroup(const std::string& _value) = 0;
        //����ȡ�������Դ
        virtual void		setItemName(const std::string& _value) =0;
		//ͨ��ָ�������ƺ���Դ���ȡ��ͼ
		virtual void		setRenderTexture(const std::string& name, const std::string& group ) = 0;
		//����2d�����Ĳ��ŷ�ʽ(ʱ�䵥λ������)
		virtual void		setImageBroadcast(MGIMAGE_BROADCAST_TYPE type, U32 time, U32 totalTime) = 0;
		//������ڵĲ��ŷ�ʽ
		virtual MGIMAGE_BROADCAST_TYPE 
							getImageBroadcast() = 0;
		
		//��תͼƬ
		virtual void		setAngle(Flt angle) = 0;
		//����ͼƬ��UV
		virtual void		setUVCoord(Flt left, Flt bottom, Flt width, Flt height) = 0;
                
		virtual void		setFrameChangeEvent(PVOIDINT_CALLBACK func) = 0;
    };
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************