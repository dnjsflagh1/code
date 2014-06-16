//**********************************************************************************************************
#ifndef _H_IMAGE_75758943_
#define _H_IMAGE_75758943_
//**********************************************************************************************************
#include "IWidget.h"
//**********************************************************************************************************
//静态图片接口
namespace MG
{
    class IImage
    {
    public:
        virtual IWidget*    getWidget() = 0;
        //设置texture
        virtual void        setTexture(const Str8& name) = 0;
        virtual void        setTexture(const std::string& _name, const std::string& _group, const std::string& _item) = 0;
        //设置texture的资源名
        virtual bool		setItemResource(const std::string& _name) = 0;
        //设置取那个群的资源
        virtual void		setItemGroup(const std::string& _value) = 0;
        //设置取具体的资源
        virtual void		setItemName(const std::string& _value) =0;
		//通过指定的名称和资源组获取贴图
		virtual void		setRenderTexture(const std::string& name, const std::string& group ) = 0;
		//设置2d动画的播放方式(时间单位，毫秒)
		virtual void		setImageBroadcast(MGIMAGE_BROADCAST_TYPE type, U32 time, U32 totalTime) = 0;
		//获得现在的播放方式
		virtual MGIMAGE_BROADCAST_TYPE 
							getImageBroadcast() = 0;
		
		//旋转图片
		virtual void		setAngle(Flt angle) = 0;
		//设置图片的UV
		virtual void		setUVCoord(Flt left, Flt bottom, Flt width, Flt height) = 0;
                
		virtual void		setFrameChangeEvent(PVOIDINT_CALLBACK func) = 0;
    };
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************