/******************************************************************************/
#ifndef _PRINT_DIALOG_H_
#define _PRINT_DIALOG_H_
/******************************************************************************/

#include "Singleton.h"
#include "FrontServerPreqs.h"
#include "MyListView.h"

/******************************************************************************/

typedef LRESULT (__stdcall *WinProc)(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

/******************************************************************************/
namespace MG
{
	class PrintDialog
	{
	public:
		PrintDialog();
		~PrintDialog();
		SINGLETON_INSTANCE(PrintDialog);

	public:
		void createMainDialog();

		void printPlayerList();


	private:
		void printSiglePlayerInfo(Int index, SPlayerPtr player);
		void printSigleGeneralInfo(Int index, SPlayerCharacter* general);

		void clearPlayerListView();
		void clearGeneralListView();

	public:
		static LRESULT CALLBACK windowPlayerMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK windowPlayerCharacterMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND mPlayerDlg;
		HWND mPlayerCharacterDlg;


		MyListView mListView_Player;
		MyListView mListView_PlayerCharacter;
	};


	static WinProc mWindowProcPlayer;
	static WinProc mWindowProcPlayerCharacter;
}

#endif	//_PRINT_DIALOG_H_