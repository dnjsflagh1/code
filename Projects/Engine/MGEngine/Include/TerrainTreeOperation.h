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
    //游戏地形TREE操作
    /******************************************************************************/
    class TerrainTreeOperation : public EditorOperation
    {
    public:
        TerrainTreeOperation();
        virtual ~TerrainTreeOperation();

        //回退一次操作
        virtual void    rollback();
        //相应一次操作
        virtual void	execute( TerrainChunk* chunk, Ogre::Rect& worldRect ){};
        //影响高度
        virtual void    influenceTree(Int x, Int y, Flt intensity) {};
    };

    /******************************************************************************/
    //游戏地形增加TREE操作
    /******************************************************************************/
    class TerrainAddTreeOperation : public TerrainTreeOperation
    {
    public:
        TerrainAddTreeOperation();
        virtual ~TerrainAddTreeOperation();

        //相应一次操作
        virtual	void	execute();
        //影响高度
        virtual void    influenceTree(Int x, Int y, Flt intensity);
	private:
		void calculateCirclePos( const Vec3 brushPos, const Flt brushSize, const Flt distance, std::vector<Vec3>& pos_list);
		void calculateColumPos(const Vec3 brushPos, const Flt brushSize, const Flt distance, std::vector<Vec3>& pos_list); 
    };

    /******************************************************************************/
    //游戏地形移除TREE操作
    /******************************************************************************/
    class TerrainRemoveTreeOperation : public TerrainTreeOperation
    {
    public:
        TerrainRemoveTreeOperation();
        virtual ~TerrainRemoveTreeOperation();

        //相应一次操作
        virtual	void	execute();
        //影响高度
        virtual void    influenceTree(Int x, Int y, Flt intensity);
    };

    /******************************************************************************/
    //游戏地形噪音分布TREE操作
    /******************************************************************************/
    class TerrainDefineTreeOperation : public TerrainTreeOperation
    {
    public:
        TerrainDefineTreeOperation();
        virtual ~TerrainDefineTreeOperation();

        //相应一次操作
        virtual	void	execute();
        //影响高度
        virtual void    influenceTree(Int x, Int y, Flt intensity);

    protected:

        virtual void	defineTree( U32 model, std::vector<ISceneObject*>& vec);

    };   
}

/******************************************************************************/

#endif

