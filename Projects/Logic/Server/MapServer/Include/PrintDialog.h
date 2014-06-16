/******************************************************************************/
#ifndef _PRINT_DIALOG_H_
#define _PRINT_DIALOG_H_
/******************************************************************************/

#include "Singleton.h"
#include "MapServerPreqs.h"
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

		void printMap();
		void printPlayerList();
		void printPlayerCharacterList();

	private:
		Int printBigRegionList(MyListView* listView_Map, std::map<RegionIdType, SBigRegionObject*>* allRegionObjectInstanceList, Int index);

	private:
		void printMapRegionObj(MyListView* listView, Int index, SInstanceRegion* realRegion);


	public:
		static LRESULT CALLBACK windowMapMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK windowPlayerMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK windowPlayerCharacterMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND mMapDlg;
		HWND mPlayerDlg;
		HWND mPlayerCharacterDlg;

	public:
		
	};

	static WinProc mWindowProcMap;
	static WinProc mWindowProcPlayer;
	static WinProc mWindowProcPlayerCharacter;

}

#endif	//_PRINT_DIALOG_H_