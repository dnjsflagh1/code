//****************************************************************************************************
#ifndef _H_UIDELEGATE_7543890jgdkl_
#define _H_UIDELEGATE_7543890jgdkl_
//****************************************************************************************************

#include "ClientPreqs.h"

//****************************************************************************************************

namespace MG
{

    /******************************************************************************/
    //界面管理
    /******************************************************************************/
    class UIManager
    {
        friend class UIObject;
    public:
        UIManager();
        virtual ~UIManager();
        SINGLETON_INSTANCE(UIManager);
    
    public:
        void        restore();

        //加载布局
        Bool        loadLayout();

        void        update(Flt delta);

		//加载主界面UI
		void        loadUI();
		void		loadUIWithGameType(GameType mode);
        //检查ESC键是否被按下
        void        checkEsc();
		//切换当前输入焦点
		void        checkEnter();
		void        mainGUIControl();

        //关闭所有界面
        void        closeAllLayout();
		void		closeCampaignLayout();			//关闭战斗相关的ui
		void		setGameType(GameType mode){ mGameType = mode;};
		GameType	getGameType() {return mGameType;};
			
    protected:
        //增加一个界面对象
        void        addUIObj(UIObject* pObj);
    private:
        std::vector<UIObject*> mUIObjList;
		GameType	mGameType;
    };
}

//****************************************************************************************************
#endif
//****************************************************************************************************