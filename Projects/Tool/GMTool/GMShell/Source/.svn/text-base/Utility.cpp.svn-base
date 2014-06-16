/******************************************************************************/
#include "stdafx.h"
#include "Utility.h"
#include "GMToolManager.h"
/******************************************************************************/
using namespace System;
using namespace System::Windows::Forms;
using namespace MG;

namespace MG {

    /******************************************************************************/
    //class Utility 
    /******************************************************************************/
    bool Utility::isIntegral(System::String ^ str)
    {
        wchar_t word;
        for(int i=0;i<str->Length;i++)
        {
            word = str->default[i];
            if ( word == L'0')
                continue;
            if ( word == L'1')
                continue;
            if ( word == L'2')
                continue;
            if ( word == L'3')
                continue;
            if ( word == L'4')
                continue;
            if ( word == L'5')
                continue;
            if ( word == L'6')
                continue;
            if ( word == L'7')
                continue;
            if ( word == L'8')
                continue;
            if ( word == L'9')
                continue;
            return false;
        }
        return true;
    }
    //-----------------------------------------------------------------------------
    WCHAR* Utility::convertStringToBSTR(System::String ^ str)
    {
        System::IntPtr intPtr = System::Runtime::InteropServices::Marshal::StringToBSTR(str);
        wchar_t* pwChar = (wchar_t*)intPtr.ToPointer();
        return pwChar;
    }
    //-----------------------------------------------------------------------------
    int Utility::convertStringToInt(System::String ^ str)
    {
        return Convert::ToInt32(str);
    }
    //-----------------------------------------------------------------------------
    double Utility::convertStringToDouble(System::String ^ str)
    {
        return Convert::ToDouble(str);
    }
    //-----------------------------------------------------------------------------
    DWORD Utility::convertStringToDWORD(System::String ^ str)
    {
        return (DWORD)Convert::ToUInt64(str);
    }
    //-----------------------------------------------------------------------------
    ULONGLONG Utility::convertStringToULONGLONG(System::String ^ str)
    {
        if (String::IsNullOrEmpty(str))
            return 0;
        return Convert::ToUInt64(str);
    }
    //-----------------------------------------------------------------------------
    System::String ^ Utility::convertIntToString(int src)
    {
        System::Int64 num = src;
        return num.ToString();
    }
    //-----------------------------------------------------------------------------
    System::String ^ Utility::convertULongToString(DWORD src)
    {
        System::UInt64 num = src;
        return num.ToString();
    }
    //-----------------------------------------------------------------------------
    System::String ^ Utility::convertTimeToString(time_t src)
    {
        time_t time = src;

        String^ result = "";
        struct tm newtime;
        char timeStr[128];  
        memset(timeStr,0,_countof(timeStr));
        if ( _localtime64_s( &newtime, &time ) == 0 )
        {
            asctime_s(timeStr, 32, &newtime);   
            result = convertAnsiToString(timeStr);
        }
        return result;
    }
    //-----------------------------------------------------------------------------
    System::DateTime Utility::convertTime_tToDateTime(time_t time)
    {
        System::DateTime dt = System::DateTime::Now;
        struct tm newtime;
        if ( _localtime64_s( &newtime, &time ) == 0 )
        {
            dt = System::DateTime(newtime.tm_year + 1900,newtime.tm_mon+1,newtime.tm_mday,
                                    newtime.tm_hour,newtime.tm_min,0);
        }
        return dt;
    }
    //-----------------------------------------------------------------------------
    System::DateTime Utility::convertTimeToDateTime(WORD hour, WORD minute, WORD second)
    {
        System::DateTime dt = System::DateTime(
            System::DateTime::Now.Year,System::DateTime::Now.Month,System::DateTime::Now.Day,
            hour,minute,second);

        return dt;
    }
    //-----------------------------------------------------------------------------
    time_t Utility::convertDateToTime_t(System::DateTime dt,int hour,int minute)
    {
        struct tm newtime;
        newtime.tm_sec      = 0;
        newtime.tm_min      = 0;
        newtime.tm_hour     = 0;
        newtime.tm_mday     = 0;
        newtime.tm_mon      = 0;
        newtime.tm_year     = 0;
        newtime.tm_wday     = 0;
        newtime.tm_yday     = 0;
        newtime.tm_isdst    = 0;

        newtime.tm_year     = dt.Year-1900;
        newtime.tm_mon      = dt.Month-1;
        newtime.tm_mday     = dt.Day;
        
        newtime.tm_hour     = hour;
        newtime.tm_min      = minute;

        return mktime(&newtime);
    }
    //-----------------------------------------------------------------------------
    System::String ^ Utility::getNowTime()
    {
        char timeStr[128];
        _strtime_s( timeStr, 128 );
        return Utility::convertAnsiToString(timeStr);
    }
    //-----------------------------------------------------------------------------
    System::String ^ Utility::convertULONGLONGToString(ULONGLONG src)
    {
        System::UInt64 num = src;
        return num.ToString();
    }
    //-----------------------------------------------------------------------------
    System::String ^ Utility::convertConstAnsiToString(const char * c)
    {
        GlobleParameter& gp = GlobleParameter::getInstance();
		StrCpy(gp.utility_ansi_string,c);
        System::IntPtr ptr(gp.utility_ansi_string);
        return System::Runtime::InteropServices::Marshal::PtrToStringAnsi(ptr);
    }
    //-----------------------------------------------------------------------------
    System::String ^ Utility::convertConstBSTRToString(const wchar_t * c)
    {
        GlobleParameter& gp = GlobleParameter::getInstance();
        WStrnCpyS(gp.utility_bstr_string,c,_countof(gp.utility_bstr_string));
        System::IntPtr ptr(gp.utility_bstr_string);
        return System::Runtime::InteropServices::Marshal::PtrToStringBSTR(ptr);
    }
    //-----------------------------------------------------------------------------
    System::String ^ Utility::convertAnsiToString(char * c)
    {
        System::IntPtr ptr(c);
        return System::Runtime::InteropServices::Marshal::PtrToStringAnsi(ptr);
    }
    //-----------------------------------------------------------------------------
    System::String ^ Utility::convertBSTRToString(wchar_t * c)
    {
        System::IntPtr ptr(c);
        return System::Runtime::InteropServices::Marshal::PtrToStringBSTR(ptr);
    }
    //-----------------------------------------------------------------------------
    void Utility::copyStringToAnsi(char * dest, int destSize, System::String ^ src)
    {
        char* charSrc = getPCharCopyFromString(src);
        StrCpy(dest,charSrc);
        freePCharCopyFromString(charSrc);
    }
    //-----------------------------------------------------------------------------
    CHAR* Utility::getPCharCopyFromString(System::String ^ str)
    {
        System::IntPtr intPtr = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str);
        char* pChar = (char*)intPtr.ToPointer();
        return pChar;
    }
    //-----------------------------------------------------------------------------
    void Utility::freePCharCopyFromString(CHAR *cr)
    {
        if (cr)
            System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr(cr));
    }
    //-----------------------------------------------------------------------------
    void Utility::showErrorMessage(System::String ^ str)
    {
        if (GMFormSet::MAIN_FORM&&GMFormSet::MAIN_FORM->Visible)
        {
            System::Windows::Forms::MessageBox::Show(GMFormSet::MAIN_FORM,str, "Error", 
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }else
        {
            System::Windows::Forms::MessageBox::Show(str, "Error", 
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
    //-----------------------------------------------------------------------------
    void Utility::showWarningMessage(System::String ^ str)
    {
        if (GMFormSet::MAIN_FORM&&GMFormSet::MAIN_FORM->Visible)
        {
            System::Windows::Forms::MessageBox::Show(GMFormSet::MAIN_FORM,str, "Warning", 
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }else
        {
            System::Windows::Forms::MessageBox::Show(str, "Warning", 
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
    }
    //-----------------------------------------------------------------------------
    void Utility::showHintMessage(System::String ^ str)
    {
        if (GMFormSet::MAIN_FORM&&GMFormSet::MAIN_FORM->Visible)
        {
            System::Windows::Forms::MessageBox::Show(GMFormSet::MAIN_FORM, str, "Hint", 
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }else
        {
            System::Windows::Forms::MessageBox::Show(str, "Hint", 
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }

    /******************************************************************************/
    //class GlobleParameter 
    /******************************************************************************/
    GlobleParameter::GlobleParameter()
    {
        memset(utility_ansi_string,0,_countof(utility_ansi_string));
        memset(utility_bstr_string,0,_countof(utility_bstr_string));
    }
}