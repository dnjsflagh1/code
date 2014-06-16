
/******************************************************************************/
#ifndef __TREEMANAGER_H__
#define __TREEMANAGER_H__
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITree.h"
#include "Tree.h"
#include "Grass.h"
#include "Forest/Forest.h"
#include "SpeedTreeDefine.h"
// CN_MODIFY
class GameFilePackManager;
namespace MG
{
    /******************************************************************************/
    // 植被管理器
    /******************************************************************************/
	class TreeManager : public ITreeManager
	{
        friend class Scene;

	public:
		SINGLETON_INSTANCE( TreeManager )

        static Str TREE_CSV_FILE;
        static Str GRASS_CSV_FILE;
		
		// 加载资源
		// CN_MODIFY
		Bool            load( CChar* treeListCsv, CChar* grassListCsv, GameFilePackManager* packManager);
		// 卸载资源
		void            unload();

		//
		void			setScene(Scene* scene);

        // 清空树世界
        virtual void    clear();

		/// 应用渲染选项
		virtual void	applyRenderConfig();

        // 创建树对象
        virtual Tree*   createTree(CChar* name, U32 baseTreeID, const Vec3& pos);
        // 创建树对象
        virtual Tree*   createTree(U32 baseTreeID, const Vec3& pos);
        // 得到树对象
        virtual Tree*   getTree(CChar* name); 
        // 销毁树对象
        virtual void    destroyTree(CChar* name);
        // 销毁所有树
        virtual void    destroyAllTree();

		/// 得到树模型声明数量
		virtual UInt					getTreeDeclarationCount();
		/// 得到树模型声明
		virtual TreeDeclaration*		getTreeDeclarationByIndex( UInt index );
		/// 得到所有树模型声明
		const std::map<MG::UInt, TreeDeclaration>& getTreeDeclMap();

		const std::map<String, Tree*>&	getAllTrees() { return mTrees; }

    public:

		// 创建草对象
		virtual Grass*					createGrass(CChar* name, U32 grassID, const Vec3& vPos);
		// 创建草对象
		virtual Grass*					createGrass(U32 grassID, const Vec3& vPos);
		//
		virtual Grass*					getGrass(CChar* name);
		// 设置草扰动位置和半径
		virtual void					setGrassPerturbCircle(const Vec3& vPos, const Flt& radiu);
		// 销毁草对象
		virtual void					destroyGrass(CChar* name);
		// 销毁所有草
		virtual void					destroyAllGrass();

		// 更新草的Id
		virtual void					updateGrassIndex(Int iRow, Int iCol, UInt uGrassId);

		/// 得到草贴图声明数量
		virtual UInt					getGrassDeclarationCount();

		/// 得到草贴图声明
		virtual GrassDeclaration*		getGrassDeclarationByIndex( UInt index );
		/// 得到所有草模型声明
		const std::map<MG::UInt, GrassDeclaration>& getGrassDeclMap();

		const std::map<String, Grass*>&	getAllGrasses() { return mGrasses; }

		// 设置摄像机可见距离
		virtual	void					setFarClipDistance(Flt farDistance);

		// 设置世界环境
		virtual void					setWorldEnv(const WorldEnvironment& env);

		//获取SpeedTree环境
		virtual const WorldEnvironment& getWorldEnv();

		// 设置雾
		virtual	void					setFog(Color cFogColor,	Flt	fFogStart, Flt fFogEnd);

		virtual void					setWindEnable(Bool bEnable);

		//是否开启风
		virtual Bool					isWindEnabled();

		// 设置风的强度
		virtual	void					setGlobalWindStrength(Flt fStrength);

		// 获取风的强度
		virtual Flt						getGlobalWindStrength(void) const;

		// 设置风的方向
		virtual void					setGlobalWindDirection(Vec3& vDir);

		// 获取风的方向
		virtual Vec3					getGlobalWindDirection(void) const;

		//
		virtual Bool					EnableSpecularLight();

		//
		virtual void					EnableSpecularLight(Bool bEnable);

		//
		virtual Bool					EnableTransmissionLight();

		//
		virtual void					EnableTransmissionLight(Bool bEnable);

		//
		virtual Bool					EnableDetailLayer();

		//
		virtual void					EnableDetailLayer(Bool bEnable);

		//
		virtual Bool					EnableDetailNormalMap();

		//
		virtual void					EnableDetailNormalMap(Bool bEnable);

		//
		virtual Bool					EnableAmbientContrast();

		//
		virtual void					EnableAmbientContrast(Bool bEnable);

		virtual void					setGrassLod(Flt fStartFade, Flt fEndFade);

		virtual void					getGrassLod(Flt& fStartFade, Flt& fEndFade);

		// 渲染深度图
		//void							renderToShadowMap(const StViewPort& viewPort, void* pColorDepthTexture, void* pDepthStencilSurface, const CameraParam& cameraParam);

		//void							renderZPass(const CameraParam& cameraParam);

		//for game,延迟加载
				void					AddTreeDelay(const STree& sTree);

				void					AddGrassDelay(const STree& sTree);

				//
				void					BuildAllTreeAndGrass();

				void					ClearBuildAllTreeAndGrass();

				//void					ClearBaseTree();
    protected:

        // 更新树世界
        void            update(Bool bUpdate);

        // 渲染
		// 传摄像机渲染阴影折射的摄像机，其它渲染用不到
        void            render(Int renderPass, Ogre::Camera* cam);
		
        // 当设备重启
        void            onResetDevice();
        // 当设备丢失
        void            onLostDevice();

    protected:
		// 加载SpeedTree的摄像机参数
		void			loadCameraParam( CameraParam& cameraParam, Ogre::Camera* pOgreCamera );

	private:

		TreeManager();//Scene* scene
		virtual ~TreeManager();

	private:

		bool			loadTreeCSV(CChar* csvName);
		
		bool			loadGrassCSV(CChar* csvName);

		void			renderTreesBox();
		
		//void			updateTreesInstanceId(int treeModelId, int delId);

	private:

        // 场景管理
		Scene*                  mScene;
        // SpeedTree系统
        SpeedTreeSystem*        mSpeedTreeSystem;
		/// SpeedTree环境
		WorldEnvironment		mWorldEnvironment;

        /// 实体列表
        std::map<String, Tree*> mTrees;
        /// 实体名字
        NameGenerator           mTreeNameGenerator;

		std::map<UInt, std::vector<STree>>	mTreeInstance;
		std::map<UInt, std::vector<STree>>	mGrassInstance;
		//std::vector<SGrassInstance>			mGrassInst;

		//SpeedTree::CArray<SpeedTree::TInstanceArray>	mTreeInstance;

		std::map<UInt, TreeDeclaration>	mTreeDeclMap;
		//std::vector<TreeDeclaration>	mTreeDeclVec;
		//std::vector<std::string>		mBaseTreesList;

		std::map<UInt, GrassDeclaration>	mGrassDeclMap;
		/// 实体列表
		std::map<String, Grass*>		mGrasses;
		/// 实体名字
		NameGenerator					mGrassNameGenerator;

		Bool							mGameMode;

	};
}
#endif