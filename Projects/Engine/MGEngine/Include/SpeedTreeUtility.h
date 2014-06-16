/******************************************************************************/
#ifndef __SPEEDUTILITY_H__
#define __SPEEDUTILITY_H__
/******************************************************************************/

#include <cstdio>
#include <cstdarg>
#ifdef SPEEDTREE_OPENGL
#ifdef __GNUC__
#include <glew/glew.h>
#include <Cg/cgGL.h>
#else
#include "glew/glew.h"
#include "Cg/cgGL.h"
#endif
#endif
#if defined(_WIN32) && !defined(_XBOX)
#include <windows.h>
#pragma warning (disable : 4996)
#endif
#ifdef _XBOX
#include <Xtl.h>
#endif
#ifdef __GNUC__
#include <dirent.h>
#include <errno.h>
#endif
#include "Core/Core.h"
#include "Core/String.h"
#include "LogSystem.h"

////////////////////////////////////////////////////////////
// UnreferencedParameter

#ifdef __CELLOS_LV2__
#define UnreferencedParameter(x) (x) = (x)
#else
#define UnreferencedParameter(x) (x)
#endif


///////////////////////////////////////////////////////////////////////  
//  INTERNAL_FORMAT_STRING macro
//  This code is used in the next few functions. Can't use a function call
//  because of the variable arguments.

#if !defined(__GNUC__) && !defined(vsnprintf)
#define vsnprintf _vsnprintf
#endif

#define INTERNAL_FORMAT_STRING \
	const st_int32 c_nMaxStringSize = 256; \
	st_char szBuffer[c_nMaxStringSize]; \
	va_list vlArgs; \
	va_start(vlArgs, pField); \
	(void) vsnprintf(szBuffer, c_nMaxStringSize - 1, pField, vlArgs); \
	szBuffer[c_nMaxStringSize - 1] = '\0'; \
	CBasicFixedString<2048> strValue(szBuffer);


///////////////////////////////////////////////////////////////////////  
//  All SpeedTree SDK classes and variables are under the namespace "SpeedTree"

namespace SpeedTree
{

	////////////////////////////////////////////////////////////
	// Error

	inline void Error(const char* pField, ...)
	{
		INTERNAL_FORMAT_STRING;

#if defined(_WIN32) && !defined(_XBOX)
		(void) MessageBoxA(NULL, strValue.c_str( ), "SpeedTree ERROR", MB_ICONERROR | MB_OK);
#else
		fprintf(stderr, "\n[Error]: %s\n", strValue.c_str( ));
#endif
	}


	////////////////////////////////////////////////////////////
	// Warning

	inline void Warning(const char* pField, ...)
	{
		INTERNAL_FORMAT_STRING;

		// display the warning
		//fprintf(stderr, "[Warning] %s\n", strValue.c_str( ));
		//MG_LOG(MG::out_error, "[Warning] %s\n", strValue.c_str( ));
	}


	////////////////////////////////////////////////////////////
	// Internal

	inline void Internal(const char* pField, ...)
	{
		INTERNAL_FORMAT_STRING;

		// display the fatal error
#if defined(_WIN32) && !defined(_XBOX)
		(void) MessageBoxA(NULL, strValue.c_str( ), "SpeedTree INTERNAL ERROR", MB_ICONERROR | MB_OK);
#else
		fprintf(stderr, "SpeedTree INTERNAL ERROR: %s\n", strValue.c_str( ));
#endif
	}


	////////////////////////////////////////////////////////////
	// Report

	inline void Report(const char* pField, ...)
	{
		INTERNAL_FORMAT_STRING;

		// display the report
		printf("%s\n", strValue.c_str( ));
	}


	////////////////////////////////////////////////////////////
	// Interpolate

	template <class T> inline T Interpolate(const T& tStart, const T& tEnd, st_float32 fPercent)
	{
		return static_cast<T>((tStart + (tEnd - tStart) * fPercent));
	}


