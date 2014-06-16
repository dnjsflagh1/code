#ifndef _JCH_SKIN_BTN_H
#define _JCH_SKIN_BTN_H
#include "MemFileDef.h"
#pragma once
enum SkinButtonState
{
	SkinButton_Disable	= 0,		// 按钮不可用
	SkinButton_MouseOut	= 1,		// 鼠标不在按钮上
	SkinButton_MouseIn	= 2,		// 鼠标在按钮上
	SkinButton_MouseDown	= 3,	// 鼠标按下
	SkinButton_StateCount,
};


class CSkinButton : public CButton
{
	DECLARE_DYNAMIC(CSkinButton)

public:
	CSkinButton();
	virtual ~CSkinButton();

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnable(BOOL bEnable);

	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

public:
	// 从资源中载入四态位图
	BOOL SetBitmapsByRes(UINT nBitmapID, CRect* pDisable, CRect* pMouseOut, CRect* pMouseIn, CRect* pMouseDown, DWORD dwColorKey =0x00FF00FF,BOOL bDrawText = FALSE);
	BOOL SetBitmapsByRes(LPCTSTR pBitmapName, CRect* pDisable, CRect* pMouseOut, CRect* pMouseIn, CRect* pMouseDown,  DWORD dwColorKey =0x00FF00FF,BOOL bDrawText = FALSE);
	BOOL SetBitmapsByFile(const char* pFileName,Memfile xFunc, CRect* pDisable, CRect* pMouseOut, CRect* pMouseIn, CRect* pMouseDown,  DWORD dwColorKey =0x00FF00FF,BOOL bDrawText = FALSE);
	// 设置按钮区域
	void SetRegion(HBITMAP hBitmap, CRect* pBitmapArea, DWORD dwColorKey = 0x00FF00FF);

	void SetIsSelected(BOOL bSelected);
	BOOL GetIsSelected(void);

private:
	HBITMAP		_bmpBackGround;
	CRect		_rcArea[SkinButton_StateCount];
	UINT		_nCurrentState;
	BOOL		_bDrawText;
	BOOL		_bSelected;
	DWORD		_bmpColorKey;
};

#endif