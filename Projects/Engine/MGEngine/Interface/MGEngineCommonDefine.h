/******************************************************************************/
#ifndef _H_MGENGINE_COMMON_DEFINE_
#define _H_MGENGINE_COMMON_DEFINE_
/******************************************************************************/

#include "MGTypes.h"

/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//控件动画类型
    /******************************************************************************/
	enum WIDGET_ACTION
	{
		WIDGET_ACTION_CENTER_TO_EDGE,
		WIDGET_ACTION_EDGE_TO_CENTER,

		WIDGET_ACTION_COUNT
	};
	static const std::string widgetAction[WIDGET_ACTION_COUNT] = {
		"action_CenterToEdge",
		"action_EdgeToCenter"
	};
	/******************************************************************************/
    //鼠标消息
    /******************************************************************************/
    enum MouseCode
    {
        MB_Left = 0, 
        MB_Right, 
        MB_Middle,
        MB_Button3, 
        MB_Button4,	
        MB_Button5, 
        MB_Button6,	
        MB_Button7
    };

    /******************************************************************************/
    //键盘消息
    /******************************************************************************/
    enum KeyCode
    {
        KC_UNASSIGNED  = 0x00,
        KC_ESCAPE      = 0x01,
        KC_1           = 0x02,
        KC_2           = 0x03,
        KC_3           = 0x04,
        KC_4           = 0x05,
        KC_5           = 0x06,
        KC_6           = 0x07,
        KC_7           = 0x08,
        KC_8           = 0x09,
        KC_9           = 0x0A,
        KC_0           = 0x0B,
        KC_MINUS       = 0x0C,    // - on main keyboard
        KC_EQUALS      = 0x0D,
        KC_BACK        = 0x0E,    // backspace
        KC_TAB         = 0x0F,
        KC_Q           = 0x10,
        KC_W           = 0x11,
        KC_E           = 0x12,
        KC_R           = 0x13,
        KC_T           = 0x14,
        KC_Y           = 0x15,
        KC_U           = 0x16,
        KC_I           = 0x17,
        KC_O           = 0x18,
        KC_P           = 0x19,
        KC_LBRACKET    = 0x1A,
        KC_RBRACKET    = 0x1B,
        KC_RETURN      = 0x1C,    // Enter on main keyboard
        KC_LCONTROL    = 0x1D,
        KC_A           = 0x1E,
        KC_S           = 0x1F,
        KC_D           = 0x20,
        KC_F           = 0x21,
        KC_G           = 0x22,
        KC_H           = 0x23,
        KC_J           = 0x24,
        KC_K           = 0x25,
        KC_L           = 0x26,
        KC_SEMICOLON   = 0x27,
        KC_APOSTROPHE  = 0x28,
        KC_GRAVE       = 0x29,    // accent
        KC_LSHIFT      = 0x2A,
        KC_BACKSLASH   = 0x2B,
        KC_Z           = 0x2C,
        KC_X           = 0x2D,
        KC_C           = 0x2E,
        KC_V           = 0x2F,
        KC_B           = 0x30,
        KC_N           = 0x31,
        KC_M           = 0x32,
        KC_COMMA       = 0x33,
        KC_PERIOD      = 0x34,    // . on main keyboard
        KC_SLASH       = 0x35,    // / on main keyboard
        KC_RSHIFT      = 0x36,
        KC_MULTIPLY    = 0x37,    // * on numeric keypad
        KC_LMENU       = 0x38,    // left Alt
        KC_SPACE       = 0x39,
        KC_CAPITAL     = 0x3A,
        KC_F1          = 0x3B,
        KC_F2          = 0x3C,
        KC_F3          = 0x3D,
        KC_F4          = 0x3E,
        KC_F5          = 0x3F,
        KC_F6          = 0x40,
        KC_F7          = 0x41,
        KC_F8          = 0x42,
        KC_F9          = 0x43,
        KC_F10         = 0x44,
        KC_NUMLOCK     = 0x45,
        KC_SCROLL      = 0x46,    // Scroll Lock
        KC_NUMPAD7     = 0x47,
        KC_NUMPAD8     = 0x48,
        KC_NUMPAD9     = 0x49,
        KC_SUBTRACT    = 0x4A,    // - on numeric keypad
        KC_NUMPAD4     = 0x4B,
        KC_NUMPAD5     = 0x4C,
        KC_NUMPAD6     = 0x4D,
        KC_ADD         = 0x4E,    // + on numeric keypad
        KC_NUMPAD1     = 0x4F,
        KC_NUMPAD2     = 0x50,
        KC_NUMPAD3     = 0x51,
        KC_NUMPAD0     = 0x52,
        KC_DECIMAL     = 0x53,    // . on numeric keypad
        KC_OEM_102     = 0x56,    // < > | on UK/Germany keyboards
        KC_F11         = 0x57,
        KC_F12         = 0x58,
        KC_F13         = 0x64,    //                     (NEC PC98)
        KC_F14         = 0x65,    //                     (NEC PC98)
        KC_F15         = 0x66,    //                     (NEC PC98)
        KC_KANA        = 0x70,    // (Japanese keyboard)
        KC_ABNT_C1     = 0x73,    // / ? on Portugese (Brazilian) keyboards
        KC_CONVERT     = 0x79,    // (Japanese keyboard)
        KC_NOCONVERT   = 0x7B,    // (Japanese keyboard)
        KC_YEN         = 0x7D,    // (Japanese keyboard)
        KC_ABNT_C2     = 0x7E,    // Numpad . on Portugese (Brazilian) keyboards
        KC_NUMPADEQUALS= 0x8D,    // = on numeric keypad (NEC PC98)
        KC_PREVTRACK   = 0x90,    // Previous Track (KC_CIRCUMFLEX on Japanese keyboard)
        KC_AT          = 0x91,    //                     (NEC PC98)
        KC_COLON       = 0x92,    //                     (NEC PC98)
        KC_UNDERLINE   = 0x93,    //                     (NEC PC98)
        KC_KANJI       = 0x94,    // (Japanese keyboard)
        KC_STOP        = 0x95,    //                     (NEC PC98)
        KC_AX          = 0x96,    //                     (Japan AX)
        KC_UNLABELED   = 0x97,    //                        (J3100)
        KC_NEXTTRACK   = 0x99,    // Next Track
        KC_NUMPADENTER = 0x9C,    // Enter on numeric keypad
        KC_RCONTROL    = 0x9D,
        KC_MUTE        = 0xA0,    // Mute
        KC_CALCULATOR  = 0xA1,    // Calculator
        KC_PLAYPAUSE   = 0xA2,    // Play / Pause
        KC_MEDIASTOP   = 0xA4,    // Media Stop
        KC_VOLUMEDOWN  = 0xAE,    // Volume -
        KC_VOLUMEUP    = 0xB0,    // Volume +
        KC_WEBHOME     = 0xB2,    // Web home
        KC_NUMPADCOMMA = 0xB3,    // , on numeric keypad (NEC PC98)
        KC_DIVIDE      = 0xB5,    // / on numeric keypad
        KC_SYSRQ       = 0xB7,
        KC_RMENU       = 0xB8,    // right Alt
        KC_PAUSE       = 0xC5,    // Pause
        KC_HOME        = 0xC7,    // Home on arrow keypad
        KC_UP          = 0xC8,    // UpArrow on arrow keypad
        KC_PGUP        = 0xC9,    // PgUp on arrow keypad
        KC_LEFT        = 0xCB,    // LeftArrow on arrow keypad
        KC_RIGHT       = 0xCD,    // RightArrow on arrow keypad
        KC_END         = 0xCF,    // End on arrow keypad
        KC_DOWN        = 0xD0,    // DownArrow on arrow keypad
        KC_PGDOWN      = 0xD1,    // PgDn on arrow keypad
        KC_INSERT      = 0xD2,    // Insert on arrow keypad
        KC_DELETE      = 0xD3,    // Delete on arrow keypad
        KC_LWIN        = 0xDB,    // Left Windows key
        KC_RWIN        = 0xDC,    // Right Windows key
        KC_APPS        = 0xDD,    // AppMenu key
        KC_POWER       = 0xDE,    // System Power
        KC_SLEEP       = 0xDF,    // System Sleep
        KC_WAKE        = 0xE3,    // System Wake
        KC_WEBSEARCH   = 0xE5,    // Web Search
        KC_WEBFAVORITES= 0xE6,    // Web Favorites
        KC_WEBREFRESH  = 0xE7,    // Web Refresh
        KC_WEBSTOP     = 0xE8,    // Web Stop
        KC_WEBFORWARD  = 0xE9,    // Web Forward
        KC_WEBBACK     = 0xEA,    // Web Back
        KC_MYCOMPUTER  = 0xEB,    // My Computer
        KC_MAIL        = 0xEC,    // Mail
        KC_MEDIASELECT = 0xED     // Media Select
    };

    enum ELM_TYPE
    {
        ET_NONE         = 0,
        ET_TEXT         = 1,
        ET_IMAGE        = 2,
    };

    /******************************************************************************/

    typedef void (__cdecl *MGENGINE_CALLBACK)(void);
    typedef void (__cdecl *PVOID_CALLBACK)(void*);
    typedef void (__cdecl *PVOIDPVOID_CALLBACK)(void*, void*);
    typedef void (__cdecl *PVOIDBOOL_CALLBACK)(void*, Bool);
    typedef void (__cdecl *PVOIDBYTE_CALLBACK)(void*, Byte);
    typedef void (__cdecl *PVOIDINT_CALLBACK)(void*, Int);
    typedef void (__cdecl *PVOIDINTINT_CALLBACK)(void*, Int, Int);
    typedef void (__cdecl *PVOIDINTINTMOUSECODE_CALLBACK)(void*, Int, Int, MouseCode);
    typedef void (__cdecl *PVOIDKEYCODECHAR_CALLBACK)(void*, KeyCode, Char);
    typedef void (__cdecl *PVOIDSTRSTR_CALLBACK)(void*, Str, Str);
    typedef void (__cdecl *PVOIDSTR_CALLBACK)(void*, Str);
    typedef void (__cdecl *PVOIDBOOLINTINT_CALLBACK)(void*, Bool, Int, Int);
    typedef void (__cdecl *PVOIDPVOIDBOOL_CALLBACK)(void*, void*, Bool);
    typedef void (__cdecl *PVOIDPVOIDBOOLREF_CALLBACK)(void*, void*, Bool&);
    typedef void (__cdecl *PVOIDBOOLREF_CALLBACK)(void*, Bool&);
    typedef void (__cdecl *PVOIDPVOIDREFRECTREF_CALLBACK)(void*, void*&, CoordI&, Byte&);
	typedef void (__cdecl *PVOIDPVOIDINT_CALLBACK)(void*, void*, Int);
	typedef void (__cdecl *PVOIDVECI2U64INTBOOL_CALLBACK)(void*, VecI2, __int64, Int, Bool);
	typedef void (__cdecl *PVOIDU64INT_CALLBACK)(void*, __int64, Int);
	typedef void (__cdecl *STRINGREF_CALLBACK)(std::string&);

    /******************************************************************************/
    typedef void* (__cdecl *GET_MGENGINE_INTERFACE_PROC)(void); 
    #define DLL_ENTRY_MGENGINE_PROC GET_MGENGINE_INTERFACE
    /******************************************************************************/
	#define MG_FLAG_NONE  0
	#define MG_FLAG(num)  (1<<(num))
	enum MGAlign
	{
		HCenter = MG_FLAG_NONE,    /**< center horizontally */
		VCenter = MG_FLAG_NONE,    /**< center vertically */
		Center = HCenter | VCenter,     /**< center in the dead center */

		Left = MG_FLAG(1),       /**< value from the left (and center vertically) */
		Right = MG_FLAG(2),      /**< value from the right (and center vertically) */
		HStretch = Left | Right,   /**< stretch horizontally proportionate to parent window (and center vertically) */

		Top = MG_FLAG(3),        /**< value from the top (and center horizontally) */
		Bottom = MG_FLAG(4),     /**< value from the bottom (and center horizontally) */
		VStretch = Top | Bottom,   /**< stretch vertically proportionate to parent window (and center horizontally) */

		Stretch = HStretch | VStretch,    /**< stretch proportionate to parent window */
		Default = Left | Top,    /**< default value (value from left and top) */

		HRelative = MG_FLAG(5),
		VRelative = MG_FLAG(6),
		Relative = HRelative | VRelative
	};
	//-------------------------------------------------------------------------------
	enum MGIMAGE_BROADCAST_TYPE
	{
		MGIMAGE_BROADCAST_TYPE_NULL,		//不播放，只显示第一帧

		MGIMAGE_BROADCAST_TYPE_ONCE,		//播放一次
		MGIMAGE_BROADCAST_TYPE_LOOP,		//循环

		MGIMAGE_BROADCAST_TYPE_MAX
	};
	//-------------------------------------------------------------------------------
	enum MGPOINTER_LEVEL					//设置等级控制鼠标的替换。
	{
		MGPOINTER_LEVEL_LOW,
		MGPOINTER_LEVEL_HIGH,
	};
	//-------------------------------------------------------------------------------
	//显示的最小时间单位
	enum MGTIMETEXT_UNIT_TYPE
	{
		MGTIMETEXT_UNIT_TYPE_NULL,

		MGTIMETEXT_UNIT_TYPE_SECOND,		//秒
		MGTIMETEXT_UNIT_TYPE_MINUTE,		//分
		MGTIMETEXT_UNIT_TYPE_HOUR,		//时
		MGTIMETEXT_UNIT_TYPE_DAY,			//天

		MGTIMETEXT_UNIT_TYPE_MAX
	};
	//显示的方式
	enum MGTIMETEXT_SHOW_TYPE
	{
		MGTIMETEXT_SHOW_TYPE_NULL,

		MGTIMETEXT_SHOW_TYPE_CD,			//CD显示时间
		MGTIMETEXT_SHOW_TYPE_REAL,		//真实时间
		MGTIMETEXT_SHOW_TYPE_GAME,		//游戏时间

		MGTIMETEXT_SHOW_TYPE_MAX
	};

    // 渲染状态
    enum RENDER_STATE
    {
        RS_IDLE         = 0,
        RS_PRE          = 1,
        RS_POST         = 2,
    };

}
/******************************************************************************/
#endif
/******************************************************************************/