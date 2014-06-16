/******************************************************************************/
#include "stdafx.h"
#include <crtdbg.h>
#include "LogSystem.h"
//#include "CWorldManager.h"
#include "ClientMain.h"
#include "UIManage.h"
#include "TestManager.h"
#include "ClientNetApplyManager.h"
#include "CSelectServerConfig.h"
#include "CGameMessageConfig.h"
#include "LoginManager.h"
#include "CSceneManager.h"
#include "LuaManager.h"
#include "CLuaSkillSystem.h"
#include "CharacterResourceConfig.h"
#include "CharacterList.h"
#include "CharacterArmyList.h"
#include "CharacterBuildList.h"
#include "CharacterGenrealList.h"
#include "CharacterNpcList.h"
#include "CharacterObjectList.h"
#include "CharacterMonsterList.h"
#include "CharacterLvlTemplate.h"
#include "AttributeAppend.h"
#include "AttributePara.h"
#include "AttributeList.h"
#include "CDTemplate.h"
#include "ItemShopTemplate.h"
#include "ItemGroupTemplate.h"
#include "ItemRandomTemplate.h"
#include "ArtIconResCsv.h"
#include "NpcFuctionInfo.h"
#include "ItemSiteTemplate.h"
#include "AudioResourceConfig.h"
#include "VideoResourceConfig.h"
#include "GameCameraConfig.h"
#include "CharacterSkillTempLate.h"
#include "GameSoundManager.h"
#include "CItemManager.h"
#include "CPlayer.h"
#include "ChannelInfo.h"
#include "CRegionManager.h"
#include "NetPacketPackManager.h"
#include "Dialog.h"
#include "ItemTemplate.h"
#include "ItemUseTemplate.h"
#include "ItemEquipTemplate.h"
#include "ItemMoneyTemplate.h"
#include "ItemOtherTemplate.h"
#include "ShortRangeGeneralAttackSkillTemplate.h"
#include "LongRangeGeneralAttackSkillTemplate.h"
#include "SingleTargetSkillTemplate.h"
#include "PassivenessSkillTemplate.h"
#include "SkillInfoList.h"
#include "SkillLearn.h"
#include "GameSettingManager.h"
#include "IDisplay.h"
#include "QuestList.h"
#include "QuestText.h"
#include "QuestNormalList.h"
#include "QuestValueChange.h"
#include "BigMapResCsv.h"
#include "InstanceListCsv.h"
#include "CGameTimeSystem.h"
#include "SingleEmitterSkillTemplate.h"
#include "SelfAreaSkillTemplate.h"
#include "TargetPosAreaSkillTemplate.h"
#include "CalendarInfo.h"
#include "BanKeyword.h"
#include "MessageManager.h"
#include "ArtDecalResTemplate.h"
#include "ParabolaAreaSkillTemplate.h"
#include "GoUpAndDownSkillTemplate.h"
#include "GameMiniMapManager.h"
#include "GameRadarConfig.h"
#include "TestUI.h"
#include "MessageManager.h"
#include "DialogueVassal.h"
#include "BaseAITemplate.h"
#include "BaseAIGroupTemplate.h"
#include "FightAITemplate.h"
#include "FightAiGroupTemplate.h"

#include "LogoScreen.h"
#include "LoginScreen.h"
#include "GameScreen.h"
#include "FontManger.h"

