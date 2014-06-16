#if !defined(AFX_FILESYSTEMTREECTRL_H__D7BE70A2_8781_11D4_BD73_000021479D21__INCLUDED_)
#define AFX_FILESYSTEMTREECTRL_H__D7BE70A2_8781_11D4_BD73_000021479D21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileSystemTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileSystemTreeCtrl window

class CFileSystemTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CFileSystemTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileSystemTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL SetSelPath( LPCTSTR strPath );
	CString GetFullPath( HTREEITEM hItem );
	LPCTSTR GetSubPath( LPCTSTR strPath );
	BOOL DisplayTree( LPCTSTR strRoot, BOOL bFiles = FALSE );
	virtual ~CFileSystemTreeCtrl();

	// Generated message map functions
protected:
	BOOL IsValidPath( LPCTSTR strPath );
	void ExpandItem( HTREEITEM hItem, UINT nCode );
	HTREEITEM SearchSiblingItem( HTREEITEM hItem, LPCTSTR strText );
	BOOL FindSubDir( LPCTSTR strPath );
	HTREEITEM AddItem( HTREEITEM hParent, LPCTSTR strPath );
	void DisplayPath( HTREEITEM hParent, LPCTSTR strPath );
	BOOL DisplayDrives();
	BOOL m_bFiles;
	CString m_strError;
	BOOL GetSysImgList();
	CImageList m_imgList;
	CString m_strRoot;
	//{{AFX_MSG(CFileSystemTreeCtrl)
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESYSTEMTREECTRL_H__D7BE70A2_8781_11D4_BD73_000021479D21__INCLUDED_)
