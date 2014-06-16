
/******************************************************************************/

#ifndef _S_SCENE_OBJECT_PTR_H_
#define _S_SCENE_OBJECT_PTR_H_

/******************************************************************************/

#include "MapServerPreqs.h"

#include "SSceneObjectFactory.h"

#include "SHomeSceneObject.h"
#include "SPlaceSceneObject.h"
#include "SPveSceneObject.h"
#include "STiroSceneObject.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //服务端【地图】智能指针
    /******************************************************************************/

    class SSceneObjectPtr : public SharedPtr<SSceneObject> 
    {

    protected:

        SSceneObjectFactory* mFactory;

    public:

        virtual ~SSceneObjectPtr() { release(); }
        SSceneObjectPtr() : SharedPtr<SSceneObject>(),mFactory(NULL){}
        explicit SSceneObjectPtr(SSceneObject* rep) : SharedPtr<SSceneObject>(rep),mFactory(NULL){}

        SSceneObjectPtr(const SSceneObjectPtr& r) : SharedPtr<SSceneObject>(r),mFactory(r.mFactory) {} 
		SSceneObjectPtr(const SPlaceSceneObjectPtr& r) : SharedPtr<SSceneObject>(),mFactory(r.mFactory) 
		{
			// lock & copy other mutex pointer
			{
				pRep = r.pRep;
				pUseCount = r.pUseCount;
				mIsAllowDestroy = r.mIsAllowDestroy; 
				// Handle zero pointer gracefully to manage STL containers
				if(pUseCount)
				{
					++(*pUseCount); 
				}
			}
		} 
		SSceneObjectPtr(const SHomeSceneObjectPtr& r) : SharedPtr<SSceneObject>(),mFactory(r.mFactory) 
		{
			// lock & copy other mutex pointer
			{
				pRep = r.pRep;
				pUseCount = r.pUseCount;
				mIsAllowDestroy = r.mIsAllowDestroy; 
				// Handle zero pointer gracefully to manage STL containers
				if(pUseCount)
				{
					++(*pUseCount); 
				}
			}
		} 
		SSceneObjectPtr(const SPveSceneObjectPtr& r) : SharedPtr<SSceneObject>(),mFactory(r.mFactory) 
		{
			// lock & copy other mutex pointer
			{
				pRep = r.pRep;
				pUseCount = r.pUseCount;
				mIsAllowDestroy = r.mIsAllowDestroy; 
				// Handle zero pointer gracefully to manage STL containers
				if(pUseCount)
				{
					++(*pUseCount); 
				}
			}
		} 
		SSceneObjectPtr(const STiroSceneObjectPtr& r) : SharedPtr<SSceneObject>(),mFactory(r.mFactory) 
		{
			// lock & copy other mutex pointer
			{
				pRep = r.pRep;
				pUseCount = r.pUseCount;
				mIsAllowDestroy = r.mIsAllowDestroy; 
				// Handle zero pointer gracefully to manage STL containers
				if(pUseCount)
				{
					++(*pUseCount); 
				}
			}
		} 

        //-----------------------------------------------------------------------------
        SSceneObjectPtr& operator=(const SSceneObjectPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;

            SSceneObjectPtr tmp(r);
            if ( isNull() == false )
            {
                tmp.mFactory = mFactory;
            }

            swap(tmp);

            mFactory = r.mFactory;

            return *this;
        }

        //-----------------------------------------------------------------------------
        SSceneObjectPtr& operator=(const SPlaceSceneObjectPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;

            SSceneObjectPtr tmp(r);
            if ( isNull() == false )
            {
                tmp.mFactory = mFactory;
            }

            swap(tmp);

            mFactory = r.mFactory;

            return *this;
        }

        //-----------------------------------------------------------------------------
        SSceneObjectPtr& operator=(const SHomeSceneObjectPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;

            SSceneObjectPtr tmp(r);
            if ( isNull() == false )
            {
                tmp.mFactory = mFactory;
            }

            swap(tmp);

            mFactory = r.mFactory;

            return *this;
        }

        //-----------------------------------------------------------------------------
        SSceneObjectPtr& operator=(const SPveSceneObjectPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;

            SSceneObjectPtr tmp(r);
            if ( isNull() == false )
            {
                tmp.mFactory = mFactory;
            }

            swap(tmp);

            mFactory = r.mFactory;

            return *this;
        }

        //-----------------------------------------------------------------------------
        SSceneObjectPtr& operator=(const STiroSceneObjectPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;

            SSceneObjectPtr tmp(r);
            if ( isNull() == false )
            {
                tmp.mFactory = mFactory;
            }

            swap(tmp);

            mFactory = r.mFactory;

            return *this;
        }

        //-----------------------------------------------------------------------------

    protected:

        virtual void    destroy(void);

    };



}

#endif	//_S_SCENE_OBJECT_PTR_H_