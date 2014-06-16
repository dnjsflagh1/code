//**********************************************************************************************************
#ifndef _H_UICLANITEMBAG_
#define _H_UICLANITEMBAG_
//**********************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//**********************************************************************************************************
namespace MG
{
    class UIClanItemBag : public UIObject
    {
    public:
        UIClanItemBag();
        ~UIClanItemBag();
        SINGLETON_INSTANCE(UIClanItemBag);

    public:
        virtual void    setEvent();

    public:
        void            addItem(PlayerItem* pItem);
        void            deleteItem(U32 index);
        void            updateItem(U32 index, U32 num);

    private:
        void            clearItem();
        void            addItemList();

    private:
        static  void    onStartDrag(void* widget1, Bool& res);
        static  void    onEndDrag(void* widget1, void* widget2, Bool res);
        static  void    onGetDragInfo(void* widget1, void*& widget2, CoordI& rect, Byte& isImage);

    private:
        void            getDragInfo(IIcon* pSend, void*& widget2, CoordI& rect, Byte& isImage);
        void            onHandlBag(IIcon* pSend, IIcon* pRece, Bool ishave);
        void            sendDropItem(IdType ID);
        void            sendBagChangePos(U32 sendIndex, U32 recvIndex,ITEM_SITE_TYPE recvType, PlayerCharacterIdType charid);

    private:
        void            clanBagDropItem(IdType itemdbid);
        void            clanBagChangePos(IconInfo* pSendInfo, IconInfo* pReceInfo);

    private:
        IImage*         mImage;
        U32             mCurPage;
        U32             mTotalPage;
        Int             mSelectIndex;

    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************