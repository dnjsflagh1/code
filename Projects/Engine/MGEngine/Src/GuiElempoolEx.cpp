//****************************************************************************************
#include "stdafx.h"
#include "GuiElempoolEx.h"
#include "Gui.h"

//****************************************************************************************
#define DEIMAGE_NUM_DEFUALT 50
#define DETEXT_NUM_DEFUALT  50
#define DEPROGRESS_NUM_DEFUALT 50
#define DEEDIT_NUM_DEFUALT  30
//****************************************************************************************
namespace MG
{
    GuiDgElmPoolOut::GuiDgElmPoolOut(std::string layoutName)
        :mCurTextNum(0)
        ,mCurImageNum(0)
        ,mCurEditNum(0)
        ,mCurProgressNum(0)
        ,mParent(NULL)
    {
		Initialize(layoutName);
    }
    //-----------------------------------------------------------------------
    GuiDgElmPoolOut::~GuiDgElmPoolOut()
    {
        clear();
    }
    //-----------------------------------------------------------------------
    DEImage* GuiDgElmPoolOut::getImage( CoordI coord, std::string imagename )
    {
        DEImage* deImage = NULL;
        //查找free list 是否有空闲。
        if ( mDEImageListFree.size() > 0 )
        {
            deImage = mDEImageListFree.back();
            deImage->setTexture(imagename);
            deImage->setCoord(coord);
            deImage->setVisible(true);

            //加入work list 中
            mDEImageListFree.pop_back();
            mDEImageListWork.push_back(deImage);

            return deImage;
        }
        //如果没有空闲
        //创建image
        MyGUI::ImageBox* image = mParent->mMainWidget->createWidget<MyGUI::ImageBox>(
            "StaticImage",
            MyGUI::IntCoord(coord.left, coord.top, coord.width, coord.height),
            MyGUI::Align(MyGUI::Align::Enum::Default)
            );
        if (image == NULL)
            return NULL;

        //设置纹理
        if ( imagename != "" )
        {
            image->setImageTexture(imagename);
        }
        image->setNeedMouseFocus(false);
        image->setNeedKeyFocus(false);
        image->setInheritsPick(false);

        //放进DEimage中
        deImage = new DEImage();
        deImage->setEGImage(image);

        //将DEimage放入表中
        mDEImageListOut.push_back(deImage);

        //加入work list 中
        mDEImageListWork.push_back(deImage);

        return deImage;
    }
    //-----------------------------------------------------------------------
    DEImage* GuiDgElmPoolOut::getImage( CoordI coord, std::string imagenrecouse, std::string group, std::string item )
    {
        DEImage* deImage = NULL;
        //查找free list 是否有空闲。
        if ( mDEImageListFree.size() > 0 )
        {
            deImage = mDEImageListFree.back();
            deImage->setItemResource(imagenrecouse);
            if ( group != "" )
                deImage->setItemGroup(group);
            if ( item != "" )
                deImage->setItemName(item);
            deImage->setCoord(coord);
            deImage->setVisible(true);

            //加入work list 中
            mDEImageListFree.pop_back();
            mDEImageListWork.push_back(deImage);

            return deImage;
        }
        //创建image
        MyGUI::ImageBox* image = mParent->mMainWidget->createWidget<MyGUI::ImageBox>(
            "StaticImage",
            MyGUI::IntCoord(coord.left, coord.top, coord.width, coord.height),
            MyGUI::Align(MyGUI::Align::Enum::Default)
            );
        if (image == NULL)
            return NULL;

        //设置纹理
        if ( imagenrecouse != "" )
        {
            image->setItemResource(imagenrecouse);
            if ( group != "" )
                image->setItemGroup(group);
            if ( item != "" )
                image->setItemName(item);
        }
        image->setNeedMouseFocus(false);
        image->setNeedKeyFocus(false);
        image->setInheritsPick(false);

        //放进DEimage中
        deImage = new DEImage();
        deImage->setEGImage(image);

        //将DEimage放入表中
        mDEImageListOut.push_back(deImage);
        //加入work list 中
        mDEImageListWork.push_back(deImage);

        return deImage;
    }
    //-----------------------------------------------------------------------
    DEText* GuiDgElmPoolOut::getText( const MGTextDs*& pTds, CoordI coord, std::wstring caption )
    {
        DEText* deText = NULL;
        //查找free list 是否有空闲。
        if ( mDETextListFree.size() > 0 )
        {
            deText = mDETextListFree.back();
            deText->setCoord(coord);
            deText->setCaption(caption);
            deText->setVisible(true);
            //加入work list 中
            mDETextListFree.pop_back();
            mDETextListWork.push_back(deText);

            return deText;
        }
        //创建text
        MyGUI::StaticText* text = mParent->mMainWidget->createWidget<MyGUI::StaticText>(
            "StaticText",
            MyGUI::IntCoord(coord.left, coord.top, coord.width, coord.height),
            MyGUI::Align(MyGUI::Align::Enum::Default)
            );
        if (text == NULL)
            return NULL;

        //设置内容
        if ( caption != L"" )
        {
            text->setCaption(caption);
        }
        text->setNeedKeyFocus(false);
        text->setNeedMouseFocus(false);
        text->setInheritsPick(false);

        //放进DEtext中
        deText = new DEText();
        deText->setEGText(text);

        //将DEtext放入表中
        mDETextListOut.push_back(deText);
        //加入work list 中
        mDETextListWork.push_back(deText);

        return deText;
    }
    //-----------------------------------------------------------------------
    DEEdit* GuiDgElmPoolOut::getEdit( const MGTextDs*& pTds, CoordI coord, std::wstring caption )
    {
        DEEdit* deEdit = NULL;
        //查找free list 是否有空闲。
        if ( mDEEditListFree.size() > 0 )
        {
            deEdit = mDEEditListFree.back();
            deEdit->setCoord(coord);
            deEdit->setCaption(caption);
            deEdit->setVisible(true);
            //加入work list 中
            mDEEditListFree.pop_back();
            mDEEditListWork.push_back(deEdit);

            return deEdit;
        }
        //创建Edit
        MyGUI::Edit* edit = mParent->mMainWidget->createWidget<MyGUI::Edit>(
            "EditEmpty",
            MyGUI::IntCoord(coord.left, coord.top, coord.width, coord.height),
            MyGUI::Align(MyGUI::Align::Enum::Default)
            );
        if (edit == NULL)
            return NULL;

        //设置内容
        if ( caption != L"" )
        {
            edit->setCaption(caption);
        }
        edit->setNeedKeyFocus(false);
        edit->setNeedMouseFocus(false);
        edit->setInheritsPick(false);

        edit->setVisibleHScroll(false);
        edit->setVisibleVScroll(false);
        edit->setEditReadOnly(true);
        edit->setEditStatic(true);
        edit->setEditMultiLine(true);

        //放进DEEdit中
        deEdit = new DEEdit();
        deEdit->setEGEdit(edit);

        //将DEEdit放入表中
        mDEEditListOut.push_back(deEdit);
        //加入work list 中
        mDEEditListWork.push_back(deEdit);

        return deEdit;
    }
    //-----------------------------------------------------------------------
    DEProgress* GuiDgElmPoolOut::getProgress( CoordI coord, U32 range, U32 pos )
    {
        DEProgress* deProgress = NULL;
        //查找free list 是否有空闲。
        if ( mDEProgressListFree.size() > 0 )
        {
            deProgress = mDEProgressListFree.back();
            deProgress->setCoord(coord);
            deProgress->setProgressPosition((pos*1.f)/(range*1.f));
            deProgress->setVisible(true);
            //加入work list 中
            mDEProgressListFree.pop_back();
            mDEProgressListWork.push_back(deProgress);

            return deProgress;
        }
        //创建Progress
        MyGUI::ProgressEx* progress = mParent->mMainWidget->createWidget<MyGUI::ProgressEx>(
            "MGProgress1001",
            MyGUI::IntCoord(coord.left, coord.top, coord.width, coord.height),
            MyGUI::Align(MyGUI::Align::Enum::Default)
            );
        if (progress == NULL)
            return NULL;

        progress->setNeedKeyFocus(false);
        progress->setNeedMouseFocus(false);
        progress->setInheritsPick(false);

        progress->setProgressPosition(pos*1.f/range);

        //放进DEProgress中
        deProgress = new DEProgress();
        deProgress->setEGProgress(progress);

        //将DEProgress放入表中
        mDEProgressListOut.push_back(deProgress);
        //加入work list 中
        mDEProgressListWork.push_back(deProgress);

        return deProgress;
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolOut::MGText( const MGTextDs*& pTds, CoordI coord, std::wstring caption )
    {
        if ( mCurTextNum++ < mDETextList.size() )
        {
            DEText* tempText = mDETextList[mCurTextNum-1] ;
            tempText->setCoord(coord);
            tempText->setCaption(caption);
            tempText->setVisible(true);

            return;
        }
        //创建text
        MyGUI::StaticText* text = mParent->mMainWidget->createWidget<MyGUI::StaticText>(
            "StaticText",
            MyGUI::IntCoord(coord.left, coord.top, coord.width, coord.height),
            MyGUI::Align(MyGUI::Align::Enum::Default)
            );
        if (text == NULL)
            return ;

        //设置内容
        text->setCaption(caption);
        text->setNeedKeyFocus(false);
        text->setNeedMouseFocus(false);
        text->setInheritsPick(false);

        //放进DEtext中
        DEText* deText = new DEText();
        deText->setEGText(text);

        //将DEtext放入表中
        mDETextList.push_back(deText);
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolOut::MGImage( CoordI coord, std::string imagename )
    {
        if ( mCurImageNum++ < mDEImageList.size() )
        {
            DEImage* tempImage = mDEImageList[mCurImageNum-1];
            tempImage->setCoord(coord);
            if ( imagename != "" )
                tempImage->setTexture(imagename);
            tempImage->setVisible(true);

            return;
        }

        //创建image
        MyGUI::ImageBox* image = mParent->mMainWidget->createWidget<MyGUI::ImageBox>(
            "StaticImage",
            MyGUI::IntCoord(coord.left, coord.top, coord.width, coord.height),
            MyGUI::Align(MyGUI::Align::Enum::Default)
            );
        if (image == NULL)
            return ;

        //设置纹理
        if ( imagename != "" )
            image->setImageTexture(imagename);
        image->setNeedMouseFocus(false);
        image->setNeedKeyFocus(false);
        image->setInheritsPick(false);

        //放进DEimage中
        DEImage* deImage = new DEImage();
        deImage->setEGImage(image);

        //将DEimage放入表中
        mDEImageList.push_back(deImage);
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolOut::MGImage( CoordI coord, std::string imagenrecouse, std::string group, std::string item )
    {
        if ( mCurImageNum++ < mDEImageList.size() )
        {
            DEImage* tempImage = mDEImageList[mCurImageNum-1];
            tempImage->setCoord(coord);
            if ( imagenrecouse != "" )
            {
                tempImage->setTexture(imagenrecouse);
                if ( group != "" )
                    tempImage->setItemGroup(group);
                if ( item != "" )
                    tempImage->setItemName(item);
            }
            tempImage->setVisible(true);

            return;
        }

        //创建image
        MyGUI::ImageBox* image = mParent->mMainWidget->createWidget<MyGUI::ImageBox>(
            "StaticImage",
            MyGUI::IntCoord(coord.left, coord.top, coord.width, coord.height),
            MyGUI::Align(MyGUI::Align::Enum::Default)
            );
        if (image == NULL)
            return ;

        //设置纹理
        if ( imagenrecouse != "" )
        {
            image->setItemResource(imagenrecouse);
            if ( group != "" )
                image->setItemGroup(group);
            if ( item != "" )
                image->setItemName(item);
        }
        image->setNeedMouseFocus(false);
        image->setNeedKeyFocus(false);
        image->setInheritsPick(false);
        
        //放进DEimage中
        DEImage* deImage = new DEImage();
        deImage->setEGImage(image);

        //将DEimage放入表中
        mDEImageList.push_back(deImage);
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolOut::MGEdit( const MGTextDs*& pTds, CoordI coord, std::wstring caption )
    {
        DEEdit* deEdit = NULL;
        if ( mCurEditNum++ < mDEEditList.size() )
        {
            deEdit = mDEEditList[mCurEditNum-1] ;
            deEdit->setCoord(coord);
            deEdit->setCaption(caption);
            deEdit->setVisible(true);

            return;
        }
        //创建Edit
        MyGUI::EditBox* edit = mParent->mMainWidget->createWidget<MyGUI::EditBox>(
            "MGEditEmpty",
            MyGUI::IntCoord(coord.left, coord.top, coord.width, coord.height),
            MyGUI::Align(MyGUI::Align::Enum::Default)
            );
        if (edit == NULL)
            return ;

        //设置内容
        if ( caption != L"" )
        {
            edit->setCaption(caption);
        }
        edit->setNeedKeyFocus(false);
        edit->setNeedMouseFocus(false);
        edit->setInheritsPick(false);

        edit->setVisibleHScroll(false);
        edit->setVisibleVScroll(false);
        edit->setEditReadOnly(true);
        edit->setEditStatic(true);
        edit->setEditMultiLine(true);

        //放进DEEdit中
        deEdit = new DEEdit();
        deEdit->setEGEdit(edit);

        //将DEEdit放入表中
        mDEEditList.push_back(deEdit);
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolOut::MGProgress( CoordI coord, U32 range, U32 pos )
    {
        DEProgress* deProgress = NULL;
        //查找free list 是否有空闲。
        if ( mCurProgressNum++ < mDEProgressList.size() )
        {
            deProgress = mDEProgressList[mCurProgressNum-1];
            deProgress->setCoord(coord);
            deProgress->setProgressPosition(pos*1.f/(range*1.f));
            deProgress->setVisible(true);

            return ;
        }
        //创建Progress
        MyGUI::ProgressEx* progress = mParent->mMainWidget->createWidget<MyGUI::ProgressEx>(
            "MGProgress1001",
            MyGUI::IntCoord(coord.left, coord.top, coord.width, coord.height),
            MyGUI::Align(MyGUI::Align::Enum::Default)
            );
        if (progress == NULL)
            return ;

        progress->setNeedKeyFocus(false);
        progress->setNeedMouseFocus(false);
        progress->setInheritsPick(false);

        progress->setProgressPosition(pos*1.f/range);

        //放进DEProgress中
        deProgress = new DEProgress();
        deProgress->setEGProgress(progress);

        //将DEProgress放入表中
        mDEProgressList.push_back(deProgress);
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolOut::Initialize(std::string layoutName)
    {
        mParent = new Layout(layoutName);
        assert(mParent);

        const MGTextDs* p = NULL;
        for (Int i=0; i<DETEXT_NUM_DEFUALT; i++)
        {
            MGText(p, CoordI(0, 0, 0, 0), L"");
        }

        for (Int i=0; i<DEIMAGE_NUM_DEFUALT; i++)
        {
            MGImage(CoordI(0, 0, 0, 0), "");
        }

        for (Int i=0; i<DEPROGRESS_NUM_DEFUALT; i++)
        {
            MGProgress(CoordI(0, 0, 0, 0), 0, 0);
        }

        for (Int i=0; i<DEEDIT_NUM_DEFUALT; i++)
        {
            MGEdit(p, CoordI(0, 0, 0, 0), L"");
        }
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolOut::clear()
    {
        std::vector<DEText*>::iterator textFront = mDETextList.begin();
        std::vector<DEText*>::iterator textBack = mDETextList.end();
        while (textFront != textBack)
        {
            delete ( *textFront );
            ++textFront;
        }

        std::vector<DEImage*>::iterator imageFront = mDEImageList.begin();
        std::vector<DEImage*>::iterator imageBack = mDEImageList.end();
        while (imageFront != imageBack)
        {
            delete ( *imageFront );
            ++imageFront;
        }

        std::vector<DEEdit*>::iterator editFront = mDEEditList.begin();
        std::vector<DEEdit*>::iterator editBack = mDEEditList.end();
        while (editFront != editBack)
        {
            delete ( *editFront );
            ++editFront;
        }

        std::vector<DEProgress*>::iterator progressFront = mDEProgressList.begin();
        std::vector<DEProgress*>::iterator progressBack = mDEProgressList.end();
        while (progressFront != progressBack)
        {
            delete ( *progressFront );
            ++progressFront;
        }

        std::vector<DEText*>::iterator textFrontOut = mDETextListOut.begin();
        std::vector<DEText*>::iterator textBackOut = mDETextListOut.end();
        while (textFrontOut != textBackOut)
        {
            delete ( *textFrontOut );
            ++textFrontOut;
        }
        
        std::vector<DEImage*>::iterator imageFrontOut = mDEImageListOut.begin();
        std::vector<DEImage*>::iterator imageBackOut = mDEImageListOut.end();
        while (imageFrontOut != imageBackOut)
        {
            delete ( *imageFrontOut );
            ++imageFrontOut;
        }

        std::vector<DEEdit*>::iterator editFrontOut = mDEEditListOut.begin();
        std::vector<DEEdit*>::iterator editBackOut = mDEEditListOut.end();
        while (editFrontOut != editBackOut)
        {
            delete ( *editFrontOut );
            ++editFrontOut;
        }

        std::vector<DEProgress*>::iterator progressFrontOut = mDEProgressListOut.begin();
        std::vector<DEProgress*>::iterator progressBackOut = mDEProgressListOut.end();
        while (progressFrontOut != progressBackOut)
        {
            delete ( *progressFrontOut );
            ++progressFrontOut;
        }

        mDETextList.clear();
        mDETextListOut.clear();
        mDETextListFree.clear();
        mDETextListWork.clear();

        mDEImageList.clear();
        mDEImageListOut.clear();
        mDEImageListFree.clear();
        mDEImageListWork.clear();

        mDEEditList.clear();
        mDEEditListOut.clear();
        mDEEditListFree.clear();
        mDEEditListWork.clear();

        mDEProgressList.clear();
        mDEProgressListOut.clear();
        mDEProgressListFree.clear();
        mDEProgressListWork.clear();  

        delete mParent;
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolOut::preUpdateClear()
    {
        for (Int i=0; i<mCurTextNum; i++)
        {
            mDETextList[i]->setVisible(false);
        }

        for (Int i=0; i<mCurImageNum; i++)
        {
            mDEImageList[i]->setVisible(false);
        }

        for (Int i=0; i<mCurEditNum; i++)
        {
            mDEEditList[i]->setVisible(false);
        }

        for (Int i=0; i<mCurProgressNum; i++)
        {
            mDEProgressList[i]->setVisible(false);
        }

        mCurTextNum = 0;
        mCurImageNum = 0;
        mCurEditNum = 0;
        mCurProgressNum = 0;
    }
    //-----------------------------------------------------------------------
    Bool GuiDgElmPoolOut::removeImage( DEImage*& pImage )
    {
        //在work list中找到指针
        std::list<DEImage* >::iterator iter = mDEImageListWork.begin();
        while (mDEImageListWork.end ()!= iter)
        {
            if ( *iter == pImage )
            {
                //拿出
                mDEImageListWork.erase(iter);
                //放入free
                mDEImageListFree.push_back(pImage);
                //隐藏掉
                pImage->setVisible(false);
                pImage = NULL;
                return true;
            }
        }

        return false;
    }
    //-----------------------------------------------------------------------
    Bool GuiDgElmPoolOut::removeText( DEText*& pText )
    {
        //在work list中找到指针
        std::list<DEText*>::iterator iter = mDETextListWork.begin();
        while (mDETextListWork.end ()!= iter)
        {
            if ( *iter == pText )
            {
                //拿出
                mDETextListWork.erase(iter);
                //放入free
                mDETextListFree.push_back(pText);
                //隐藏掉
                pText->setVisible(false);
                pText = NULL;
                return true;
            }
        }

        return false;
    }
    //-----------------------------------------------------------------------
    Bool GuiDgElmPoolOut::removeEdit( DEEdit*& pEdit )
    {
        //在work list中找到指针
        std::list<DEEdit*>::iterator iter = mDEEditListWork.begin();
        while (mDEEditListWork.end ()!= iter)
        {
            if ( *iter == pEdit )
            {
                //拿出
                mDEEditListWork.erase(iter);
                //放入free
                mDEEditListFree.push_back(pEdit);
                //隐藏掉
                pEdit->setVisible(false);
                pEdit = NULL;
                return true;
            }
        }

        return false;
    }
    //-----------------------------------------------------------------------
    Bool GuiDgElmPoolOut::removeProgress( DEProgress*& pProgress )
    {
        //在work list中找到指针
        std::list<DEProgress*>::iterator iter = mDEProgressListWork.begin();
        while (mDEProgressListWork.end ()!= iter)
        {
            if ( *iter == pProgress )
            {
                //拿出
                mDEProgressListWork.erase(iter);
                //放入free
                mDEProgressListFree.push_back(pProgress);
                //隐藏掉
                pProgress->setVisible(false);
                pProgress = NULL;
                return true;
            }
        }

        return false;
    }
    //-----------------------------------------------------------------------
    GuiDgElmPoolEx::GuiDgElmPoolEx()
    {
    }
    //-----------------------------------------------------------------------
    GuiDgElmPoolEx::~GuiDgElmPoolEx()
    {
        unInitialize();
    }
    //-----------------------------------------------------------------------
    DEImage* GuiDgElmPoolEx::getImage( CoordI coord, std::string imagename, Bool isTop )
    {
        if ( isTop )
            return mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP]->getImage(coord, imagename);
        else
            return mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM]->getImage(coord, imagename);
    }
    //-----------------------------------------------------------------------
    DEImage* GuiDgElmPoolEx::getImage( CoordI coord, std::string imagenrecouse, std::string group, std::string item, Bool isTop )
    {
        if ( isTop )
            return mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP]->getImage(coord, imagenrecouse, group, item);
        else
            return mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM]->getImage(coord, imagenrecouse, group, item);
    }
    //-----------------------------------------------------------------------
    DEText* GuiDgElmPoolEx::getText( const MGTextDs*& pTds, CoordI coord, std::wstring caption, Bool isTop )
    {
        if ( isTop )
            return mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP]->getText(pTds, coord, caption);
        else
            return mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM]->getText(pTds, coord, caption);
    }
    //-----------------------------------------------------------------------
    DEEdit* GuiDgElmPoolEx::getEdit( const MGTextDs*& pTds, CoordI coord, std::wstring caption, Bool isTop )
    {
        if ( isTop )
            return mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP]->getEdit(pTds, coord, caption);
        else
            return mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM]->getEdit(pTds, coord, caption);
    }
    //-----------------------------------------------------------------------
    DEProgress* GuiDgElmPoolEx::getProgress( CoordI coord, U32 range, U32 pos, Bool isTop )
    {
        if ( isTop )
            return mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP]->getProgress(coord, range, pos);
        else
            return mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM]->getProgress(coord, range, pos);
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolEx::MGText( const MGTextDs*& pTds, CoordI coord, std::wstring caption, Bool isTop )
    {
        if ( isTop )
            mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP]->MGText(pTds, coord, caption);
        else
            mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM]->MGText(pTds, coord, caption);
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolEx::MGImage( CoordI coord, std::string imagename, Bool isTop )
    {
        if ( isTop )
            mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP]->MGImage(coord, imagename);
        else
            mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM]->MGImage(coord, imagename);
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolEx::MGImage( CoordI coord, std::string imagenrecouse, std::string group, std::string item, Bool isTop )
    {
        if ( isTop )
            mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP]->MGImage(coord, imagenrecouse, group, item);
        else
            mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM]->MGImage(coord, imagenrecouse, group, item);
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolEx::MGEdit( const MGTextDs*& pTds, CoordI coord, std::wstring caption, Bool isTop )
    {
        if ( isTop )
            mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP]->MGEdit(pTds, coord, caption);
        else
            mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM]->MGEdit(pTds, coord, caption);
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolEx::MGProgress( CoordI coord, U32 range, U32 pos, Bool isTop )
    {
        if ( isTop )
            mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP]->MGProgress(coord, range, pos);
        else
            mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM]->MGProgress(coord, range, pos);
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolEx::preUpdateClear()
    {
         mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP]->preUpdateClear();
         mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM]->preUpdateClear();
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolEx::removeImage( DEImage*& pImage )
    {
        if ( mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP]->removeImage(pImage) )
            return;
        else
            mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM]->removeImage(pImage);
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolEx::removeText( DEText*& pText )
    {
        if ( mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP]->removeText(pText) )
            return;
        else
            mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM]->removeText(pText);
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolEx::removeEdit( DEEdit*& pEdit )
    {
        if ( mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP]->removeEdit(pEdit) )
            return;
        else
            mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM]->removeEdit(pEdit);
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolEx::removeProgress( DEProgress*& pProgress )
    {
        if ( mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP]->removeProgress(pProgress) )
            return;
        else
            mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM]->removeProgress(pProgress);
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolEx::Initialize()
    {
        mGuiDgElmPoolOut[GUIDGELMPOOLOUT_TOP] = new GuiDgElmPoolOut("GuiElemPoolTop.layout");
        mGuiDgElmPoolOut[GUIDGELMPOOLOUT_BOTTOM] = new GuiDgElmPoolOut("GuiElemPoolBottom.layout");
    }
    //-----------------------------------------------------------------------
    void GuiDgElmPoolEx::unInitialize()
    {
        for (Int i=0; i<GUIDGELMPOOLOUT_MAX; i++)
        {
            MG_SAFE_DELETE(mGuiDgElmPoolOut[i]);
        }
    }
}