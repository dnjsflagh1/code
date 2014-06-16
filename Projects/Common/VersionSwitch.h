/******************************************************************************/
#ifndef _VERSIONSWITCH_H_
#define _VERSIONSWITCH_H_
/******************************************************************************/

/******************************************************************************/
//游戏加密
/******************************************************************************/
//MG Encrypt Key
#define ENCRYPT_KEY1	0x111A630D
#define ENCRYPT_KEY2	0x12A2B0B5
#define ENCRYPT_KEY3	0x1A5378FF
#define ENCRYPT_KEY4	0x1DCCD2E3

/******************************************************************************/
//游戏版本控制
#define _SCHINESE
/******************************************************************************/
#define GAME_APP_TITLE_PART1		L" - Ver. "
#define GAME_APP_TITLE_PART2		L" 【"
#define GAME_APP_TITLE_PART3		L"】 "
//CH -- 簡體中文
//TH -- 繁體中文
//JP -- 日文
//EN -- 英文
//District Setting
//地區號. 資料片號碼. 版本號碼. 修正次數 
#ifdef _SCHINESE	//China
    #define CLIENT_VERSION_NUMBER		"CH.20121217"
    #define SERVER_VERSION_NUMBER		"CH.20121217"
    #define _MG_RELEASE_20121217
#endif
#ifdef _TCHINESE	//Taiwan, Hong Kong
    #define CLIENT_VERSION_NUMBER		"TH.20121217"
    #define SERVER_VERSION_NUMBER		"TH.20121217"
#endif

/******************************************************************************/
//游戏逻辑控制
/******************************************************************************/
#ifdef _MG_RELEASE_20121217

    // ------------------------------------------------------------------
    //@ use
    // ------------------------------------------------------------------
    #define _SYSTEM_GM_				    // 秘密指令
    #define _CHECK_VER_					// 版本检查
    #define _SYSTEM_ACCELERATION_HACK_	// 防加速
    #define _SYSTEM_GM_TOOL_            // GM工具
    #define _USE_MAX_LVL
    // -------------------------------------------------------------------
    //@ unUse
    /* -------------------------------------------------------------------
    #define _SYSTEM_GUILD_              // 公會
    #define _SYSTEM_AUCTION_            // 拍卖
    #define _SYSTEM_RMBSHOP_            // 商城
    #define _SYSTEM_MAIL_				// 郵件

    #define _SYSTEM_FCM_				// 防沉迷
    #define _SYSTEM_NAVI_               // 航海
    #define _SYSTEM_INLAY_              // 镶嵌
    #define _SYSTEM_TALENT_             // 天赋  

    #define _LOG_SERVER_				// log服务器
    #define _USE_AI_SERVER		        // Boss是否使用AIServer
    ------------------------------------------------------------------- */
#endif

/******************************************************************************/
#endif

