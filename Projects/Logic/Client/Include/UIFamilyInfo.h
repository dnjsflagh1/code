//***************************************************************************************************
#ifndef _H_UIFAMILYINFO_
#define _H_UIFAMILYINFO_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************

namespace MG
{
	class UIFamilyInfo : public UIObject
      {
      public:
		  UIFamilyInfo();
		  ~UIFamilyInfo();
		  SINGLETON_INSTANCE(UIFamilyInfo)
	  public:
		  virtual void	setEvent();
		  virtual Bool  openGui();
      protected:

      private:
		  void    initFamilyInfo();

      };
  

}


#endif