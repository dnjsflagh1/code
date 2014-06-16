#include "StdAfx.h"
#include "WaterEditor.h"
#include "GlobalOptions.h"
#include "CoreManager.h"
#include "IResourceManager.h"
#include "Utility.h"

namespace SceneEditor {


	//-----------------------------------------------------------------------
	void WaterEditor::initialize()
	{
		clearEditPanel();
		loadTotalWaterEffectList();
	}
	//-----------------------------------------------------------------------
	void WaterEditor::unInitialize()
	{

	}
	//-----------------------------------------------------------------------
	void WaterEditor::closeForm()
	{
		FormSet::waterEditor_form = nullptr;
	}
	//-----------------------------------------------------------------------
	void WaterEditor::clearEditPanel()
	{
        edit_waterDeepColorX->Clear();
        edit_waterDeepColorY->Clear();
        edit_waterDeepColorZ->Clear();

        edit_waterReflectColorX->Clear();
        edit_waterReflectColorY->Clear();
        edit_waterReflectColorZ->Clear();
        edit_waterReflectColorW->Clear();

        edit_waterReflectScalsesX->Clear();
        edit_waterReflectScalsesY->Clear();
        edit_waterReflectScalsesZ->Clear();
        edit_waterReflectScalsesW->Clear();

        edit_waterRefractScalsesX->Clear();
        edit_waterRefractScalsesY->Clear();
        edit_waterRefractScalsesZ->Clear();
        edit_waterRefractScalsesW->Clear();

        edit_waterSpecularColorX->Clear();
        edit_waterSpecularColorY->Clear();
        edit_waterSpecularColorZ->Clear();

        edit_waterSpecularScalsesX->Clear();
        edit_waterSpecularScalsesY->Clear();
        edit_waterSpecularScalsesZ->Clear();
        edit_waterSpecularScalsesW->Clear();

        edit_waterBumpTexParamsX->Clear();
        edit_waterBumpTexParamsY->Clear();
        edit_waterBumpTexParamsZ->Clear();
        edit_waterBumpTexParamsW->Clear();

        edit_waterSkyCubeTexName->Clear();
        edit_waterBumpTexName1->Clear();
        edit_waterBumpTexName2->Clear();
        edit_waterBumpTexName3->Clear();

        edit_waterBumpTexAnimX->Clear();
        edit_waterBumpTexAnimY->Clear();
        edit_waterBumpTexAnimZ->Clear();
        edit_waterBumpTexAnimW->Clear();
	}
	//-----------------------------------------------------------------------
	void WaterEditor::selectWaterEffectList(U32 effect_id)
	{
		clearEditPanel();

		mSelectEffectID = 0;

		IResourceManager* resourceMgr = CoreManager::getInstance().getEngineMain()->resourceMgr();

		if ( resourceMgr )
		{
			WaterEffectResourceDeclaration* decl = resourceMgr->getWaterEffectResourceDeclaration(effect_id);
			if ( decl )
			{
                edit_waterDeepColorX->Text          = TypeConverter::DoubleToStr(decl->waterDeepColor.x);
                edit_waterDeepColorY->Text          = TypeConverter::DoubleToStr(decl->waterDeepColor.y);
                edit_waterDeepColorZ->Text          = TypeConverter::DoubleToStr(decl->waterDeepColor.z);

                edit_waterReflectColorX->Text       = TypeConverter::DoubleToStr(decl->waterReflectColor.x);
                edit_waterReflectColorY->Text       = TypeConverter::DoubleToStr(decl->waterReflectColor.y);
                edit_waterReflectColorZ->Text       = TypeConverter::DoubleToStr(decl->waterReflectColor.z);
                edit_waterReflectColorW->Text       = TypeConverter::DoubleToStr(decl->waterReflectColor.w);

                edit_waterReflectScalsesX->Text       = TypeConverter::DoubleToStr(decl->waterReflectScalses.x);
                edit_waterReflectScalsesY->Text       = TypeConverter::DoubleToStr(decl->waterReflectScalses.y);
                edit_waterReflectScalsesZ->Text       = TypeConverter::DoubleToStr(decl->waterReflectScalses.z);
                edit_waterReflectScalsesW->Text       = TypeConverter::DoubleToStr(decl->waterReflectScalses.w);

                edit_waterRefractScalsesX->Text     = TypeConverter::DoubleToStr(decl->waterRefractScalses.x);
                edit_waterRefractScalsesY->Text     = TypeConverter::DoubleToStr(decl->waterRefractScalses.y);
                edit_waterRefractScalsesZ->Text     = TypeConverter::DoubleToStr(decl->waterRefractScalses.z);
                edit_waterRefractScalsesW->Text     = TypeConverter::DoubleToStr(decl->waterRefractScalses.w);

                edit_waterSpecularColorX->Text      = TypeConverter::DoubleToStr(decl->waterSpecularColor.x);
                edit_waterSpecularColorY->Text      = TypeConverter::DoubleToStr(decl->waterSpecularColor.y);
                edit_waterSpecularColorZ->Text      = TypeConverter::DoubleToStr(decl->waterSpecularColor.z);

                edit_waterSpecularScalsesX->Text    = TypeConverter::DoubleToStr(decl->waterSpecularScalses.x);
                edit_waterSpecularScalsesY->Text    = TypeConverter::DoubleToStr(decl->waterSpecularScalses.y);
                edit_waterSpecularScalsesZ->Text    = TypeConverter::DoubleToStr(decl->waterSpecularScalses.z);
                edit_waterSpecularScalsesW->Text    = TypeConverter::DoubleToStr(decl->waterSpecularScalses.w);

                edit_waterBumpTexParamsX->Text      = TypeConverter::DoubleToStr(decl->waterBumpTexParams.x);
                edit_waterBumpTexParamsY->Text      = TypeConverter::DoubleToStr(decl->waterBumpTexParams.y);
                edit_waterBumpTexParamsZ->Text      = TypeConverter::DoubleToStr(decl->waterBumpTexParams.z);
                edit_waterBumpTexParamsW->Text      = TypeConverter::DoubleToStr(decl->waterBumpTexParams.w);

                edit_waterSkyCubeTexName->Text      = TypeConverter::Char8ToStr(decl->waterSkyCubeTexName.c_str());
                edit_waterBumpTexName1->Text        = TypeConverter::Char8ToStr(decl->waterBumpTexName1.c_str());
                edit_waterBumpTexName2->Text        = TypeConverter::Char8ToStr(decl->waterBumpTexName2.c_str());
                edit_waterBumpTexName3->Text        = TypeConverter::Char8ToStr(decl->waterBumpTexName3.c_str());

                edit_waterBumpTexAnimX->Text        = TypeConverter::DoubleToStr(decl->waterBumpTexAnim.x);
                edit_waterBumpTexAnimY->Text        = TypeConverter::DoubleToStr(decl->waterBumpTexAnim.y);
                edit_waterBumpTexAnimZ->Text        = TypeConverter::DoubleToStr(decl->waterBumpTexAnim.z);
                edit_waterBumpTexAnimW->Text        = TypeConverter::DoubleToStr(decl->waterBumpTexAnim.w);


				mSelectEffectID = effect_id;
			}
		}
	}

