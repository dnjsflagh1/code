/******************************************************************************/
#include "stdafx.h"
#include "DllLoader.h"
/******************************************************************************/


//-----------------------------------------------------------------------------
DllLoader::DllLoader()
	:mHinst(NULL)
{
}
//-----------------------------------------------------------------------------
DllLoader::~DllLoader()
{
	unload();
}
//-----------------------------------------------------------------------------
bool DllLoader::load(const char* filePath, bool isFirst)
{
	if (isFirst==false)
        mHinst = GetModuleHandleA(filePath);
	if (mHinst==NULL)
	{
		mHinst = LoadLibraryA(filePath);
	}


	return mHinst != NULL;
}
//-----------------------------------------------------------------------------
bool DllLoader::unload()
{
	bool result = true;
	if (mHinst!=NULL)
	{
		result = FreeLibrary(mHinst) != 0;
	}
	mHinst = NULL;

	return result;
}
//-----------------------------------------------------------------------------
FARPROC DllLoader::getProcAddress(const char* name)
{
	if (mHinst == NULL) 
		return NULL;
    
	FARPROC farProc =  GetProcAddress(mHinst, name); 

	return farProc;
}
//-----------------------------------------------------------------------------
