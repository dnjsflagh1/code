/******************************************************************************/
#ifndef _STATICENTITYSET_H_
#define _STATICENTITYSET_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IEntity.h"
#include "ILogicBinder.h"
#include "OgreEntity.h"
#include "OgreEntityWrapper.h"
#include "IEntityGroup.h"

/******************************************************************************/
namespace MG
{
    
    struct StaticGeometryInstance
    {
        StaticGeometry* staticGeometry;
        Bool changeDirty;
        Bool isBuilded;

        StaticGeometryInstance()
            :staticGeometry(NULL)
            ,isBuilded(false)
            ,changeDirty(false)
        {

        }
    };
    
    
    /******************************************************************************/
    //��̬ʵ�弯��
    /******************************************************************************/
    class StaticEntitySet
    {
    public:
        StaticEntitySet(U32 modelDeclID, Scene* scene);
        virtual ~StaticEntitySet();

    public:

        //����
        void                update( Flt delta );

        /// Ӧ����Ⱦ����
        void                applyRenderConfig();
        /// ���ÿɼ���
        void                applyVisibleFlag();

        /// ���豸����
        void                reset();

        // ���Ӿ�̬ʵ��
        void                addStaticEntity(Vec3& pos, Qua& orientation, Vec3& scale, Bool isRandom, 
                                    Str staticGroup, Bool isReset); 

        // ������̬ʵ��
        void                buildStaticEntity(); 


        OgreEntityWrapper*  getModelObject();

    protected:

        //���¶�̬����
        void                updateMaterialDynamicParameter( Flt delta );
        
        void                createEntityTemplate( U32 modelDeclID );
        void                destroyEntityTemplate();
        
        StaticGeometry*     createOrRetriveStaticGeometry( Str staticGroup );
        void                destroyAllStaticGeometry();
        void                destroyAllStaticGeometryBackupData();

    private:

        Scene* mScene;

        U32 mModelDeclID;

        OgreEntityWrapper*  mOgreEntityTemplate;
        
        std::map< Str, StaticGeometryInstance > mStaticGeometryInstanceList;
  
    };







}


/******************************************************************************/

#endif
