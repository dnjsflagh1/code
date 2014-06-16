//*******************************************************************************************************
#ifndef _H_CDTIMERFACTORY_
#define _H_CDTIMERFACTORY_
//*******************************************************************************************************
#include "WorldCorePreqs.h"
#include "WorldCoreDefine.h"
#include "CDTemplate.h"
//*******************************************************************************************************
namespace MG
{
    class CDTimerFactory
    {
    public:
        CDTimerFactory();
        ~CDTimerFactory();

    public:
        void            addData( U32 ID, CDTempInfo* pInfo, U32 liveTime, U32 useTime );
        CDTimerData*    getData( U32 ID );


    protected:
    private:
    };
}
//*******************************************************************************************************
#endif
//*******************************************************************************************************