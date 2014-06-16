#include "StdAfx.h"
#include "Form1.h"
#include "GlobalOptions.h"
#include "CoreManager.h"
#include "Utility.h"

#define LEN 1024

namespace PackTool {

	void str_replace( std::string& strBig, const std::string& strsrc, const std::string& strdst )
	{
		std::string::size_type pos = 0;
		std::string::size_type srclen = strsrc.size();
		std::string::size_type dstlen = strdst.size();

		while( (pos = strBig.find(strsrc, pos)) != std::string::npos )
		{
			strBig.replace(pos, srclen, strdst);
			pos += dstlen;
		}
	}


	// ������ȵݹ����Ŀ¼�����е��ļ�
	// �������ﲻ�õݹ�.ֻ��Ҫ��һ����ļ���
	BOOL  DirectoryList(LPCSTR SrcPath, LPCSTR DestPath, CZipArchive &ziparchive)
	{
		WIN32_FIND_DATA FindData;
		HANDLE hError;
		int FileCount = 0;
		char FilePathName[LEN];
		// ����·��
		char FullPathName[LEN];
		strcpy(FilePathName, SrcPath);
		strcat(FilePathName, "\\*.*");
		hError = FindFirstFile(FilePathName, &FindData);
		if (hError == INVALID_HANDLE_VALUE)
		{
			return 0;
		}
		while(::FindNextFile(hError, &FindData))
		{
			// ����.��..
			if (strcmp(FindData.cFileName, ".") == 0
				|| strcmp(FindData.cFileName, "..") == 0 )
			{
				continue;
			}
			// ��������·��
			wsprintf(FullPathName, "%s\\%s", SrcPath,FindData.cFileName);
			FileCount++;
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{	
				char PackName[LEN];
				wsprintf(PackName, "%s\\%s.cn", DestPath, FindData.cFileName);
				if (!ziparchive.Open(PackName, CZipArchive::zipCreate))
					return false;

				std::string pathname = FullPathName;
				str_replace(pathname, "\\", "/");

				ziparchive.AddNewFiles(pathname.c_str(), "*.*", true, -1, true, CZipArchive::zipsmIgnoreDirectories);
				ziparchive.Close();
			}
		}
		return 0;
	}

    //-----------------------------------------------------------------------
    void Form1::selectSrcFolder()
    {
        BEGINDELEGATE(Form1,selectSrcFolder)
        ENDDELEGATE

        folderBrowserDialog1->SelectedPath = System::Windows::Forms::Application::StartupPath;
        if ( folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
        {
            mSrcDir = folderBrowserDialog1->SelectedPath;
            StrToChar8 pathStr( mSrcDir );

            src_folder->Text = mSrcDir;

            // ����Ŀ¼��ʾ���б���

        }
    }

    //-----------------------------------------------------------------------
    void Form1::selectDestFolder()
    {
        BEGINDELEGATE(Form1,selectDestFolder)
        ENDDELEGATE

        folderBrowserDialog1->SelectedPath = System::Windows::Forms::Application::StartupPath;
        if ( folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
        {
            mDestDir = folderBrowserDialog1->SelectedPath;
            StrToChar8 pathStr( mDestDir );

            dest_folder->Text = mDestDir;

            // ����Ŀ¼��ʾ���б���

        }
    }

    //-----------------------------------------------------------------------
    void Form1::startPack()
    {
        BEGINDELEGATE(Form1,startPack)
        ENDDELEGATE

		CoreManager::getInstance().test();

    }

 
}

