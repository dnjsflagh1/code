/******************************************************************************/
#ifndef _UTILITY_H_
#define _UTILITY_H_
/******************************************************************************/

/******************************************************************************/
namespace MG {

    public ref class Utility 
    {
    public:
        static bool             isIntegral(System::String ^ str);

        static WCHAR *          convertStringToBSTR(System::String ^ str);
        static int              convertStringToInt(System::String ^ str);
        static double           convertStringToDouble(System::String ^ str);
        static DWORD            convertStringToDWORD(System::String ^ str);
        static ULONGLONG        convertStringToULONGLONG(System::String ^ str);

        static System::String ^ convertConstAnsiToString(const char * c);
        static System::String ^ convertConstBSTRToString(const wchar_t * c);

        static System::String ^ convertAnsiToString(char * c);
        static System::String ^ convertBSTRToString(wchar_t * c);

        static System::String ^ convertIntToString(int src);
        static System::String ^ convertULongToString(DWORD src);
        static System::String ^ convertULONGLONGToString(ULONGLONG src);
        static System::String ^ convertTimeToString(time_t src);

        static time_t           convertDateToTime_t(System::DateTime dt,int hour,int minute);
        static System::DateTime convertTime_tToDateTime(time_t time);
        static System::DateTime convertTimeToDateTime(WORD hour, WORD minute, WORD second);
        static System::String ^ getNowTime();

        static void             copyStringToAnsi(char * dest, int destSize, System::String ^ src);   

        static CHAR  *          getPCharCopyFromString(System::String ^ str);
        static void             freePCharCopyFromString(CHAR *cr);

        static void             showErrorMessage(System::String ^ str);
        static void             showWarningMessage(System::String ^ str);
        static void             showHintMessage(System::String ^ str);
    };
    
    struct StringToChar
    {
    public:
        StringToChar(System::String ^ str)
        {
            str_char = Utility::getPCharCopyFromString(str);
        }
        ~StringToChar()
        {
            Utility::freePCharCopyFromString(str_char);
        }
        char* str_char;
    };

    class GlobleParameter 
    {
    public:
        SINGLETON_INSTANCE(GlobleParameter)
        GlobleParameter();

        char    utility_ansi_string[2000];
        wchar_t utility_bstr_string[2000];
    };
}
/******************************************************************************/

#endif //_UTILITY_H_