	///////////////////////////////////////////////////////////////////////  
	//  FileExists

	inline bool FileExists(const char* pFilename)
	{
		FILE* pFile = fopen(pFilename, "r");
		bool bExists = (pFile != NULL);
		if (pFile)
			fclose(pFile);

		return bExists;
	}


	/////////////////////////////////////////////////////////////////////////////
	//  ColorToUInt

	inline st_uint32 ColorToUInt(st_float32 fR, st_float32 fG, st_float32 fB, st_float32 fA = 1.0f)
	{
		st_uint32 uiRed = (unsigned int) (fR * 255.0f);
		st_uint32 uiGreen = (unsigned int) (fG * 255.0f);
		st_uint32 uiBlue = (unsigned int) (fB * 255.0f);
		st_uint32 uiAlpha = (unsigned int) (fA * 255.0f);

		return ((uiRed << 0) + (uiGreen << 8) + (uiBlue << 16) + (uiAlpha << 24));
	}


	/////////////////////////////////////////////////////////////////////////////
	//  ColorToUInt

	inline st_uint32 ColorToUInt(const st_float32 afColor[4])
	{
		return ColorToUInt(afColor[0], afColor[1], afColor[2], afColor[3]);
	}


	/////////////////////////////////////////////////////////////////////////////
	//  ColorToFloats

	inline void ColorToFloats(st_uint32 uiColor, st_float32 afColor[4])
	{
		afColor[0] = ((uiColor & 0x000000FF) >> 0) / 255.0f;
		afColor[1] = ((uiColor & 0x0000FF00) >> 8) / 255.0f;
		afColor[2] = ((uiColor & 0x00FF0000) >> 16) / 255.0f;
		afColor[3] = ((uiColor & 0xFF000000) >> 24) / 255.0f;
	}


	////////////////////////////////////////////////////////////
	// Clamp

	template <class T> inline T Clamp(T tValue, T tMinValue, T tMaxValue)
	{
		T tReturn = st_min(tValue, tMaxValue);

		return st_max(tReturn, tMinValue);
	}


	////////////////////////////////////////////////////////////
	// Swap

	template <class T> inline void Swap(T& tA, T& tB)
	{
		T tTemp = tA;
		tA = tB; 
		tB = tTemp;
	}


	////////////////////////////////////////////////////////////
	// Frac

	inline SpeedTree::st_float32 Frac(SpeedTree::st_float32 x)
	{
		return x - st_int32(x);
	}


	///////////////////////////////////////////////////////////////////////
	//  PrintSpeedTreeError

	inline void PrintSpeedTreeErrors(const char* pLocation = NULL)
	{
		const char* pError = SpeedTree::CCore::GetError( );
		while (pError)
		{
			if (pLocation)
				Warning("(%s): %s", pLocation, pError);
			else
				Warning("%s", pError);

			pError = SpeedTree::CCore::GetError( );
		}
	}


#ifdef SPEEDTREE_OPENGL
	///////////////////////////////////////////////////////////////////////  
	//  PrintOpenGLErrors

	inline void PrintOpenGLErrors(const char* pLocation = NULL)
	{
		// query and print opengl errors
		GLenum eError = glGetError( );
		while (eError != GL_NO_ERROR)
		{
			if (pLocation)
				Warning("OpenGL error (%s): [%s]\n", pLocation, gluErrorString(eError));
			else
				Warning("OpenGL error: [%s]\n", gluErrorString(eError));

			// continue to retrieve until empty
			eError = glGetError( );
		}

		// query and print Cg errors
		CGerror cgError = cgGetError( );
		while (cgError != CG_NO_ERROR)
		{
			if (pLocation)
				Warning("Cg error (%s): [%s]\n", pLocation, cgGetErrorString(cgError));
			else
				Warning("Cg error: [%s]\n", cgGetErrorString(cgError));

			cgError = cgGetError( );
		}
	}
#endif


	///////////////////////////////////////////////////////////////////////  
	//  Strcmpi 