#include "GameMain.h"
#include "VersionSwitch.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    inline void EnableMemLeakCheck()
    {
        _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
    }

    //-----------------------------------------------------------------------
    #ifdef _DEBUG
        #define new     new(_NORMAL_BLOCK, __FILE__, __LINE__)
    #endif

    //-----------------------------------------------------------------------

	WinProc ClientMain::mWindowProcBackup = NULL;

    //-----------------------------------------------------------------------
    ClientMain::ClientMain()
        :mEngineMain(NULL)
        ,mStopUpdateDirty(false)
        ,mMainScene(NULL)
        ,mMainGui(NULL)
        ,mConsole(false)
		,mPackManager(NULL)
    {
        mLuaMgr = MG_NEW LuaManager;
		//MG::InstallMyExceptHandle();

		mPackManager = MG_NEW GameFilePackManager();
		mExPackManager = MG_NEW MGExternalPackManager(mPackManager);
    }

    //-----------------------------------------------------------------------
    ClientMain::~ClientMain()
    {
		MG::UnInstallMyExceptHandle();
        MG_SAFE_DELETE(mLuaMgr);

		MG_SAFE_DELETE(mPackManager);
		MG_SAFE_DELETE(mExPackManager);
    }

	//-----------------------------------------------------------------------
	Bool ClientMain::initialize()
    {
		//FUNDETECTION(__MG_FUNC__);
		Bool ret = false;
		MG_EXCEPTION_BEGIN
		{
			ret = _initialize();
		}
		MG_EXCEPTION_END("ClientMain::initialize()");
		return ret;
	}
	//-----------------------------------------------------------------------
	Bool ClientMain::uninitialize()
	{
		Bool ret = false;
		MG_EXCEPTION_BEGIN
		{
			ret = _uninitialize();
		}
		MG_EXCEPTION_END("ClientMain::uninitialize()");
		return ret;
	}

    //-----------------------------------------------------------------------
    void ClientMain::quitApplication()
    {
        mStopUpdateDirty = true;
    }

    //-----------------------------------------------------------------------
    void ClientMain::run()
    {
		MG_EXCEPTION_BEGIN
		_run();
		MG_EXCEPTION_END("ClientMain::run()");
    }

    //-----------------------------------------------------------------------
    Bool ClientMain::update( Dbl delta )
    {
        //----------------------------------------------------

        // ���·���������
        ClientNetApplyManager::getInstance().update();

        // �������������
        NetPacketPackManager::getInstance().update((Flt)delta);

		//----------------------------------------------------

		// �������
		if ( mEngineMain->update( (Flt)delta ) == false )
		{ 
			//MG::MsgBox::show("�������ʧ��","Error");
			return false;
		}

        // ����������״̬��
        GameMain::getInstance().update( (Flt)delta );

        //----------------------------------------------------

        // ��Ⱦ
        mEngineMain->render( (Flt)delta );

        //----------------------------------------------------

        return true;
    }

    //-----------------------------------------------------------------------
    Bool ClientMain::loadEngine()
    {
		//FUNDETECTION(__MG_FUNC__);

        Bool result = false;

        //----------------------------------------------------

        GET_MGENGINE_INTERFACE_PROC proc; 
        std::wstring dllName;
    #ifdef _DEBUG
        dllName = L"Core\\MGEngine_d.dll";
    #else
        dllName = L"Core\\MGEngine.dll";
    #endif
        
        //----------------------------------------------------

        if (mEngineDllLoader.load(dllName.c_str(),false)) 
        { 
            proc = (GET_MGENGINE_INTERFACE_PROC) mEngineDllLoader.getProcAddress("GET_MGENGINE_INTERFACE"); 
            if (NULL != proc) 
            {
                mEngineMain = (MG::IEngineMain*)proc(); 
                if (mEngineMain==NULL)
                {
                    MG::MsgBox::show("Load IEngineMain Failed!");
                    return 0;
                }
            }else
            {
                MG::MsgBox::show("Don't Find IEngineMain Entry!");
                return 0;
            }
        }else
        {
            MG::MsgBox::show("Don't Load IEngineMain DLL!");
            return 0;
        }

        //----------------------------------------------------
        
		// ��ͨģʽ
		mEngineMain->setMode( EM_NORMAL );

        //��������
		EngineInitConfig* config = GameSettingManager::getInstance().getEngineInitConfig();
        {
            config->packManager = mPackManager;
            result = mEngineMain->initialize( config );
        }
        GameSettingManager::getInstance().configSetting( mEngineMain );
	
        //----------------------------------------------------

		//�ػ񴰿���Ϣ
		HWND mainWnd = (HWND)mEngineMain->app()->getWindowHandle();
		std::string version = "Ӣ��־ ��ǰ�汾��";
		version += CLIENT_VERSION_NUMBER;
		::SetWindowTextA(mainWnd,version.c_str());
		DWORD   dwStyle   =   GetWindowLong(mainWnd,   GWL_STYLE); 

		dwStyle		&=		~WS_MAXIMIZEBOX; 
		dwStyle		&=		~WS_MINIMIZEBOX; 
		dwStyle		&=		~WS_MINIMIZEBOX; 
		//dwStyle		&=		~WS_SYSMENU; 
		dwStyle		&=		~WS_THICKFRAME;
		SetWindowLong(mainWnd,GWL_STYLE,dwStyle);  

		mWindowProcBackup = (WinProc)GetWindowLong(mainWnd,GWL_WNDPROC);
		SetWindowLong(mainWnd, GWL_WNDPROC, (LONG)(&windowMsg));

        //----------------------------------------------------

        //@��������
        mMainScene  = mEngineMain->createScene("MainSceneManager","MainCamera");
        mMainGui    = mMainScene->createGui(
				"resources.xml","core.xml",
				FontManager::getInstance().getTrueFontName(),
				mPointer,
				mFont
			);
		mMainScene->getXmlSerializer()->createSceneContent();
        
        mMainScene->setUnitScale(0.01f);

        //----------------------------------------------------

		//@�ر�treeϵͳ�� �����ٶ�
		ClientMain::getInstance().getEngine()->lockTreeManager();

		//----------------------------------------------------

        return result;
    }
    //-----------------------------------------------------------------------
    Bool ClientMain::unLoadEngine()
    {
		//FUNDETECTION(__MG_FUNC__);
        Bool result = false;

        if ( mEngineMain )
        {
            result = mEngineMain->uninitialize();
        }

        mEngineDllLoader.unload();
        return result;
    }

    //-----------------------------------------------------------------------
    void ClientMain::setConsole( Bool console )
    {
        mConsole = console;
    }

    //-----------------------------------------------------------------------
    Bool ClientMain::isConsole()
    {
        return mConsole;
    }

    //-----------------------------------------------------------------------
	MG::Bool ClientMain::_initialize()
	{
		EnableMemLeakCheck();

		_CrtSetBreakAlloc(130);

        // ��־ϵͳ
		LogSystem::getInstance().setGameLogicLogPath("log//client");
		LogSystem::getInstance().setSysLogPath("log//client");

        LogSystem::getInstance().setEnableConsole(true);
        LogSystem::getInstance().setSaveToFile(true);

#ifdef _DEBUG
		LogSystem::getInstance().setLogLevel( out_max );
#endif

		////////////////////////////////////////////////////////////////////////////////////////////

		// ���ش����Դ��
		mPackManager->load();

		////////////////////////////////////////////////////////////////////////////////////////////

		if ( GameSettingManager::getInstance().initialize(L"Config\\ClientSetting.ini") )
		{
			if ( GameSettingManager::getInstance().restoreInitConfig() == false )
			{
				MG::MsgBox::show("��ȡ��Ϸ�����ļ�ʧ��","Error");
				return false;
			}
		}
		else
		{
			MG::MsgBox::show("��ʼ����Ϸ�����ļ�ʧ��","Error");
			return false;
		}

		//��Ϸ�ű���ʼ��
		if ( mLuaMgr->initialize() == false )
		{
			MG::MsgBox::show("�ű���ʼ��ʧ��","Error");
			return false;
		}
		// MG_CN_MODIFY
		// ��lua����FileSystem.
		if (mExPackManager)
		{
			mLuaMgr->setPackManager(mExPackManager);
		}

		//��Ϸ�������
		if ( loadEngine() == false )
		{
			MG::MsgBox::show("��������ʧ��","Error");
			return false;
		}

		//��Ϸ�������
		if ( ClientNetApplyManager::getInstance().initialize() == false )
		{
			MG::MsgBox::show("��ʼ������ʧ��","Error");
			return false;
		}

        //��Ϸ���ܼ���
        if ( GameMain::getInstance().initialize(mExPackManager) == false )
        {
            MG::MsgBox::show("��ʼ����Ϸ����ʧ��","Error");
            return false;
        }

		return true;
	}

    //-----------------------------------------------------------------------
	void ClientMain::_run()
	{
        // ��ʼ������Ϸ    
        GameMain::getInstance().run();

        // ��ʼ����
		mCurrUpdateTicks = GetTickCount() * 0.001;
		mLastUpdateTicks = mCurrUpdateTicks;
		mUpdateDelta = 0.0;
		while( mStopUpdateDirty == false )
		{
			mCurrUpdateTicks = GetTickCount() * 0.001;
			mUpdateDelta = mCurrUpdateTicks - mLastUpdateTicks;
			mLastUpdateTicks = mCurrUpdateTicks;

			if ( update( mUpdateDelta ) == false )
			{
				//MG::MsgBox::show("��Ϸ���´���","Error");
				return;
			}				
		}
	}

    //-----------------------------------------------------------------------
	MG::Bool ClientMain::_uninitialize()
	{
		::ShowCursor(true);

        GameMain::getInstance().uninitialize();

		//FUNDETECTION(__MG_FUNC__);
		ClientNetApplyManager::getInstance().unInitialize();

		//ж������
		unLoadEngine();

		//ж����Ϸ�ű�
		mLuaMgr->unInitialize() ;

		// MG_CN_MODIFY
		MG_SAFE_DELETE(mExPackManager);
		MG_SAFE_DELETE(mPackManager);

		return true;
	}

    //-----------------------------------------------------------------------
	LRESULT CALLBACK ClientMain::windowMsg( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
	{
		switch(message)
		{
			case WM_SYSCOMMAND:
				{
					switch(wParam)
					{
					case SC_MINIMIZE:
					case SC_MAXIMIZE:
						return TRUE;
					}
					break;
				}
			case WM_SIZE:
				return TRUE;
			case WM_SIZING:
				return TRUE;
		}
		return (CallWindowProc((WinProc)mWindowProcBackup, hwnd, message, wParam, lParam));
	}

   
}


