// FileSystemTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "FileSystemTreeCtrl.h"
#include "SortStringArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileSystemTreeCtrl

CFileSystemTreeCtrl::CFileSystemTreeCtrl()
{
	m_strRoot = "";
}

CFileSystemTreeCtrl::~CFileSystemTreeCtrl()
{
	m_imgList.Detach();
}


BEGIN_MESSAGE_MAP(CFileSystemTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CFileSystemTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSystemTreeCtrl message handlers

BOOL CFileSystemTreeCtrl::DisplayTree(LPCTSTR strRoot, BOOL bFiles)
{
	DWORD dwStyle = GetStyle();   // read the windowstyle
	if ( dwStyle & TVS_EDITLABELS ) 
	{
		// Don't allow the user to edit ItemLabels
		ModifyStyle( TVS_EDITLABELS , 0 );
	}
	
	DeleteAllItems();

	if ( !GetSysImgList() )
		return FALSE;
    m_bFiles = bFiles;  // if TRUE, Display Path- and Filenames 
	if ( strRoot == NULL || strRoot[0] == '\0' )
	{
		if ( !DisplayDrives() )
			return FALSE;
		m_strRoot = "";
	}
    else
	{
		m_strRoot = strRoot;
		if ( m_strRoot.Right(1) != '\\' )
			m_strRoot += "\\";
		HTREEITEM hParent = AddItem( TVI_ROOT, m_strRoot );
		DisplayPath( hParent, strRoot );
	}
	return TRUE;	
}
/////////////////////////////////////////////////
BOOL CFileSystemTreeCtrl::GetSysImgList()
{
	SHFILEINFO shFinfo;
	HIMAGELIST hImgList = NULL;

	if ( GetImageList( TVSIL_NORMAL ) )
		m_imgList.Detach();
	
	hImgList = (HIMAGELIST)SHGetFileInfo( "C:\\",
							  0,
							  &shFinfo,
							  sizeof( shFinfo ),
							  SHGFI_SYSICONINDEX | 
							  SHGFI_SMALLICON );
	if ( !hImgList )
	{
		m_strError = "Cannot retrieve the Handle of SystemImageList!";
		return FALSE;
	}

	m_imgList.m_hImageList = hImgList;    
    
	SetImageList( &m_imgList, TVSIL_NORMAL );
	return TRUE;
}

BOOL CFileSystemTreeCtrl::DisplayDrives()
{
	DeleteAllItems();
	char  szDrives[128];
	char* pDrive;

	if ( !GetLogicalDriveStrings( sizeof(szDrives), szDrives ) )
	{
		m_strError = "Error Getting Logical DriveStrings!";
		return FALSE;
	}

	pDrive = szDrives;
	while( *pDrive )
	{
		HTREEITEM hParent = AddItem( TVI_ROOT, pDrive );
		if ( FindSubDir( pDrive ) )
			InsertItem( "", 0, 0, hParent );
		pDrive += strlen( pDrive ) + 1;
	}
	return TRUE;
}

void CFileSystemTreeCtrl::DisplayPath(HTREEITEM hParent, LPCTSTR strPath)
{
	CFileFind find;
	CString   strPathFiles = strPath;
	BOOL      bFind;
	CSortStringArray strDirArray;
	CSortStringArray strFileArray;
	
	if ( strPathFiles.Right(1) != "\\" )
		strPathFiles += "\\";
	strPathFiles += "*.*";

	bFind = find.FindFile( strPathFiles );

	while ( bFind )
	{
		bFind = find.FindNextFile();
		if ( find.IsDirectory() && !find.IsDots() )
		{		
			strDirArray.Add( find.GetFilePath() );
		}
		if ( !find.IsDirectory() && m_bFiles )
			strFileArray.Add( find.GetFilePath() );
	}
    
	strDirArray.Sort();
	SetRedraw( FALSE );
	CWaitCursor wait;
    
	for ( int i = 0; i < strDirArray.GetSize(); i++ )
	{
			HTREEITEM hItem = AddItem( hParent, strDirArray.GetAt(i) );
			if ( FindSubDir( strDirArray.GetAt(i) ) )
				InsertItem( "", 0, 0, hItem );
	}

	if ( m_bFiles )
	{
		strFileArray.Sort();
		for (int i = 0; i < strFileArray.GetSize(); i++ )
		{
			HTREEITEM hItem = AddItem( hParent, strFileArray.GetAt(i) );
			
		}
	}
	SetRedraw( TRUE );
}

HTREEITEM CFileSystemTreeCtrl::AddItem(HTREEITEM hParent, LPCTSTR strPath)
{
	SHFILEINFO shFinfo;
	int iIcon, iIconSel;
    CString    strTemp = strPath;
    
	if ( strTemp.Right(1) != '\\' )
		 strTemp += "\\";
	if ( !SHGetFileInfo( strTemp,
						0,
						&shFinfo,
						sizeof( shFinfo ),
						SHGFI_ICON | 
					    SHGFI_SMALLICON ) )
	{
		m_strError = "Error Gettting SystemFileInfo!";
		return NULL;
	}
	iIcon = shFinfo.iIcon;
	DestroyIcon( shFinfo.hIcon );

	if ( !SHGetFileInfo( strTemp,
						0,
						&shFinfo,
						sizeof( shFinfo ),
						SHGFI_ICON | SHGFI_OPENICON |
					    SHGFI_SMALLICON ) )
	{
		m_strError = "Error Gettting SystemFileInfo!";
		return NULL;
	}
	iIconSel = shFinfo.iIcon;
	DestroyIcon( shFinfo.hIcon );

	if ( strTemp.Right(1) == "\\" )
		strTemp.SetAt( strTemp.GetLength() - 1, '\0' );
	
	if ( hParent == TVI_ROOT )
		return InsertItem( strTemp, iIcon, iIconSel, hParent );
	
	return InsertItem( GetSubPath( strTemp ), iIcon, iIconSel, hParent );
}

LPCTSTR CFileSystemTreeCtrl::GetSubPath(LPCTSTR strPath)
{
	static CString strTemp;
	int     iPos;

	strTemp = strPath;
	if ( strTemp.Right(1) == '\\' )
		 strTemp.SetAt( strTemp.GetLength() - 1, '\0' );
	iPos = strTemp.ReverseFind( '\\' );
	if ( iPos != -1 )
	    strTemp = strTemp.Mid( iPos + 1);

	return (LPCTSTR)strTemp;
}

BOOL CFileSystemTreeCtrl::FindSubDir( LPCTSTR strPath)
{
	CFileFind find;
	CString   strTemp = strPath;
	BOOL      bFind;

	if ( strTemp[strTemp.GetLength()-1] == '\\' )
		strTemp += "*.*";
	else
		strTemp += "\\*.*";
		
	bFind = find.FindFile( strTemp );
	
	while ( bFind )
	{
		bFind = find.FindNextFile();

		if ( find.IsDirectory() && !find.IsDots() )
		{
			return TRUE;
		}
		if ( !find.IsDirectory() && m_bFiles && !find.IsHidden() )
			return TRUE;
	}
	return FALSE;
}

void CFileSystemTreeCtrl::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	CString strPath;
	 
	if ( pNMTreeView->itemNew.state & TVIS_EXPANDED )
	{
		ExpandItem( pNMTreeView->itemNew.hItem, TVE_EXPAND );
	}
	else
	{
		HTREEITEM hChild = GetChildItem( pNMTreeView->itemNew.hItem );
				
		while ( hChild ) 
		{
			DeleteItem( hChild );
			hChild = GetChildItem( pNMTreeView->itemNew.hItem );
		}
		InsertItem( "", pNMTreeView->itemNew.hItem );
	}

	*pResult = 0;
}

