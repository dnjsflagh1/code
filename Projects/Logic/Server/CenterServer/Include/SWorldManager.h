//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\CenterServer\Include\SWorldManagerNew.h
//        Author: yuanlinhu
//          Date: 2012-3-21
//          Time: 15:25
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-21      add
//////////////////////////////////////////////////////////////


/******************************************************************************/
#ifndef _S_WORLD_MANAGER_NEW_H_
#define _S_WORLD_MANAGER_NEW_H_
/******************************************************************************/

#include "CenterServerPreqs.h"
#include "SRegionObjectManager.h"

/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//世界管理者
	/******************************************************************************/
	class SWorldManager
	{
	public:
		SWorldManager();
		~SWorldManager();
		SINGLETON_INSTANCE(SWorldManager);

		Bool			initialize(ServerLauncherInterface* launcher);
		Bool			unInitialize();

		void			setDBDriver(DBDriver* driver);

		I32				getActiveMapsId( std::vector<IdType>& mapsId,I32 divideIndex,I32 activeMapServerCount );
	private:
		DBDriver*					mDBDriver;
		//SRegionObjectManager		mRegionObjectManager;

	};

}

#endif	//_S_WORLD_MANAGER_NEW_H_