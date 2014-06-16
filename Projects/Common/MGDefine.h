/******************************************************************************/
#ifndef _MGDEFINE_H_
#define _MGDEFINE_H_
/******************************************************************************/

namespace MG{

	#define TS     (*this)
	#define Super __super
	#define NULL  0
	#define CNULL ((CChar*)NULL)
		/******************************************************************************/
		// TEMPLATE MACROS
		/******************************************************************************/
	#define T1(a    )   template<typename a                        > // 1 type  template
	#define T2(a,b  )   template<typename a, typename b            > // 2 types template
	#define T3(a,b,c)   template<typename a, typename b, typename c> // 3 types template
		/******************************************************************************/
		// HELPER MACROS
		/******************************************************************************/
	#define SIZE(       x           )               sizeof(x)              // get raw size of c++ element in bytes
	#define MEMBER(     Class,member)         (((Class*)NULL)-> member)    // NULL based Class::member, this macro is used to obtain member information by many other macros/functions
	#define OFFSET(     Class,member)   UIntPtr(&MEMBER(Class,  member))   // get offset of member in class
	#define MEMBER_SIZE(Class,member)      SIZE( MEMBER(Class,  member))   // get size   of member in class
	#define CAST(       Class,object)      dynamic_cast<Class*>(object)    // perform a dynamic cast of 'object' to 'Class' class
		/******************************************************************************/
		// ITERATION MACROS
		/******************************************************************************/
	#define    REP(   n)   for(Int i=(n); --i>= 0 ;    ) //         repeat                : n-1 .. 0
	#define    REPD(i,n)   for(Int i=(n); --i>= 0 ;    ) //         repeat with definition: n-1 .. 0
	#define   FREP(   n)   for(Int i= 0 ;   i< (n); i++) // forward repeat                :   0 .. n-1
	#define   FREPD(i,n)   for(Int i= 0 ;   i< (n); i++) // forward repeat with definition:   0 .. n-1

	#define   REPA(   t)   for(Int i=Elms(t); --i>=     0 ;    ) //         repeat all                : Elms(t)-1 .. 0
	#define   REPAD(i,t)   for(Int i=Elms(t); --i>=     0 ;    ) //         repeat all with definition: Elms(t)-1 .. 0
	#define  FREPA(   t)   for(Int i=     0 ;   i< Elms(t); i++) // forward repeat all                :         0 .. Elms(t)-1
	#define  FREPAD(i,t)   for(Int i=     0 ;   i< Elms(t); i++) // forward repeat all with definition:         0 .. Elms(t)-1

	#define  REPAO(   t)   for(Int i=Elms(t); --i>=     0 ;    ) (t)[i] //         repeat all                 and operate: Elms(t)-1 .. 0
	#define  REPAOD(i,t)   for(Int i=Elms(t); --i>=     0 ;    ) (t)[i] //         repeat all with definition and operate: Elms(t)-1 .. 0
	#define FREPAO(   t)   for(Int i=     0 ;   i< Elms(t); i++) (t)[i] // forward repeat all                 and operate:         0 .. Elms(t)-1
	#define FREPAOD(i,t)   for(Int i=     0 ;   i< Elms(t); i++) (t)[i] // forward repeat all with definition and operate:         0 .. Elms(t)-1
		/******************************************************************************/
		// ASSERTIONS
		/******************************************************************************/
	#define COMPILE_ASSERT(value      )   extern char _AssertDummyName[(value) ? 1 : -1]                             // compile time assertion

    #define  DYNAMIC_ASSERT_LOG(value,error) {if(!(value)){Str hint=Str(error)+"\n File:"; hint+=__FILE__; hint+="\n Function:"; hint+=__FUNCTION__; hint+="\n";MG::LogSystem::getInstance().log(out_error,hint.c_str()); MsgBox::show(hint.c_str());}}
    #define  DYNAMIC_EEXCEPT_LOG(error) {Str hint=Str(error)+"\n File:"; hint+=__FILE__; hint+="\n Function:"; hint+=__FUNCTION__; hint+="\n";MG::LogSystem::getInstance().log(out_error,hint.c_str()); MsgBox::show(hint.c_str());}

