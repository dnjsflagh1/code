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
	//@������:      �쿪��
	//@Э����:      ???
	**********************************************************************/

    /******************************************************************************/
    //��Ϸ��Ʒ������
    /******************************************************************************/
    enum ItemNetPacketType
    {
        PT_ITEM_UNKNOW = 0,

		PT_ITEM_S2C_ADDLIST_BEGIN,												//��ʼ������֪ͨ�ͻ�����ձ�����
        PT_ITEM_S2C_ADDLIST,                                                    //�ӵ����屳�� ����¼ʱ��
        PT_ITEM_S2C_ADDLIST_END,                                                //�����ı�־��
        
        PT_ITEM_S2C_ADD,                                                        //����ӵ���
		PT_ITEM_S2C_UPDATE_NUM_LIST,                                            //�޸����е�������
        PT_ITEM_C2S_DELETE,                                                     //�ͻ��˴ӽ�����ɾ��
        PT_ITEM_S2C_DELETE,                                                     //�������ӽ�����ɾ���Ľ����
        PT_ITEM_C2S_CHANGEPOS,                                                  //�任λ�ã��ͻ������󣩡�
        PT_ITEM_S2C_CHANGEPOS,                                                  //�任λ�ý��(������ͬ��)��

        PT_ITEM_C2S_SPLIT,                                                      //�ͻ���������
        PT_ITEM_S2C_SPLIT,                                                      //���µ��ߵĶѵ���
             
        PT_ITEM_F2M_EQUIP_LIST,                                                 //֪ͨmapServer��¼��ɫ��װ��
        PT_ITEM_F2M_CHANGE_EQUIP,                                               //֪ͨMapServer��װ
        PT_ITEM_M2C_EQUIP_LIST,                                                 //�㲥��ɫ��װ��
        PT_ITEM_M2C_CHANGE_EQUIP,                                               //�㲥��ɫ��װ��

        PT_ITEM_C2F_USE_ITEM,                                                   //�ͻ�������ʹ����Ʒ
        PT_ITEM_F2M_USE_ITEM,                                                   //����mapServerʹ����Ʒ
        PT_ITEM_F2C_USE_ITEM,                                                   //���߿ͻ����Ƿ�ɹ���
		PT_ITEM_M2F_USE_ITEM,													//����FrontServerʹ����Ʒ��ɾ����Ʒ��

		PT_ITEM_M2C_DROP_ITEM_LIST,												//mapServerͬ��������Ϣ
		PT_ITEM_M2F_DROP_ITEM_ADD_EXP,											//mapServer������Ʒʱ������ֱ�Ӽ� ylh
        PT_ITEM_C2F_PICK_ITEM,                                                  //�ͻ���ʰȡ����
        PT_ITEM_F2M_PICK_ITEM,                                                  //֪ͨMapServerɾ����ͼ�еĵ���
        PT_ITEM_M2C_PICK_ITEM,                                                  //MapServer�㲥�ͻ���ɾ����ͼ�ϵĵ���
        PT_ITEM_M2F_PICK_ITEM,                                                  //֪ͨfrontserver�ӵ��ߡ�
		PT_ITEM_F2C_PICK_ITEM,													//�����������뼰ʱ��������

		PT_ITEM_F2C_ADD_MONEY,													//֪ͨ�ͻ��˼�Ǯ
		PT_ITEM_F2C_ADD_EXP,													//֪ͨ�ͻ��˼Ӿ��顣

		PT_ITEM_M2C_ATFD_REWARD,												//֪ͨClient��ʾ���Ǹ�������
		PT_ITEM_C2M_ATFD_REWARD,												//����MapServer��ȡ���Ǹ�������
		PT_ITEM_M2F_ATFD_REWARD,												//֪ͨFrontServer���͹��Ǹ�������
		PT_ITEM_F2C_ATFD_REWARD,												//�����������뼰ʱ��������
		
		PT_ITEM_C2F_QUEST_REWARD,                                               //��FrontServer��ȡ������

		PT_ITEM_M2C_DROP_ITEM_DISAPPEAR,										//������Ʒ ʱ�䵽�ˣ� �Զ���ʧ
	};

