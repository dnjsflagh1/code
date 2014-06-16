/******************************************************************************/
#ifndef _PLAYER_H_
#define _PLAYER_H_
/******************************************************************************/
#include "WorldCorePreqs.h"
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//玩家对象，表示一个客户端登入的玩家。
	/******************************************************************************/
    enum  PLAYER_STATE
    {
        PLAYER_STATE_NULL = 0,

        PLAYER_STATE_NORMAL,
        PLAYER_STATE_TEST,
        PLAYER_STATE_LOCK,
        PLAYER_STATE_DELETE,

        PLAYER_STATE_MAX
    };
    //-------------------------------------------------------------------------------------
    struct PlayerData
    {
        Str16	            accountName;                       //帐号名
        Str16	            accountPsw;                        //密码
        Str16               superPsw;                          //超级密码
        U64 	            accountId;                         //帐号ID
        PLAYER_STATE	    state;                              //帐号的状态类型
        U32	                vip;                                //VIP帐号
        U32	                currGameBin;                        //当前帐号内的游戏币数量
        U32                 totalGameBinPast;                   //累计充值过的游戏币总量
        U32	                lastLoginIp;                        //最后的连接IP
        U32                 lastServerId;                       //最近一次所在的serverID
        U32                 loginTimes;                         //登录的次数
        U64                 lastClanId;                         //最近使用的氏族ID
        U64	                startForbidTime;                    //帐号被封的开始时间
        U64	                endForbidTime;                      //帐号被封的结束时间
        U64	                lastAddBinTime;
        U64	                lastCostBinTime;                    //最近一次消费额游戏币的时间
        U64	                lastLoginTime;
        U64	                lastLogoutTime; 
        U64                 createTime;
        U64                 allInGameTime;
        //-------------------------------------------------------------------------------------   
        PlayerData()
            :accountId(0),    
            state(PLAYER_STATE_NULL),          
            vip(0),            
            currGameBin(0),    
            totalGameBinPast(0),
            lastLoginIp(0),    
            lastServerId(0),   
            loginTimes(0),     
            lastClanId(0),    
            startForbidTime(0),
            endForbidTime(0),  
            lastAddBinTime(0),
            lastCostBinTime(0),
            lastLoginTime(0),
            lastLogoutTime(0), 
            createTime(0),
            allInGameTime(0)
        {
            ;
        }
        //-------------------------------------------------------------------------------------
        PlayerData& operator=(const PlayerData& A)
        {
            accountName               = A.accountName;     
            accountPsw                = A.accountPsw;      
            superPsw                  = A.superPsw;        
            accountId                 = A.accountId;       
            state                     = A.state;           
            vip                       = A.vip;             
            currGameBin               = A.currGameBin;     
            totalGameBinPast          = A.totalGameBinPast;
            lastLoginIp               = A.lastLoginIp;     
            lastServerId              = A.lastServerId;    
            loginTimes                = A.loginTimes;      
            lastClanId                = A.lastClanId;      
            startForbidTime           = A.startForbidTime; 
            endForbidTime             = A.endForbidTime;   
            lastAddBinTime            = A.lastAddBinTime;
            lastCostBinTime           = A.lastCostBinTime; 
            lastLoginTime             = A.lastLoginTime;
            lastLogoutTime            = A.lastLogoutTime; 
            createTime                = A.createTime;
            allInGameTime             = A.allInGameTime;
        }
    };
    /******************************************************************************/
    class Player
    {   
    public:
		Player();
		virtual ~Player();

        //////////////////////////////////////////////////////////

		//@{
		//帐号信息
    public:
		PlayerIdType	getAccountID();
		void			setAccountID(PlayerIdType id);

		const Str16&	getName();
		void			setName(CChar16* name);
		
		const Str16&	getPassword();
		void			setPassword(CChar16* password);
		//@}

        //////////////////////////////////////////////////////////
        
        // 得到槽位编号
        virtual I32     getSlotID( Byte slotGroup = 0 ) {return 0;};

        //////////////////////////////////////////////////////////

        PlayerData*     getData(){return &mPlayerData;}
        void            setData(PlayerData* pData){ mPlayerData = *pData;}

        //////////////////////////////////////////////////////////

	private:

		PlayerData  mPlayerData;

    };

}
#endif