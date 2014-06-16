//***********************************************************************************************************
#ifndef _H_HEADDES_
#define _H_HEADDES_
//***********************************************************************************************************
#include "ClientPreqs.h"
//***********************************************************************************************************
namespace  MG
{
	enum HEADDES_OPTIONALTEXT_TYPE
	{
		HEADDES_OPTIONALTEXT_TYPE_NULL,
		HEADDES_OPTIONALTEXT_TYPE_TITEL,
		HEADDES_OPTIONALTEXT_TYPE_TIPS,
		//...	陆续修改、添加
	};
    class HeadDes
    {
        friend class HeadDesManage;
    public:
        HeadDes(CSceneEntity* pParent);
        ~HeadDes();

    public:
        void update();

		void setVisible(bool visible);

		void setIsTemplateCharacter(bool isTemp) { mIsTemplateCharacter = isTemp; }

    protected:

        void	resetParent(CSceneEntity* pParent);
        void	closeDes();
		void	hide();

    private:

        void	clear();

	public:

		void	init();

    private:

		void	updateTemplateCharacter();
        void	updatePlayerCharacter();
		void	updateNpc();
		void	updateBattleBuild();
        void	updateTroop();
        void    updateItem();
		void    updateMonster();
		void    updateRotPlace();

        void	initName(GAMEOBJ_TYPE type, Str16 name);
        void	initSpeak(const CharacterTempInfo*& charTemp);
        void	initHeadFlag();
        void	initHp();
        void	initOptional(const CharacterTempInfo*& charTemp);
        Bool	calBasePoint();

    public:

		void	setBackImg(UInt id);	
		void	setSpeakImg(UInt id);
		void	setSpeakContent(Str16& content);
		void	setMaxSpeakTime(U32 time);
		
		void	setFlagImg(UInt id);

		void	setOptionalTextType(HEADDES_OPTIONALTEXT_TYPE type);
		void	setOptionalText(Str16& content);

		void	setHeight(Flt height);

    private:

		// 是否在屏幕中
		Bool		mIsInScreen;

		///背景 说话时图标 内容
		IImage*		mBackImg;
		IImage*		mCharacterSpeakImg;
		IEdit*		mCharacterSpeakEdit;
		Vec2		mSpeakImageSize;
		Vec2		mSpeakEditSize;
		Vec2		mBackImgSize;
		///显示最大时间 当前消耗时间
		U64			mCharacterSpeakMaxTime;
		U64			mCharacterSpeakCurrTime;

		///头顶标记
		IImage*		mFlagImg;
		Vec2		mFlagImgSize;

		///character名字
		IText*      mName;
		Vec2		mNameTextSize;

		///玩家自选内容
		IText*						mOptionalText;
		HEADDES_OPTIONALTEXT_TYPE	mCurrType;
		Vec2		mOptionalTextSize;


		///血条
		IProgress*  mHpProcess;
		Vec2		mHpProcessSize;
		
		///高度
		Flt			mHeightAboveParent;
        CSceneEntity* mParent;
        const CharacterTempInfo*    mCharacterTempInfo;
		const ItemInfo*             mItemIempInfo;
		const CRegionObject*        mRegionObject;

		Vec2		mBasePoint;

		Bool		mInit;

		//是否按下Tab键
		Bool		mIsPressTab;

		//是否是登录的模版角色在update
		Bool		mIsTemplateCharacter;
		Bool		mIsVisible;
    };
}
//***********************************************************************************************************
#endif
//***********************************************************************************************************