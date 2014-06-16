//****************************************************************************************************
#ifndef _H_UIDELEGATE_7543890jgdkl_
#define _H_UIDELEGATE_7543890jgdkl_
//****************************************************************************************************

#include "ClientPreqs.h"

//****************************************************************************************************

namespace MG
{

    /******************************************************************************/
    //�������
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

        //���ز���
        Bool        loadLayout();

        void        update(Flt delta);

		//����������UI
		void        loadUI();
		void		loadUIWithGameType(GameType mode);
        //���ESC���Ƿ񱻰���
        void        checkEsc();
		//�л���ǰ���뽹��
		void        checkEnter();
		void        mainGUIControl();

        //�ر����н���
        void        closeAllLayout();
		void		closeCampaignLayout();			//�ر�ս����ص�ui
		void		setGameType(GameType mode){ mGameType = mode;};
		GameType	getGameType() {return mGameType;};
			
    protected:
        //����һ���������
        void        addUIObj(UIObject* pObj);
    private:
        std::vector<UIObject*> mUIObjList;
		GameType	mGameType;
    };
}

//****************************************************************************************************
#endif
//****************************************************************************************************