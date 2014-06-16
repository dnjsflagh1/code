/******************************************************************************/
#ifndef _SHOPNETPACKET_H_
#define _SHOPNETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"
/******************************************************************************/

namespace MG
{
	/**********************************************************************
	//@负责人:      徐开超
	//@协助人:      ???
	**********************************************************************/
    /******************************************************************************/
    //游戏物品包类型
    /******************************************************************************/
    enum ShopNetPacketType
    {
        PT_SHOP_UNKNOW = 0,

        PT_SHOP_C2S_OPEN,                                                       //客户端请求打开商店
        PT_SHOP_S2C_OPEN,                                                       //服务器通知客户端打开商店。
        //PT_SHOP_C2S_CLOSE,                                                      //服务器关掉商店。
        //买
        PT_SHOP_C2M_BUY_ITEM,                                                   //客户端请求在商店中买道具。
        PT_SHOP_F2C_BUY_ITEM,                                                   //frontServer告诉客户端购买结果。
        //PT_SHOP_F2M_ITEM_ADD,                                                   //frontServer告诉MapServer此次购买失败，Mapserver加上刚减去的道具
        //PT_SHOP_M2F_BUY_ITEM,                                                   //MapServer通知FrontSever玩家需要购买XX道具的结果
        //卖
        PT_SHOP_C2F_BUYBACK_ITEM,                                               //客户端请求回购物品
        PT_SHOP_F2C_BUYBACK_ITEM,                                               //frontServer告诉客户端回购结果
        PT_SHOP_C2F_SELL_ITEM,                                                  //客户端请求在商店中买道具。
        PT_SHOP_F2C_SELL_ITEM,                                                  //frontServer告诉客户端购买结果。
        //修理
        PT_SHOP_C2F_REPAIR_ITEM,                                                //客户端请求在商店中买道具。
        PT_SHOP_F2C_REPAIR_ITEM,                                                //frontServer告诉客户端购买结果。
    };

#pragma pack (push)
#pragma pack (1)

