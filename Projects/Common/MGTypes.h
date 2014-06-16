/******************************************************************************/
#ifndef _MGTYPES_H_
#define _MGTYPES_H_
/******************************************************************************/
#include "MGStd.h"
/******************************************************************************/

namespace MG{

    /////////////////////////////////////////////////////////////////////////////////

    #if (defined(WIN32) || defined(WIN64))
    #define		PLATFORM(windows,unix) windows
    #define		MG_PLATFORM_WINDOWS 1
    #define		WINDOWS
    #if defined(WIN32)
    #define MG_CPU_32
    #elif defined(WIN64)
    #define MG_CPU_64
    #endif
    #elif (defined(__linux__) )
    #define		PLATFORM(windows,unix) unix
    #define		MG_PLATFORM_LINUX 1
    #define		LINUX
    #if defined(__LP64__)
    #define MG_CPU_64
    #else
    #define MG_CPU_32
    #endif
    #elif (defined(__FreeBSD__) )
    #define		PLATFORM(windows,unix) unix
    #define		MG_PLATFORM_FREEBSD 1
    #define		FREEBSD
    #else
    #error Error: unsupport platform
    #endif

    /////////////////////////////////////////////////////////////////////////////////

	typedef bool            Bool    ; // Boolean Value (8-bit) false/true

	typedef char            Char8   ; // Character ( 8-bit)
	typedef wchar_t         Char16  ; // Character (16-bit)
	typedef signed char     SChar8   ; // Character ( 8-bit)

//由于很多地方都将Char写成了Char8 造成Char8和Char16不能通用	所以暂时统一将Char定为8位
#if MG_WCHAR_T_STRINGS	
	typedef Char8 Char;
#else
	typedef Char8 Char;
#endif

	typedef   PLATFORM(  signed __int8 ,  int8_t)   I8      ; //   Signed Int ( 8-bit)                        -128 .. 127
	typedef   PLATFORM(unsigned __int8 , uint8_t)   U8 ,Byte; // Unsigned Int ( 8-bit)                           0 .. 255
	typedef   PLATFORM(  signed __int16, int16_t)   I16     ; //   Signed Int (16-bit)                     -32 768 .. 32 767
	typedef   PLATFORM(unsigned __int16,uint16_t)   U16     ; // Unsigned Int (16-bit)                           0 .. 65 535
	typedef   PLATFORM(  signed __int32, int32_t)   I32, Int; //   Signed Int (32-bit)              -2 147 483 648 .. 2 147 483 647
	typedef   PLATFORM(unsigned __int32,uint32_t)   U32,UInt; // Unsigned Int (32-bit)                           0 .. 4 294 967 295
	typedef   PLATFORM(  signed __int64, int64_t)   I64     ; //   Signed Int (64-bit)  -9 223 372 036 854 775 808 ..  9 223 372 036 854 775 807
	typedef   PLATFORM(unsigned __int64,uint64_t)   U64     ; // Unsigned Int (64-bit)                           0 .. 18 446 744 073 709 551 615
	typedef                       U32				mhandle_t; 
	typedef                       float             Flt     ; //  Float (32-bit)  1-bit sign +  8-bit exponent + 23-bit mantissa
	typedef                       double            Dbl     ; // Double (64-bit)  1-bit sign + 11-bit exponent + 52-bit mantissa
	typedef                       double            Dlb    ; // General Floating Point        (the most precise available)
	typedef                       void             *Ptr     ; // General Pointer               (32-bit or 64-bit)
	typedef                 const void             *CPtr    ; // General Pointer to const data (32-bit or 64-bit)

	/******************************************************************************/

	typedef   const Char8   CChar8; // Const Char8
	typedef   const Char16  CChar16 ; // Const Char16

#if MG_WCHAR_T_STRINGS
	typedef CChar16 CChar;
#else
	typedef CChar8 CChar;
#endif

	/******************************************************************************/
	typedef std::wstring Str16;
	typedef std::string Str8;
//由于很多地方都将Str8写成了Str 造成Str8和Str16不能通用	所以暂时统一将Str定为Str8位
#if MG_WCHAR_T_STRINGS
	typedef Str8 Str;
#else
	typedef Str8 Str;
#endif

	/******************************************************************************/
#ifdef X64
	typedef U64 UIntPtr; // unsigned integer capable of storing full memory address (needs to be 64-bit on 64-bit platforms)
#else
	typedef U32 UIntPtr; // unsigned integer capable of storing full memory address (needs to be 32-bit on 32-bit platforms)
#endif      

}
/******************************************************************************/

#endif