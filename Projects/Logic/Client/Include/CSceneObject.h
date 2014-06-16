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
  //  //��̬����
  //  /******************************************************************************/
  //  struct CSceneObjectDynamicData
  //  {
  //      Flt     moveSpeed;
  //      Flt     yawSpeed;

		//Bool	isDestroy;
		//Bool	isAI;

  //      IdType  belongPlayerID;     // �������
  //      FORCE   force;              // ����
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

    //��������������������������������������������������������������������������������������������������
    //  [��Ҫ����]
    //��������������������������������������������������������������������������������������������������

        // ����
        virtual void				        update( Flt delta );

        // ��ʼ��
        virtual void				        initialize(){};
        // ����ʼ��
        virtual void				        unInitialize(){};

    //��������������������������������������������������������������������������������������������������
    // [��������]
    //��������������������������������������������������������������������������������������������������

        // �õ���������
        SceneObjectData*					getDynamicData();

    
        /////////////////////////////////////////////////////////////////////////////////////


        // �õ�״̬����
        LinedStateManager&                  getActionStateManager(){return mLinedStateManagerForAction;};
        // ֹͣ����Action
        void                                stopAllAction();

        /////////////////////////////////////////////////////////////////////////////////////

        // �õ�AI״̬����
        LinedStateManager&                  getAIStateManager(){return mLinedStateManagerForAI;};

        // ����AI
        void                                setAIEnable( Bool enable );
        // ֹͣ����Action
        void                                stopAllAI();

    private:
        LinedStateManager	                mLinedStateManagerForAI;
        LinedStateManager                   mLinedStateManagerForAction;

    };
}
/******************************************************************************/
#endif // CSceneObject
/******************************************************************************/