CString CFileSystemTreeCtrl::GetFullPath(HTREEITEM hItem)
{
	// get the Full Path of the item
	CString strReturn;
	CString strTemp;
	HTREEITEM hParent = hItem;

	strReturn = "";

	while ( hParent )
	{
		
		strTemp  = GetItemText( hParent );
		strTemp += "\\";
		strReturn = strTemp + strReturn;
		hParent = GetParentItem( hParent );
	}
    
	strReturn.TrimRight( '\\' );

    return strReturn;

}

BOOL CFileSystemTreeCtrl::SetSelPath(LPCTSTR strPath)
{
	// Setting the Selection in the Tree
	HTREEITEM hParent  = TVI_ROOT;
	int       iLen    = strlen(strPath) + 2;
	char*     pszPath = new char[iLen];
	char*     pPath   = pszPath;
	BOOL      bRet    = FALSE;
    
	if ( !IsValidPath( strPath ) )
	{
		delete [] pszPath; // this must be added 29.03.99
		return FALSE;
	}
		
	strcpy( pszPath, strPath );
	strupr( pszPath );
	
	if ( pszPath[strlen(pszPath)-1] != '\\' )
		strcat( pszPath, "\\" );
    
	int iLen2 = strlen( pszPath );
	
	for (WORD i = 0; i < iLen2; i++ )
	{
		if ( pszPath[i] == '\\' )
		{
			SetRedraw( FALSE );
			pszPath[i] = '\0';
			hParent = SearchSiblingItem( hParent, pPath );
			if ( !hParent )  // Not found!
				break;
			else
			{
				UINT uState;
				uState = GetItemState( hParent, TVIS_EXPANDEDONCE );
				if ( uState )
				{
					Expand( hParent, TVE_EXPAND );
					Expand( hParent, TVE_COLLAPSE | TVE_COLLAPSERESET );
					InsertItem("", hParent ); // insert a blank child-item
					Expand( hParent, TVE_EXPAND ); // now, expand send a notification
				}
				else
					Expand( hParent, TVE_EXPAND );
			}
			pPath += strlen(pPath) + 1;
		}
	}

	delete [] pszPath;
	
	if ( hParent ) // Ok the last subpath was found
	{		
		SelectItem( hParent ); // select the last expanded item
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}
	
	SetRedraw( TRUE );

    return bRet;
}

