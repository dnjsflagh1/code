/******************************************************************************/
#ifndef _S_PLAYER_CHARACTER_H_
#define _S_PLAYER_CHARACTER_H_
/******************************************************************************/
#include "FrontServerPreqs.h"
#include "SCharacter.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //玩家角色
    /******************************************************************************/
    class SPlayerCharacter : public SCharacter
    {
    public:

        SPlayerCharacter();
        virtual ~SPlayerCharacter();
        
	public:

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool                    initialize( PlayerCharacterData& clarData );
        virtual Bool                    unInitialize();

        virtual void                    update(Flt delta);
        virtual void                    clear();


        //-----------------------------------------------------------------------------------
        // Debug
        //-----------------------------------------------------------------------------------

		virtual		void                print();

        //-----------------------------------------------------------------------------------
        // Server Info
        //-----------------------------------------------------------------------------------

        void                            setMapServerNetId(NetIdType mapServerNetId);
        NetIdType				        getMapServerNetId() const;
        NetIdType				        getLastMapServerNetId() const;

        //-----------------------------------------------------------------------------------
        // Base Info
        //-----------------------------------------------------------------------------------

        virtual PlayerCharacterData*    getData();

		virtual void                    setDBAttrInit(UInt index, Flt value);
		virtual Flt                     getDBAttrInit(UInt index);
		virtual void               		setDBAttrLvlAdd(UInt index, Flt value);
		virtual Flt                		getDBAttrLvlAdd(UInt index);
		virtual UInt					getDBAttrInitID();
		virtual UInt					getDBAttrLvlAddID();
		virtual void					setDBAttrInitID(UInt id);
		virtual void					setDBAttrLvlAddID(UInt id);

		void							setBaseAttr();
		U32								setGenrealAge( const CalendarInfo* pCalendarInfo, U32 age );

        //-----------------------------------------------------------------------------------
        // Alive
        //-----------------------------------------------------------------------------------
    
		void							setAlive();
       

		void							setParentClan(SClan* parentClan);

	private:

        PlayerCharacterData             mPlayerCharacterData;

		NetIdType						mMapServerNetId;
		NetIdType						mLastMapServerNetId;

		SClan*							mParentClan;
    };


    /******************************************************************************/
    //SPlayerCharacter的智能指针
    /******************************************************************************/
    class SPlayerCharacterPtr : public SharedPtr<SPlayerCharacter> 
    {
        friend class SPlayerCharacterFactory;

    protected:

        SPlayerCharacterFactory* mFactory;

    public:

        virtual ~SPlayerCharacterPtr() { release(); }
        SPlayerCharacterPtr() : SharedPtr<SPlayerCharacter>(),mFactory(NULL){}
        explicit SPlayerCharacterPtr(SPlayerCharacter* rep) : SharedPtr<SPlayerCharacter>(rep),mFactory(NULL){}
        SPlayerCharacterPtr(const SPlayerCharacterPtr& r) : SharedPtr<SPlayerCharacter>(r),mFactory(r.mFactory) {} 

        SPlayerCharacterPtr& operator=(const SPlayerCharacterPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;

            SPlayerCharacterPtr tmp(r);
            if ( isNull() == false )
            {
                tmp.mFactory = mFactory;
            }

            swap(tmp);

            mFactory = r.mFactory;

            return *this;
        }

    protected:

        virtual void    destroy(void);

    };


}
#endif	//_S_PLAYER_CHARACTER_H_