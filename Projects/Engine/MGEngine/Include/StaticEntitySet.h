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
    //静态实体集合
    /******************************************************************************/
    class StaticEntitySet
    {
    public:
        StaticEntitySet(U32 modelDeclID, Scene* scene);
        virtual ~StaticEntitySet();

    public:

        //更新
        void                update( Flt delta );

        /// 应用渲染配置
        void                applyRenderConfig();
        /// 设置可见组
        void                applyVisibleFlag();

        /// 当设备重置
        void                reset();

        // 增加静态实体
        void                addStaticEntity(Vec3& pos, Qua& orientation, Vec3& scale, Bool isRandom, 
                                    Str staticGroup, Bool isReset); 

        // 构建静态实体
        void                buildStaticEntity(); 


        OgreEntityWrapper*  getModelObject();

    protected:

        //更新动态数据
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
