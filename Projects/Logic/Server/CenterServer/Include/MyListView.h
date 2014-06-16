
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

		//  ��ȡ�б�ؼ����
		void GetListViewHandle(HWND parent, int ctlid);

		//  �����С�index������txt��ʾ���⣬size�п��
		void InsertColumn(int index, const char* txt, int size, int fmt = LVCFMT_RIGHT);

		//  ɾ����
		void DeleteColum(int index);

		//  ɾ��������
		void DeleteAllColum();

		//  ����һ�м�¼
		int InsertItem(int index = 0);

		//  ���ü�¼���ݣ�index������col��������txt����
		void SetItemTextStr(int index, int col, const char* txt);
		void SetItemTextInt(int index, int col, const int txt);
		void SetItemTextU64(int index, int col, const U64 txt);
		void SetItemTextStr16(int index, int col, const wchar_t* txt);

		//  ɾ�����м�¼
		void DeleteAllItem();

		//  ������չ
		void SetExtended(long ext = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE);

	public:
		HWND        m_hwnd;
		int         m_ColIndex;
	};


}

#endif	//_MY_LIST_VIEW_H_

