//***************************************************************************************************
#ifndef _H_UISYSTEMINFO_
#define _H_UISYSTEMINFO_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{

	enum UI_ROLL_STATE
	{
		UI_ROLL_STATE_PLAY,
		UI_ROLL_STATE_STOP,
		UI_ROLL_STATE_END
	};

	struct BroadCastData 
	{
		Flt		speed;
		Int		times;
		Str16	Data;

		BroadCastData()
		{
			speed = 0.9f;
			times = 3;
			Data = L"";
		}
	};

	
	//***************************************************************************************************
	//系统公告栏
	//***************************************************************************************************
    class UISystemInfoBroadCast  : public UIObject
    {
    public:
        UISystemInfoBroadCast();
        ~UISystemInfoBroadCast();
        SINGLETON_INSTANCE(UISystemInfoBroadCast);

    public:
		void			addData(Char16* text,Int speed = 1,Int times = 3);
		void			setState(UI_ROLL_STATE rollState);
        virtual void	setEvent();
				void	update(Flt delta);

    protected:
    private:
		std::list<BroadCastData*>	mSystemBroadCastDatas;
		BroadCastData*				mCurrData;
		UI_ROLL_STATE				mRollState;
		
    };

	//***************************************************************************************************
	//GM公告栏
	//***************************************************************************************************
	class UIGMInfoBroadCast : public UIObject
	{
	public:
		UIGMInfoBroadCast();
		~UIGMInfoBroadCast();
		SINGLETON_INSTANCE(UIGMInfoBroadCast);

	public:
		void			addData(Char16* text,Int speed = 1,Int times = 3);
		void			setState(UI_ROLL_STATE rollState);
		virtual void	setEvent();
		void			update(Flt delta);

	protected:
	private:
		std::list<BroadCastData*>	mSystemBroadCastDatas;
		BroadCastData*				mCurrData;
		UI_ROLL_STATE				mRollState;
	};
}
//***************************************************************************************************
#endif
//***************************************************************************************************