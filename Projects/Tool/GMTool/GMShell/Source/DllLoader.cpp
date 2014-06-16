/******************************************************************************/
#include "stdafx.h"
#include "DllLoader.h"
#include "Utility.h"
/******************************************************************************/
/******************************************************************************/
//class DllLoader 
/******************************************************************************/

//DllLoader::DllLoader()
//    :m_hinstLib(NULL)
//{
//}
////-----------------------------------------------------------------------------
//DllLoader::~DllLoader()
//{
//    unload();
//}
////-----------------------------------------------------------------------------
//bool DllLoader::load(String ^ filePath, BOOLEAN isNew)
//{
//    if ( String::IsNullOrEmpty(filePath) )
//        return false;
//    else
//        unload();
//    
//    m_hinstLib = NULL;
//#ifdef UNICODE
//    wchar_t* wpCharPath =  Utility::convertStringToBSTR(filePath);
//
//    if (isNew==false)
//        m_hinstLib = GetModuleHandle(wpCharPath);
//    if (m_hinstLib==NULL)
//    {
//        m_hinstLib = LoadLibrary(wpCharPath);
//    }
//#else
//    char * charPath  = Utility::getPCharCopyFromString(filePath);
//    if (isNew==false)
//        m_hinstLib = GetModuleHandle(charPath);
//    if (m_hinstLib==NULL)
//    {
//        m_hinstLib = LoadLibrary(charPath);
//    }
//     Utility::freePCharCopyFromString(charPath);
//#endif // !UNICODE
//
//    return m_hinstLib!=NULL;
//}
////-----------------------------------------------------------------------------
//bool DllLoader::unload()
//{
//    bool result = true;
//    if (m_hinstLib!=NULL)
//    {
//        result = FreeLibrary(m_hinstLib) != 0;
//    }
//    m_hinstLib = NULL;
//
//    return result;
//}
////-----------------------------------------------------------------------------
//FARPROC DllLoader::getProcAddress(String ^ procName)
//{
//    if (m_hinstLib == NULL) 
//        return NULL;
//    
//    char* wpCharName =  Utility::getPCharCopyFromString(procName);
//    FARPROC farProc =  GetProcAddress(m_hinstLib, wpCharName); 
//    Utility::freePCharCopyFromString(wpCharName);
//
//    return farProc;
//}