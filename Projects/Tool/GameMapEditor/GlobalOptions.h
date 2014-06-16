/******************************************************************************/
#ifndef _GLOBALOPTIONS_H_
#define _GLOBALOPTIONS_H_
/******************************************************************************/

#include "MainForm.h"
#include "SceneForm.h"
#include "MapLoadForm.h"

/******************************************************************************/

namespace GameMapEditor {


    /******************************************************************************/
    public ref class FormSet
    {
    public:
        static MainForm^    main_form;
        static SceneForm^   scene_form;
		static MapLoadForm^	mapload_form;
    };
    
    
}

/******************************************************************************/
#endif

