//**********************************************************************************************************
#ifndef _H_DEIMAGE_6543728975874_
#define _H_DEIMAGE_6543728975874_
//**********************************************************************************************************
#include "IImage.h"
#include "DEWidget.h"
//**********************************************************************************************************
class  MyGUI::Widget;
class  MyGUI::ISubWidgetRect;
//**********************************************************************************************************
namespace MG
{
    class DEImage : public IImage, public DEWidget  
    {
    public:
                                DEImage();
        virtual                 ~DEImage();

    public:
        virtual IWidget*        getWidget();
        virtual void            setTexture(const Str& name);
        virtual void            setTexture(const std::string& _name, const std::string& _group, const std::string& _item);
        virtual bool            setItemResource(const std::string& _name);
        virtual void            setItemGroup(const std::string& _value);
        virtual void            setItemName(const std::string& _value);
		virtual void			setImageBroadcast(MGIMAGE_BROADCAST_TYPE type, U32 broadcastTime, U32 totalTime);
		virtual MGIMAGE_BROADCAST_TYPE 
								getImageBroadcast();

		virtual void			setRenderTexture(const std::string& name, const std::string& group );

	public:

		virtual void			setAngle(Flt angle);
		virtual void			setUVCoord(Flt left, Flt bottom, Flt width, Flt height);

    public:
        //引擎事件
                Bool            setEGImage(MyGUI::Widget* p);
                MyGUI::Widget*  getEGImage(){return mpEGImage;}

	public:
		virtual void			setFrameChangeEvent(PVOIDINT_CALLBACK func);

	protected:
		//引擎事件
		void					notifyFrameChangeEvent( MyGUI::ImageBox* p, Int lastFrame );

	protected:
		//记录引擎对象和对应的回调函数，当引擎的回调响应时可找到client的回调函数
		static std::map<MyGUI::ImageBox*, PVOIDINT_CALLBACK>                    mMapFrameChangeEvent;

    private:
        //引擎对象指针
        MyGUI::ImageBox*                                             mpEGImage;
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************