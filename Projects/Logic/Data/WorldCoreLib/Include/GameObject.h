/******************************************************************************/
#ifndef _NEW_GAMEOBJECT_H_
#define _NEW_GAMEOBJECT_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
#include "GameObjectData.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //GameObject
    /******************************************************************************/

    class GameObject
    {
    public:
		GameObject(GameObject& rhs);
		GameObject(GAMEOBJ_TYPE type, GAMEOBJ_QUERY_TYPE queryType, GameObjectData* data, IdType id = 0);
		virtual ~GameObject();

    public:

        // 设置基础数据
        void							setGameObjectData(GameObjectData* pData);
        // 得到基础数据
        GameObjectData*				    getGameObjectData();
	
	public: // 【基础属性】

		//得到和设置编号
		void                    		setID(GameObjectIdType id);
		GameObjectIdType                getID();

		//得到类型
		GAMEOBJ_TYPE	        		getType();
		//得到类型
		GAMEOBJ_QUERY_TYPE				getQueryType();

		//得到和设置名字
		void                    		setName( CChar16* name );
		Str16&                  		getName();
	
        // 打印
		virtual void				    print();

    private:

        GameObjectData*     		mObjectData;
        GAMEOBJ_TYPE                mType;          // 对象类型
		GAMEOBJ_QUERY_TYPE			mQueryType;		// 对象查询类型

	private:
		GameObject();
		GameObject& operator=(const GameObject&);

	};

}
#endif	//_NEW_GAMEOBJECT_H_