/******************************************************************************/
#ifndef _ITEMNETPACKET_H_
#define _ITEMNETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "PlayerItem.h"
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
    enum ItemNetPacketType
    {
        PT_ITEM_UNKNOW = 0,

		PT_ITEM_S2C_ADDLIST_BEGIN,												//开始发包，通知客户端清空背包。
        PT_ITEM_S2C_ADDLIST,                                                    //加到氏族背包 （登录时）
        PT_ITEM_S2C_ADDLIST_END,                                                //结束的标志。
        
        PT_ITEM_S2C_ADD,                                                        //界面加道具
		PT_ITEM_S2C_UPDATE_NUM_LIST,                                            //修改已有道具数量
        PT_ITEM_C2S_DELETE,                                                     //客户端从界面中删除
        PT_ITEM_S2C_DELETE,                                                     //服务器从界面中删除的结果。
        PT_ITEM_C2S_CHANGEPOS,                                                  //变换位置（客户端请求）。
        PT_ITEM_S2C_CHANGEPOS,                                                  //变换位置结果(服务器同意)。

        PT_ITEM_C2S_SPLIT,                                                      //客户端请求拆分
        PT_ITEM_S2C_SPLIT,                                                      //更新道具的堆叠数
             
        PT_ITEM_F2M_EQUIP_LIST,                                                 //通知mapServer记录角色的装备
        PT_ITEM_F2M_CHANGE_EQUIP,                                               //通知MapServer换装
        PT_ITEM_M2C_EQUIP_LIST,                                                 //广播角色的装备
        PT_ITEM_M2C_CHANGE_EQUIP,                                               //广播角色换装。

        PT_ITEM_C2F_USE_ITEM,                                                   //客户端请求使用物品
        PT_ITEM_F2M_USE_ITEM,                                                   //告诉mapServer使用物品
        PT_ITEM_F2C_USE_ITEM,                                                   //告诉客户端是否成功。
		PT_ITEM_M2F_USE_ITEM,													//告诉FrontServer使用物品，删除物品。

		PT_ITEM_M2C_DROP_ITEM_LIST,												//mapServer同步掉落信息
		PT_ITEM_M2F_DROP_ITEM_ADD_EXP,											//mapServer掉落物品时，经验直接加 ylh
        PT_ITEM_C2F_PICK_ITEM,                                                  //客户端拾取道具
        PT_ITEM_F2M_PICK_ITEM,                                                  //通知MapServer删除地图中的道具
        PT_ITEM_M2C_PICK_ITEM,                                                  //MapServer广播客户端删除地图上的道具
        PT_ITEM_M2F_PICK_ITEM,                                                  //通知frontserver加道具。
		PT_ITEM_F2C_PICK_ITEM,													//背包已满，请及时清理背包。

		PT_ITEM_F2C_ADD_MONEY,													//通知客户端加钱
		PT_ITEM_F2C_ADD_EXP,													//通知客户端加经验。

		PT_ITEM_M2C_ATFD_REWARD,												//通知Client显示攻城副本奖励
		PT_ITEM_C2M_ATFD_REWARD,												//请求MapServer获取攻城副本奖励
		PT_ITEM_M2F_ATFD_REWARD,												//通知FrontServer发送攻城副本奖励
		PT_ITEM_F2C_ATFD_REWARD,												//背包已满，请及时清理背包。
		
		PT_ITEM_C2F_QUEST_REWARD,                                               //向FrontServer获取任务奖励

		PT_ITEM_M2C_DROP_ITEM_DISAPPEAR,										//掉落物品 时间到了， 自动消失
	};

