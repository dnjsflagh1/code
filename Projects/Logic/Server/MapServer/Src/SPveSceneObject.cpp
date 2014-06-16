/******************************************************************************/

#include "stdafx.h"
#include "SPveSceneObject.h"
#include "SGameObjectFactory.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//SHomeSceneObjectPtr
	/******************************************************************************/
	void SPveSceneObjectPtr::destroy(void)
	{
		mFactory->destroySPveSceneObjectPtr( *this );
	}

	//-----------------------------------------------------------------------------
	SPveSceneObject::SPveSceneObject()
	{
	}

	//-----------------------------------------------------------------------------
	SPveSceneObject::~SPveSceneObject()
	{
	}
	Bool SPveSceneObject::initialize()
	{
		return true;
	}

	Bool SPveSceneObject::unInitialize()
	{
		return true;
	}

	void SPveSceneObject::clear()
	{

	}

	void SPveSceneObject::update(Flt delta)
	{

	}

}	//namespace MG