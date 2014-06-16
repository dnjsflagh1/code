/******************************************************************************/
#ifndef _DATASETCONTROLLER_H_
#define _DATASETCONTROLLER_H_
/******************************************************************************/
#include "ThreadControlable.h"
//#include <CMisc.h>
#include <map>
#include <vector>
/******************************************************************************/
//interface IDataSetController 
/******************************************************************************/
template<typename TYPE0, typename TYPE1>
class IDataSetController
{
public:
    typedef std::map<ULONGLONG, TYPE0> DataSetMap;
    typedef std::vector<TYPE0> DataSetList;
    typedef std::vector<TYPE0*> DataSetPtrList;

    virtual TYPE0*              addOrUpdate(ULONGLONG key, TYPE0& data, bool isLock=true)=0;
    virtual bool                hasData(ULONGLONG key, bool isLock=true)=0; 
    virtual TYPE0*              getData(ULONGLONG key, bool isLock=true)=0; 
    virtual TYPE0*              getDataByName(std::string name, bool isLock=true){return NULL;}; 
    virtual void                remove(ULONGLONG key, bool isLock=true)=0;
    virtual void                removeAll(bool isLock=true)=0;
    virtual DataSetMap&         getDataSet()=0;

    virtual void                copyData(DataSetList& list,bool isLock=true)=0;
    virtual void                copyFilterDataSet(DataSetList& list, TYPE1& filter,bool isLock=true)=0;
    virtual void                copyFilterDataSet(DataSetPtrList& list, TYPE1& filter,bool isLock=true)=0;
};
/******************************************************************************/
//class DataSetController 
/******************************************************************************/
template<typename TYPE0, typename TYPE1>
class DataSetController : public ThreadControlable, public IDataSetController<TYPE0,TYPE1>
{
public:
    virtual TYPE0*              addOrUpdate(ULONGLONG key, TYPE0& data, bool isLock=true);
    virtual bool                hasData(ULONGLONG key, bool isLock=true); 
    virtual TYPE0*              getData(ULONGLONG key, bool isLock=true); 
    virtual void                remove(ULONGLONG key, bool isLock=true);
    virtual void                removeAll(bool isLock=true);
    virtual DataSetMap&         getDataSet(){return core_data;};

            void                copyData(DataSetList& list,bool isLock=true);
    virtual void                copyFilterDataSet(DataSetList& list, TYPE1& filter,bool isLock=true);
    virtual void                copyFilterDataSet(DataSetPtrList& list, TYPE1& filter,bool isLock=true);
private:
    DataSetMap core_data;
};
/******************************************************************************/
//class DataSetController definition
/******************************************************************************/

//-----------------------------------------------------------------------------
template<typename TYPE0, typename TYPE1>
TYPE0* DataSetController<TYPE0,TYPE1>::addOrUpdate(ULONGLONG key, TYPE0& data, bool isLock)
{
    if (isLock) lock();
    {
        core_data[key] = data;
    }
    if (isLock) unLock();
    return &(core_data[key]);
}
//-----------------------------------------------------------------------------
template<typename TYPE0, typename TYPE1>
bool DataSetController<TYPE0,TYPE1>::hasData(ULONGLONG key, bool isLock)
{
    bool result = false;
    if (isLock) lock();
    {
        DataSetController::DataSetMap::iterator it = core_data.find(key);
        if ( it != core_data.end() )
        {
            result = true;
        }
    }
    if (isLock) unLock();
    return result;
}
//-----------------------------------------------------------------------------
template<typename TYPE0, typename TYPE1>
TYPE0* DataSetController<TYPE0,TYPE1>::getData(ULONGLONG key, bool isLock)
{
    TYPE0* result = NULL;
    if (isLock) lock();
    {
        DataSetController::DataSetMap::iterator it = core_data.find(key);
        if ( it != core_data.end() )
        {
            result = &(it->second);
        }
    }
    if (isLock) unLock();
    return result;
}
//-----------------------------------------------------------------------------
template<typename TYPE0, typename TYPE1>
void DataSetController<TYPE0,TYPE1>::remove(ULONGLONG key, bool isLock)
{
    if (isLock) lock();
    {
        DataSetController::DataSetMap::iterator it = core_data.find(key);
        if ( it != core_data.end() )
        {
            core_data.erase(it);
        }  
    }
    if (isLock) unLock();
}
//-----------------------------------------------------------------------------
template<typename TYPE0, typename TYPE1>
void DataSetController<TYPE0,TYPE1>::removeAll(bool isLock)
{
    if (isLock) lock();
    {
        core_data.clear();
    }
    if (isLock) unLock();
}
//-----------------------------------------------------------------------------
template<typename TYPE0, typename TYPE1>
void DataSetController<TYPE0,TYPE1>::copyData(DataSetList& list,bool isLock)
{
    if (isLock) lock();
    {
        DataSetController::DataSetMap::iterator it = core_data.begin();
        for(; it != core_data.end(); it++)
        {
            list.push_back(it->second);
        }
    }
    if (isLock) unLock();
}
//-----------------------------------------------------------------------------
template<typename TYPE0, typename TYPE1>
void DataSetController<TYPE0,TYPE1>::copyFilterDataSet(DataSetList& list, TYPE1& filter,bool isLock)
{
    if (isLock) lock();
    {
        DataSetController::DataSetMap::iterator it = core_data.begin();
        TYPE0 * data;
        //TODO: filter use index map
        for(; it != core_data.end(); it++)
        {
            data = &(it->second);
            if (filter == *data)
                list.push_back(*data);
        }
    }
    if (isLock) unLock();
}
//-----------------------------------------------------------------------------
template<typename TYPE0, typename TYPE1>
void DataSetController<TYPE0,TYPE1>::copyFilterDataSet(DataSetPtrList& list, TYPE1& filter,bool isLock)
{
    if (isLock) lock();
    {
        DataSetController::DataSetMap::iterator it = core_data.begin();
        TYPE0 * data;
        //TODO: filter use index map
        for(; it != core_data.end(); it++)
        {
            data = &(it->second);
            if (filter == *data)
                list.push_back(data);
        }
    }
    if (isLock) unLock();
}

/******************************************************************************/

#endif 

