/******************************************************************************/
#ifndef _MATERIAL_SERIALIZER_H_
#define _MATERIAL_SERIALIZER_H_
/******************************************************************************/

#include "EnginePreqs.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//MG≤ƒ÷ –Ú¡–ªØ
	/******************************************************************************/
	class MaterialSerializer
	{
	public:

		MaterialSerializer(){};
		virtual ~MaterialSerializer(){};

	public:
		
		Bool	parseScript(std::vector<std::wstring> stringVector, MaterialDeclaration* mat_decls);

	};
}

/******************************************************************************/

#endif