    //-----------------------------------------------------------------------
    void WaterEditor::applyWaterEffectList(U32 id, bool isSave)
    {
        if ( id == 0 )
            return;

        IResourceManager* resourceMgr = CoreManager::getInstance().getEngineMain()->resourceMgr();

        if ( resourceMgr )
        {
            WaterEffectResourceDeclaration* decl  = resourceMgr->getWaterEffectResourceDeclaration(id);

            if ( decl )
            {
                decl->waterDeepColor.x          = TypeConverter::StrToDouble(edit_waterDeepColorX->Text);
                decl->waterDeepColor.y          = TypeConverter::StrToDouble(edit_waterDeepColorY->Text);
                decl->waterDeepColor.z          = TypeConverter::StrToDouble(edit_waterDeepColorZ->Text);

                decl->waterReflectColor.x       = TypeConverter::StrToDouble(edit_waterReflectColorX->Text);
                decl->waterReflectColor.y       = TypeConverter::StrToDouble(edit_waterReflectColorY->Text);
                decl->waterReflectColor.z       = TypeConverter::StrToDouble(edit_waterReflectColorZ->Text);
                decl->waterReflectColor.w       = TypeConverter::StrToDouble(edit_waterReflectColorW->Text);

                decl->waterReflectScalses.x     = TypeConverter::StrToDouble(edit_waterReflectScalsesX->Text);
                decl->waterReflectScalses.y     = TypeConverter::StrToDouble(edit_waterReflectScalsesY->Text);
                decl->waterReflectScalses.z     = TypeConverter::StrToDouble(edit_waterReflectScalsesZ->Text);
                decl->waterReflectScalses.w     = TypeConverter::StrToDouble(edit_waterReflectScalsesW->Text);

                decl->waterRefractScalses.x     = TypeConverter::StrToDouble(edit_waterRefractScalsesX->Text);
                decl->waterRefractScalses.y     = TypeConverter::StrToDouble(edit_waterRefractScalsesY->Text);
                decl->waterRefractScalses.z     = TypeConverter::StrToDouble(edit_waterRefractScalsesZ->Text);
                decl->waterRefractScalses.w     = TypeConverter::StrToDouble(edit_waterRefractScalsesW->Text);

                decl->waterSpecularColor.x      = TypeConverter::StrToDouble(edit_waterSpecularColorX->Text);
                decl->waterSpecularColor.y      = TypeConverter::StrToDouble(edit_waterSpecularColorY->Text);
                decl->waterSpecularColor.z      = TypeConverter::StrToDouble(edit_waterSpecularColorZ->Text);

                decl->waterSpecularScalses.x    = TypeConverter::StrToDouble(edit_waterSpecularScalsesX->Text);
                decl->waterSpecularScalses.y    = TypeConverter::StrToDouble(edit_waterSpecularScalsesY->Text);
                decl->waterSpecularScalses.z    = TypeConverter::StrToDouble(edit_waterSpecularScalsesZ->Text);
                decl->waterSpecularScalses.w    = TypeConverter::StrToDouble(edit_waterSpecularScalsesW->Text);

                decl->waterBumpTexParams.x      = TypeConverter::StrToDouble(edit_waterBumpTexParamsX->Text);
                decl->waterBumpTexParams.y      = TypeConverter::StrToDouble(edit_waterBumpTexParamsY->Text);
                decl->waterBumpTexParams.z      = TypeConverter::StrToDouble(edit_waterBumpTexParamsZ->Text);
                decl->waterBumpTexParams.w      = TypeConverter::StrToDouble(edit_waterBumpTexParamsW->Text);

                decl->waterSkyCubeTexName       = StrToChar8(edit_waterSkyCubeTexName->Text).getChar8();
                decl->waterBumpTexName1         = StrToChar8(edit_waterBumpTexName1->Text).getChar8();
                decl->waterBumpTexName2         = StrToChar8(edit_waterBumpTexName2->Text).getChar8();
                decl->waterBumpTexName3         = StrToChar8(edit_waterBumpTexName3->Text).getChar8();

                decl->waterBumpTexAnim.x      = TypeConverter::StrToDouble(edit_waterBumpTexAnimX->Text);
                decl->waterBumpTexAnim.y      = TypeConverter::StrToDouble(edit_waterBumpTexAnimY->Text);
                decl->waterBumpTexAnim.z      = TypeConverter::StrToDouble(edit_waterBumpTexAnimZ->Text);
                decl->waterBumpTexAnim.w      = TypeConverter::StrToDouble(edit_waterBumpTexAnimW->Text);
            }

            resourceMgr->saveWaterEffectResourceDeclaration( id );

            IDisplay* dis = CoreManager::getInstance().getEngineMain()->display();
            if ( dis )
                dis->apply();
        }
    }

