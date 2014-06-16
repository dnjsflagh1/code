/******************************************************************************/
#ifndef _ACTION_RESOURCE_CONFIG_H_
#define _ACTION_RESOURCE_CONFIG_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IResourceManager.h"

/******************************************************************************/

namespace MG
{
	enum
	{
		ACTION_ID = 0,
		ACTION_DESC,
		ACTION_WEAPON_GROUP,
		ACTION_RIDE_GROUP,
		ACTION_NAME,
		ACTION_RESPATH,
		ACTION_RESNAME,
		ACTION_TIME,
		ACTION_SPEED,
		ACTION_LOOP,
		ACTION_REVERSE,
		ACTION_FREEZE,
	};

	/******************************************************************************/
	//This is a interface class for reading CSV table of animation resource .
	/******************************************************************************/
	class ActionResourceConfig
	{
	public:
		ActionResourceConfig(){};
		~ActionResourceConfig(){};
		SINGLETON_INSTANCE(ActionResourceConfig);

	public:

		//Load file for initializing model declaration maps of resource manager;
		Bool							load(ModelDeclaration* modelDecl);
		//UnLoad model declaration maps;
		void							unLoad();
		//
		void							showErrorList();

	private:

		Str								errorList;
	};
}

#endif