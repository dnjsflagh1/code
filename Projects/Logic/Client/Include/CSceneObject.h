/******************************************************************************/
#ifndef _CSCENEOBJECT_H_
#define _CSCENEOBJECT_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "GameObject.h"

/******************************************************************************/
namespace MG
{


  //  /******************************************************************************/
  //  //动态属性
  //  /******************************************************************************/
  //  struct CSceneObjectDynamicData
  //  {
  //      Flt     moveSpeed;
  //      Flt     yawSpeed;

		//Bool	isDestroy;
		//Bool	isAI;

  //      IdType  belongPlayerID;     // 所属玩家
  //      FORCE   force;              // 势力
  //      
  //      CSceneObjectDynamicData()
  //          : moveSpeed(1)
  //          ,yawSpeed(1)
  //          ,belongPlayerID(0)
  //          ,force(FORCE_INIT)
		//	,isDestroy(false)
		//	,isAI(false)
  //      {
  //      }

		//CSceneObjectDynamicData& operator=(const CSceneObjectDynamicData& A)
		//{
		//	if (this == &A)
		//	{
		//		return *this;
		//	}

		//	moveSpeed		=    A.moveSpeed;
		//	yawSpeed		=    A.yawSpeed;
		//	belongPlayerID	=    A.belongPlayerID;
		//	force			=    A.force;
		//	isDestroy		=	 A.isDestroy;
		//	isAI			=	 A.isAI;

		//	return *this;
		//};
  //  };
    
    
    /******************************************************************************/
    //CSceneObject
    /******************************************************************************/

    class CSceneObject : public GameObject
    {
    public:

        CSceneObject(GAMEOBJ_TYPE type, GAMEOBJ_QUERY_TYPE queryType, SceneObjectData* dynamicData);
        virtual ~CSceneObject();

    public:

    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //  [主要方法]
    //×××××××××××××××××××××××××××××××××××××××××××××××××

        // 更新
        virtual void				        update( Flt delta );

        // 初始化
        virtual void				        initialize(){};
        // 反初始化
        virtual void				        unInitialize(){};

    //×××××××××××××××××××××××××××××××××××××××××××××××××
    // [基本属性]
    //×××××××××××××××××××××××××××××××××××××××××××××××××

        // 得到基础数据
        SceneObjectData*					getDynamicData();

    
        /////////////////////////////////////////////////////////////////////////////////////


        // 得到状态管理
        LinedStateManager&                  getActionStateManager(){return mLinedStateManagerForAction;};
        // 停止所有Action
        void                                stopAllAction();

        /////////////////////////////////////////////////////////////////////////////////////

        // 得到AI状态管理
        LinedStateManager&                  getAIStateManager(){return mLinedStateManagerForAI;};

        // 设置AI
        void                                setAIEnable( Bool enable );
        // 停止所有Action
        void                                stopAllAI();

    private:
        LinedStateManager	                mLinedStateManagerForAI;
        LinedStateManager                   mLinedStateManagerForAction;

    };
}
/******************************************************************************/
#endif // CSceneObject
/******************************************************************************/