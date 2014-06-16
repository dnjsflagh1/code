/******************************************************************************/
#ifndef _TERRAINTREEOPERATION_H_
#define _TERRAINTREEOPERATION_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "EditorOperation.h"
#include "MGNoise3D.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //��Ϸ����TREE����
    /******************************************************************************/
    class TerrainTreeOperation : public EditorOperation
    {
    public:
        TerrainTreeOperation();
        virtual ~TerrainTreeOperation();

        //����һ�β���
        virtual void    rollback();
        //��Ӧһ�β���
        virtual void	execute( TerrainChunk* chunk, Ogre::Rect& worldRect ){};
        //Ӱ��߶�
        virtual void    influenceTree(Int x, Int y, Flt intensity) {};
    };

    /******************************************************************************/
    //��Ϸ��������TREE����
    /******************************************************************************/
    class TerrainAddTreeOperation : public TerrainTreeOperation
    {
    public:
        TerrainAddTreeOperation();
        virtual ~TerrainAddTreeOperation();

        //��Ӧһ�β���
        virtual	void	execute();
        //Ӱ��߶�
        virtual void    influenceTree(Int x, Int y, Flt intensity);
	private:
		void calculateCirclePos( const Vec3 brushPos, const Flt brushSize, const Flt distance, std::vector<Vec3>& pos_list);
		void calculateColumPos(const Vec3 brushPos, const Flt brushSize, const Flt distance, std::vector<Vec3>& pos_list); 
    };

    /******************************************************************************/
    //��Ϸ�����Ƴ�TREE����
    /******************************************************************************/
    class TerrainRemoveTreeOperation : public TerrainTreeOperation
    {
    public:
        TerrainRemoveTreeOperation();
        virtual ~TerrainRemoveTreeOperation();

        //��Ӧһ�β���
        virtual	void	execute();
        //Ӱ��߶�
        virtual void    influenceTree(Int x, Int y, Flt intensity);
    };

    /******************************************************************************/
    //��Ϸ���������ֲ�TREE����
    /******************************************************************************/
    class TerrainDefineTreeOperation : public TerrainTreeOperation
    {
    public:
        TerrainDefineTreeOperation();
        virtual ~TerrainDefineTreeOperation();

        //��Ӧһ�β���
        virtual	void	execute();
        //Ӱ��߶�
        virtual void    influenceTree(Int x, Int y, Flt intensity);

    protected:

        virtual void	defineTree( U32 model, std::vector<ISceneObject*>& vec);

    };   
}

/******************************************************************************/

#endif