    ///数据包声明
	//**********************************************************************
	//@名字:        PT_SHOP_C2S_OPEN
	//@功能:        客户端向frontServerr发送打开商店的请求
	//@备注:        
	//**********************************************************************/
    struct PT_SHOP_C2S_OPEN_DATA
    {
        U32         shopID;
        IdType      accountID;
    };
    struct PT_SHOP_C2S_OPEN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SHOP_C2S_OPEN_DATA);
    };
	class PT_SHOP_C2S_OPEN_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SHOP_C2S_OPEN_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_SHOP;
			mType                               =   PT_SHOP_C2S_OPEN;
			mBaseDataSize                       =   PT_SHOP_C2S_OPEN_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_C2S;

			mReplaceLevelInSendQueue            =   GPRL_NONE;
			mReplaceIndexInSendQueue            =   0;
			mReplaceLevelInRecvQueue            =   GPRL_NONE;
			mReplaceIndexInRecvQueue            =   0;

			mDiscardLevelInSendQueue            =   GPDL_NORMAL;
			mDiscardLevelInRecvQueue            =   GPDL_NORMAL;

			mBlockWaitLevelInSendQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInSendQueue        =   0;
			mBlockWaitReplyChannelInSendQueue   =   0;
			mBlockWaitReplyTypeInSendQueue      =   0;

			mBlockWaitLevelInRecvQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInRecvQueue        =   0;
			mBlockWaitReplyChannelInRecvQueue   =   0;
			mBlockWaitReplyTypeInRecvQueue      =   0;
		}
	};
    //---------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_SHOP_S2C_OPEN
	//@功能:        frontServerr向客户端发送打开商店的回复
	//@备注:        
	//**********************************************************************/
    struct shopitem 
    {
        U32 itemTemplate;
        U32 num;
    };
    struct PT_SHOP_S2C_OPEN_DATA
    {
        U32         shopID;
        Bool		isOpen;
    };
    struct PT_SHOP_S2C_OPEN_DATA_INFO
    {
        static const Int  dataSize = sizeof(PT_SHOP_S2C_OPEN_DATA);
    };
	class PT_SHOP_S2C_OPEN_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SHOP_S2C_OPEN_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_SHOP;
			mType                               =   PT_SHOP_S2C_OPEN;
			mBaseDataSize                       =   PT_SHOP_S2C_OPEN_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2C;

			mReplaceLevelInSendQueue            =   GPRL_NONE;
			mReplaceIndexInSendQueue            =   0;
			mReplaceLevelInRecvQueue            =   GPRL_NONE;
			mReplaceIndexInRecvQueue            =   0;

			mDiscardLevelInSendQueue            =   GPDL_NORMAL;
			mDiscardLevelInRecvQueue            =   GPDL_NORMAL;

			mBlockWaitLevelInSendQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInSendQueue        =   0;
			mBlockWaitReplyChannelInSendQueue   =   0;
			mBlockWaitReplyTypeInSendQueue      =   0;

			mBlockWaitLevelInRecvQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInRecvQueue        =   0;
			mBlockWaitReplyChannelInRecvQueue   =   0;
			mBlockWaitReplyTypeInRecvQueue      =   0;
		}
	};
    //---------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_SHOP_C2M_BUY_ITEM
	//@功能:        客户端向mapServer发送买道具的请求
	//@备注:        
	//**********************************************************************/
    //---------------------------------------------------------------------------------
    struct PT_SHOP_C2M_BUY_ITEM_DATA
    {
        IdType      accountID;
        U32         shopID;
        shopitem    itemNum;
    };
    struct PT_SHOP_C2M_BUY_ITEM_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SHOP_C2M_BUY_ITEM_DATA);
    };
	class PT_SHOP_C2M_BUY_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SHOP_C2M_BUY_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_SHOP;
			mType                               =   PT_SHOP_C2M_BUY_ITEM;
			mBaseDataSize                       =   PT_SHOP_C2M_BUY_ITEM_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_C2S;

			mReplaceLevelInSendQueue            =   GPRL_NONE;
			mReplaceIndexInSendQueue            =   0;
			mReplaceLevelInRecvQueue            =   GPRL_NONE;
			mReplaceIndexInRecvQueue            =   0;

			mDiscardLevelInSendQueue            =   GPDL_NORMAL;
			mDiscardLevelInRecvQueue            =   GPDL_NORMAL;

			mBlockWaitLevelInSendQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInSendQueue        =   0;
			mBlockWaitReplyChannelInSendQueue   =   0;
			mBlockWaitReplyTypeInSendQueue      =   0;

			mBlockWaitLevelInRecvQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInRecvQueue        =   0;
			mBlockWaitReplyChannelInRecvQueue   =   0;
			mBlockWaitReplyTypeInRecvQueue      =   0;
		}
	};
    //---------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_SHOP_F2C_BUY_ITEM
	//@功能:        frontServer向客户端发送买道具的回复
	//@备注:        
	//**********************************************************************/
    //枚举
    enum shop_buy_res
    {
        shop_buy_res_success,
        shop_buy_res_shop_not_found,
        shop_buy_res_item_count_none,
        shop_buy_res_not_enough_money,
        shop_buy_res_bag_capacity_not_enough,
        shop_buy_res_item_not_found,
    };
    struct PT_SHOP_F2C_BUY_ITEM_DATA
    {
        U32         shopID;
        shopitem    itemNum;
        Byte        res;
    };
    struct PT_SHOP_F2C_BUY_ITEM_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SHOP_F2C_BUY_ITEM_DATA);
    };
	class PT_SHOP_F2C_BUY_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SHOP_F2C_BUY_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_SHOP;
			mType                               =   PT_SHOP_F2C_BUY_ITEM;
			mBaseDataSize                       =   PT_SHOP_F2C_BUY_ITEM_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2C;

			mReplaceLevelInSendQueue            =   GPRL_NONE;
			mReplaceIndexInSendQueue            =   0;
			mReplaceLevelInRecvQueue            =   GPRL_NONE;
			mReplaceIndexInRecvQueue            =   0;

			mDiscardLevelInSendQueue            =   GPDL_NORMAL;
			mDiscardLevelInRecvQueue            =   GPDL_NORMAL;

			mBlockWaitLevelInSendQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInSendQueue        =   0;
			mBlockWaitReplyChannelInSendQueue   =   0;
			mBlockWaitReplyTypeInSendQueue      =   0;

			mBlockWaitLevelInRecvQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInRecvQueue        =   0;
			mBlockWaitReplyChannelInRecvQueue   =   0;
			mBlockWaitReplyTypeInRecvQueue      =   0;
		}
	};
    //---------------------------------------------------------------------------------
    //struct PT_SHOP_F2M_ITEM_ADD_DATA
    //{
    //    U32         shopID;
    //    shopitem    itemNum;
    //};
    //struct PT_SHOP_F2M_ITEM_ADD_DATA_INFO
    //{
    //    static const Int dataSize = sizeof(PT_SHOP_F2M_ITEM_ADD_DATA);
    //};
    ////---------------------------------------------------------------------------------
    //struct PT_SHOP_M2F_BUY_ITEM_DATA
    //{
    //    IdType      accountID;
    //    U32         shopID;
    //    shopitem    itemNum;
    //    Byte        res;
    //};
    //struct PT_SHOP_M2F_BUY_ITEM_DATA_INFO
    //{
    //    static const Int dataSize = sizeof(PT_SHOP_M2F_BUY_ITEM_DATA);
    //}; 
    //---------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_SHOP_C2F_SELL_ITEM
	//@功能:        客户端向frontServer发送买道具的请求
	//@备注:        
	//**********************************************************************/
    //卖
    struct PT_SHOP_C2F_SELL_ITEM_DATA
    {
        U32         shopID;
        IdType      itemDBID;
    };
    struct PT_SHOP_C2F_SELL_ITEM_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_SHOP_C2F_SELL_ITEM_DATA);
    } ;
	class PT_SHOP_C2F_SELL_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SHOP_C2F_SELL_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_SHOP;
			mType                               =   PT_SHOP_C2F_SELL_ITEM;
			mBaseDataSize                       =   PT_SHOP_C2F_SELL_ITEM_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_C2S;

			mReplaceLevelInSendQueue            =   GPRL_NONE;
			mReplaceIndexInSendQueue            =   0;
			mReplaceLevelInRecvQueue            =   GPRL_NONE;
			mReplaceIndexInRecvQueue            =   0;

			mDiscardLevelInSendQueue            =   GPDL_NORMAL;
			mDiscardLevelInRecvQueue            =   GPDL_NORMAL;

			mBlockWaitLevelInSendQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInSendQueue        =   0;
			mBlockWaitReplyChannelInSendQueue   =   0;
			mBlockWaitReplyTypeInSendQueue      =   0;

			mBlockWaitLevelInRecvQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInRecvQueue        =   0;
			mBlockWaitReplyChannelInRecvQueue   =   0;
			mBlockWaitReplyTypeInRecvQueue      =   0;
		}
	};
    //---------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_SHOP_F2C_SELL_ITEM
	//@功能:        frontServer向客户端发送买道具的回复
	//@备注:        
	//**********************************************************************/
    enum shop_sell_item_res
    {
        shop_sell_item_res_suc,
        shop_sell_item_res_item_exist,
        shop_sell_item_res_shop_exist,
        shop_sell_item_res_notbuy,
    };
    struct PT_SHOP_F2C_SELL_ITEM_DATA
    {
        U32         shopID;
        IdType      itemDBID;
        Byte        res;
    };
    struct PT_SHOP_F2C_SELL_ITEM_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_SHOP_F2C_SELL_ITEM_DATA);
    } ;
	class PT_SHOP_F2C_SELL_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SHOP_F2C_SELL_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_SHOP;
			mType                               =   PT_SHOP_F2C_SELL_ITEM;
			mBaseDataSize                       =   PT_SHOP_F2C_SELL_ITEM_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2C;

			mReplaceLevelInSendQueue            =   GPRL_NONE;
			mReplaceIndexInSendQueue            =   0;
			mReplaceLevelInRecvQueue            =   GPRL_NONE;
			mReplaceIndexInRecvQueue            =   0;

			mDiscardLevelInSendQueue            =   GPDL_NORMAL;
			mDiscardLevelInRecvQueue            =   GPDL_NORMAL;

			mBlockWaitLevelInSendQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInSendQueue        =   0;
			mBlockWaitReplyChannelInSendQueue   =   0;
			mBlockWaitReplyTypeInSendQueue      =   0;

			mBlockWaitLevelInRecvQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInRecvQueue        =   0;
			mBlockWaitReplyChannelInRecvQueue   =   0;
			mBlockWaitReplyTypeInRecvQueue      =   0;
		}
	};
    //---------------------------------------------------------------------------------   
	//**********************************************************************
	//@名字:        PT_SHOP_C2F_REPAIR_ITEM
	//@功能:        客户端向frontServer发送修理道具的请求
	//@备注:        
	//**********************************************************************/
    //修理
    struct PT_SHOP_C2F_REPAIR_ITEM_DATA
    {
        Byte        itemSiteType;
        U32         shopID;
        IdType      itemDBID;
        PlayerCharacterIdType charid;
    };
    struct PT_SHOP_C2F_REPAIR_ITEM_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_SHOP_C2F_REPAIR_ITEM_DATA);
    } ;
	class PT_SHOP_C2F_REPAIR_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SHOP_C2F_REPAIR_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_SHOP;
			mType                               =   PT_SHOP_C2F_REPAIR_ITEM;
			mBaseDataSize                       =   PT_SHOP_C2F_REPAIR_ITEM_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_C2S;

			mReplaceLevelInSendQueue            =   GPRL_NONE;
			mReplaceIndexInSendQueue            =   0;
			mReplaceLevelInRecvQueue            =   GPRL_NONE;
			mReplaceIndexInRecvQueue            =   0;

			mDiscardLevelInSendQueue            =   GPDL_NORMAL;
			mDiscardLevelInRecvQueue            =   GPDL_NORMAL;

			mBlockWaitLevelInSendQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInSendQueue        =   0;
			mBlockWaitReplyChannelInSendQueue   =   0;
			mBlockWaitReplyTypeInSendQueue      =   0;

			mBlockWaitLevelInRecvQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInRecvQueue        =   0;
			mBlockWaitReplyChannelInRecvQueue   =   0;
			mBlockWaitReplyTypeInRecvQueue      =   0;
		}
	};
    //---------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_SHOP_F2C_REPAIR_ITEM
	//@功能:        frontServer向客户端发送修理道具的回复
	//@备注:        
	//**********************************************************************/
    enum shop_repair_res
    {
        shop_repair_res_suc,
        shop_repair_res_item_exist,
        shop_repair_res_not_equip,
        shop_repair_res_shop_exist,
        shop_repair_res_notrepair,
        shop_repair_res_not_money,
    };
    struct PT_SHOP_F2C_REPAIR_ITEM_DATA
    {
        Byte        itemSiteType; 
        Byte        res;
        U32         shopID;
        IdType      itemDBID;
        PlayerCharacterIdType charid;
    };
    struct PT_SHOP_F2C_REPAIR_ITEM_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_SHOP_F2C_REPAIR_ITEM_DATA);
    };
	class PT_SHOP_F2C_REPAIR_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SHOP_F2C_REPAIR_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_SHOP;
			mType                               =   PT_SHOP_F2C_REPAIR_ITEM;
			mBaseDataSize                       =   PT_SHOP_F2C_REPAIR_ITEM_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2C;

			mReplaceLevelInSendQueue            =   GPRL_NONE;
			mReplaceIndexInSendQueue            =   0;
			mReplaceLevelInRecvQueue            =   GPRL_NONE;
			mReplaceIndexInRecvQueue            =   0;

			mDiscardLevelInSendQueue            =   GPDL_NORMAL;
			mDiscardLevelInRecvQueue            =   GPDL_NORMAL;

			mBlockWaitLevelInSendQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInSendQueue        =   0;
			mBlockWaitReplyChannelInSendQueue   =   0;
			mBlockWaitReplyTypeInSendQueue      =   0;

			mBlockWaitLevelInRecvQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInRecvQueue        =   0;
			mBlockWaitReplyChannelInRecvQueue   =   0;
			mBlockWaitReplyTypeInRecvQueue      =   0;
		}
	};
    //-----------------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_SHOP_F2C_BUYBACK_ITEM
	//@功能:        frontServer向客户端发送回购道具的回复
	//@备注:        
	//**********************************************************************/
    enum shop_buyback_res
    {
        shop_buyback_res_suc,
        shop_buyback_res_item_exist,
        shop_buyback_res_shop_exist,
        shop_buyback_res_not_money,
        shop_buyback_res_clanbag_ful,
    };
    struct PT_SHOP_F2C_BUYBACK_ITEM_DATA
    {
        Byte            res;
        U32             shopID;
        U32             index;
        ItemIdType      itemDBID;
    };
    struct PT_SHOP_F2C_BUYBACK_ITEM_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_SHOP_F2C_BUYBACK_ITEM_DATA);
    };
	class PT_SHOP_F2C_BUYBACK_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SHOP_F2C_BUYBACK_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_SHOP;
			mType                               =   PT_SHOP_F2C_BUYBACK_ITEM;
			mBaseDataSize                       =   PT_SHOP_F2C_BUYBACK_ITEM_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2C;

			mReplaceLevelInSendQueue            =   GPRL_NONE;
			mReplaceIndexInSendQueue            =   0;
			mReplaceLevelInRecvQueue            =   GPRL_NONE;
			mReplaceIndexInRecvQueue            =   0;

			mDiscardLevelInSendQueue            =   GPDL_NORMAL;
			mDiscardLevelInRecvQueue            =   GPDL_NORMAL;

			mBlockWaitLevelInSendQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInSendQueue        =   0;
			mBlockWaitReplyChannelInSendQueue   =   0;
			mBlockWaitReplyTypeInSendQueue      =   0;

			mBlockWaitLevelInRecvQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInRecvQueue        =   0;
			mBlockWaitReplyChannelInRecvQueue   =   0;
			mBlockWaitReplyTypeInRecvQueue      =   0;
		}
	};
    //-----------------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_SHOP_C2F_BUYBACK_ITEM
	//@功能:        客户端向frontServer发送回购道具的请求
	//@备注:        
	//**********************************************************************/
    struct PT_SHOP_C2F_BUYBACK_ITEM_DATA
    {
        U32             shopID;
        ItemIdType      itemDBID;
    };
    struct PT_SHOP_C2F_BUYBACK_ITEM_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_SHOP_C2F_BUYBACK_ITEM_DATA);
    };
	class PT_SHOP_C2F_BUYBACK_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SHOP_C2F_BUYBACK_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_SHOP;
			mType                               =   PT_SHOP_C2F_BUYBACK_ITEM;
			mBaseDataSize                       =   PT_SHOP_C2F_BUYBACK_ITEM_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_C2S;

			mReplaceLevelInSendQueue            =   GPRL_NONE;
			mReplaceIndexInSendQueue            =   0;
			mReplaceLevelInRecvQueue            =   GPRL_NONE;
			mReplaceIndexInRecvQueue            =   0;

			mDiscardLevelInSendQueue            =   GPDL_NORMAL;
			mDiscardLevelInRecvQueue            =   GPDL_NORMAL;

			mBlockWaitLevelInSendQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInSendQueue        =   0;
			mBlockWaitReplyChannelInSendQueue   =   0;
			mBlockWaitReplyTypeInSendQueue      =   0;

			mBlockWaitLevelInRecvQueue          =   GPWL_NONE;
			mBlockWaitMaxTimeInRecvQueue        =   0;
			mBlockWaitReplyChannelInRecvQueue   =   0;
			mBlockWaitReplyTypeInRecvQueue      =   0;
		}
	};

#pragma pack (pop)
}

/******************************************************************************/

#endif