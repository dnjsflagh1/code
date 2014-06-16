//******************************************************************************************
#ifndef _DIALOG_H_
#define _DIALOG_H_
//******************************************************************************************
namespace MG
{

#define MAX_DIALOGINFO_NAME_LEN  32
#define MAX_DIALOGINFO_CONTENT_LEN 64
#define MAX_DIALOGINFO_NAME_COUNT 6
//******************************************************************************************
	enum
	{
		id,
		modestnameformyself = 2,
		pridenameformyself,
		respectnameforother,
		slandernameforother,
		specialrespectnameforother,
		specialslandernameforother,
		normaldialog1,
		normaldialog2,
		fightdialog1,
		fightdialog2,
		wounddialog1,
		wounddialog2,
		windialog1,
		windialog2,
		faildialog1,
		faildialog2
	};
	struct DialogInfo
	{
		U32		id;
		Str16	modestNameForSelf;
		Str16	prideNameForSelf;
		Str16	respectNameForOther;
		Str16	slandeNameForOther;
		Str16	specialRespectNameForOther;
		Str16	specialSlandeNameForOther;


		Str16	normalContent1;
		Str16	normalContent2;

		Str16	fightContent1;
		Str16	fightContent2;

		Str16	woundContent1;
		Str16	woundContent2;

		Str16	winContent1;
		Str16	winContent2;

		Str16	failContent1;
		Str16	failContent2;

		DialogInfo()
		{
            modestNameForSelf.reserve(MAX_DIALOGINFO_NAME_LEN);
            prideNameForSelf.reserve(MAX_DIALOGINFO_NAME_LEN);
            respectNameForOther.reserve(MAX_DIALOGINFO_NAME_LEN);
            slandeNameForOther.reserve(MAX_DIALOGINFO_NAME_LEN);
            specialRespectNameForOther.reserve(MAX_DIALOGINFO_NAME_LEN);
			specialSlandeNameForOther.reserve(MAX_DIALOGINFO_NAME_LEN);
			normalContent1.reserve(MAX_DIALOGINFO_CONTENT_LEN);
			normalContent2.reserve(MAX_DIALOGINFO_CONTENT_LEN);
			failContent1.reserve(MAX_DIALOGINFO_CONTENT_LEN);
			failContent2.reserve(MAX_DIALOGINFO_CONTENT_LEN);
			woundContent1.reserve(MAX_DIALOGINFO_CONTENT_LEN);
			woundContent2.reserve(MAX_DIALOGINFO_CONTENT_LEN);
			winContent1.reserve(MAX_DIALOGINFO_CONTENT_LEN);
			winContent2.reserve(MAX_DIALOGINFO_CONTENT_LEN);
			failContent1.reserve(MAX_DIALOGINFO_CONTENT_LEN);
			failContent2.reserve(MAX_DIALOGINFO_CONTENT_LEN);
		}

	};
	 
//******************************************************************************************
	//对应策划文档Dialogue.csv表
    class DialogInfos                       
    {
    public:
        DialogInfos();
        ~DialogInfos();
        SINGLETON_INSTANCE(DialogInfos);

    public:
		// MG_CN_MODIFY
        ///Dialogue.csv 
        Bool                            load(Str16 fileName, IMGExternalPackManager* packManager = NULL);

        //根据ID获得  DialogInfo
        DialogInfo*						getDialogInfo(U32 id);

    protected:
        void                            clear();

    private:
        std::map<U32, DialogInfo*> mDialogMap;

    };
}
//******************************************************************************************
#endif  // _DIALOG_H_
//*************************