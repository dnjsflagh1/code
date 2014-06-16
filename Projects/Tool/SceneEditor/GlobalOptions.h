/******************************************************************************/
#ifndef _GLOBALOPTIONS_H_
#define _GLOBALOPTIONS_H_
/******************************************************************************/

#include "MainForm.h"
#include "CreateForm.h"
#include "SceneInfo.h"
#include "SceneForm.h"
#include "GameDataEditorForm.h"
#include "TerrainTextureForm.h"
#include "WaterEditor.h"

/******************************************************************************/

namespace SceneEditor {


    /******************************************************************************/
    public ref class FormSet
    {
    public:
        static MainForm^    main_form;
        static SceneForm^   scene_form;
		static CreateForm^  create_form;
		static SceneInfo^  SceneInfo_form;
        static GameDataEditorForm^   gameData_form;
        static TerrainTextureForm^   terrainTexture_form;
		static WaterEditor^			 waterEditor_form;			 
    };
    
    
}

/******************************************************************************/
#endif

