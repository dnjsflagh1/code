/******************************************************************************/
#ifndef _PRINT_DIALOG_H_
#define _PRINT_DIALOG_H_
/******************************************************************************/

#include "Singleton.h"
#include "CenterServerPreqs.h"
#include "MyListView.h"



/******************************************************************************/
namespace MG
{

	typedef LRESULT (__stdcall *WinProc)(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	/******************************************************************************/
	enum BattleType
	{
		BattleType_Prepare,
		BattleType_Battle,
		BattleType_End
	};
	/******************************************************************************/

	class PrintDialog
	{
	public:
		PrintDialog();
		~PrintDialog();
		SINGLETON_INSTANCE(PrintDialog);

	public:
		void createMainDialog();

		void printCampaign();


	private:
		void printSigleCampaignInfo(MyListView* listView_Campaign, Int index, SCampaign* campaign, BattleType battleType);

		Int getPosInfoStr(std::map<POSITION, ClanArmy*>* posListInfo, std::string* outStr);

	public:
		static LRESULT CALLBACK windowCampaignMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	private:
		HWND mCampaignDlg;
		HWND mPlayerDlg;
		HWND mPlayerCharacterDlg;
	};

	static WinProc mWindowProcCampaign;

}

#endif	//_PRINT_DIALOG_H_