    // dynamic assertion
    #ifdef _DEBUG
	    #define DEBUG_ASSERT_LOG(value,error)   DYNAMIC_ASSERT_LOG(value,error) // debug        assertion available only in debug   mode
	#else
        #ifdef _LOG
	        #define DEBUG_ASSERT_LOG(value,error)   DYNAMIC_ASSERT_LOG(value,error) // debug        assertion available only in debug   mode
        #else
	        #define DEBUG_ASSERT_LOG(value,error)   {}                              // debug        assertion unavailable    in release mode
        #endif
	#endif

    #define DYNAMIC_ASSERT(value)  {DEBUG_ASSERT_LOG(value,"DYNAMIC_ASSERT_ERROR!!!"); assert(value);}

    #define UNREFERENCED_PARAMETER(P) (P)

	#define RANGE_ASSERT(index,elms )   DEBUG_ASSERT(InRange(index,elms),"Element out of range")                   // out of range assertion, asserts that 'index' is in range "0..elms-1"
		/******************************************************************************/
		// STRUCT DECLARATION
		/******************************************************************************/
	#define const_mem_addr // custom keyword specifying that the struct/class must be stored in constant memory address, if you see this keyword next to a struct/class declaration you must ensure that when defining objects of that struct/class you will store them in constant memory address (this can be either global namespace or inside 'Memx' 'Meml' containers)

	#define STRUCT(        Extended,Base)   struct Extended :         Base { PLATFORM(,typedef Base super;) // macro for declaring an 'Extended' structure from 'Base' version, and declaring 'super' keyword at the same time (this is needed for non Windows platforms which don't declare 'super' automatically)
	#define STRUCT_PRIVATE(Extended,Base)   struct Extended : private Base { PLATFORM(,typedef Base super;) // macro for declaring an 'Extended' structure from 'Base' version, and declaring 'super' keyword at the same time (this is needed for non Windows platforms which don't declare 'super' automatically)

	#define UNION(    x)   PLATFORM(union {x}; , x) //                                  uses union     on Windows Platform, and no union     for non-Windows platforms
	#define UNION_ELM(x)   PLATFORM(struct{x}; , x) // encapsulates element into a non-named structure on Windows Platform, and no structure for non-Windows platforms

	#define NO_COPY_CONSTRUCTOR(Class)                                                     \
		T1(UNUSED)   void operator=(Class &src) {PLATFORM(Class has no copy constructor,)} \
		T1(UNUSED)            Class(Class &src) {PLATFORM(Class has no copy constructor,)} // when declared inside a class this macro disables the use of copy constructors
		/******************************************************************************/
		// OBJECT CLASSES
		/******************************************************************************/
		T2(TA,TB) inline Bool EQUAL_TYPE(TA &a, TB &b) {return typeid(a)==typeid(b);} // if 'a' and 'b' objects are of the same classes (this checks the most derived classes)
		/******************************************************************************/

		/******************************************************************************/
		//Æ½Ì¨×Ö½ÚÐò
		/******************************************************************************/
	#define MG_LITTLE_ENDIAN			1234
	#define MG_BIG_ENDIAN				4321
	#define MG_PDP_ENDIAN				3412

	#if defined(MG_PLATFORM_WINDOWS)

	#define MG_NET_BYTE_ORDER			MG_LITTLE_ENDIAN

	#elif defined(MG_PLATFORM_LINUX)

	#include <endian.h>
	#if __BYTE_ORDER == __LITTLE_ENDIAN
	#define MG_NET_BYTE_ORDER		MG_LITTLE_ENDIAN
	#elif __BYTE_ORDER == __BIG_ENDIAN
	#define MG_NET_BYTE_ORDER		MG_BIT_ENDIAN
	#else
		//#define MG_BYTE_ORDER		MG_PDP_ENDIAN
	#error Error: unknow byte order
	#endif

	#elif defined(MG_PLATFORM_FREEBSD)

