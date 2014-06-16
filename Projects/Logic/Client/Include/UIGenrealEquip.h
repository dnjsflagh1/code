//***************************************************************************************************
#ifndef _H_UIGENREALEQUIP_
#define _H_UIGENREALEQUIP_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
    class UIGenrealEquip  : public UIObject
    {
    public:
        UIGenrealEquip();
        ~UIGenrealEquip();
        SINGLETON_INSTANCE(UIGenrealEquip);

    public: //对道具和装备的操作。
        void         addItemList();
        void         addItem(PlayerItem* pItem);
        void         deleteItem(U32 index);
        void         updateItem(U32 index, U32 num);

        void         addEquipList();
        void         addEquip(PlayerItem* pItem);
        void         deleteEquip(U32 index);

        PlayerCharacterIdType   
                    getCharID(){return mCharid;}
        void        setCharID(PlayerCharacterIdType id){mCharid = id;}            

    public:
        virtual void setEvent();

    private:
        static void  onStartDrag(void* widget1, Bool& res);
        static void  onEndDrag(void* widget1, void* widget2, Bool res);
        static void  onGetDragInfo(void* widget1, void*& widget2, CoordI& rect, Byte& isImage);

    private:
        void         onHandlBag( IconInfo* pSend, IconInfo* pRece, Bool ishave );
        void         onHandlEquip( IconInfo* pSend, IconInfo* pRece, Bool ishave  );
        void         getDragInfo(IIcon* pSend, void*& widget2, CoordI& rect, Byte& isImage);

        void         characterBagDropItem(IdType itemdbid);
        void         characterEquipDropItem(IdType itemdbid);
        void         characterBagChangePos(IconInfo* pSendInfo, IconInfo* pReceInfo);
        void         characterEquipChangePos(IconInfo* pSendInfo, IconInfo* pReceInfo);

    private:
        void         sendDropItem(IdType ID);
        void         sendBagChangePos(U32 sendIndex, U32 recvIndex,ITEM_SITE_TYPE sendType,ITEM_SITE_TYPE recvType, PlayerCharacterIdType charid);

    private:
        IImage* mImage;
        IText* mText;
        PlayerCharacterIdType mCharid;
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************