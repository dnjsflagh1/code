/******************************************************************************/
#ifndef _TERRAINTILESMATERIAL_H_
#define _TERRAINTILESMATERIAL_H_
/******************************************************************************/

#include "EnginePreqs.h"

/******************************************************************************/
namespace MG
{
    /** \addtogroup Optional Components
    *  @{
    */
    /** \addtogroup Terrain
    *  Some details on the terrain component
    *  @{
    */


    /** Enumeration of types of data that can be read from textures that are
    specific to a given layer. Notice that global texture information 
    such as shadows and terrain normals are not represented
    here because they are not a per-layer attribute, and blending
    is stored in packed texture structures which are stored separately.
    */
    enum TerrainLayerSamplerSemantic
    {
        /// Albedo colour (diffuse reflectance colour)
        TLSS_ALBEDO = 0,
        /// Tangent-space normal information from a detail texture
        TLSS_NORMAL = 1,
        /// Height information for the detail texture
        TLSS_HEIGHT = 2,
        /// Specular reflectance
        TLSS_SPECULAR = 3
    };

    /** Information about one element of a sampler / texture within a layer. 
    */
    struct TerrainLayerSamplerElement
    {
        /// The source sampler index of this element relative to LayerDeclaration's list
        uint8 source;
        /// The semantic this element represents
        TerrainLayerSamplerSemantic semantic;
        /// The colour element at which this element starts
        uint8 elementStart;
        /// The number of colour elements this semantic uses (usually standard per semantic)
        uint8 elementCount;

        bool operator==(const TerrainLayerSamplerElement& e) const
        {
            return source == e.source &&
                semantic == e.semantic &&
                elementStart == e.elementStart &&
                elementCount == e.elementCount;
        }

        TerrainLayerSamplerElement() {}
        TerrainLayerSamplerElement(uint8 src, TerrainLayerSamplerSemantic sem,
            uint8 elemStart, uint8 elemCount)
            : source(src), semantic(sem), elementStart(elemStart), elementCount(elemCount)
        {
        }
    };
    typedef Ogre::vector<TerrainLayerSamplerElement>::type TerrainLayerSamplerElementList;

    /** Description of a sampler that will be used with each layer. 
    */
    struct TerrainLayerSampler
    {
        /// A descriptive name that is merely used to assist in recognition
        String alias;
        /// The format required of this texture
        PixelFormat format;

        bool operator==(const TerrainLayerSampler& s) const
        {
            return alias == s.alias && format == s.format;
        }

        TerrainLayerSampler() {}

        TerrainLayerSampler(const String& aliasName, PixelFormat fmt)
            : alias(aliasName), format(fmt)
        {
        }
    };
    typedef Ogre::vector<TerrainLayerSampler>::type TerrainLayerSamplerList;

    /** The definition of the information each layer will contain in this terrain.
    All layers must contain the same structure of information, although the
    input textures can be different per layer instance. 
    */
    struct TerrainLayerDeclaration
    {
        TerrainLayerSamplerList samplers;
        TerrainLayerSamplerElementList elements;

        bool operator==(const TerrainLayerDeclaration& dcl) const
        {
            return samplers == dcl.samplers && elements == dcl.elements;
        }
    };

    /** Class that provides functionality to generate materials for use with a terrain.
    @remarks
    Terrains are composed of one or more layers of texture information, and
    require that a material is generated to render them. There are various approaches
    to rendering the terrain, which may vary due to:
    <ul><li>Hardware support (static)</li>
    <li>Texture instances assigned to a particular terrain (dynamic in an editor)</li>
    <li>User selection (e.g. changing to a cheaper option in order to increase performance, 
    or in order to test how the material might look on other hardware (dynamic)</li>
    </ul>
    Subclasses of this class are responsible for responding to these factors and
    to generate a terrain material. 
    @par
    In order to cope with both hardware support and user selection, the generator
    must expose a number of named 'profiles'. These profiles should function on
    a known range of hardware, and be graded by quality. At runtime, the user 
    should be able to select the profile they wish to use (provided hardware
    support is available). 
    */
    class TerrainMaterialGenerator : public GeneralAllocatedObject
    {
    public:
        /** Inner class which should also be subclassed to provide profile-specific 
        material generation.
        */
        class Profile : public GeneralAllocatedObject
        {
        protected:
            TerrainMaterialGenerator* mParent;
            String mName;
            String mDesc;
        public:
            Profile(TerrainMaterialGenerator* parent, const String& name, const String& desc)
                : mParent(parent), mName(name), mDesc(desc) {}
            Profile(const Profile& prof) 
                : mParent(prof.mParent), mName(prof.mName), mDesc(prof.mDesc) {}
            virtual ~Profile() {}
            /// Get the generator which owns this profile
            TerrainMaterialGenerator* getParent() const { return mParent; }
            /// Get the name of this profile
            const String& getName() const { return mName; }
            /// Get the description of this profile
            const String& getDescription() const { return mDesc; }

