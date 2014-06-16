//*************************************************************************************
#ifndef _H_ITEXTDS_
#define _H_ITEXTDS_
//*************************************************************************************

#include "MGEngineInterfacePreqs.h"

//*************************************************************************************

class ITextDs
{
public:
    U32 textWidth(const Str16& str, Int max_Length= -1 ) = 0;
    U32 textWidth(const Str8&str , Int max_length=-1) = 0; 

    U32 textHeight(const Str16& str, Int rowWidth ) = 0;
    U32 textHeight(const Str8&str , Int rowWidth) = 0; 
protected:
private:
};
//*************************************************************************************
#endif
//*************************************************************************************