#pragma pack (push)
#pragma pack (1)

    ///���ݰ�����
    
    //-----------------------------------------------------------------------------------------
	//**********************************************************************
	//@����:        PT_ITEM_S2C_ADDLIST
	//@����:        frontServerr��ͻ��˷��͵����б�
	//@��ע:        ��½ʱ���ʹ�DB��ȡ�ĵ�������
	//**********************************************************************/
    //���屳��
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
	//@����:        PT_ITEM_S2C_ADD
	//@����:        frontServerr��ͻ��˷�����������
	//@��ע:        
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
	//@����:        PT_ITEM_S2C_UPDATE_NUM_LIST
	//@����:        frontServerr��ͻ��˷��͸��µ����б�
	//@��ע:        
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
	 //@����:        PT_ITEM_C2S_DELETE
	 //@����:        �ͻ�����frontServerr����ɾ������
	 //@��ע:        
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
	//@����:        PT_ITEM_S2C_DELETE
	//@����:        frontServerr��ͻ��˷���ȷ��ɾ�����ߵ���Ϣ
	//@��ע:        
	//**********************************************************************/
    //ö��
    enum    itembag_del_res
    {
        itembag_del_res_Succeed,
        itembag_del_res_Error_ItemNone,                       //û�е��ߡ�
        itembag_del_res_Error_Delete,                         //����ɾ��
        itembag_del_res_Error_UI,                             //�˽���û��ɾ������
        itembag_del_res_Error_Not_Enough_Num                  //��������
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
	//@����:        PT_ITEM_C2S_CHANGEPOS
	//@����:        �ͻ�����frontServerr���ͽ�������λ�õ�����
	//@��ע:        
	//**********************************************************************/
    struct PT_ITEM_C2S_CHANGEPOS_DATA
    {
        PlayerCharacterIdType   id;
        U32             IndexSend;                              //�����λ�á�
        Byte            sendType;
        U32             IndexRecv;                              //���ܵ�λ��
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
	//@����:        PT_ITEM_S2C_CHANGEPOS
	//@����:        frontServerr��ͻ��˷��ͽ�������λ�õĻظ�
	//@��ע:        
	//**********************************************************************/
    //ö��
    enum    item_changepos_res
    {
        item_changepos_res_Succeed,
        item_changepos_res_Error_pos,                       //λ��û�н��
        item_changepos_res_Error_notEquip,                  //����װ��
        item_changepos_res_Error_Equip_pos,                 //װ��λ����
        item_changepos_res_Error_notchange,                 //�����ƶ������λ��
        item_changepos_res_Error_character_level,           //��ɫ�ȼ�����
        item_changepos_res_Error_unknown,                   //δ֪����
    };
    struct PT_ITEM_S2C_CHANGEPOS_DATA
    {
        PlayerCharacterIdType   id;
        U32             IndexSend;                              //�����λ�á�
        Byte            sendType;
        U32             IndexRecv;                              //���ܵ�λ��
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
	//@����:        PT_ITEM_C2S_SPLIT
	//@����:        �ͻ�����frontServerr���ͷֽ����λ�õ�����
	//@��ע:        
	//**********************************************************************/
    struct PT_ITEM_C2S_SPLIT_DATA
    {
        PlayerCharacterIdType   characterId;        //���ڵĵ���������һ����ɫ
      //IdType          xItemDBID;                  //��ֵĵ���ID
		UInt            selfSlot;
        Byte            selfType;                   //���ڽ���
        Byte            splitType;                  //����Ľ���
       // UInt            splitPos;                   //λ��
        UInt            splitNum;                   //����
		UInt            selectIndex;                //ѡ��λ�õ����к�
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
	//@����:        PT_ITEM_S2C_SPLIT
	//@����:        frontServerr��ͻ��˷��ͷֽ����λ�õĻظ�
	//@��ע:        
	//**********************************************************************/
    enum item_split_res
    {
        item_split_res_Succeed,
        item_split_res_Error_cannot,                //���ֽܷ�
        item_split_res_Error_ful,                   //����������
    };
    struct PT_ITEM_S2C_SPLIT_DATA
    {
		PlayerCharacterIdType   characterId;                 //���ڵĵ���������һ����ɫ
		//IdType          xItemDBID;                  //��ֵĵ���ID
		UInt            selfSlot;
		Byte            selfType;                   //���ڽ���
		Byte            splitType;                  //����Ľ���
		//UInt            splitPos;                   //λ��
		UInt            splitNum;                   //����
		UInt            selectIndex;                //ѡ��λ�õ����к�
		
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
	//@����:        PT_ITEM_F2M_EQUIP_LIST
	//@����:        frontServerr��mapserver���ͷֽ��佫װ���б�
	//@��ע:        
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
	//@����:        PT_ITEM_M2C_EQUIP_LIST
	//@����:        mapserver��ͻ���ͬ���佫װ���б�
	//@��ע:        
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
	//@����:        PT_ITEM_F2M_CHANGE_EQUIP
	//@����:        frontserver��mapserver�����佫װ���ĸ���
	//@��ע:        
	//**********************************************************************/
    struct PT_ITEM_F2M_CHANGE_EQUIP_DATA
    {
        PlayerCharacterIdType   charid;
        netItemEquip            putonEquipAttr;      //���ϵ�װ��id
        U32                     pos;                 //λ��
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
	//@����:        PT_ITEM_M2C_CHANGE_EQUIP
	//@����:        mapserver��ͻ���ͬ���佫װ���ĸ���
	//@��ע:        
	//**********************************************************************/
    struct PT_ITEM_M2C_CHANGE_EQUIP_DATA
    {
        PlayerCharacterIdType   charid;
        U32                     putonEquipId;        //���ϵ�װ��id
        U32                     pos;                 //λ��
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
	//@����:        PT_ITEM_C2F_USE_ITEM
	//@����:        �ͻ�����frontserver����ʹ�õ��ߵ�����
	//@��ע:        
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
	//@����:        PT_ITEM_F2C_USE_ITEM
	//@����:        frontserver��ͻ��˷���ʹ�õ��ߵĻظ�
	//@��ע:        
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
	//@����:        PT_ITEM_F2M_USE_ITEM
	//@����:        frontserver��mapserver����ʹ�õ��ߵ�����
	//@��ע:        
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
	//@����:        PT_ITEM_M2F_USE_ITEM
	//@����:        mapserver��frontserver����ʹ�õ��ߵĻظ�
	//@��ע:        
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
	//@����:        PT_ITEM_C2F_PICK_ITEM
	//@����:        �ͻ�����frontserver����ʰȡ���ߵ�����
	//@��ע:        
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
	//@����:        PT_ITEM_F2M_PICK_ITEM
	//@����:        frontserver��mapserver����ʹ�õ��ߵĻظ�
	//@��ע:        
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
	//@����:        PT_ITEM_M2C_PICK_ITEM
	//@����:        mapserver��ͻ���ͬ�������еĵ���
	//@��ע:        
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
	//@����:        PT_ITEM_M2C_DROP_ITEM_DISAPPEAR
	//@����:        mapserver��ͻ���ͬ����������ʧ�ĵ���
	//@��ע:        
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
	//@����:        PT_ITEM_M2F_PICK_ITEM
	//@����:        mapserver��frontserverͬ�������б�ʰȡ�ĵ���
	//@��ע:        
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
	//@����:        PT_ITEM_M2C_ATFD_REWARD
	//@����:        mapserver��ͻ��˷���ͨ�غ�Ľ�������
	//@��ע:        
	//**********************************************************************/
	struct PT_ITEM_M2C_ATFD_REWARD_DATA
	{
		U32                     groupItemId;
		Bool					isShow;					//true��ʾ��ʾ��false��ʾ�ͻ����쳣������
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
	//@����:        PT_ITEM_M2F_ATFD_REWARD
	//@����:        mapserver��frontserver����ͨ�غ�Ľ�������
	//@��ע:        
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
	//@����:        PT_ITEM_C2M_ATFD_REWARD
	//@����:        �ͻ�����mapserver����ͨ�غ�Ľ������ߵ�����
	//@��ע:        
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
	//@����:        PT_ITEM_F2C_ADD_MONEY
	//@����:        frontserver��ͻ��˷��ͼ�Ǯ����Ϣ
	//@��ע:        
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
	//@����:        PT_ITEM_F2C_ADD_EXP
	//@����:        frontserver��ͻ��˷��ͼӾ������Ϣ
	//@��ע:        
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
	//@����:        PT_ITEM_M2C_DROP_ITEM_LIST
	//@����:        mapserver��ͻ���ͬ�����ߵ������Ϣ
	//@��ע:        
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
	//@����:        PT_ITEM_M2F_DROP_ITEM_ADD_EXP
	//@����:        mapserver��frontserver���͵��ߵ������Ϣ
	//@��ע:        
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
	//@����:        PT_ITEM_C2F_QUEST_REWARD
	//@����:        �ͻ�����frontserver��������������Ϣ
	//@��ע:        
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