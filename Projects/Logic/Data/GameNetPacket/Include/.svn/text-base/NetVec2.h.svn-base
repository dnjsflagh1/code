/******************************************************************************/
#ifndef _NETVEC2_H_
#define _NETVEC2_H_
/******************************************************************************/

#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "MGVector.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
#pragma pack (push)
#pragma pack (1)
	//**********************************************************************
	struct NetVec2Data 
	{
		U16 mX;
		U16 mY;
		U8	mScrap;
	};
	struct NetVec2
	{
	public:

		NetVec2();
		NetVec2(NetVec2Data & data);
		NetVec2(NetVec2& netVec2);
		NetVec2(Vec2& vec2);
		NetVec2(Vec3& vec3);
		NetVec2(Flt x,Flt y);
		~NetVec2();

	public:

		NetVec2& operator = (const NetVec2& netVec2);
		NetVec2& operator = (const Vec2& vec2);
		NetVec2& operator = (const Vec3& vec3);
		NetVec2& operator = (const NetVec2Data& data);

		operator Vec2();
		operator Vec3();
		//operator NetVec2Data ();
		//operator NetVec2Data& ();

	public:

		Flt					getX();
		Flt					getY();
		void				setData(Flt x,Flt y);
		void				setData(NetVec2Data & data);
		const NetVec2Data &	getData();

	public:

		NetVec2Data  mData;
	};
	//**********************************************************************

#pragma pack (pop)

}

/******************************************************************************/

#endif