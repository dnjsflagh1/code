/******************************************************************************/
#ifndef _DBMANAGER_H_
#define _DBMANAGER_H_
/******************************************************************************/
#include "Singleton.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//数据库管理类 
	//主要负责数据库Table创建
	/******************************************************************************/
	class DbManager
	{
	public:
		SINGLETON_INSTANCE(DbManager);
		DbManager();
		virtual	~DbManager();

		/// 初始化和反初始化
		Bool			initialize(DBDriver* driver,SServerSetting* setting);
		void			uninitialize();

		/// 创建所有表
		void			createAllTable();
	private:
		DBDriver*		mMySqlDriver;
		Bool			mIsCreateTable;
	};
}
#endif