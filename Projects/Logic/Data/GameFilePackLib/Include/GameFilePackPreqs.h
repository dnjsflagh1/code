/******************************************************************************/
#ifndef _GAMEFILEPACKPREQS_H_
#define _GAMEFILEPACKPREQS_H_
/******************************************************************************/

#include "MGTypes.h"
#include "CommonGameDefine.h"
#include "GameFilePackDefine.h"

#include "MGPackDefine.h"
#include "MGPackManager.h"

/******************************************************************************/
namespace MG
{
	typedef	std::map<std::string, MG::IMGPackFileSet*> ZIP_ARC_MAP;
	typedef	std::map<std::string, MG::IMGPackFileSet*>::iterator ZIP_ARC_MAP_ITER;
}

#endif	