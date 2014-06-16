#include "StdAfx.h"
#include "MainForm.h"
#include "GlobalOptions.h"
#include "CoreManager.h"
#include "Utility.h"
#include "XmlHelper.h"
#include "OperationManager.h"

namespace ModelEditor {

    //-----------------------------------------------------------------------
    void MainForm::initialize()
    {
        setSceneFormLocation();
    }
    //-----------------------------------------------------------------------
    void MainForm::clearAll()
    {

    }
    //-----------------------------------------------------------------------
    void MainForm::revert()
    {
 
    }
    //-----------------------------------------------------------------------
    void MainForm::update()
    {

    }
   
    //-----------------------------------------------------------------------
    void MainForm::setSceneFormLocation()
    {
        UInt margin = 5;

        Point scene_loation  = this->scene_panel->PointToScreen( this->scene_panel->Location );
        scene_loation.X  = this->DesktopLocation.X + this->scene_panel->Location.X + margin;

        FormSet::scene_form->DesktopLocation = scene_loation ;

        System::Drawing::Size  size = this->scene_panel->Size;
        size.Width  -= margin;
        size.Height -= margin;
        FormSet::scene_form->Size = size;
    }
}

