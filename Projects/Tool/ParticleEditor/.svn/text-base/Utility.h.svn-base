/******************************************************************************/
#ifndef _UTILITY_H_
#define _UTILITY_H_
/******************************************************************************/


/******************************************************************************/
namespace ParticleEditor {


    public ref class TypeConverter 
    {
    public:
        static Char16*          StrToChar16(System::String ^ str);
        static Int              StrToInt(System::String ^ str);
        static Dbl              StrToDouble(System::String ^ str);
        static U32              StrToU32(System::String ^ str);
        static U64              StrToU64(System::String ^ str);

        static System::String ^ Char8ToStr(Char8 * c);
        static System::String ^ Char16ToStr(Char16 * c);
        static System::String ^ Char8ToStr(CChar8 * c);
        static System::String ^ Char16ToStr(CChar16 * c);
        static System::String ^ IntToStr(Int src);
        static System::String ^ U32ToStr(U32 src);
        static System::String ^ U64ToStr(U64 src);
		static System::String ^ DoubleToStr(Dbl src);
    };

    struct StrToChar8
    {
    public:
        StrToChar8(System::String ^ rstr);
        ~StrToChar8();
        CChar8* getChar8(){return mStr.c_str();};
    private:
        Str8 mStr;
    };

    public ref class Utility 
    {
    public:

        static Bool isIntegral(System::String ^ str);
        static void showWarningMessage(System::String ^ str);
    };

}
/******************************************************************************/

#endif //_UTILITY_H_

