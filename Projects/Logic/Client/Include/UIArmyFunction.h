//***************************************************************************************************
#ifndef _H_UIARMYFUNCTION_
#define _H_UIARMYFUNCTION_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
	enum army_click_state
	{
		army_click_state_null,		
		army_click_state_general1,	
		army_click_state_general2,
		army_click_state_general3,
		army_click_state_soldier1,
		army_click_state_soldier2,
		army_click_state_soldier3,
		army_click_state_soldier_skill1,
		army_click_state_soldier_skill2,
		army_click_state_soldier_skill3,
	};

	//***************************************************************************************************
	// 军团界面
	//***************************************************************************************************
    class UIArmyFunction : public UIObject
    {
    public:
        UIArmyFunction();
        ~UIArmyFunction();
        SINGLETON_INSTANCE(UIArmyFunction);

    public:
        virtual void setEvent();

		static	void	onClickGeneral(void* widget);
		
		static	void	onClickSoldier(void* widget);

		static  void	onClickGeneralSkill(void* widget, int x, int y, MouseCode index);
		
		static  void	onClickSoldierSkill(void* widget);
		
		static	void	onClickTroopGroupRight(void* widget);
		static	void	onClickTroopGroupLeft(void* widget);
		static  void	onClickTroopGroupStopMove(void* widget);

		void			adjustUi();
		void			setState(army_click_state state);

		void			clearGeneralSkillIcon();

		void			clearSelect();

		void			clearSelectPlayerCharacter();

		void			clearSelectTroopGroup();

    protected:
    private:
		army_click_state	mState;
		// 武将 兵团 栏位置
		Vec2				mImgSoldier1Pos1;
		Vec2				mImgSoldier2Pos1;
		Vec2				mImgSoldier3Pos1;
		Vec2				mImgSoldier1Pos2;
		Vec2				mImgSoldier2Pos2;
		Vec2				mImgSoldier3Pos2;
		// 武将 技能栏位置
		Vec2				mImgGeneralSkillPos1;
		Vec2				mImgGeneralSkillPos2;
		Vec2				mImgGeneralSkillPos3;
		// 兵团 命令栏位置
		Vec2				mImgSoldierCmdPos1;
		Vec2				mImgSoldierCmdPos2;
		Vec2				mImgSoldierCmdPos3;

		UInt                mSelectIndex;

		//static CPlayerTroopGroup*       mSelectTroopGroup;
		static CPlayerCharacterEntity*	mSelectPlayerCharacterEntity;
		static CPlayerCharacter*		mSelectPlayerCharacter;

    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************