	#include <sys/endian.h>
	#if _BYTE_ORDER == _LITTLE_ENDIAN
	#define MG_NET_BYTE_ORDER		MG_LITTLE_ENDIAN
	#elif _BYTE_ORDER == _BIG_ENDIAN
	#define MG_NET_BYTE_ORDER		MG_BIT_ENDIAN
	#else
		//#define MG_BYTE_ORDER		MG_PDP_ENDIAN
	#error Error: unknow byte order
	#endif

	#endif

		/******************************************************************************/
		//__stdcall
		/******************************************************************************/
	#ifdef	WINDOWS
	#define API	__stdcall
	#elif	LINUX
	#define API			
	#endif

		/******************************************************************************/
		//__forceinline
		/******************************************************************************/
	#if defined(WINDOWS)
	#define MG_INLINE   __forceinline
	#elif defined(LINUX)
	#define MG_INLINE   inline
	#endif

		/******************************************************************************/
		//
		/******************************************************************************/
	#if defined(MG_PLATFORM_WINDOWS)

	#if defined(MG_CPU_32)
		typedef  U32		mhandle_t;
	#elif defined(MG_CPU_64)
		typedef  U64		mhandle_t;
	# endif

	#define	__MG_FUNC__			MG_STR_CONV(__FUNCTION__)
	#define	__MG_FILE__			MG_STR_CONV(__FILE__)
	#define	__MG_LINE__			MG_STR_CONV(__LINE__)

	#elif defined(MG_PLATFORM_LINUX)
	#if defined(MG_CPU_32)
		typedef U32			mhandle_t;
	#elif defined(MG_CPU_64)
		typedef U64			mhandle_t;
	#endif
	#define __MG_FUNC__			MG_STR_CONV(__func__)
	#else

	#endif
		/******************************************************************************/
		//
		/******************************************************************************/
	#define		MG_FILE_PATH 256

		/******************************************************************************/
		//
		/******************************************************************************/
	

	#if	defined(MG_PLATFORM_WINDOWS)

        #define StrCat			strcat
        #define StrnCat			strncat
        #define StrCpy			strcpy
        #define StrnCpy			strncpy
        #define StrnCpyS        strncpy_s
        #define StrLen			strlen
        #define WStrLen			wcslen
        #define StrnLen			strnlen
        #define StrChr			strchr
        #define StrrChr			strrchr
        #define StrStr			strstr
        #define WcsStr			wcsstr
        #define StrCmp			strcmp
        #define StrnCmp			strncmp
        #define StrTok			strtok
        #define WStrnCmp		_wcsnicmp
        #define WStrnCpyS       wcsncpy_s

	    #define StriCmp			stricmp
	    #define SnprintF		_snprintf
	    #define snprintf		_snprintf
	    #define AtoLL			_atoi64
	    #define StrtoULL		_strtoui64
	    #define VsnprintF		vsprintf_s

	#elif defined(MG_PLATFORM_LINUX)

	    #define StriCmp			strcasecmp
	    #define AtoLL			atoll
	    #define SnprintF		snprintf
	    #define StrtoULL		strtoull

	#else
	    #error	"Please define string case-insensitive compare for your OS/compiler"
	#endif

	#define PrintF			printf
	#define SprintF			sprintf
	#define SScanF			sscanf
	#define GetCwd			_getcwd

	#define VsprintF		vsprintf

	#define	FOpen			fopen
	#define FPuts			fputs

	#define ToUpper			toupper
	#define ToLower			tolower

	#define AtoI			atoi
	#define AtoL			atol

	#define AtoF			atof

	#define StrtoL			strtol
	#define StrtoUL			strtoul

	#ifndef BIT
	#define BIT( num )				( 1 << ( num ) )
	#endif

	#ifndef MGMin
		#define MGMin(x,y) ((x) < (y)) ? (x) : (y)
	#endif

	#ifndef MGMax
		#define MGMax(x,y) ((x) > (y)) ? (x) : (y)
	#endif

	#define Abs				abs

	/******************************************************************************/
	//
	/******************************************************************************/

}

/******************************************************************************/
#endif