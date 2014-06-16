/******************************************************************************/
#ifndef _EDITOROPERATION_H_
#define _EDITOROPERATION_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IEditorOperation.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //游戏编辑主接口
    /******************************************************************************/
    class EditorOperation : public IEditorOperation
    {
    public:
        EditorOperation();
        virtual ~EditorOperation();

        // 得到场景对象
        virtual Scene*      getScene( ) { return mScene; };
        
		//响应一次操作
		virtual void		execute();
		//回退一次操作
		virtual void		rollback();

    public:

        //响应一次操作
        virtual void		execute( TerrainChunk* chunk, Ogre::Rect& worldRect ) = NULL;

    protected:

        Scene* mScene;
    };

}

/******************************************************************************/

#endif

