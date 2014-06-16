#include "StdAfx.h"
#include "TerrainTextureForm.h"
#include "GlobalOptions.h"
#include "CoreManager.h"
#include "Utility.h"

namespace SceneEditor {


    //-----------------------------------------------------------------------
    void TerrainTextureForm::initialize()
    {
        refresh();
        loadTotalTerrainTextureList();
    }
    //-----------------------------------------------------------------------
    void TerrainTextureForm::unInitialize()
    {

    }
    //-----------------------------------------------------------------------
    void TerrainTextureForm::closeForm()
    {
        FormSet::terrainTexture_form = nullptr;
    }
    //-----------------------------------------------------------------------
    void TerrainTextureForm::refresh()
    {
        loadCurrSceneTerrainTextureList();
    }

    //-----------------------------------------------------------------------
    void TerrainTextureForm::loadTotalTerrainTextureList()
    {
        treeView_globle_terrain_tex_list->Nodes->Clear();

        IResourceManager* resourceMgr = CoreManager::getInstance().getEngineMain()->resourceMgr();

        if ( resourceMgr )
        {
            UInt count = resourceMgr->getTerrainTextureLayerDeclarationCount();

            for ( UInt i=0; i<count; i++ )
            {
                TerrainTextureLayerDeclaration* decl = resourceMgr->getTerrainTextureLayerDeclaration(i);

                if ( decl )
                {
                    String^ treeNodeName = "Node" + TypeConverter::IntToStr(i);
                    TreeNode ^ currTreeNode = gcnew TreeNode(treeNodeName);
                    Str text = decl->name + " " + decl->describe;
                    currTreeNode->Text  = TypeConverter::Char8ToStr(text.c_str());
                    currTreeNode->Tag   = TypeConverter::Char8ToStr(decl->name.c_str());

                    treeView_globle_terrain_tex_list->Nodes->Add( currTreeNode );
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void TerrainTextureForm::selectTotalTerrainTextureList()
    {
        if ( treeView_globle_terrain_tex_list->SelectedNode != nullptr &&
            treeView_globle_terrain_tex_list->SelectedNode->Tag != nullptr )
        {
            String^ tag = treeView_globle_terrain_tex_list->SelectedNode->Tag->ToString();
            if ( !String::IsNullOrEmpty(tag) )
            {
                StrToChar8 nameStr(tag);

                Str name = nameStr.getChar8();

                ////////////////////////////////////////////////////////////

                ITerrainSurfaceManager* surfaceMgr    = CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainSurfaceManager();

                surfaceMgr->addGlobleTextureLayer( name );

                /////////////////////////////////////////////////////////////

                loadCurrSceneTerrainTextureList();
            }
        } 
    }

    //-----------------------------------------------------------------------
    void TerrainTextureForm::loadCurrSceneTerrainTextureList()
    {
        treeView_scene_terrain_tex_list->Nodes->Clear();
        ITerrainSurfaceManager* surfaceMgr    = CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainSurfaceManager();
        if ( surfaceMgr )
        {
            Int count = surfaceMgr->getGlobleTextureLayerMaxCount();

            for ( Int i=0; i<count; i++ )
            {
                TerrainTextureLayerDeclaration* decl = surfaceMgr->getGlobleTextureLayer( i );
                
                if ( decl )
                {
                    String^ treeNodeName = "Node" + TypeConverter::IntToStr(i);
                    TreeNode ^ currTreeNode = gcnew TreeNode(treeNodeName);
                    Str text = decl->name + " " + decl->describe;
                    currTreeNode->Text  = TypeConverter::Char8ToStr(text.c_str());
                    currTreeNode->Tag   = TypeConverter::IntToStr(i);

                    treeView_scene_terrain_tex_list->Nodes->Add( currTreeNode );
                }
            }
        }
    }
    //-----------------------------------------------------------------------
    void TerrainTextureForm::selectCurrSceneTerrainTextureList()
    {
        if ( treeView_scene_terrain_tex_list->SelectedNode != nullptr &&
            treeView_scene_terrain_tex_list->SelectedNode->Tag != nullptr )
        {
            String^ tag = treeView_scene_terrain_tex_list->SelectedNode->Tag->ToString();
            if ( !String::IsNullOrEmpty(tag) )
            {
                Int index = TypeConverter::StrToInt( tag );

                FormSet::main_form->setActiveTerrainTexture( index );
            }
        }
    }
    
    
}