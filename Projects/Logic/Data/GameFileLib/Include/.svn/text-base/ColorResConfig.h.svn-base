//***********************************************************************************************
#ifndef _H_COLORRES_CONFIG_
#define _H_COLORRES_CONFIG_
//***********************************************************************************************
#include "GameFilePreqs.h"
//***********************************************************************************************
namespace MG
{
	enum ColorUSeType
	{
		Color_Use_Null,
		Color_Use_Text,				    //文字色
		Color_Use_Text_Shadow,	       //文字阴影色
		Color_Use_Text_Select,		   //文字选中色
		Color_Use_ClanFlag,			  //氏族徽记色
		Color_Use_ClanBack,			  //氏族背景色
		Colour_Use_Army,			  //军队换色
		Color_Use_Max
	};
    //--------------------------------------------------------------------------
	//ColorRes_Id		序列id
	//Notes				策划备注
	//ColorName	        颜色名
	//UseType	        使用类型
	//ColorValue	    颜色值
	//replaceString		转义字符
    struct  ColorResCsvInfo
    {
        U32             ColorRes_Id   ;	       	        ;
        Str8            ColorName;
		ColorUSeType	UseType;
		Color			ColorValue;
		Str8			EscapeChar;
    };
    //--------------------------------------------------------------------------
    class ColorResConfig
    {
    public:
        ColorResConfig(){;}
        ~ColorResConfig();
        SINGLETON_INSTANCE(ColorResConfig);

    public:
		// MG_CN_MODIFY
        Bool                    load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        const ColorResCsvInfo*  getColorResInfo(U32 id);
		bool					getColorResInfo( U32 id, const ColorResCsvInfo*& info );
		bool                    getColorResInfo(ColorUSeType type,std::map<U32, ColorResCsvInfo*>& mapinfo);

    private:
        void                    clear();

    private:
        std::map<U32, ColorResCsvInfo*>  mColorResCsvMap;

    };
}
//***********************************************************************************************
#endif
//***********************************************************************************************