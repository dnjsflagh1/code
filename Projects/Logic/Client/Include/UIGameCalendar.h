//***************************************************************************************************
#ifndef _H_UIGAMECALENDAR_
#define _H_UIGAMECALENDAR_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
	struct ArtIconResCsvInfo;
	class UIGameCalendar  : public UIObject
	{
	public:
		UIGameCalendar();
		~UIGameCalendar();
		SINGLETON_INSTANCE(UIGameCalendar);

	public:
		virtual void	setEvent();
		virtual bool	isOpen();
		void			setCurrentDate(U8 seasonType,CChar16* dateInfo);
		void			setCurrentDate();
		void			update(Flt delta);
	protected:
		
	private: 
		 //设置季节图片资源
         void setArtResInfo();
		 std::map<U32, ArtIconResCsvInfo*> mArtResInfo;
	};
}
//***************************************************************************************************
#endif
//***************************************************************************************************