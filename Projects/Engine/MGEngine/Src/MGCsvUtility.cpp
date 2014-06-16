/******************************************************************************/
#include "stdafx.h"
#include "MGCsvUtility.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	Bool MGCsvUtility::CsvParseVec3::parse(Str16& src, Vec3& dest)
	{
		dest.x = 0;
		dest.y = 0;
		dest.z = 0;

		int srclen = src.length();
		int parse_count = 0;

		Str16 token;

		for ( int i = 0; i < srclen; i++ )
		{
			if ( src.at(i) == L';' || 
				srclen == i + 1 )
			{
				if ( src.at(i) != L';' )
					token += src.at(i);

				if ( parse_count < 3 )
				{
					Flt* destValue = ((Flt*)(&dest.x)) + parse_count;
					MGStrOp::toFlt(token.c_str(), *destValue);
					token = L"";
					parse_count++;
				}
			}
			else
			{
				token += src.at(i);
			}
		}

		return ( parse_count == 3 );
	}
	//-----------------------------------------------------------------------------
	Bool MGCsvUtility::CsvParseVec3::write(Vec3& src, Str16& dest)
	{
		dest = L"";
		Str16 str;

		MGStrOp::toString(src.x, str);
		dest += str;
		dest += L";";

		MGStrOp::toString(src.y, str);
		dest += str;
		dest += L";";

		MGStrOp::toString(src.z, str);
		dest += str;

		return true;
	}
	//-----------------------------------------------------------------------------
	Bool MGCsvUtility::CsvParseVec4::parse(Str16& src, Vec4& dest)
	{
		dest.x = 0;
		dest.y = 0;
		dest.z = 0;
		dest.w = 0;

		int srclen = src.length();
		int parse_count = 0;

		Str16 token;

		for ( int i = 0; i < srclen; i++ )
		{
			if ( src.at(i) == L';' || 
				srclen == i + 1 )
			{
				if ( src.at(i) != L';' )
					token += src.at(i);

				if ( parse_count < 3 )
				{
					Flt* destValue = ((Flt*)(&dest.x)) + parse_count;
					MGStrOp::toFlt(token.c_str(), *destValue);
					token = L"";
					parse_count++;
				}
				if ( parse_count == 3 )
				{
					MGStrOp::toFlt(token.c_str(), dest.w);
					token = L"";
					parse_count++;
				}
			}
			else
			{
				token += src.at(i);
			}
		}

		return ( parse_count == 4 );
	}
	//-----------------------------------------------------------------------------
	Bool MGCsvUtility::CsvParseVec4::write(Vec4& src, Str16& dest)
	{
		dest = L"";
		Str16 str;

		MGStrOp::toString(src.x, str);
		dest += str;
		dest += L";";

		MGStrOp::toString(src.y, str);
		dest += str;
		dest += L";";

		MGStrOp::toString(src.z, str);
		dest += str;
		dest += L";";

		MGStrOp::toString(src.w, str);
		dest += str;

		return true;
	}
	//-----------------------------------------------------------------------------
	Bool MGCsvUtility::CsvParseColor::parse(Str16& src, Color& dest)
	{
		/*dest.r = 0;
		dest.g = 0;
		dest.b = 0;
		dest.a = 0;

		int srclen = src.length();
		int parse_count = 0;

		Str16 token;

		for ( int i = 0; i < srclen; i++ )
		{
			if ( src.at(i) == L';' || 
				srclen == i + 1 )
			{
				if ( src.at(i) != L';' )
					token += src.at(i);

				if ( parse_count < 4 )
				{
					Flt* destValue = ((Flt*)(&dest.r)) + parse_count;
					MGStrOp::toFlt(token.c_str(), *destValue);
					token = L"";
					parse_count++;
				}
			}
			else
			{
				token += src.at(i);
			}
		}

		return ( parse_count == 4 );*/

		bool succeed = false;

		dest.r = 0;
		dest.g = 0;
		dest.b = 0;
		dest.a = 0;

		if ( MGStrOp::toFlt(src.substr(0, 3).c_str(), dest.a) &&
			MGStrOp::toFlt(src.substr(3, 3).c_str(), dest.r) && 
			MGStrOp::toFlt(src.substr(6, 3).c_str(), dest.g) &&
			MGStrOp::toFlt(src.substr(9, 3).c_str(), dest.b) )
		{
			succeed = true;
		}

		if ( !succeed )
		{
			dest.r = 0;
			dest.g = 0;
			dest.b = 0;
			dest.a = 0;
		}

		return succeed;
	}
	//-----------------------------------------------------------------------------
	Bool MGCsvUtility::CsvParseColor::write(Color& src, Str16& dest)
	{
		dest = L"";
		Str16 str;

		MGStrOp::toString(src.a, str);
		dest += str;

		MGStrOp::toString(src.r, str);
		dest += str;

		MGStrOp::toString(src.g, str);
		dest += str;

		MGStrOp::toString(src.b, str);
		dest += str;

		return true;
	}
	//-----------------------------------------------------------------------------
	Bool MGCsvUtility::CsvParseSpecular::parse(Str16& src, Color& destColor, Flt& destShininess)
	{
		destColor.r = 0;
		destColor.g = 0;
		destColor.b = 0;
		destColor.a = 0;
		destShininess = 0;

		int srclen = src.length();
		int parse_count = 0;

		Str16 token;

		for ( int i = 0; i < srclen; i++ )
		{
			if ( src.at(i) == L';' || 
				srclen == i + 1 )
			{
				if ( src.at(i) != L';' )
					token += src.at(i);

				if ( parse_count < 4 )
				{
					Flt* destValue = ((Flt*)(&destColor.r)) + parse_count;
					MGStrOp::toFlt(token.c_str(), *destValue);
					token = L"";
					parse_count++;
				}
				else if ( parse_count == 4 )
				{
					MGStrOp::toFlt(token.c_str(), destShininess); 
				}
			}
			else
			{
				token += src.at(i);
			}
		}

		return ( parse_count == 5 );
	}
	//-----------------------------------------------------------------------------
	Bool MGCsvUtility::CsvParseSpecular::write(Color& srcColor, Flt& srcShininess, Str16& dest)
	{
		dest = L"";
		Str16 str;

		MGStrOp::toString(srcColor.r, str);
		dest += str;
		dest += L";";

		MGStrOp::toString(srcColor.g, str);
		dest += str;
		dest += L";";

		MGStrOp::toString(srcColor.b, str);
		dest += str;
		dest += L";";

		MGStrOp::toString(srcColor.a, str);
		dest += str;
		dest += L";";

		MGStrOp::toString(srcShininess, str);
		dest += str;

		return true;
	}
	//-----------------------------------------------------------------------------
	Bool MGCsvUtility::CsvParseCullingMode::parse(Str16& src, U8& CullingHardWare, U8& CullingSoftWare )
	{
		CullingHardWare = (U8)CULL_NONE;
		CullingSoftWare = (U8)MANUAL_CULL_NONE;

		std::string multi_src;
		MG::MGStrOp::toString(src.c_str(), multi_src);

		Ogre::StringVector vecparams = Ogre::StringUtil::split(multi_src, ";");

		if ( vecparams.size() == 0 )
			return false;

		if ( vecparams.size() > 0 )
		{
			if ( vecparams[0].empty() )
				return false;

			U32 result = 0;
			MGStrOp::toU32(vecparams[0].c_str(), result);
			if ( result < (U8)CULL_ANTICLOCKWISE + 1 )
				CullingHardWare = (U8)result;
		}

		if ( vecparams.size() > 1 )
		{
			U32 result = 0;
			MGStrOp::toU32(vecparams[1].c_str(), result);
			if ( result < (U8)MANUAL_CULL_FRONT + 1 )
				CullingSoftWare = (U8)result;
		}

		return true;
	}
	//-----------------------------------------------------------------------------
	Bool MGCsvUtility::CsvParseCullingMode::write(U8& CullingHardWare, U8& CullingSoftWare, Str16& dest )
	{
		dest = L"";
		Str16 str;

		MGStrOp::toString((U32&)CullingHardWare, str);
		dest += str;
		dest += L";";

		MGStrOp::toString((U32&)CullingSoftWare, str);
		dest += str;
		dest += L";";

		return true;
	}
	//-----------------------------------------------------------------------------
	Bool MGCsvUtility::CsvParseAlphaRejection::parse(Str16& src, U8& alphaRejectionCmp, U8& alphaRejectionValue )
	{
		alphaRejectionCmp = (U8)CMPF_ALWAYS_PASS;
		alphaRejectionValue = (U8)0;

		std::string multi_src;
		MG::MGStrOp::toString(src.c_str(), multi_src);

		Ogre::StringVector vecparams = Ogre::StringUtil::split(multi_src, ";");

		if ( vecparams.size() == 0 )
			return false;

		if ( vecparams.size() > 0 )
		{
			if ( vecparams[0].empty() )
				return false;

			U32 result = 0;
			MGStrOp::toU32(vecparams[0].c_str(), result);
			if ( result < (U8)CMPF_GREATER + 1 )
				alphaRejectionCmp = (U8)result;
		}

		if ( vecparams.size() > 1 )
		{
			MGStrOp::toU32(vecparams[1].c_str(), (U32&)alphaRejectionValue);
		}

		return true;
	}
	//-----------------------------------------------------------------------------
	Bool MGCsvUtility::CsvParseAlphaRejection::write(U8& alphaRejectionCmp, U8& alphaRejectionValue, Str16& dest )
	{
		dest = L"";
		Str16 str;

		MGStrOp::toString((U32&)alphaRejectionCmp, str);
		dest += str;
		dest += L";";

		MGStrOp::toString((U32&)alphaRejectionValue, str);
		dest += str;
		dest += L";";

		return true;
	}
	//-----------------------------------------------------------------------------
	Bool MGCsvUtility::CsvParseSceneBlendMode::parse(Str16& src, Bool& isUseBlendType, U8& sceneBlendType, U8& sceneBlendFactorSrc, U8& sceneBlendFactorDest )
	{
		isUseBlendType = true;
		sceneBlendType = (U8)SBT_REPLACE;
		sceneBlendFactorSrc = (U8)SBF_ONE;
		sceneBlendFactorDest = (U8)SBF_ZERO;

		std::string multi_src;
		MG::MGStrOp::toString(src.c_str(), multi_src);

		Ogre::StringVector vecparams = Ogre::StringUtil::split(multi_src, ";");

		if ( vecparams.size() == 0 )
			return false;

		if ( vecparams.size() > 0 )
		{
			if ( vecparams[0].empty() )
				return false;

			U32 result = 0;
			MGStrOp::toU32(vecparams[0].c_str(), result);
			isUseBlendType = (result != 0);
		}

		if ( vecparams.size() > 1 )
		{
			U32 result = 0;
			MGStrOp::toU32(vecparams[1].c_str(), result);
			if ( result < (U8)SBT_REPLACE + 1 )
				sceneBlendType = (U8)result;
		}

		if ( vecparams.size() > 2 )
		{
			U32 result = 0;
			MGStrOp::toU32(vecparams[2].c_str(), result);
			if ( result < (U8)SBF_ONE_MINUS_SOURCE_ALPHA + 1 )
				sceneBlendFactorSrc = (U8)result;
		}

		if ( vecparams.size() > 3 )
		{
			U32 result = 0;
			MGStrOp::toU32(vecparams[3].c_str(), result);
			if ( result < (U8)SBF_ONE_MINUS_SOURCE_ALPHA + 1 )
				sceneBlendFactorDest = (U8)result;
		}

		return true;
	}
	//-----------------------------------------------------------------------------
	Bool MGCsvUtility::CsvParseSceneBlendMode::write(Bool& isUseBlendType, U8& sceneBlendType, U8& sceneBlendFactorSrc, U8& sceneBlendFactorDest, Str16& dest )
	{
		dest = L"";
		Str16 str;

		MGStrOp::toString((U32&)isUseBlendType, str);
		dest += str;
		dest += L";";

		MGStrOp::toString((U32&)sceneBlendType, str);
		dest += str;
		dest += L";";

		MGStrOp::toString((U32&)sceneBlendFactorSrc, str);
		dest += str;
		dest += L";";

		MGStrOp::toString((U32&)sceneBlendFactorDest, str);
		dest += str;

		return true;
	}
	

}