            /// Generate / resuse a material for the terrain
            virtual MaterialPtr generate(TerrainGroundTileRender* tileRender) = 0;
            /// Get the number of layers supported
            virtual uint8 getMaxLayers(TerrainGroundTileRender* tileRender) const = 0;

            /// Update params for a terrain
            virtual void updateParams(const MaterialPtr& mat, TerrainGroundTileRender* tileRender) = 0;

            /// Request the options needed from the terrain
            virtual void requestOptions(TerrainGroundTileRender* tileRender) = 0;

            /// Request the options needed from the terrain
            virtual void respondOptions(Bool immediately, Bool isSimple) = 0;
        };

        TerrainMaterialGenerator();
        virtual ~TerrainMaterialGenerator();

        /// List of profiles - NB should be ordered in descending complexity
        typedef Ogre::vector<Profile*>::type ProfileList;

        /** Get the list of profiles that this generator supports.
        */
        virtual const ProfileList& getProfiles() const { return mProfiles; }

        /** Set the active profile by name. */
        virtual void setActiveProfile(const String& name)
        {
            if (!mActiveProfile || mActiveProfile->getName() != name)
            {
                for (ProfileList::iterator i = mProfiles.begin(); i != mProfiles.end(); ++i)
                {
                    if ((*i)->getName() == name)
                    {
                        setActiveProfile(*i);
                        break;
                    }
                }
            }

        }

        /** Set the active Profile. */
        virtual void setActiveProfile(Profile* p)
        {
            if (mActiveProfile != p)
            {
                mActiveProfile = p;
                _markChanged();
            }
        }
        /// Get the active profile
        Profile* getActiveProfile() const 
        { 
            // default if not chosen yet
            if (!mActiveProfile && !mProfiles.empty())
                mActiveProfile = mProfiles[0];

            return mActiveProfile; 
        }

        /// Internal method - indicates that a change has been made that would require material regeneration
        void _markChanged() { ++mChangeCounter; }

        /** Returns the number of times the generator has undergone a change which 
        would require materials to be regenerated.
        */
        unsigned long long int getChangeCount() const { return mChangeCounter; }

        /** Triggers the generator to request the options that it needs.
        */
        virtual void respondOptions(Bool immediately,Bool isSimple)
        {
            Profile* p = getActiveProfile();
            if (p)
                p->respondOptions(immediately,isSimple);
        }

        /** Triggers the generator to request the options that it needs.
        */
        virtual void requestOptions(TerrainGroundTileRender* tileRender)
        {
            Profile* p = getActiveProfile();
            if (p)
                p->requestOptions(tileRender);

        }
        /** Generate a material for the given terrain using the active profile.
        */
        virtual MaterialPtr generate(TerrainGroundTileRender* tileRender)
        {
            Profile* p = getActiveProfile();
            if (!p)
                return MaterialPtr();
            else
                return p->generate(tileRender);
        }

        /** Get the maximum number of layers supported with the given terrain. 
        @note When you change the options on the terrain, this value can change. 
        */
        virtual uint8 getMaxLayers(TerrainGroundTileRender* tileRender) const
        {
            Profile* p = getActiveProfile();
            if (p)
                return p->getMaxLayers(tileRender);
            else
                return 0;
        }


        /** Update parameters for the given terrain using the active profile.
        */
        virtual void updateParams(const MaterialPtr& mat, TerrainGroundTileRender* tileRender)
        {
            Profile* p = getActiveProfile();
            if (p)
                p->updateParams(mat, tileRender);
        }

        /** Set the debug level of the material. 
        @remarks
        Sets the level of debug display for this material.
        What this debug level means is entirely depdendent on the generator, 
        the only constant is that 0 means 'no debug' and non-zero means 
        'some level of debugging', with any graduations in non-zero values
        being generator-specific.
        */
        virtual void setDebugLevel(unsigned int dbg)
        {
            if (mDebugLevel != dbg)
            {
                mDebugLevel = dbg;
                _markChanged();
            }
        }
        /// Get the debug level of the material. 
        virtual unsigned int getDebugLevel() const { return mDebugLevel; }

    protected:

        ProfileList mProfiles;
        mutable Profile* mActiveProfile;
        unsigned long long int mChangeCounter;
        TerrainLayerDeclaration mLayerDecl;
        unsigned int mDebugLevel;

    };

    typedef Ogre::SharedPtr<TerrainMaterialGenerator> TerrainMaterialGeneratorPtr;

    /** @} */
    /** @} */

}

/******************************************************************************/

#endif