HTREEITEM CFileSystemTreeCtrl::SearchSiblingItem( HTREEITEM hItem, LPCTSTR strText)
{
	HTREEITEM hFound = GetChildItem( hItem );
	CString   strTemp;
	while ( hFound )
	{
		strTemp = GetItemText( hFound );
        strTemp.MakeUpper();
		if ( strTemp == strText )
			return hFound;
		hFound = GetNextItem( hFound, TVGN_NEXT );
	}

	return NULL;
}


void CFileSystemTreeCtrl::ExpandItem(HTREEITEM hItem, UINT nCode)
{	
	CString strPath;
	
	if ( nCode == TVE_EXPAND )
	{
		HTREEITEM hChild = GetChildItem( hItem );
		while ( hChild )
		{
			DeleteItem( hChild );
			hChild = GetChildItem( hItem );
		}
        
		strPath = GetFullPath( hItem );
		DisplayPath( hItem, strPath );
	}
}

BOOL CFileSystemTreeCtrl::IsValidPath(LPCTSTR strPath)
{
	// This function check the Pathname
	
	HTREEITEM hChild;
	CString   strItem;
	CString   strTempPath = strPath;
	BOOL      bFound = FALSE;
	CFileFind find;

	hChild = GetChildItem( TVI_ROOT );
	strTempPath.MakeUpper();
	strTempPath.TrimRight('\\');

	while ( hChild )
	{
		strItem = GetItemText( hChild );
		strItem.MakeUpper();
		if ( strItem == strTempPath.Mid( 0, strItem.GetLength() ) )
		{
			bFound = TRUE;
			break;
		}
		hChild = GetNextItem( hChild, TVGN_NEXT );
	}
    
	if ( !bFound )
		return FALSE;

	strTempPath += "\\nul";
	if ( find.FindFile( strTempPath ) )
		return TRUE;
     
	return FALSE;
}