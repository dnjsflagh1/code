
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
    // ֲ��������
    /******************************************************************************/
	class TreeManager : public ITreeManager
	{
        friend class Scene;

	public:
		SINGLETON_INSTANCE( TreeManager )

        static Str TREE_CSV_FILE;
        static Str GRASS_CSV_FILE;
		
		// ������Դ
		// CN_MODIFY
		Bool            load( CChar* treeListCsv, CChar* grassListCsv, GameFilePackManager* packManager);
		// ж����Դ
		void            unload();

		//
		void			setScene(Scene* scene);

        // ���������
        virtual void    clear();

		/// Ӧ����Ⱦѡ��
		virtual void	applyRenderConfig();

        // ����������
        virtual Tree*   createTree(CChar* name, U32 baseTreeID, const Vec3& pos);
        // ����������
        virtual Tree*   createTree(U32 baseTreeID, const Vec3& pos);
        // �õ�������
        virtual Tree*   getTree(CChar* name); 
        // ����������
        virtual void    destroyTree(CChar* name);
        // ����������
        virtual void    destroyAllTree();

		/// �õ���ģ����������
		virtual UInt					getTreeDeclarationCount();
		/// �õ���ģ������
		virtual TreeDeclaration*		getTreeDeclarationByIndex( UInt index );
		/// �õ�������ģ������
		const std::map<MG::UInt, TreeDeclaration>& getTreeDeclMap();

		const std::map<String, Tree*>&	getAllTrees() { return mTrees; }

    public:

		// �����ݶ���
		virtual Grass*					createGrass(CChar* name, U32 grassID, const Vec3& vPos);
		// �����ݶ���
		virtual Grass*					createGrass(U32 grassID, const Vec3& vPos);
		//
		virtual Grass*					getGrass(CChar* name);
		// ���ò��Ŷ�λ�úͰ뾶
		virtual void					setGrassPerturbCircle(const Vec3& vPos, const Flt& radiu);
		// ���ٲݶ���
		virtual void					destroyGrass(CChar* name);
		// �������в�
		virtual void					destroyAllGrass();

		// ���²ݵ�Id
		virtual void					updateGrassIndex(Int iRow, Int iCol, UInt uGrassId);

		/// �õ�����ͼ��������
		virtual UInt					getGrassDeclarationCount();

		/// �õ�����ͼ����
		virtual GrassDeclaration*		getGrassDeclarationByIndex( UInt index );
		/// �õ����в�ģ������
		const std::map<MG::UInt, GrassDeclaration>& getGrassDeclMap();

		const std::map<String, Grass*>&	getAllGrasses() { return mGrasses; }

		// ����������ɼ�����
		virtual	void					setFarClipDistance(Flt farDistance);

		// �������绷��
		virtual void					setWorldEnv(const WorldEnvironment& env);

		//��ȡSpeedTree����
		virtual const WorldEnvironment& getWorldEnv();

		// ������
		virtual	void					setFog(Color cFogColor,	Flt	fFogStart, Flt fFogEnd);

		virtual void					setWindEnable(Bool bEnable);

		//�Ƿ�����
		virtual Bool					isWindEnabled();

		// ���÷��ǿ��
		virtual	void					setGlobalWindStrength(Flt fStrength);

		// ��ȡ���ǿ��
		virtual Flt						getGlobalWindStrength(void) const;

		// ���÷�ķ���
		virtual void					setGlobalWindDirection(Vec3& vDir);

		// ��ȡ��ķ���
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

		// ��Ⱦ���ͼ
		//void							renderToShadowMap(const StViewPort& viewPort, void* pColorDepthTexture, void* pDepthStencilSurface, const CameraParam& cameraParam);

		//void							renderZPass(const CameraParam& cameraParam);

		//for game,�ӳټ���
				void					AddTreeDelay(const STree& sTree);

				void					AddGrassDelay(const STree& sTree);

				//
				void					BuildAllTreeAndGrass();

				void					ClearBuildAllTreeAndGrass();

				//void					ClearBaseTree();
    protected:

        // ����������
        void            update(Bool bUpdate);

        // ��Ⱦ
		// ���������Ⱦ��Ӱ������������������Ⱦ�ò���
        void            render(Int renderPass, Ogre::Camera* cam);
		
        // ���豸����
        void            onResetDevice();
        // ���豸��ʧ
        void            onLostDevice();

    protected:
		// ����SpeedTree�����������
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

        // ��������
		Scene*                  mScene;
        // SpeedTreeϵͳ
        SpeedTreeSystem*        mSpeedTreeSystem;
		/// SpeedTree����
		WorldEnvironment		mWorldEnvironment;

        /// ʵ���б�
        std::map<String, Tree*> mTrees;
        /// ʵ������
        NameGenerator           mTreeNameGenerator;

		std::map<UInt, std::vector<STree>>	mTreeInstance;
		std::map<UInt, std::vector<STree>>	mGrassInstance;
		//std::vector<SGrassInstance>			mGrassInst;

		//SpeedTree::CArray<SpeedTree::TInstanceArray>	mTreeInstance;

		std::map<UInt, TreeDeclaration>	mTreeDeclMap;
		//std::vector<TreeDeclaration>	mTreeDeclVec;
		//std::vector<std::string>		mBaseTreesList;

		std::map<UInt, GrassDeclaration>	mGrassDeclMap;
		/// ʵ���б�
		std::map<String, Grass*>		mGrasses;
		/// ʵ������
		NameGenerator					mGrassNameGenerator;

		Bool							mGameMode;

	};
}
#endif