/******************************************************************************/
#include "stdafx.h"
#include "EditorOperation.h"
#include "EditorSystem.h"
#include "EngineMain.h"
#include "Scene.h"
#include "BrushSystem.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    EditorOperation::EditorOperation()
    {
        mScene = EngineMain::getInstance().getFirstScene();
    }

    //-----------------------------------------------------------------------
    EditorOperation::~EditorOperation()
    {
        
    }

	//-----------------------------------------------------------------------
	void EditorOperation::execute() 
	{
        if ( getScene() )
        {
            TerrainManager* terrain = getScene()->getTerrainManager();
            if ( terrain )
            {
                Ogre::Rect rect = BrushSystem::getInstance().getActiveRect();
                UInt chunkCount = terrain->getTerrainChunkCount();

                for (UInt i=0;i<chunkCount; i++)
                {
                    TerrainChunk* chunk = terrain->getTerrainChunkByIndex(i);
                    
                    if ( chunk )
                    {
                        Ogre::Rect chunkRect = rect.intersect( chunk->getBoundingRect() );

                        if ( chunkRect.isNull() == false )
                        {
                            execute( chunk, chunkRect );
                        }
                    }
                }
            }
        }
	}

	//-----------------------------------------------------------------------
	void EditorOperation::rollback()
	{
		
	}
}