	//-----------------------------------------------------------------------
	void WaterEditor::loadTotalWaterEffectList()
	{
		////////////////////////////////////////////////////////////
		listView_WaterEffect_list->Items->Clear();
		cur_water_effect_label->Text = nullptr;
		////////////////////////////////////////////////////////////

		IResourceManager* resourceMgr = CoreManager::getInstance().getEngineMain()->resourceMgr();

		if ( resourceMgr )
		{
			UInt count = resourceMgr->getNumWaterEffectResourceDeclaration();

			for ( UInt i=0; i<count; i++ )
			{
				WaterEffectResourceDeclaration* decl = resourceMgr->getWaterEffectResourceDeclarationByIndex(i);

				if ( decl )
				{
					String ^ name   = TypeConverter::Char8ToStr(decl->waterEffectDesc.c_str());
					String ^ id		= TypeConverter::U32ToStr(decl->waterEffectID);

					ListViewItem ^ item = gcnew ListViewItem;

					item->SubItems->default[0]->Text            = id;
					item->SubItems->default[0]->Name            = "columnHeader_water_effect_index";

					ListViewItem::ListViewSubItem ^subItem = item->SubItems->Add(name);
					subItem->Text = name;
					subItem->Name = "columnHeader_water_effect_name";

					listView_WaterEffect_list->Items->Add(item);
				}
			}
		}
	}

	//-----------------------------------------------------------------------
	void WaterEditor::onEventPressListView()
	{
		if ( listView_WaterEffect_list->SelectedItems->Count <= 0 )
			return;

		ListViewItem^ item = listView_WaterEffect_list->SelectedItems[0];
		if ( item != nullptr )
		{
			String ^ strID = item->SubItems["columnHeader_water_effect_index"]->Text;
			String ^ strName = item->SubItems["columnHeader_water_effect_name"]->Text;

			cur_water_effect_label->Text = strName;
			U32 effectID = TypeConverter::StrToInt(strID);

			selectWaterEffectList(effectID);
		}
	}
	//-----------------------------------------------------------------------
	void WaterEditor::onEventPressOK()
	{
		applyWaterEffectList(mSelectEffectID, false);
	}
	//-----------------------------------------------------------------------
	void WaterEditor::onEventPressSave()
	{
		applyWaterEffectList(mSelectEffectID, true);
	}
	//-----------------------------------------------------------------------
	void WaterEditor::onEventPressReload()
	{
		IResourceManager* resourceMgr = CoreManager::getInstance().getEngineMain()->resourceMgr();
		if ( resourceMgr )
			resourceMgr->reloadWaterEffectResourceDeclaration();
	}
	
}

