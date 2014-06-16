/******************************************************************************/
#ifndef _DBMANAGER_H_
#define _DBMANAGER_H_
/******************************************************************************/
#include "Singleton.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//���ݿ������ 
	//��Ҫ�������ݿ�Table����
	/******************************************************************************/
	class DbManager
	{
	public:
		SINGLETON_INSTANCE(DbManager);
		DbManager();
		virtual	~DbManager();

		/// ��ʼ���ͷ���ʼ��
		Bool			initialize(DBDriver* driver,SServerSetting* setting);
		void			uninitialize();

		/// �������б�
		void			createAllTable();
	private:
		DBDriver*		mMySqlDriver;
		Bool			mIsCreateTable;
	};
}
#endif