//***************************************************************************************************
#ifndef _H_UIGENREALPICTURE_
#define _H_UIGENREALPICTURE_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
    class UIGenrealPicture  : public UIObject
    {
    public:
        UIGenrealPicture();
        ~UIGenrealPicture();
        SINGLETON_INSTANCE(UIGenrealPicture);

    public:
        virtual void setEvent();
		virtual void update(Flt delta);

		Bool	setCharacterId(IdType id);
		void    setLV(U32 lv);
		void	setMp(PlayerCharacterIdType playerCharacterId);
		void	setSp(PlayerCharacterIdType playerCharacterId);
		void	setHp(PlayerCharacterIdType playerCharacterId);
		void	setHp(CPlayerCharacter* playerCharacter);
		void	setSp(CPlayerCharacter* playerCharacter);
		void	setMp(CPlayerCharacter* playerCharacter);
		void    setLV(CPlayerCharacter* playerCharacter);
		
		void	setGenrealHead(UInt index);
		void	setGenrealName(Str16 name);

		IdType	getCharacterId();

		static	void onDoubleClickGenrealHead( void* widget );

    protected:
    private:
		IdType mCharacterId;
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************