/******************************************************************************/
#ifndef _GUI_H_
#define _GUI_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IGui.h"
#include <OIS\OISMouse.h>
#include <OIS\OISKeyboard.h>
/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //��Ϸ�������
    /******************************************************************************/
    class Layout : public ILayout
    {
        friend GuiDgElmPoolEx;
        friend GuiDgElmPoolOut;
    public:
                                        Layout(Str8 fileName);
        virtual                         ~Layout();
    public:
        virtual IButton*                getButton( const Str8 name );
        virtual IEdit*                  getEdit( const Str8 name );
        virtual IForm*                  getForm( const Str8 name );
        virtual IImage*                 getImage( const Str8 name );
        virtual IProgress*              getProgress( const Str8 name );
        virtual IText*                  getText( const Str8 name );
        virtual IViewScroll*            getViewScroll( const Str8 name );
        virtual IWidget*                getWidget( const Str8 name );
        virtual IList*                  getList( const Str8 name );
        virtual ITab*                   getTab( const Str8 name );
        virtual ITabItem*               getTabItem( const Str8 name );
        virtual IComboBox*              getComboBox( const Str8 name );
        virtual IMixTree*               getMixTree( const Str8 name );
        virtual IRollingText*           getRollingText( const Str8 name );
        virtual IMixList*               getMixList( const Str8 name );
        virtual IMixListRow*            getMixListRow( const Str8 name );
		virtual	IHScroll*				getHScroll( const Str8 name );
		virtual	IVScroll*				getVScroll( const Str8 name );
		virtual ITimeText*				getTimeText( const Str8 name );


        virtual Bool                    isMouseInUI();
    public:
        virtual Bool                    isVisible();
        virtual void                    setVisible(Bool bVisible);

    protected:
               void                     shunDown();              
    protected:
        std::vector<MyGUI::Widget*>     mElements;
        MyGUI::Widget*                  mMainWidget;

    };


	/******************************************************************************/
	//��Ϸ�û���������
	/******************************************************************************/
    class Gui : public IGui , public OIS::KeyListener, public OIS::MouseListener
	{
	public:
                                        Gui(CChar* resourceFileName, CChar* FileName, Scene* scene);
        virtual                         ~Gui();

	public:
		
        virtual     Layout*             loadLayOut(const Str8 fileName);
        virtual     Layout*             getLayOut(const Str8 fileName);

		std::map<Str, Layout*>&			getAllLayOuts() { return mLayouts; }
										
    public:
					void				init(Str8 fontName, IPointer*& pIPointer, IFont*& pIFont);
                    void                preUpdate();
					void				update(Flt delta);

        virtual     IText*              getText(const MGTextDs* pTds, CoordI coord, std::wstring caption, Bool isTop = false);
        virtual     IText*              getText(const MGTextDs* pTds, VecI2 pos, VecI2 size, std::wstring caption, Bool isTop = false);
        virtual     IText*              getText(const MGTextDs* pTds, Int left, Int top, Int width, Int height, std::wstring caption, Bool isTop = false);

        virtual     IEdit*              getEdit(const MGTextDs* pTds, CoordI coord, std::wstring caption, Bool isTop = false);
        virtual     IEdit*              getEdit(const MGTextDs* pTds, VecI2 pos, VecI2 size, std::wstring caption, Bool isTop = false);
        virtual     IEdit*              getEdit(const MGTextDs* pTds, Int left, Int top, Int width, Int height, std::wstring caption, Bool isTop = false);

        virtual     IProgress*          getProgress(CoordI coord, U32 range, U32 position, Bool isTop = false);
        virtual     IProgress*          getProgress(VecI2 pos, VecI2 size, U32 range, U32 position, Bool isTop = false);
        virtual     IProgress*          getProgress(Int left, Int top, Int width, Int height, U32 range, U32 position, Bool isTop = false);

        virtual     IImage*             getImage(CoordI coord, std::string imagename, Bool isTop = false);
        virtual     IImage*             getImage(VecI2 pos, VecI2 size, std::string imagename, Bool isTop = false);
        virtual     IImage*             getImage(Int left, Int top, Int width, Int height, std::string imagename, Bool isTop = false);

        virtual     IImage*             getImage(CoordI coord, std::string imagenrecouse, std::string group, std::string item, Bool isTop = false);
        virtual     IImage*             getImage(VecI2 pos, VecI2 size, std::string imagenrecouse, std::string group, std::string item, Bool isTop = false);
        virtual     IImage*             getImage(Int left, Int top, Int width, Int height, std::string imagenrecouse, std::string group, std::string item, Bool isTop = false);
        
        virtual     void                destroyImage(IImage*& pImage);
        virtual     void                destroyText(IText*& pText);
        virtual     void                destroyEdit(IEdit*& pEdit);
        virtual     void                destroyProgress(IProgress*& pProgress);
        //ֱ�����
        virtual     void                MGText(const MGTextDs*& pTds, CoordI coord, std::wstring caption, Bool isTop = false);
        virtual     void                MGText(const MGTextDs*& pTds, VecI2 pos, VecI2 size, std::wstring caption, Bool isTop = false);
        virtual     void                MGText(const MGTextDs*& pTds, Int left, Int top, Int width, Int height, std::wstring caption, Bool isTop = false);

        virtual     void                MGEdit(const MGTextDs* pTds, CoordI coord, std::wstring caption, Bool isTop = false);
        virtual     void                MGEdit(const MGTextDs* pTds, VecI2 pos, VecI2 size, std::wstring caption, Bool isTop = false);
        virtual     void                MGEdit(const MGTextDs* pTds, Int left, Int top, Int width, Int height, std::wstring caption, Bool isTop = false);

        virtual     void                MGProgress(CoordI coord, U32 range, U32 position, Bool isTop = false);
        virtual     void                MGProgress(VecI2 pos, VecI2 size, U32 range, U32 position, Bool isTop = false);
        virtual     void                MGProgress(Int left, Int top, Int width, Int height, U32 range, U32 position, Bool isTop = false);

        virtual     void                MGImage(CoordI coord, std::string imagename, Bool isTop = false);
        virtual     void                MGImage(VecI2 pos, VecI2 size, std::string imagename, Bool isTop = false);
        virtual     void                MGImage(Int left, Int top, Int width, Int height, std::string imagename, Bool isTop = false);

        virtual     void                MGImage(CoordI coord, std::string imagenrecouse, std::string group, std::string item, Bool isTop = false);
        virtual     void                MGImage(VecI2 pos, VecI2 size, std::string imagenrecouse, std::string group, std::string item, Bool isTop = false);
        virtual     void                MGImage(Int left, Int top, Int width, Int height, std::string imagenrecouse, std::string group, std::string item, Bool isTop = false);

        //�����ַ����ĳ���,�߶ȡ�
        virtual     U32                 getLengthStr(Str16 src, Str8 fontName = "");
        virtual     U32                 getLengthStr(Str8 src, Str8 fontName = "");
        virtual     U32                 getHeightStrAddBreak(Str16& src, Int width, Str8 fontName = "");
        virtual     U32                 getHeightStrAddBreak(Str8& src, Int width, Str8 fontName = "");
        virtual     U32                 getHeightStr(Str16 src, Int width, Str8 fontName = "");
        virtual     U32                 getHeightStr(Str8 src, Int width, Str8 fontName = "");
        virtual     U32                 getHeightChar(Str8 fontName = "");
        virtual     U32                 getIndexByWidth(Str16 src, U32 width, Str8 fontName = "");
        virtual     U32                 getIndexByWidth(Str8 src, U32 width, Str8 fontName = "");
        //���ͼƬ�ĳ��Ϳ�
        virtual     VecI2               getImageSize(Str8 textureName);
        virtual     VecI2               getImageSize(Str8 imageRecouse, Str8 group, Str8 item);

		virtual     Bool                isMouseCanHoldUI(); 
		virtual     Bool                isKeyCanHoldUI();  
    public://������ͼ�����Ϣ
        virtual     bool                keyPressed( const OIS::KeyEvent &e );
        virtual     bool                keyReleased( const OIS::KeyEvent &e );

        virtual     bool                mouseMoved( const OIS::MouseEvent &e );
        virtual     bool                mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
        virtual     bool                mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );

    public://�鿴��Ϣ
                    void                SeeInfo(Flt delta);
					void                resizeWindow( Ogre::RenderWindow* window);
					void				resizeWindow();

	protected:
        ///������Դ·��
                    Bool                setupResources(const Str fileName);
        ///��ø���Դ·��
                    const std::string&  getRootMedia() { return mRootMedia; }
        //�ͷ��Լ�new�����Ķ���
                    void                clear();
		
    private:
        /// MyGUI����.
        MyGUI::Gui*                     mMyGUI;
        /// MyGUIƽ̨����
        MyGUI::OgrePlatform*            mPlatform;
        /*/// MyGUI���ͳ�ƶ���
        diagnostic::StatisticInfo*      mInfo;
        /// MyGUI��Ͻ������
        diagnostic::InputFocusInfo*     mFocusInfo;*/
        /// ������������
        Scene*                          mScene;
        /** ����Դ·�� */
        Str                             mRootMedia;
        //layout�б�
        std::map<Str , Layout*>         mLayouts;
	};
	
}

/******************************************************************************/

#endif
