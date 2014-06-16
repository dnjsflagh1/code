/******************************************************************************/
#include "StdAfx.h"
#include "CoreManager.h"
#include "GlobalOptions.h"


/******************************************************************************/


namespace PackTool {

    //-----------------------------------------------------------------------
    CoreManager::CoreManager()
        :mStopUpdateDirty(false)
    {
    }
    //-----------------------------------------------------------------------
    CoreManager::~CoreManager()
    {
		
    }
    //-----------------------------------------------------------------------
    Bool CoreManager::initialize()
    {
        if ( loadLib() == false )
            return false;
        if ( loadForm() == false )
            return false;
        if ( loadGameFile() == false )
            return false;

        return true;
    }
    //-----------------------------------------------------------------------
    Bool CoreManager::uninitialize()
    {
        unLoadForm();
        unLoadLib();
        unLoadGameFile();
        
        return true;
    }
    //-----------------------------------------------------------------------
    void CoreManager::stop()
    {
        mStopUpdateDirty = true;
    }
    //-----------------------------------------------------------------------
    void CoreManager::run()
    {
        FormSet::main_form->Show();

        mCurrUpdateTicks = GetTickCount() * 0.001;
        mLastUpdateTicks = mCurrUpdateTicks;
        mUpdateDelta = 0.0;
        while( mStopUpdateDirty == false )
        {
            System::Windows::Forms::Application::DoEvents();
            if ( FormSet::main_form->Visible == false )
                break;

            mCurrUpdateTicks = GetTickCount() * 0.001;
            mUpdateDelta = mCurrUpdateTicks - mLastUpdateTicks;
            mLastUpdateTicks = mCurrUpdateTicks;
            if ( update( mUpdateDelta ) == false )
                break;
        }
    }

    //-----------------------------------------------------------------------
    Bool CoreManager::update( Dbl delta )
    {
		//test();
        return true;
    }
    
    //-----------------------------------------------------------------------
    Bool CoreManager::loadLib()
    {
       

        return true;
    }
    //-----------------------------------------------------------------------
    Bool CoreManager::unLoadLib()
    {

        return true;
    }

    //-----------------------------------------------------------------------
    Bool CoreManager::loadGameFile()
    {
        unLoadGameFile();

		//mMapObjInfoList = new std::map<IdType, MapObjectInfo*>;
		//mPlaceObjInfoList = new std::map<IdType, PlaceObjectInfo*>;

		//MapObjectInfos::getInstance().loadFile(L"Config\\World\\MapObject.csv", NULL, mMapObjInfoList, LFT_EDIT);
		//DistrictInfos::getInstance().loadFile(L"Config\\World\\DistrictTemplate.csv");
		//DistrictObjectInfos::getInstance().loadFile(L"Config\\World\\DistrictObject.csv", LFT_EDIT);
		//PlaceTemplateInfos::getInstance().loadFile(L"Config\\World\\CityTemplate.csv");
		//PlaceObjectInfos::getInstance().loadFile(L"Config\\World\\CityObject.csv", NULL, mPlaceObjInfoList, LFT_EDIT);
		//MapResourceInfos::getInstance().loadFile(L"Config\\World\\ArtMapRes.csv");
		
        return true;
    }
    //-----------------------------------------------------------------------
    Bool CoreManager::unLoadGameFile()
    {
        return true;
    }

    //-----------------------------------------------------------------------
    Bool CoreManager::loadForm()
    {
        // Initialize Window
        //// Enabling Windows XP visual effects before any controls are created
        System::Windows::Forms::Application::EnableVisualStyles();
        System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false); 

        FormSet::main_form  = gcnew Form1();

        FormSet::main_form->CreateControl();

        return true;
    }
    //-----------------------------------------------------------------------
    Bool CoreManager::unLoadForm()
    {


        return true;
    }

	//-----------------------------------------------------------------------
	void CoreManager::test()
	{

		{
			CZipString str1 = "adadad";
			str1.MakeLower();
		}



		//if(!mSrcDir)
		//{
		//	System::Windows::Forms::MessageBox::Show("请选择源散包目录", "Warning", 
		//		MessageBoxButtons::OK, MessageBoxIcon::Warning);

		//	return;
		//}

		//if(!mDestDir)
		//{
		//	System::Windows::Forms::MessageBox::Show("请选择压缩包存放目录", "Warning", 
		//		MessageBoxButtons::OK, MessageBoxIcon::Warning);

		//	return;
		//}

		//StrToChar8 srcStr( mSrcDir );
		//      StrToChar8 destStr( mDestDir );

		CZipArchive* mArchive = MG_NEW CZipArchive();
		if (!mArchive->Open("Res1/Config/Base.cn",CZipArchive::zipCreate))
			return;

		//std::string str = "*.*";

		//std::transform(
		//	str.begin(),
		//	str.end(),
		//	str.begin(),
		//	tolower);
		mArchive->AddNewFiles("Res1/Base", "*.*");


		//mArchive.AddNewFile("Config\\Base\\GameMessageConfig.ini", "Config\\Base\\GameMessageConfig.ini");
		//mArchive.AddNewFile("Config\\Base\\SelectServerConfig.ini", "Config\\Base\\SelectServerConfig.ini");

		mArchive->Close();
		// 根据传进来的路径,找到下面路径下的config和media文件夹,分别打包.

		//char SrcPathName[LEN], DestPathName[LEN];

		//wsprintf(DestPathName, "%s\\%s", mSrcDir, "Config");
		//wsprintf(SrcPathName, "%s\\%s", mSrcDir, "Config");
		//DirectoryList("Res1/Config", "Res1/Config", archive);

		//wsprintf(DestPathName, "%s\\%s", mSrcDir, "Media");
		//wsprintf(SrcPathName, "%s\\%s", mSrcDir, "Media");
		//DirectoryList(SrcPathName, DestPathName, archive);
	}
}

