
/******************************************************************************/
#ifndef _MY_LIST_VIEW_H_
#define _MY_LIST_VIEW_H_
/******************************************************************************/

#include <windows.h>
#include <commctrl.h>

/******************************************************************************/

namespace MG
{
	class MyListView
	{
	public:
		MyListView();
		MyListView(HWND parent, int ctlid);
		virtual ~MyListView();

		//  获取列表控件句柄
		void GetListViewHandle(HWND parent, int ctlid);

		//  插入列。index索引，txt显示标题，size列宽度
		void InsertColumn(int index, const char* txt, int size, int fmt = LVCFMT_RIGHT);

		//  删除列
		void DeleteColum(int index);

		//  删除所有列
		void DeleteAllColum();

		//  插入一行记录
		int InsertItem(int index = 0);

		//  设置记录内容，index索引，col列索引，txt内容
		void SetItemTextStr(int index, int col, const char* txt);
		void SetItemTextInt(int index, int col, const int txt);
		void SetItemTextU64(int index, int col, const U64 txt);
		void SetItemTextStr16(int index, int col, const wchar_t* txt);

		//  删除所有记录
		void DeleteAllItem();

		//  设置扩展
		void SetExtended(long ext = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE);

	public:
		HWND        m_hwnd;
		int         m_ColIndex;
	};


}

#endif	//_MY_LIST_VIEW_H_

