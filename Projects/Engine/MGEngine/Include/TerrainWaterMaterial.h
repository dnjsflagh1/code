/******************************************************************************/
#ifndef _TERRAINWATERMATERIAL_H_
#define _TERRAINWATERMATERIAL_H_
/******************************************************************************/

#include "EnginePreqs.h"

/******************************************************************************/
namespace MG
{

    //¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á
    //¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á

    /******************************************************************************/

    /******************************************************************************/
	class TerrainWaterMaterial
    {
    public:
        TerrainWaterMaterial( Scene* scene, TerrainSurfaceManager* surfaceMgr );
        virtual ~TerrainWaterMaterial();

    public:
        
        void                    update( Flt delta );
        void                    reset();

        void                    applyRenderConfig();

        MaterialPtr&            getOrGenerateMaterialPtr( UInt groupID, TerrainChunk* chunk );

        void                    freeAllMaterialPtr( );

		Bool                    isWaterRendering(){return mIsRenderWater;};

	public:

		class WaterMaterialWrapper : public Ogre::RenderTargetListener
		{
		public:

			TerrainWaterMaterial*		mgr;

			UInt						groupID;
            std::map<Str,MaterialPtr>	matList;
			RenderTarget*				refractionTarget;
			RenderTarget*				reflectionTarget;
            Bool						renderFirst;

			WaterMaterialWrapper()
				:mgr(NULL)
				,refractionTarget(NULL)
				,reflectionTarget(NULL)
                ,renderFirst(true)
			{
			}

		protected:

			/// Overridden from RenderTargetListener
			virtual void			preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
			virtual void			postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
		};
		friend class WaterMaterialWrapper;

	public:

		static Str              getWaterMaterialSuffixName( UInt groupID, TerrainChunk* chunk );
		static Str              getWaterReflectionTextureName( UInt groupID );
		static Str              getWaterRefractionTextureName( UInt groupID );

    protected:

		WaterMaterialWrapper*	getWaterMaterialWrapper( UInt groupID );

		void					createReflectionTexture( WaterMaterialWrapper* wrapper, TerrainChunk* chunk );
		void					destroyReflectionTexture( WaterMaterialWrapper* wrapper );

		void					createRefractionTexture( WaterMaterialWrapper* wrapper, TerrainChunk* chunk );
		void					destroyRefractionTexture( WaterMaterialWrapper* wrapper );

        void					setLightingMap( WaterMaterialWrapper* wrapper, TerrainChunk* chunk );

		void					freeMaterial( WaterMaterialWrapper* wrapper );

        void                    setReflectionPlane( RenderTarget* rt, Plane& plane );

    protected:

        Scene* mScene;

        TerrainSurfaceManager* mTerrainSurfaceManager;
        
        std::map<UInt, WaterMaterialWrapper> mMaterialList;

        Bool mIsRenderWater;

        MaterialPtr mNullMaterialPtr;
        
    };



}


/******************************************************************************/

#endif