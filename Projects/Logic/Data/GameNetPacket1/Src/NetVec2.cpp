/******************************************************************************/
#include "stdafx.h"
#include "NetVec2.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	NetVec2::NetVec2()
	{
		mData.mX = 0;
		mData.mY = 0;
		mData.mScrap = 0;
	}
	//--------------------------------------------------------------------------
	NetVec2::NetVec2( NetVec2& netVec2 )
	{
		mData.mX = netVec2.mData.mX;
		mData.mY = netVec2.mData.mY;
		mData.mScrap = netVec2.mData.mScrap;
	}
	//--------------------------------------------------------------------------
	NetVec2::NetVec2( Vec2& vec2 )
	{
		// 整数部分16位
		// 15位最大可以表示 (0X7FFF)32767
		// 1位用来表示正负
		DYNAMIC_ASSERT(vec2.x <= 0x7fff && vec2.x >= -0x7fff);
		DYNAMIC_ASSERT(vec2.y <= 0x7fff && vec2.y >= -0x7fff);
		U8 scrapX = 0;
		U8 scrapY = 0;
		if (vec2.x >= 0)
		{
			mData.mX = (U16)vec2.x;
			scrapX = (U8)( ((vec2.x - mData.mX )+ 0.05f) * 10 );
		}
		else
		{
			mData.mX = (U16)(-vec2.x);
			scrapX = (U8)( ((-vec2.x - mData.mX )+ 0.05f) * 10 );
			mData.mX |= 0x8000;
		}
		if (vec2.y >= 0)
		{
			mData.mY = (U16)vec2.y;
			scrapY = (U8)(((vec2.y - mData.mY )+ 0.05f) * 10 );
		}
		else
		{
			mData.mY = (U16)(-vec2.y);
			scrapY = (U8)( ((-vec2.y - mData.mY )+ 0.05f) * 10 );
			mData.mY |= 0x8000;
		}
		mData.mScrap = scrapX << 4;
		mData.mScrap += scrapY;
	}
	//--------------------------------------------------------------------------
	NetVec2::NetVec2( Vec3& vec3 )
	{
		// 整数部分16位
		// 15位最大可以表示 32767
		// 1位用来表示正负
		DYNAMIC_ASSERT(vec3.x <= 0x7fff && vec3.x >= -0x7fff);
		DYNAMIC_ASSERT(vec3.z <= 0x7fff && vec3.z>= -0x7fff);
		U8 scrapX = 0;
		U8 scrapY = 0;
		if (vec3.x >= 0)
		{
			mData.mX = (U16)vec3.x;
			scrapX = (U8)( ((vec3.x - mData.mX )+ 0.05f) * 10 );
		}
		else
		{
			mData.mX = (U16)(-vec3.x);
			scrapX = (U8)( ((-vec3.x - mData.mX )+ 0.05f) * 10 );
			mData.mX |= 0x8000;
		}
		if (vec3.z >= 0)
		{
			mData.mY = (U16)vec3.z;
			scrapY = (U8)( ((vec3.z - mData.mY )+ 0.05f) * 10 );
		}
		else
		{
			mData.mY = (U16)(-vec3.z);
			scrapY = (U8)( ((-vec3.z - mData.mY )+ 0.05f) * 10 );
			mData.mY |= 0x8000;
		}
		mData.mScrap = scrapX << 4;
		mData.mScrap += scrapY;
	}
	//--------------------------------------------------------------------------
	NetVec2::NetVec2( Flt x,Flt y )
	{
		// 整数部分16位
		// 15位最大可以表示 32767
		// 1位用来表示正负
		DYNAMIC_ASSERT(x <= 0x7fff && x >= -0x7fff);
		DYNAMIC_ASSERT(y <= 0x7fff && y >= -0x7fff);
		U8 scrapX = 0;
		U8 scrapY = 0;
		if (x >= 0)
		{
			mData.mX = (U16)x;
			scrapX = (U8)( ((x - mData.mX )+ 0.05f) * 10 );
		}
		else
		{
			mData.mX = (U16)(-x);
			scrapX = (U8)( ((-x - mData.mX )+ 0.05f) * 10 );
			mData.mX |= 0x8000;
		}
		if (y >= 0)
		{
			mData.mY = (U16)(y);
			scrapY = (U8)( ((y - mData.mY )+ 0.05f) * 10 );
		}
		else
		{
			mData.mY = (U16)(-y);
			scrapY = (U8)( ((-y - mData.mY )+ 0.05f) * 10 );
			mData.mY |= 0x8000;
		}
		mData.mScrap = scrapX << 4;
		mData.mScrap += scrapY;
	}
	//--------------------------------------------------------------------------
	NetVec2::NetVec2( NetVec2Data & data )
	{
		mData = data;
	}
	//--------------------------------------------------------------------------
	NetVec2::~NetVec2()
	{

	}
	//==========================================================================
	NetVec2& NetVec2::operator = (const NetVec2& netVec2 )
	{
		mData.mX = netVec2.mData.mX;
		mData.mY = netVec2.mData.mY;
		mData.mScrap = netVec2.mData.mScrap;
		return *this;
	}
	//--------------------------------------------------------------------------
	NetVec2& NetVec2::operator = (const Vec2& vec2 )
	{
		// 整数部分16位
		// 15位最大可以表示 (0X7FFF)32767
		// 1位用来表示正负
		DYNAMIC_ASSERT(vec2.x <= 0x7fff && vec2.x >= -0x7fff);
		DYNAMIC_ASSERT(vec2.y <= 0x7fff && vec2.y>= -0x7fff);
		U8 scrapX = 0;
		U8 scrapY = 0;
		if (vec2.x >= 0)
		{
			mData.mX = (U16)vec2.x;
			scrapX = (U8)( ((vec2.x - mData.mX) + 0.05f) * 10 );
		}
		else
		{
			mData.mX = (U16)(-vec2.x);
			scrapX = (U8)( ((-vec2.x - mData.mX)+ 0.05f) * 10 );
			mData.mX |= 0x8000;
		}
		if (vec2.y >= 0)
		{
			mData.mY = (U16)(vec2.y);
			scrapY = (U8)( ((vec2.y - mData.mY) + 0.05f)* 10 );
		}
		else
		{
			mData.mY = (U16)(-vec2.y);
			scrapY = (U8)( ((-vec2.y - mData.mY) + 0.05f)* 10 );
			mData.mY |= 0x8000;
		}
		mData.mScrap = scrapX << 4;
		mData.mScrap += scrapY;
		return *this;
	}
	//--------------------------------------------------------------------------
	NetVec2& NetVec2::operator = (const Vec3& vec3 )
	{
		// 整数部分16位
		// 15位最大可以表示 32767
		// 1位用来表示正负
		DYNAMIC_ASSERT(vec3.x <= 0x7fff && vec3.x >= -0x7fff);
		DYNAMIC_ASSERT(vec3.z <= 0x7fff && vec3.z>= -0x7fff);
		U8 scrapX = 0;
		U8 scrapY = 0;
		if (vec3.x >= 0)
		{
			mData.mX = (U16)vec3.x;
			scrapX = (U8)( ((vec3.x - mData.mX) + 0.05f)* 10 );
		}
		else
		{
			mData.mX = (U16)(-vec3.x);
			scrapX = (U8)( ((-vec3.x - mData.mX)+ 0.05f) * 10 );
			mData.mX |= 0x8000;
		}
		if (vec3.z >= 0)
		{
			mData.mY = (U16)vec3.z;
			scrapY = (U8)( ((vec3.z - mData.mY) + 0.05f)* 10 );
		}
		else
		{
			mData.mY = (U16)(-vec3.z);
			scrapY = (U8)( ((-vec3.z - mData.mY) + 0.05f)* 10 );
			mData.mY |= 0x8000;
		}
		mData.mScrap = scrapX << 4;
		mData.mScrap += scrapY;
		return *this;
	}

	NetVec2& NetVec2::operator=( const NetVec2Data& data )
	{
		mData = data;
		return *this;
	}

    //==========================================================================
	Flt NetVec2::getX()
	{
		Flt ret = 0.0f;
		U16 tX = 0;
		U8 tS = mData.mScrap;
		if (mData.mX >= 0x7fff)
		{
			tX = mData.mX & 0x7fff;
			tS &= 0xf0;
			tS >>= 4;
			ret = -tX - (Flt)tS * 0.1f;
		}
		else
		{
			tX = mData.mX;
			tS &= 0xf0;
			tS >>= 4;
			ret = tX + (Flt)tS * 0.1f;
		}
		return ret;
	}

	//--------------------------------------------------------------------------
	Flt NetVec2::getY()
	{
		Flt ret = 0.0f;
		U16 tY = 0;
		U8 tS = mData.mScrap;
		if (mData.mY >= 0x7fff)
		{
			tY = mData.mY & 0x7fff;
			tS &= 0x0f;
			ret = -tY - (Flt)tS * 0.1f;
		}
		else
		{
			tS &= 0x0f;
			ret = mData.mY + (Flt)tS * 0.1f;
		}
		return ret;
	}

	//==========================================================================
	NetVec2::operator Vec2()
	{
		return Vec2(getX(),getY());
	}

	//--------------------------------------------------------------------------
	NetVec2::operator Vec3()
	{
		return Vec3(getX(),0.0f,getY());
	}

	//--------------------------------------------------------------------------
	/*NetVec2::operator NetVec2Data ()
	{
		return mData;
	}*/

	//--------------------------------------------------------------------------
	void NetVec2::setData( Flt x,Flt y )
	{
		// 整数部分16位
		// 15位最大可以表示 32767
		// 1位用来表示正负
		DYNAMIC_ASSERT(x <= 0x7fff && x >= -0x7fff);
		DYNAMIC_ASSERT(y <= 0x7fff && y >= -0x7fff);
		U8 scrapX = 0;
		U8 scrapY = 0;
		if (x >= 0)
		{
			mData.mX = (U16)x;
			scrapX = (U8)(((x - mData.mX )+ 0.05f) * 10);
		}
		else
		{
			mData.mX = (U16)(-x);
			scrapX = (U8)( ((-x - mData.mX )+ 0.05f) * 10 );
			mData.mX |= 0x8000;
		}
		if (y >= 0)
		{
			mData.mY = (U16)y;
			scrapY = (U8)( ((y - mData.mY )+ 0.05f) * 10 );
		}
		else
		{
			mData.mY = (U16)(-y);
			scrapY = (U8)( ((-y - mData.mY )+ 0.05f) * 10 );
			mData.mY |= 0x8000;
		}
		mData.mScrap = scrapX << 4;
		mData.mScrap += scrapY;
	}

	//--------------------------------------------------------------------------
	void NetVec2::setData(NetVec2Data & data)
	{
		mData = data;
	}

	//--------------------------------------------------------------------------
	const NetVec2Data & NetVec2::getData() 
	{
		return mData;
	}

	//==========================================================================
        
}

/******************************************************************************/
