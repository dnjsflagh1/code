/******************************************************************************/
#ifndef _COMMONGAMEDBOP_H_
#define _COMMONGAMEDBOP_H_
/******************************************************************************/


/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //常用的数据库操作
    /******************************************************************************/
    class CommonGameDBOp
    {
    public:

        //线程锁定表,多连接适用
        static void lockTable(DBDriver& driver, Char16* tableName, Bool lockWrite = true, Bool lockRead = false);
        //线程解锁定表,多连接适用
        static void unLockTable(DBDriver& driver, Char16* tableName);

        //得到最后插入的编号,此方法多连接安全,线程不安全
        static U64 getLastInsertID(DBDriver& driver, Bool isCheckLock);
      
    };

}

/******************************************************************************/

#endif