//*************************************************************************************
#ifndef _UICLANCREATE_H_
#define _UICLANCREATE_H_
//*************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
#include "CharacterRandNameCsv.h"
#include "ColorResConfig.h"
//*************************************************************************************
namespace MG
{
#define		Max_XZ			4
#define		COLUMN_COUNT	5
#define		COLOR_COUNT		16
	struct CreateClanResInfo;
	struct CreateListRowBtnInfo
	{
		U32		row;
		U32		column;
		Str16	text;
	};
    class  UIClanCreate:public UIObject
    {
    public:
        UIClanCreate();
        virtual ~UIClanCreate();
        SINGLETON_INSTANCE(UIClanCreate);
    public:
        virtual void setEvent();
		virtual void restore();
		virtual bool openGui();
		virtual void update(Flt delta);

		//uimessagebox�ص�
		static void onNotificateOK(void* arg);
		static void onNotificateCancle(void* arg);

    protected:
        static void onClickCreateClan(void* widget);
		static void onClickReset(void* widget);
		static void onClickRandom(void* widget);
		static void onClickSelectBtn(void* widget);

	
		static void OnLeftXZClick(void* widget);
		static void OnRightXZClick(void* widget);
		static void OnLeftBackClick(void* widget);
		static void OnRightBackClick(void* widget);
		static void OnLeftFlagClick(void* widget);
		static void OnRightFlagClick(void* widget);
		static void OnOpenJWList(void* widget, void* newWidget);
		static void OnOpenClanNameList(void* widget, void* newWidget);
		static void OnCloseJWList(void* widget, void* newWidget);
		static void OnCloseClanNameLsit(void* widget, void* newWidget);

		static void OnSelectJWBtn(void* wiget);
		static void OnSelectClanNameBtn(void* widget);

		static void	OnClickBackColor(void* widget);
		static void	OnClickFlagColor(void* widget);

    protected:
		void		initBackColorImgs();			//���ÿ���ѡ�����屳����ɫ��imag����ɫֵ
		void		initFlagColorImgs();
		void		initBackArtResInfo();
		void		initFlagArtResInfo();
		void		initJWList();
		void		initClanNameList();
        void        createClan();
		void        initFamily();
		void		resetClanInfo();

		
		void		setCLanImgSettingVisible();
		void		openJWList();
		void		openClanNameList();
		void		closeJWList();
		void		closeClanNameList();
		void		randomSetting();
		void		randomJW();
		void		randomClan();

		void		modifyXZIndex(U32 index);
		void		modifyBackIndex(U32 index );
		void		modifyFlagIndex(U32 index );

		void		updateXZPartUI(U32 index, bool immdiately = false, Flt speed = 0.5f); //���ѡ�������ٶȣ������ʱ��ֱ�Ӷ�λ��Ŀ��
		void		updateBackPartUI(U32 index);
		void		updateFlagPartUI(U32 index);
		void		setJWContent(Str16 text);
		void		setClanNameContent(Str16 text);
		void		updateSelectBackColor();
		void		updateSelectFlagColor();

	private:
		U32			mSelectXZ;
		std::map<U32, ArtIconResCsvInfo*> mBackArtResInfoList;  //����ͼƬ��Դ
		std::map<U32, ArtIconResCsvInfo*> mFlagArtResInfoList;  //���ͼƬ��Դ
		std::vector< CharacterRandNameCsvInfo*> *mJWNameList;	//���������б�
		std::vector<CharacterRandNameCsvInfo*> *mClanNameList;	//���������б�
		std::map<U32, ColorResCsvInfo*> mBackColorInfoList;		//������ɫѡ���б�
		std::map<U32, ColorResCsvInfo*> mFlagColorInfoList;		//��־��ɫѡ���б�

		U32			mSelectBackIndex;
		U32			mSelectFlagIndex;
		U32			mSelectBackColorIndex;
		U32			mSelectFlagColorIndex;
	private:
		void		updateJWBtnState(U32 row, U32 column);     //���¶����У������е�����״̬
		void		updateClanBtnState(U32 row, U32 column);
		U32			mSelectJWRow;							  //��¼֮ǰѡ����
		U32			mSelectJWColumn;
		U32			mSelectClanRow;
		U32			mSelectClanColumn;
    };
}


#endif