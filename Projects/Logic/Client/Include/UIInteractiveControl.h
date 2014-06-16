#ifndef  _UIINTERACTIVECONTROL_H
#define  _UIINTERACTIVECONTROL_H
/******************************************************************************/
#include "WorldCorePreqs.h"
#include "ClientPreqs.h"
/******************************************************************************/

namespace MG
{
      class UIInteractiveControl
      {
      public:
		  UIInteractiveControl();
          SINGLETON_INSTANCE(UIInteractiveControl);
	      void update(Flt delta);
		  void clearInteractiveInfo();
		  //设置交互对象
		  void setInteractiveObject(U64 targetId,U64 operateEntityID,GAMEOBJ_TYPE targetType);
      private:
        void            clear();
		void            closeUIByType(GAMEOBJ_TYPE targetType);
	  private:
		
        U64             mTargetId;
        GAMEOBJ_TYPE    mtargetType;
		U64             mOperateEntityID;
		CSceneEntity*   mOperateEntity;
        
      };

}

//////////////////////////////////////////////////////////////////////////
#endif