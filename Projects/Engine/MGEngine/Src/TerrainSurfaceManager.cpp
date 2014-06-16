/******************************************************************************/
#include "stdafx.h"
#include "TerrainChunk.h"
#include "TerrainSurfaceManager.h"
#include "ResourceManager.h"
#include "TerrainGroundSurface.h"
#include "TerrainWaterSurface.h"
#include "TerrainWaterMaterial.h"
#include "TerrainTilesMaterialA.h"
#include "TerrainTilesMaterialB.h"

#include "TerrainBBGroundSurface.h"
#include "TerrainSBGroundSurface.h"

/******************************************************************************/

namespace MG
{

    //---------------------------------------------------------------------
    TerrainSurfaceManager::TerrainSurfaceManager(TerrainManager* mgr, Scene* scene)
        :mOwner(mgr)
        ,mScene(scene)
    {
        mTerrainWaterMaterial = MG_NEW TerrainWaterMaterial(scene,this);
    }

    //---------------------------------------------------------------------
    TerrainSurfaceManager::~TerrainSurfaceManager()
    {
        MG_SAFE_DELETE(mTerrainWaterMaterial);
    }

    //---------------------------------------------------------------------
    void TerrainSurfaceManager::update( Flt delta )
    {
        if ( mTerrainWaterMaterial )
            mTerrainWaterMaterial->update( delta );
    }

    //---------------------------------------------------------------------
    void TerrainSurfaceManager::clearGlobleTextureLayer()
    {
        mGlobleTerrainTextureLayerList.clear();
    }

    //---------------------------------------------------------------------
    void TerrainSurfaceManager::addGlobleTextureLayer(Int index, Str name)
    {
        TerrainTextureLayerDeclaration* decl = MG::ResourceManager::getSingletonPtr()->getTerrainTextureLayerDeclaration( name.c_str() );
        if ( decl )
        {
            GlobleTerrainTextureLayer layer;
            layer.decl = decl;
            mGlobleTerrainTextureLayerList[index] = layer;
        }
    }

    //---------------------------------------------------------------------
    Bool TerrainSurfaceManager::hasGlobleTextureLayer(Str name)
    {
        std::map<Int, GlobleTerrainTextureLayer>::iterator iter =  mGlobleTerrainTextureLayerList.begin();
        for ( ; iter != mGlobleTerrainTextureLayerList.end(); iter++ )
        {
            if ( iter->second.decl->name == name ) 
            {
                return true;
            }
        }
        return false;
    }

    //---------------------------------------------------------------------
    void TerrainSurfaceManager::addGlobleTextureLayer(Str name)
    {
        if ( !hasGlobleTextureLayer(name) )
        {
            TerrainTextureLayerDeclaration* decl = MG::ResourceManager::getSingletonPtr()->getTerrainTextureLayerDeclaration( name.c_str() );
            if ( decl )
            {
                UInt index  = 0;
                UInt maxNum = getGlobleTextureLayerMaxCount();
                for( ; index <= maxNum; index++ )
                {
                    if ( mGlobleTerrainTextureLayerList.end() == mGlobleTerrainTextureLayerList.find(index) )
                    {
                        GlobleTerrainTextureLayer layer;
                        layer.decl = decl;
                        mGlobleTerrainTextureLayerList[index] = layer;
                        break;
                    }
                }
            }
        }
    }
    //---------------------------------------------------------------------
    Int TerrainSurfaceManager::getGlobleTextureLayerMaxCount()
    {
        return 255;
    }

    //---------------------------------------------------------------------
    TerrainTextureLayerDeclaration* TerrainSurfaceManager::getGlobleTextureLayer( Int index )
    {
        std::map<Int, GlobleTerrainTextureLayer>::iterator iter =  mGlobleTerrainTextureLayerList.find(index);
        if ( mGlobleTerrainTextureLayerList.end() != iter )
        {
            return iter->second.decl;
        }
        return NULL;
    }

    //---------------------------------------------------------------------
    void TerrainSurfaceManager::clearGlobleTextureLayerUsedDirty()
    {
        std::map<Int, GlobleTerrainTextureLayer>::iterator iter =  mGlobleTerrainTextureLayerList.begin();
        for ( ;iter != mGlobleTerrainTextureLayerList.end() ; iter++ )
        {
            iter->second.usedDirty = false;
        }
    }