	inline bool Strcmpi(const SpeedTree::CFixedString& strA, const SpeedTree::CFixedString& strB)
	{
#ifdef __GNUC__
		return strcasecmp(strA.c_str( ), strB.c_str( )) == 0;
#else
		return _strcmpi(strA.c_str( ), strB.c_str( )) == 0;
#endif
	}


	///////////////////////////////////////////////////////////////////////  
	//  IsAbsolutePath 

	inline st_bool IsAbsolutePath(const SpeedTree::CFixedString& strPath)
	{
		st_bool bAbsolutePath = false;

		if (!strPath.empty( ))
		{
			char szLeadChar = strPath[0];

			if (szLeadChar == '/' || szLeadChar == '\\')
				bAbsolutePath = true;
			else
			{
				// does a colon appear anywhere in the filename?
				size_t siPos = strPath.find(':');
				if (siPos != (size_t)SpeedTree::CFixedString::npos)
					bAbsolutePath = true;
			}
		}

		return bAbsolutePath;
	}


	///////////////////////////////////////////////////////////////////////  
	//  IsFolder

	inline st_bool IsFolder(const char* pFilename)
	{
		st_bool bIsFolder = false;

#if defined(_WIN32) && !defined(_XBOX)
		DWORD dwAttributes = GetFileAttributesA(pFilename);
		if (dwAttributes != DWORD(-1))
			bIsFolder = (dwAttributes | FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY;
#endif

		return bIsFolder;
	}


	///////////////////////////////////////////////////////////////////////  
	//  ScanFolder

	inline void ScanFolder(const char* pFolder, const char* pExtension, bool bRecurse, CArray<CFixedString>& vFiles)
	{
		CFixedString strFolder(pFolder);
		CFixedString strExtension(pExtension);

#if defined(_WIN32) || defined(_XBOX)
		WIN32_FIND_DATAA sDirEntry;
		CFixedString strSearch = CFixedString(strFolder) + "\\*";

		HANDLE hDirHandle = FindFirstFileA(strSearch.c_str( ), &sDirEntry);
		if (hDirHandle != INVALID_HANDLE_VALUE)
		{
			// check "../data" for any folder
			do
			{
				CFixedString strFilename(sDirEntry.cFileName);
				if (Strcmpi(strFilename.Extension( ), strExtension))
					vFiles.push_back(strFolder + "\\" + strFilename);
				else if (bRecurse &&
					sDirEntry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&
					strcmp(sDirEntry.cFileName, ".") && 
					strcmp(sDirEntry.cFileName, ".."))
				{
					ScanFolder((strFolder + "\\" + CFixedString(sDirEntry.cFileName)).c_str( ), pExtension, bRecurse, vFiles);
				}

			} while (FindNextFileA(hDirHandle, &sDirEntry));

			(void) FindClose(hDirHandle);
		}
		else
			Warning("Failed to scan folder [%s] with wildcard [%s]\n", strFolder.c_str( ), strSearch.c_str( ));

#elif defined(__GNUC__)

		DIR* pDir = opendir(strFolder.c_str( ));
		if (pDir)
		{
			struct dirent* pEntry = readdir(pDir);
			while (pEntry)
			{
				CFixedString strFilename(pEntry->d_name);
				if (Strcmpi(strFilename.Extension( ), strExtension))
				{
					strFilename = strFolder + "/" + strFilename;
					vFiles.push_back(strFilename);
				}
				else if (bRecurse &&
					pEntry->d_type == DT_DIR &&
					strcmp(pEntry->d_name, ".") && 
					strcmp(pEntry->d_name, ".."))
				{
					ScanFolder(pEntry->d_name, pExtension, bRecurse, vFiles);
				}

				pEntry = readdir(pDir);
			}
			closedir(pDir);
		}
		else
			Warning("Failed to scan folder [%s] - %s\n", strFolder.c_str( ), strerror(errno));
#endif
	}

} // end namespace SpeedTree

#endif