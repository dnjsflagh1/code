//*****************************************************************************************************
#ifndef _H_UISKILLTIPS_
#define _H_UISKILLTIPS_
//*****************************************************************************************************
#include "UIObject.h"
//*****************************************************************************************************
namespace MG
{
	class UISkillTips : public UIObject
     {
     public:
        UISkillTips();
		SINGLETON_INSTANCE(UISkillTips);
        void openSkillTips(IconInfo* picon,CoordI coord,CCharacter* character = NULL);


		virtual Bool    closeGui();
     protected:


     private:
		 //set tips info
		 void setSkillTipsInfo(CoordI coord);
         void setSkillNameAndLevel(U32& height);
		 void setSkillKindNameAndType(U32& height);
		 void setSkillSpend(U32& height);
		 void setSkillTimeDelay(U32& height);
		 void setSkillActionTime(U32& height);
         void setSkillDescribe(U32& height);
		 
		
		 //…Ë÷√tipsµƒŒª÷√
		 void    setTipsCoord(U32 height, CoordI coord);

		 //clear
		 void    clearAllItems();

	 private:
		const SkillInfo* mSelectSkillInfo;
		CCharacter*   mCurrentCharacter;

     };



}



#endif