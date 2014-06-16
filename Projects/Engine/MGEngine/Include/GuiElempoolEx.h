//****************************************************************************************
#ifndef _H_GUIEELEMENTPOOLEX_
#define _H_GUIEELEMENTPOOLEX_
//****************************************************************************************
#include "DEWidget.h"
#include "DEImage.h"
#include "DEText.h"
#include "DEEdit.h"
#include "DEProgress.h"
//****************************************************************************************
class MyGUI::Widget;
//****************************************************************************************
namespace MG
{
    //****************************************************************************************
    class Layout;
    //****************************************************************************************
    class GuiDgElmPoolOut
    {
    public:
        GuiDgElmPoolOut(std::string layoutName);
        ~GuiDgElmPoolOut();

    public:
        DEImage*            getImage(CoordI coord, std::string imagename);
        DEImage*            getImage(CoordI coord, std::string imagenrecouse, std::string group, std::string item);
        DEText*             getText(const MGTextDs*& pTds, CoordI coord, std::wstring caption);
        DEEdit*             getEdit(const MGTextDs*& pTds, CoordI coord, std::wstring caption);
        DEProgress*         getProgress(CoordI coord, U32 range, U32 pos);


        void                MGText(const MGTextDs*& pTds, CoordI coord, std::wstring caption);
        void                MGImage(CoordI coord, std::string imagename);
        void                MGImage(CoordI coord, std::string imagenrecouse, std::string group, std::string item);
        void                MGEdit(const MGTextDs*& pTds, CoordI coord, std::wstring caption);
        void                MGProgress(CoordI coord, U32 range, U32 pos);

    public:
        void                preUpdateClear();
        Bool                removeImage(DEImage*& pImage);
        Bool                removeText(DEText*& pText);
        Bool                removeEdit(DEEdit*& pEdit);
        Bool                removeProgress(DEProgress*& pProgress);

    protected:
        void                Initialize(std::string layoutName);
        void                clear();


    protected:
        Layout* mParent;

    private:
        //�������
        std::vector<DEText*> mDETextList;
        std::vector<DEImage*> mDEImageList;
        std::vector<DEEdit*> mDEEditList;
        std::vector<DEProgress*> mDEProgressList;

        //�ⲿ����
        std::vector<DEText*> mDETextListOut;
        std::vector<DEImage*> mDEImageListOut;
        std::vector<DEEdit*> mDEEditListOut;
        std::vector<DEProgress*> mDEProgressListOut;

        //��¼
        Int mCurTextNum;            //��ǰ����ʹ�õ�Text�ؼ���
        Int mCurImageNum;           //��ǰ����ʹ�õ�Image�ؼ���
        Int mCurEditNum;            //��ǰ����ʹ�õ�edit�ؼ���
        Int mCurProgressNum;           //��ǰ����ʹ�õ�Progress�ؼ���

        std::list<DEText* > mDETextListWork;
        std::list<DEText*> mDETextListFree; 

        std::list<DEImage* > mDEImageListWork;
        std::list<DEImage*> mDEImageListFree;

        std::list<DEEdit*> mDEEditListWork;
        std::list<DEEdit*> mDEEditListFree;

        std::list<DEProgress*> mDEProgressListWork;
        std::list<DEProgress*> mDEProgressListFree;
    };
    //****************************************************************************************
    class GuiDgElmPoolEx
    {
    private:
        GuiDgElmPoolEx();
        ~GuiDgElmPoolEx();

    public:
        SINGLETON_INSTANCE(GuiDgElmPoolEx);

    public:
        DEImage*            getImage(CoordI coord, std::string imagename, Bool isTop);
        DEImage*            getImage(CoordI coord, std::string imagenrecouse, std::string group, std::string item, Bool isTop);
        DEText*             getText(const MGTextDs*& pTds, CoordI coord, std::wstring caption, Bool isTop);
        DEEdit*             getEdit(const MGTextDs*& pTds, CoordI coord, std::wstring caption, Bool isTop);
        DEProgress*         getProgress(CoordI coord, U32 range, U32 pos, Bool isTop);


        void                MGText(const MGTextDs*& pTds, CoordI coord, std::wstring caption, Bool isTop);
        void                MGImage(CoordI coord, std::string imagename, Bool isTop);
        void                MGImage(CoordI coord, std::string imagenrecouse, std::string group, std::string item, Bool isTop);
        void                MGEdit(const MGTextDs*& pTds, CoordI coord, std::wstring caption, Bool isTop);
        void                MGProgress(CoordI coord, U32 range, U32 pos, Bool isTop);

    public:
        void                preUpdateClear();
        void                removeImage(DEImage*& pImage);
        void                removeText(DEText*& pText);
        void                removeEdit(DEEdit*& pEdit);
        void                removeProgress(DEProgress*& pProgress);

    public:
        void                Initialize();
        void                unInitialize();
        
       //-------------------------------
    enum
    {
        GUIDGELMPOOLOUT_TOP,
        GUIDGELMPOOLOUT_BOTTOM,

        GUIDGELMPOOLOUT_MAX
    };
    private:
        GuiDgElmPoolOut*    mGuiDgElmPoolOut[GUIDGELMPOOLOUT_MAX];

    };
}

//****************************************************************************************
#endif //_H_GUIEELEMENTPOOLEX_
//****************************************************************************************