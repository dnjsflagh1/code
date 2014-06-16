//***************************************************************************************************
#ifndef _H_UIRPGTARGETPIC_
#define _H_UIRPGTARGETPIC_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
    class UIRPGTargetPic: public UIObject
    {
    public:
        UIRPGTargetPic();
        ~UIRPGTargetPic();
        SINGLETON_INSTANCE(UIRPGTargetPic);

    public:
        virtual void setEvent();
		virtual void update(Flt delta);

		Bool	setCharacterId(IdType id);
		void    setTargetLV(U32 lv);
		void	setTargetMp(PlayerCharacterIdType playerCharacterId);
		void	setTargetSp(PlayerCharacterIdType playerCharacterId);
		void	setTargetHp(PlayerCharacterIdType playerCharacterId);
		void	setTargetHp(CPlayerCharacter* playerCharacter);
		void	setTargetSp(CPlayerCharacter* playerCharacter);
		void	setTargetMp(CPlayerCharacter* playerCharacter);
		void    setTargetLV(CPlayerCharacter* playerCharacter);
		
		void	setTargetHead(UInt index);
		void	setTargetName(Str16 name);

		IdType	getCharacterId();

		static	void onDoubleClickTargetHead( void* widget );
		void	setTargetEntity(CSceneEntity* entity);

    protected:
    private:
		void                     clear();
		void                    _setTextName(const Str16& name);
		void                    _setTextLevel(const Str16& level);
        void                    _setProgressHp(const Flt currHp,const Flt maxHp);
        void                    _setProgressMp(const Flt currMp,const Flt maxMp);
		void                    _setIconImage(const Str8& groupName,const Str8& ResourceName,const Str8& ItemName);
		//
		CSceneEntity*           mTargetEntity;
		//当前点选的实体ID
		U32						mCharacterId;
		//当前点选实体的类型
		GAMEOBJ_TYPE            mCharacterType;
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************