#pragma pack (push)
#pragma pack (1)

    ///数据包声明
    
    //-----------------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_ITEM_S2C_ADDLIST
	//@功能:        frontServerr向客户端发送道具列表
	//@备注:        登陆时发送从DB读取的道具数据
	//**********************************************************************/
    //氏族背包
    struct PT_ITEM_S2C_ADDLIST_DATA
    {
        U32             num;
        ItemRecord      xItemRecord[1];
    };
    struct PT_ITEM_S2C_ADDLIST_DATA_INFO
    {
        static const Int itemRecordSize = sizeof(ItemRecord);
        static const Int headSize       = sizeof(PT_ITEM_S2C_ADDLIST_DATA) - sizeof(ItemRecord);
		static const Int dataSize       = sizeof(PT_ITEM_S2C_ADDLIST_DATA);
    };
	class PT_ITEM_S2C_ADDLIST_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_S2C_ADDLIST_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_S2C_ADDLIST;
			mBaseDataSize                       =   PT_ITEM_S2C_ADDLIST_DATA_INFO::dataSize ;

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
	//@名字:        PT_ITEM_S2C_ADD
	//@功能:        frontServerr向客户端发送新增道具
	//@备注:        
	//**********************************************************************/
    struct  PT_ITEM_S2C_ADD_DATA
    {
        ItemRecord      xItemRecord;
    };
    struct PT_ITEM_S2C_ADD_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_ITEM_S2C_ADD_DATA);
    };
	class PT_ITEM_S2C_ADD_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_S2C_ADD_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_S2C_ADD;
			mBaseDataSize                       =   PT_ITEM_S2C_ADD_DATA_INFO::dataSize ;

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
	//@名字:        PT_ITEM_S2C_UPDATE_NUM_LIST
	//@功能:        frontServerr向客户端发送更新道具列表
	//@备注:        
	//**********************************************************************/
     struct PT_ITEM_S2C_UPDATE_NUM_DATA
	 {
         U32  slotIndex;
		 Byte belongPos;
         U32  curNum;
	 };
	 struct PT_ITEM_S2C_UPDATE_NUM_lIST_DATA
	 {
		 U8   account;
         PT_ITEM_S2C_UPDATE_NUM_DATA  data[1];
	 };
	 struct PT_ITEM_S2C_UPDATE_NUM_lIST_DATA_INFO
	 { 
        static const Int updateDataSize = sizeof(PT_ITEM_S2C_UPDATE_NUM_DATA);
        static const Int headSize = sizeof(PT_ITEM_S2C_UPDATE_NUM_lIST_DATA) - updateDataSize;
		static const Int dataSize = sizeof(PT_ITEM_S2C_UPDATE_NUM_lIST_DATA);

	 };
	 class PT_ITEM_S2C_UPDATE_NUM_lIST_DESCRIBE : public GameNetPacketDataDescribe
	 {
	 public:
		 PT_ITEM_S2C_UPDATE_NUM_lIST_DESCRIBE()
			 :GameNetPacketDataDescribe()
		 {
			 mChannel                            =   GNPC_ITEM;
			 mType                               =   PT_ITEM_S2C_UPDATE_NUM_LIST;
			 mBaseDataSize                       =   PT_ITEM_S2C_UPDATE_NUM_lIST_DATA_INFO::dataSize ;

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
	 //@名字:        PT_ITEM_C2S_DELETE
	 //@功能:        客户端向frontServerr发送删除道具
	 //@备注:        
	 //**********************************************************************/
    struct  PT_ITEM_C2S_DELETE_DATA 
    {
        PlayerCharacterIdType   id;
        IdType                  xItemDBID;
        Byte                    type;
    };
    struct PT_ITEM_C2S_DELETE_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_ITEM_C2S_DELETE_DATA);
    };
	class PT_ITEM_C2S_DELETE_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_C2S_DELETE_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_C2S_DELETE;
			mBaseDataSize                       =   PT_ITEM_C2S_DELETE_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_C2S;

			mReplaceLevelInSendQueue            =   GPRL_SELF;
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
	//@名字:        PT_ITEM_S2C_DELETE
	//@功能:        frontServerr向客户端发送确认删除道具的消息
	//@备注:        
	//**********************************************************************/
    //枚举
    enum    itembag_del_res
    {
        itembag_del_res_Succeed,
        itembag_del_res_Error_ItemNone,                       //没有道具。
        itembag_del_res_Error_Delete,                         //不能删除
        itembag_del_res_Error_UI,                             //此界面没有删除功能
        itembag_del_res_Error_Not_Enough_Num                  //数量不够
    };
    struct  PT_ITEM_S2C_DELETE_DATA
    {
        PlayerCharacterIdType   id;
        IdType          xItemDBID;
        Byte            type;
        Byte            res;
    };
    struct PT_ITEM_S2C_DELETE_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_ITEM_S2C_DELETE_DATA);
    };
	class PT_ITEM_S2C_DELETE_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_S2C_DELETE_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_S2C_DELETE;
			mBaseDataSize                       =   PT_ITEM_S2C_DELETE_DATA_INFO::dataSize ;

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
	//@名字:        PT_ITEM_C2S_CHANGEPOS
	//@功能:        客户端向frontServerr发送交换道具位置的请求
	//@备注:        
	//**********************************************************************/
    struct PT_ITEM_C2S_CHANGEPOS_DATA
    {
        PlayerCharacterIdType   id;
        U32             IndexSend;                              //发起的位置。
        Byte            sendType;
        U32             IndexRecv;                              //接受的位置
        Byte            recvType;   
    };
    struct PT_ITEM_C2S_CHANGEPOS_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_ITEM_C2S_CHANGEPOS_DATA);
    };
	class PT_ITEM_C2S_CHANGEPOS_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_C2S_CHANGEPOS_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_C2S_CHANGEPOS;
			mBaseDataSize                       =   PT_ITEM_C2S_CHANGEPOS_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_C2S;

			mReplaceLevelInSendQueue            =   GPRL_SELF;
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
	//@名字:        PT_ITEM_S2C_CHANGEPOS
	//@功能:        frontServerr向客户端发送交换道具位置的回复
	//@备注:        
	//**********************************************************************/
    //枚举
    enum    item_changepos_res
    {
        item_changepos_res_Succeed,
        item_changepos_res_Error_pos,                       //位置没有解封
        item_changepos_res_Error_notEquip,                  //不是装备
        item_changepos_res_Error_Equip_pos,                 //装备位不对
        item_changepos_res_Error_notchange,                 //不能移动到这个位置
        item_changepos_res_Error_character_level,           //角色等级不够
        item_changepos_res_Error_unknown,                   //未知错误
    };
    struct PT_ITEM_S2C_CHANGEPOS_DATA
    {
        PlayerCharacterIdType   id;
        U32             IndexSend;                              //发起的位置。
        Byte            sendType;
        U32             IndexRecv;                              //接受的位置
        Byte            recvType;
        Byte            res;
    };
    struct PT_ITEM_S2C_CHANGEPOS_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_ITEM_S2C_CHANGEPOS_DATA);
    };
	class PT_ITEM_S2C_CHANGEPOS_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_S2C_CHANGEPOS_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_S2C_CHANGEPOS;
			mBaseDataSize                       =   PT_ITEM_S2C_CHANGEPOS_DATA_INFO::dataSize ;

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
	//@名字:        PT_ITEM_C2S_SPLIT
	//@功能:        客户端向frontServerr发送分界道具位置的请求
	//@备注:        
	//**********************************************************************/
    struct PT_ITEM_C2S_SPLIT_DATA
    {
        PlayerCharacterIdType   characterId;        //所在的道具属于哪一个角色
      //IdType          xItemDBID;                  //拆分的道具ID
		UInt            selfSlot;
        Byte            selfType;                   //所在界面
        Byte            splitType;                  //拆出的界面
       // UInt            splitPos;                   //位置
        UInt            splitNum;                   //数量
		UInt            selectIndex;                //选种位置的序列号
    };
    struct PT_ITEM_C2S_SPLIT_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_ITEM_C2S_SPLIT_DATA);
    };
	class PT_ITEM_C2S_SPLIT_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_C2S_SPLIT_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_C2S_SPLIT;
			mBaseDataSize                       =   PT_ITEM_C2S_SPLIT_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2C;

			mReplaceLevelInSendQueue            =   GPRL_SELF;
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
	//@名字:        PT_ITEM_S2C_SPLIT
	//@功能:        frontServerr向客户端发送分界道具位置的回复
	//@备注:        
	//**********************************************************************/
    enum item_split_res
    {
        item_split_res_Succeed,
        item_split_res_Error_cannot,                //不能分解
        item_split_res_Error_ful,                   //道具栏已满
    };
    struct PT_ITEM_S2C_SPLIT_DATA
    {
		PlayerCharacterIdType   characterId;                 //所在的道具属于哪一个角色
		//IdType          xItemDBID;                  //拆分的道具ID
		UInt            selfSlot;
		Byte            selfType;                   //所在界面
		Byte            splitType;                  //拆出的界面
		//UInt            splitPos;                   //位置
		UInt            splitNum;                   //数量
		UInt            selectIndex;                //选种位置的序列号
		
		Byte            res;
    };
    //-----------------------------------------------------------------------------------------
    struct PT_ITEM_S2C_SPLIT_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_ITEM_S2C_SPLIT_DATA);
    };
	class PT_ITEM_S2C_SPLIT_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_S2C_SPLIT_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_S2C_SPLIT;
			mBaseDataSize                       =   PT_ITEM_S2C_SPLIT_DATA_INFO::dataSize ;

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
	//@名字:        PT_ITEM_F2M_EQUIP_LIST
	//@功能:        frontServerr向mapserver发送分界武将装备列表
	//@备注:        
	//**********************************************************************/
	struct netItemEquip 
	{
		U32						equipId;
		U32						randAppendID;
		U32						strengthenAppendID;
		U32						curStrengthenLv;
	};
    struct PT_ITEM_F2M_EQUIP_LIST_DATA
    {
        PlayerCharacterIdType   charid;
        netItemEquip            equipAttr[ITEM_EQUIP_SLOT_TYPE_MAX];
    };
    struct PT_ITEM_F2M_EQUIP_LIST_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_ITEM_F2M_EQUIP_LIST_DATA);
    };
	class PT_ITEM_F2M_EQUIP_LIST_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_F2M_EQUIP_LIST_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_F2M_EQUIP_LIST;
			mBaseDataSize                       =   PT_ITEM_F2M_EQUIP_LIST_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_ITEM_M2C_EQUIP_LIST
	//@功能:        mapserver向客户端同步武将装备列表
	//@备注:        
	//**********************************************************************/
    struct PT_ITEM_M2C_EQUIP_LIST_DATA
    {
        PlayerCharacterIdType   charid;
        U32                     equipId[ITEM_EQUIP_SLOT_TYPE_MAX];
    };
    struct PT_ITEM_M2C_EQUIP_LIST_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_ITEM_M2C_EQUIP_LIST_DATA);
    };
	class PT_ITEM_M2C_EQUIP_LIST_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_M2C_EQUIP_LIST_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_M2C_EQUIP_LIST;
			mBaseDataSize                       =   PT_ITEM_M2C_EQUIP_LIST_DATA_INFO::dataSize ;

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
	//@名字:        PT_ITEM_F2M_CHANGE_EQUIP
	//@功能:        frontserver向mapserver发送武将装备的更新
	//@备注:        
	//**********************************************************************/
    struct PT_ITEM_F2M_CHANGE_EQUIP_DATA
    {
        PlayerCharacterIdType   charid;
        netItemEquip            putonEquipAttr;      //穿上的装备id
        U32                     pos;                 //位置
    };
    struct PT_ITEM_F2M_CHANGE_EQUIP_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_ITEM_F2M_CHANGE_EQUIP_DATA);
    };
	class PT_ITEM_F2M_CHANGE_EQUIP_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_F2M_CHANGE_EQUIP_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_F2M_CHANGE_EQUIP;
			mBaseDataSize                       =   PT_ITEM_F2M_CHANGE_EQUIP_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_ITEM_M2C_CHANGE_EQUIP
	//@功能:        mapserver向客户端同步武将装备的更新
	//@备注:        
	//**********************************************************************/
    struct PT_ITEM_M2C_CHANGE_EQUIP_DATA
    {
        PlayerCharacterIdType   charid;
        U32                     putonEquipId;        //穿上的装备id
        U32                     pos;                 //位置
    };
    struct PT_ITEM_M2C_CHANGE_EQUIP_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_ITEM_M2C_CHANGE_EQUIP_DATA);
    };
	class PT_ITEM_M2C_CHANGE_EQUIP_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_M2C_CHANGE_EQUIP_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_M2C_CHANGE_EQUIP;
			mBaseDataSize                       =   PT_ITEM_M2C_CHANGE_EQUIP_DATA_INFO::dataSize ;

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
	//@名字:        PT_ITEM_C2F_USE_ITEM
	//@功能:        客户端向frontserver发送使用道具的请求
	//@备注:        
	//**********************************************************************/
    struct PT_ITEM_C2F_USE_ITEM_DATA
    {
        PlayerCharacterIdType   charid;
        //IdType                  itemId;
		U32                    slotIndex;
		Byte                   itemType;
    };
    struct PT_ITEM_C2F_USE_ITEM_DATA_INFO 
    {
        static const Int dataSize = sizeof(PT_ITEM_C2F_USE_ITEM_DATA);
    };
	class PT_ITEM_C2F_USE_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_C2F_USE_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_C2F_USE_ITEM;
			mBaseDataSize                       =   PT_ITEM_C2F_USE_ITEM_DATA_INFO::dataSize ;

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
    //-----------------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_ITEM_F2C_USE_ITEM
	//@功能:        frontserver向客户端发送使用道具的回复
	//@备注:        
	//**********************************************************************/
    enum item_use_res
    {
        item_use_res_Succeed,
        item_use_res_Error_None,
        item_use_res_Error_Type,
		item_use_res_Error_CD,
		item_use_res_Error_PC,
		item_use_res_Error_Judge,
        item_use_res_Error_ClanBag_Full
    };
    struct PT_ITEM_F2C_USE_ITEM_DATA
    {
        PlayerCharacterIdType   charid;
       // IdType                  itemId;
		U32                    slotIndex;
		Byte                   itemType;
        Byte                    res;
    };
    struct PT_ITEM_F2C_USE_ITEM_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_ITEM_F2C_USE_ITEM_DATA);
    };
	class PT_ITEM_F2C_USE_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_F2C_USE_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_F2C_USE_ITEM;
			mBaseDataSize                       =   PT_ITEM_F2C_USE_ITEM_DATA_INFO::dataSize ;

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
	//@名字:        PT_ITEM_F2M_USE_ITEM
	//@功能:        frontserver向mapserver发送使用道具的请求
	//@备注:        
	//**********************************************************************/
    struct PT_ITEM_F2M_USE_ITEM_DATA
    {
        PlayerCharacterIdType  charid;
        U32                    slotIndex;
		Byte                   itemType;
        U32                    itemid;
		//IdType                 itemDBId;
    };
    struct PT_ITEM_F2M_USE_ITEM_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_ITEM_F2M_USE_ITEM_DATA);
    };
	class PT_ITEM_F2M_USE_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_F2M_USE_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_F2M_USE_ITEM;
			mBaseDataSize                       =   PT_ITEM_F2M_USE_ITEM_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_ITEM_M2F_USE_ITEM
	//@功能:        mapserver向frontserver发送使用道具的回复
	//@备注:        
	//**********************************************************************/
	struct PT_ITEM_M2F_USE_ITEM_DATA
	{
		I32						netId;
		PlayerCharacterIdType   charid;
		//IdType                  itemId;
		U32                    slotIndex;
		Byte                   itemType;
		Byte                    res;
	};
	struct PT_ITEM_M2F_USE_ITEM_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_ITEM_M2F_USE_ITEM_DATA);
	};
	class PT_ITEM_M2F_USE_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_M2F_USE_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_M2F_USE_ITEM;
			mBaseDataSize                       =   PT_ITEM_M2F_USE_ITEM_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
    //------------------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_ITEM_C2F_PICK_ITEM
	//@功能:        客户端向frontserver发送拾取道具的请求
	//@备注:        
	//**********************************************************************/
    struct PT_ITEM_C2F_PICK_ITEM_DATA 
    {
        PlayerCharacterIdType   charId;
        U32                     itemIndex;
		U32						itemTempId;
    };
    struct  PT_ITEM_C2F_PICK_ITEM_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_ITEM_C2F_PICK_ITEM_DATA);  
    };
	class PT_ITEM_C2F_PICK_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_C2F_PICK_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_C2F_PICK_ITEM;
			mBaseDataSize                       =   PT_ITEM_C2F_PICK_ITEM_DATA_INFO::dataSize ;

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
    //------------------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_ITEM_F2M_PICK_ITEM
	//@功能:        frontserver向mapserver发送使用道具的回复
	//@备注:        
	//**********************************************************************/
    struct PT_ITEM_F2M_PICK_ITEM_DATA
    {
        PlayerCharacterIdType   charId;
        U32                     itemIndex;
    };
    struct PT_ITEM_F2M_PICK_ITEM_DATA_INFO
    {
        static const Int dataSize = sizeof ( PT_ITEM_F2M_PICK_ITEM_DATA );
    };
	class PT_ITEM_F2M_PICK_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_F2M_PICK_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_F2M_PICK_ITEM;
			mBaseDataSize                       =   PT_ITEM_F2M_PICK_ITEM_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
    //------------------------------------- ----------------------------------------------------
	//**********************************************************************
	//@名字:        PT_ITEM_M2C_PICK_ITEM
	//@功能:        mapserver向客户端同步场景中的道具
	//@备注:        
	//**********************************************************************/
    struct PT_ITEM_M2C_PICK_ITEM_DATA
    {
        PlayerCharacterIdType   charid;
		Int						index;
        U32                     itemid;
        U32                     num;
    };
    struct PT_ITEM_M2C_PICK_ITEM_DATA_INFO
    {
        static const Int dataSize = sizeof ( PT_ITEM_M2C_PICK_ITEM_DATA );
    };
	class PT_ITEM_M2C_PICK_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_M2C_PICK_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_M2C_PICK_ITEM;
			mBaseDataSize                       =   PT_ITEM_M2C_PICK_ITEM_DATA_INFO::dataSize ;

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
	//@名字:        PT_ITEM_M2C_DROP_ITEM_DISAPPEAR
	//@功能:        mapserver向客户端同步场景中消失的道具
	//@备注:        
	//**********************************************************************/
	struct PT_ITEM_M2C_DROP_ITEM_DISAPPEAR_DATA
	{
		Int						index;
		U32                     itemid;
		U32                     num;
	};
	struct PT_ITEM_M2C_DROP_ITEM_DISAPPEAR_DATA_INFO
	{
		static const Int dataSize = sizeof ( PT_ITEM_M2C_DROP_ITEM_DISAPPEAR_DATA );
	};
	class PT_ITEM_M2C_DROP_ITEM_DISAPPEAR_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_M2C_DROP_ITEM_DISAPPEAR_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_M2C_DROP_ITEM_DISAPPEAR;
			mBaseDataSize                       =   PT_ITEM_M2C_DROP_ITEM_DISAPPEAR_DATA_INFO::dataSize ;

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
	//@名字:        PT_ITEM_M2F_PICK_ITEM
	//@功能:        mapserver向frontserver同步场景中被拾取的道具
	//@备注:        
	//**********************************************************************/
    struct PT_ITEM_M2F_PICK_ITEM_DATA
    {
		I32						netId;
        PlayerCharacterIdType   charid;
        U32                     itemid;
        U32                     num;
    };
    struct  PT_ITEM_M2F_PICK_ITEM_DATA_INFO
    {
        static const Int dataSize = sizeof ( PT_ITEM_M2F_PICK_ITEM_DATA );
    };
	class PT_ITEM_M2F_PICK_ITEM_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_M2F_PICK_ITEM_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_M2F_PICK_ITEM;
			mBaseDataSize                       =   PT_ITEM_M2F_PICK_ITEM_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_ITEM_M2C_ATFD_REWARD
	//@功能:        mapserver向客户端发送通关后的奖励道具
	//@备注:        
	//**********************************************************************/
	struct PT_ITEM_M2C_ATFD_REWARD_DATA
	{
		U32                     groupItemId;
		Bool					isShow;					//true表示显示，false表示客户端异常发包。
	};
	struct  PT_ITEM_M2C_ATFD_REWARD_DATA_INFO
	{
		static const Int dataSize = sizeof ( PT_ITEM_M2C_ATFD_REWARD_DATA );
	};
	class PT_ITEM_M2C_ATFD_REWARD_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_M2C_ATFD_REWARD_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_M2C_ATFD_REWARD;
			mBaseDataSize                       =   PT_ITEM_M2C_ATFD_REWARD_DATA_INFO::dataSize ;

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
	//@名字:        PT_ITEM_M2F_ATFD_REWARD
	//@功能:        mapserver向frontserver发送通关后的奖励道具
	//@备注:        
	//**********************************************************************/
	struct PT_ITEM_M2F_ATFD_REWARD_DATA
	{
		U32                     groupItemId;
		I32						netId;
		PlayerCharacterIdType	playerCharId;
	};
	struct  PT_ITEM_M2F_ATFD_REWARD_DATA_INFO
	{
		static const Int dataSize = sizeof ( PT_ITEM_M2F_ATFD_REWARD_DATA );
	};
	class PT_ITEM_M2F_ATFD_REWARD_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_M2F_ATFD_REWARD_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_M2F_ATFD_REWARD;
			mBaseDataSize                       =   PT_ITEM_M2F_ATFD_REWARD_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_ITEM_C2M_ATFD_REWARD
	//@功能:        客户端向mapserver发送通关后的奖励道具的请求
	//@备注:        
	//**********************************************************************/
	struct PT_ITEM_C2M_ATFD_REWARD_DATA
	{
		U32                     groupItemId;
		PlayerCharacterIdType	playerCharId;
	};
	struct  PT_ITEM_C2M_ATFD_REWARD_DATA_INFO
	{
		static const Int dataSize = sizeof ( PT_ITEM_C2M_ATFD_REWARD_DATA );
	};
	class PT_ITEM_C2M_ATFD_REWARD_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_C2M_ATFD_REWARD_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_C2M_ATFD_REWARD;
			mBaseDataSize                       =   PT_ITEM_C2M_ATFD_REWARD_DATA_INFO::dataSize ;

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
	//-----------------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_ITEM_F2C_ADD_MONEY
	//@功能:        frontserver向客户端发送加钱的消息
	//@备注:        
	//**********************************************************************/
	struct PT_ITEM_F2C_ADD_MONEY_DATA
	{
		Int                     moneyNum;
		Byte					moneyType;					
	};
	struct  PT_ITEM_F2C_ADD_MONEY_DATA_INFO
	{
		static const Int dataSize = sizeof ( PT_ITEM_F2C_ADD_MONEY_DATA );
	};
	class PT_ITEM_F2C_ADD_MONEY_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_F2C_ADD_MONEY_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_F2C_ADD_MONEY;
			mBaseDataSize                       =   PT_ITEM_F2C_ADD_MONEY_DATA_INFO::dataSize ;

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
	//@名字:        PT_ITEM_F2C_ADD_EXP
	//@功能:        frontserver向客户端发送加经验的消息
	//@备注:        
	//**********************************************************************/
	struct PT_ITEM_F2C_ADD_EXP_DATA
	{
		Byte					charType;
		Byte					expType;
		U32                     expNum;
		IdType					charId;	
	};
	struct  PT_ITEM_F2C_ADD_EXP_DATA_INFO
	{
		static const Int dataSize = sizeof ( PT_ITEM_F2C_ADD_EXP_DATA );
	};
	class PT_ITEM_F2C_ADD_EXP_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_F2C_ADD_EXP_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_F2C_ADD_EXP;
			mBaseDataSize                       =   PT_ITEM_F2C_ADD_EXP_DATA_INFO::dataSize ;

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
	//@名字:        PT_ITEM_M2C_DROP_ITEM_LIST
	//@功能:        mapserver向客户端同步道具掉落的消息
	//@备注:        
	//**********************************************************************/
	struct netDropItemData
	{
		U32		index;
		U32		itemTempId;
		U32		num;
		Vec2	pos;
	};
	struct PT_ITEM_M2C_DROP_ITEM_LIST_DATA
	{
		Int nCount;
		netDropItemData data[1];
	};
	struct  PT_ITEM_M2C_DROP_ITEM_LIST_DATA_INFO
	{
		static const Int elemSize = sizeof ( netDropItemData );
		static const Int headSize = sizeof ( PT_ITEM_M2C_DROP_ITEM_LIST_DATA ) - elemSize;
		static const Int dataSize = sizeof ( PT_ITEM_M2C_DROP_ITEM_LIST_DATA );
	};
	class PT_ITEM_M2C_DROP_ITEM_LIST_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_M2C_DROP_ITEM_LIST_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_M2C_DROP_ITEM_LIST;
			mBaseDataSize                       =   PT_ITEM_M2C_DROP_ITEM_LIST_DATA_INFO::dataSize ;

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
	//**********************************************************************
	//@名字:        PT_ITEM_M2F_DROP_ITEM_ADD_EXP
	//@功能:        mapserver向frontserver发送道具掉落的消息
	//@备注:        
	//**********************************************************************/
	struct PT_ITEM_M2F_DROP_ITEM_ADD_EXP_DATA
	{
		AccountIdType			accountId;
		PlayerCharacterIdType	charId;
		U32						itemId;
		Int						itemNum;
	};
	struct  PT_ITEM_M2F_DROP_ITEM_ADD_EXP_DATA_INFO
	{
		static const Int dataSize = sizeof ( PT_ITEM_M2F_DROP_ITEM_ADD_EXP_DATA );
	};
	class PT_ITEM_M2F_DROP_ITEM_ADD_EXP_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_M2F_DROP_ITEM_ADD_EXP_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_M2F_DROP_ITEM_ADD_EXP;
			mBaseDataSize                       =   PT_ITEM_M2F_DROP_ITEM_ADD_EXP_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_ITEM_C2F_QUEST_REWARD
	//@功能:        客户端向frontserver请求任务奖励的消息
	//@备注:        
	//**********************************************************************/
	struct PT_ITEM_C2F_QUEST_REWARD_DATA
	{
		U32                     groupItemId;
		PlayerCharacterIdType	playerCharId;
	};
	struct  PT_ITEM_C2F_QUEST_REWARD_DATA_INFO
	{
		static const Int dataSize = sizeof ( PT_ITEM_C2F_QUEST_REWARD_DATA );
	};
	class PT_ITEM_C2F_QUEST_REWARD_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ITEM_C2F_QUEST_REWARD_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ITEM;
			mType                               =   PT_ITEM_C2F_QUEST_REWARD;
			mBaseDataSize                       =   PT_ITEM_C2F_QUEST_REWARD_DATA_INFO::dataSize ;

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