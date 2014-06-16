//************************************************************************************************
#ifndef _H_ID_BUILDERMANAGER_
#define _H_ID_BUILDERMANAGER_
//************************************************************************************************
#include "WorldCorePreqs.h"
//************************************************************************************************
namespace MG
{
	class IDObject
	{
		friend IDBuilderManager;
	public:
		IDObject(){}
		virtual ~IDObject(){}

	protected:
		GameObjectIdType		getSelfCreateID(){return 0;}
		void					setSelfCreateID(GameObjectIdType id){}

	};
	//----------------------------------------------------------------------------------------
	class IDBuilderManager
	{
	public:
		IDBuilderManager(){;}
		~IDBuilderManager(){;}

	public:
		Bool						addIDObject(IDObject* pIDObject);
		Bool						removeIDObject(IDObject* pIDObject);
		Bool						removeIDObject(GameObjectIdType id);

	public:
		void						init(GameObjectIdType maxId);
		void						unInit();
		void						clear();

	private:
		GameObjectIdType			getFreeID();

	private:
		std::map<GameObjectIdType, IDObject*>		mMapIDObject;
		GameObjectIdType							mMaxId;
		GameObjectIdType							mCurMaxId;

	};
}
//************************************************************************************************
#endif
//************************************************************************************************