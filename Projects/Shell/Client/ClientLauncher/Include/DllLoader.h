/******************************************************************************/
#ifndef _DLLLOADER_H_
#define _DLLLOADER_H_
/******************************************************************************/

/******************************************************************************/
//DLL ╪сть
/******************************************************************************/
class DllLoader
{
public:
	DllLoader();
	~DllLoader();

public:
    bool		load(const char* filePath, bool isFirst=false);
    bool		unload();

    FARPROC		getProcAddress(const char* name);


private:

    HINSTANCE	mHinst;

};



#endif