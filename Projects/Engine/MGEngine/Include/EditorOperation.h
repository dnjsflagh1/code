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
    //��Ϸ�༭���ӿ�
    /******************************************************************************/
    class EditorOperation : public IEditorOperation
    {
    public:
        EditorOperation();
        virtual ~EditorOperation();

        // �õ���������
        virtual Scene*      getScene( ) { return mScene; };
        
		//��Ӧһ�β���
		virtual void		execute();
		//����һ�β���
		virtual void		rollback();

    public:

        //��Ӧһ�β���
        virtual void		execute( TerrainChunk* chunk, Ogre::Rect& worldRect ) = NULL;

    protected:

        Scene* mScene;
    };

}

/******************************************************************************/

#endif

