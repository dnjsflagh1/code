/******************************************************************************/
#include "stdafx.h"
#include "Utility.h"
/******************************************************************************/
using namespace System;
using namespace System::Windows::Forms;

namespace ParticleEditor {

    Char16* TypeConverter::StrToChar16(System::String ^ str)
    {
        System::IntPtr intPtr = System::Runtime::InteropServices::Marshal::StringToBSTR(str);
        Char16* pwChar = (wchar_t*)intPtr.ToPointer();
        return pwChar;
    }
    //-----------------------------------------------------------------------------
    Int TypeConverter::StrToInt(System::String ^ str)
    {
        return Convert::ToInt32(str);
    }
    //-----------------------------------------------------------------------------
    Dbl TypeConverter::StrToDouble(System::String ^ str)
    {
        return Convert::ToDouble(str);
    }
    //-----------------------------------------------------------------------------
    U32 TypeConverter::StrToU32(System::String ^ str)
    {
        return (U32)Convert::ToUInt64(str);
    }
    //-----------------------------------------------------------------------------
    U64 TypeConverter::StrToU64(System::String ^ str)
    {
        return (U64)Convert::ToUInt64(str);
    }
    //-----------------------------------------------------------------------------
    System::String ^ TypeConverter::Char8ToStr(Char8 * c)
    {
        System::IntPtr ptr(c);
        return System::Runtime::InteropServices::Marshal::PtrToStringAnsi(ptr);
    }
    //-----------------------------------------------------------------------------
    System::String ^ TypeConverter::Char16ToStr(Char16 * c)
    {
        System::IntPtr ptr(c);
        return System::Runtime::InteropServices::Marshal::PtrToStringUni(ptr);
    }
    //-----------------------------------------------------------------------------
    System::String ^ TypeConverter::Char8ToStr(CChar8 * c)
    {
        return Char8ToStr(const_cast<Char8*>(c));
    }
    //-----------------------------------------------------------------------------
    System::String ^ TypeConverter::Char16ToStr(CChar16 * c)
    {
        return Char16ToStr(const_cast<Char16*>(c));
    }
    //-----------------------------------------------------------------------------
    System::String ^ TypeConverter::IntToStr(Int src)
    {
        System::Int64 num = src;
        return num.ToString();
    }
    //-----------------------------------------------------------------------------
    System::String ^ TypeConverter::U32ToStr(U32 src)
    {
        System::UInt64 num = src;
        return num.ToString();
    }
    //-----------------------------------------------------------------------------
    System::String ^ TypeConverter::U64ToStr(U64 src)
    {
        System::UInt64 num = src;
        return num.ToString();
    }
	//-----------------------------------------------------------------------------
	System::String ^ TypeConverter::DoubleToStr(Dbl src)
	{
		System::Double num = src;
		return num.ToString("n");
	}
    //-----------------------------------------------------------------------------
    StrToChar8::StrToChar8(System::String ^ rstr)
    {
        System::IntPtr intPtr = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(rstr);
        Char8* headChar = (Char8*)intPtr.ToPointer();
        mStr = headChar;
        System::Runtime::InteropServices::Marshal::FreeHGlobal(intPtr);
    }
    //-----------------------------------------------------------------------------
    StrToChar8::~StrToChar8()
    {
    }
    //-----------------------------------------------------------------------------
    Bool Utility::isIntegral(System::String ^ str)
    {
        Char16 word;
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
    void Utility::showWarningMessage(System::String ^ str)
    {
        System::Windows::Forms::MessageBox::Show(str, "Warning", 
            MessageBoxButtons::OK, MessageBoxIcon::Warning);
    }


}