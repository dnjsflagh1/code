//***************************************************************************************************
#ifndef _H_UI_LOADING_PROGRESS_
#define _H_UI_LOADING_PROGRESS_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
	class UILoadingProgress: public UIObject
	{

	public:
		UILoadingProgress();
		~UILoadingProgress();
		SINGLETON_INSTANCE(UILoadingProgress);

	public:

		virtual Bool	openGui();
		virtual Bool	closeGui();

		virtual	void	setEvent();

		/*设置读取进度，0.0-1.0f*/
		Flt				getValue();
		void			setValue(Flt val);

		void			setPosition(Int val);
		void			setText(Char16* str);
		void			update(Flt delta);

	protected:

		Flt				mProgress;

	private:
	};
}
//***************************************************************************************************
#endif
//***************************************************************************************************