    //---------------------------------------------------------------------
    void TerrainSurfaceManager::cleanNoUsedGlobleTextureLayer()
    {
        std::map<Int, GlobleTerrainTextureLayer>::iterator iter =  mGlobleTerrainTextureLayerList.begin();
        for ( ;iter != mGlobleTerrainTextureLayerList.end() ; )
        {
            if ( iter->second.usedDirty == false )
            {
                iter = mGlobleTerrainTextureLayerList.erase( iter );
            }else
            {
                iter++;
            }
        }

    }

    //---------------------------------------------------------------------
    TerrainBBGroundSurface* TerrainSurfaceManager::createTerrainBBGroundSurface(TerrainChunk* chunk)
    {
        TerrainBBGroundSurface* surface = MG_NEW TerrainBBGroundSurface( mOwner, mScene, chunk );
        return surface;
    }

    //---------------------------------------------------------------------
    TerrainSBGroundSurface* TerrainSurfaceManager::createTerrainSBGroundSurface(TerrainChunk* chunk)
    {
        TerrainSBGroundSurface* surface = MG_NEW TerrainSBGroundSurface( mOwner, mScene, chunk );
        return surface;
    }

    //---------------------------------------------------------------------
    void TerrainSurfaceManager::destroyTerrainGroundSurface(TerrainGroundSurface* surface)
    {
        MG_SAFE_DELETE( surface );
    }
    
    //---------------------------------------------------------------------
    TerrainWaterSurface* TerrainSurfaceManager::createTerrainWaterSurface(TerrainChunk* chunk)
    {
        TerrainWaterSurface* surface = MG_NEW TerrainWaterSurface( mOwner, mScene, chunk );
        return surface;
    }

    //---------------------------------------------------------------------
    void TerrainSurfaceManager::destroyTerrainWaterSurface(TerrainWaterSurface* surface)
    {
        MG_SAFE_DELETE( surface );
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    Int TerrainSurfaceManager::getGlobleWaterGroupMaxCount()
    {
        return mGlobleTerrainWaterGroupList.size();
    }

    //---------------------------------------------------------------------
    TerrainWaterGroupDeclaration* TerrainSurfaceManager::getGlobleWaterGroupByIndex( UInt index )
    {
        if ( mGlobleTerrainWaterGroupList.empty() )
            return NULL ;

        std::map<Int, TerrainWaterGroupDeclaration>::iterator iter =  mGlobleTerrainWaterGroupList.begin();
        std::advance( iter, index );

        if ( iter != mGlobleTerrainWaterGroupList.end() )
            return &(iter->second);

        iter = mGlobleTerrainWaterGroupList.begin(); 
        return &(iter->second);
    }

    //---------------------------------------------------------------------
    TerrainWaterGroupDeclaration* TerrainSurfaceManager::getGlobleWaterGroup( U32 groupID )
    {
        if ( mGlobleTerrainWaterGroupList.empty() )
            return NULL;

        std::map<Int, TerrainWaterGroupDeclaration>::iterator iter =  mGlobleTerrainWaterGroupList.find(groupID);
        if ( mGlobleTerrainWaterGroupList.end() != iter )
        {
            return &(iter->second);
        }else
        {
            iter = mGlobleTerrainWaterGroupList.begin(); 
            return &(iter->second);
        }
        return NULL;
    }

    //---------------------------------------------------------------------
    TerrainWaterGroupDeclaration* TerrainSurfaceManager::addGlobleWaterGroup( U32 groupID )
    {
        // 暂时只支持一张全局水组配置
        if ( mGlobleTerrainWaterGroupList.empty() == false )
            return getGlobleWaterGroup(groupID);
       
        TerrainWaterGroupDeclaration* decl = getGlobleWaterGroup( groupID );

        if ( !decl )
        {
            mGlobleTerrainWaterGroupList[groupID] = TerrainWaterGroupDeclaration();

            decl = getGlobleWaterGroup( groupID );

            decl->groupID = groupID;
        }

        return decl;
    }

    //---------------------------------------------------------------------
    void TerrainSurfaceManager::clearGlobleWaterGroups()
    {
        mGlobleTerrainWaterGroupList.clear();

        mTerrainWaterMaterial->freeAllMaterialPtr();
    }

}