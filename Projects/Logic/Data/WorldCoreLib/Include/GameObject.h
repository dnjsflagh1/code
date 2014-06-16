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

        // ���û�������
        void							setGameObjectData(GameObjectData* pData);
        // �õ���������
        GameObjectData*				    getGameObjectData();
	
	public: // ���������ԡ�

		//�õ������ñ��
		void                    		setID(GameObjectIdType id);
		GameObjectIdType                getID();

		//�õ�����
		GAMEOBJ_TYPE	        		getType();
		//�õ�����
		GAMEOBJ_QUERY_TYPE				getQueryType();

		//�õ�����������
		void                    		setName( CChar16* name );
		Str16&                  		getName();
	
        // ��ӡ
		virtual void				    print();

    private:

        GameObjectData*     		mObjectData;
        GAMEOBJ_TYPE                mType;          // ��������
		GAMEOBJ_QUERY_TYPE			mQueryType;		// �����ѯ����

	private:
		GameObject();
		GameObject& operator=(const GameObject&);

	};

}
#endif	//_NEW_GAMEOBJECT_H_