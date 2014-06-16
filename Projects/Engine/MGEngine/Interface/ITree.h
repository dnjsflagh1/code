
/******************************************************************************/
#ifndef __ITREE_H__
#define __ITREE_H__
/******************************************************************************/

#include "ISceneObject.h"

namespace MG
{

	struct TreeDeclaration 
	{
		U32		uId;
		Str		strName;
		Str		strPath;
		Flt		fLodStart;
		Flt		fLodEnd;
		Str		strNote;
	};
	
	struct GrassDeclaration
	{
		U32		uId;
		U32		uImageId;
		Str		strName;
		U32		uTotalRow;
		U32		uTotalCol;
		Flt		fWidth;
		Flt		fHeight;
		Flt		fWMin;
		Flt		fWMax;
		Flt		fHMin;
		Flt		fHMax;
		Flt		fRTWindWeight;		// right top
		Flt		fLTWindWeight;		// left top
		Flt		fLBWindWeight;		// left bottom
		Flt		fRBWindWeight;		// right bottom
		Str		strNote;
	};

	struct WorldEnvironment
	{
		WorldEnvironment()
		{
			vLightDir			= Vec3(1.f, 1.f, -1.f);
			cLightAmbient		= ColorSet::white();
			cLightDiffuse		= ColorSet::white();
			cLightSpecular		= ColorSet::white();
			cEmissive			= ColorSet::white();

			cGrassLightAmbient	= ColorSet::white();
			cGrassLightDiffuse	= ColorSet::white();
			cGrassLightSpecular	= ColorSet::white();
			cGrassEmissive		= ColorSet::white();

			cFogColor			= ColorSet::white();
			fFogStart			= 500.f;
			fFogEnd				= 5000.f;
		}

		// light
		Vec3	vLightDir;
		Color	cLightAmbient;
		Color	cLightDiffuse;
		Color	cLightSpecular;
		Color	cEmissive;

		//grass
		Color	cGrassLightAmbient;
		Color	cGrassLightDiffuse;
		Color	cGrassLightSpecular;
		Color	cGrassEmissive;

		// fog
		Color	cFogColor;
		Flt		fFogStart;
		Flt		fFogEnd;

		// shadow
	};
	
    /******************************************************************************/
    // 植被对象
    /******************************************************************************/
    class ITree : public ISceneObject
    {
	public:
		virtual UInt	getBaseTreeId() = 0;

		virtual	void	setReflect(Bool bReflect) = 0;

		virtual Bool	isNeedReflect() = 0;
    };

	class IGrass : public ISceneObject
	{
	public:
		virtual UInt	getBaseGrassId() = 0;

		virtual Flt		width() = 0;

		virtual void	width(Flt w) = 0;

		virtual Flt		height() = 0;

		virtual void	height(Flt h) = 0;
	};

    /******************************************************************************/
    // 植被管理器
    /******************************************************************************/
	class ITreeManager
	{
	public:
        
        // 清空树世界
        virtual void							clear() = 0;

        // 创建树对象
        virtual ITree*							createTree(CChar* name, U32 baseTreeID, const Vec3& pos) = 0;
        // 创建树对象
		virtual ITree*							createTree(U32 baseTreeID, const Vec3& pos) = 0;

        // 得到树对象
        virtual ITree*							getTree(CChar* name) = 0; 
        // 销毁树对象
        virtual void							destroyTree(CChar* name) = 0;
        // 销毁所有树
        virtual void							destroyAllTree() = 0;
		// 设置摄像机可见距离
		virtual void							setFarClipDistance(Flt farDistance) = 0;
		// 设置世界环境
		virtual void							setWorldEnv(const WorldEnvironment& env) = 0;
		//获取SpeedTree环境
		virtual const WorldEnvironment&			getWorldEnv() = 0;
		// 设置雾
		virtual	void							setFog(Color cFogColor,	Flt	fFogStart, Flt fFogEnd) = 0;

		/// 得到树模型声明数量
		virtual UInt							getTreeDeclarationCount() = 0 ;
		/// 得到树模型声明
		virtual TreeDeclaration*				getTreeDeclarationByIndex( UInt index ) = 0 ;
		/// 得到所有树模型声明
		virtual const std::map<MG::UInt, TreeDeclaration>& getTreeDeclMap() = 0;

		// 创建草对象
		virtual IGrass*							createGrass(CChar* name, U32 textureID, const Vec3& vPos) = 0;
		// 创建草对象
		virtual IGrass*							createGrass(U32 textureID, const Vec3& vPos) = 0;
		//
		virtual IGrass*							getGrass(CChar* name) = 0;
		// 设置草扰动位置和半径
		virtual void							setGrassPerturbCircle(const Vec3& vPos, const Flt& radiu) = 0;
		// 销毁草对象
		virtual void							destroyGrass(CChar* name) = 0;
		// 销毁所有草
		virtual void							destroyAllGrass() = 0;
		// 更新草的Id
		virtual void							updateGrassIndex(Int iRow, Int iCol, UInt uGrassId) = 0;
		/// 得到草贴图声明数量
		virtual UInt							getGrassDeclarationCount() = 0 ;
		/// 得到草贴图声明
		virtual GrassDeclaration*				getGrassDeclarationByIndex( UInt index ) = 0 ;
		/// 得到所有草模型声明
		virtual const std::map<MG::UInt, GrassDeclaration>& getGrassDeclMap() = 0;

		//开关风
		virtual void							setWindEnable(Bool bEnable) = 0;

		//是否开启风
		virtual Bool							isWindEnabled() = 0;

		//设置风的强度
		virtual void							setGlobalWindStrength(Flt fStrength) = 0;
		//获取风的强度
		virtual Flt								getGlobalWindStrength(void) const = 0;
		//设置风的方向
		virtual void							setGlobalWindDirection(Vec3& vDir) = 0;
		//获取风的方向
		virtual Vec3							getGlobalWindDirection(void) const = 0;

		//
		virtual Bool							EnableSpecularLight() = 0;

		//
		virtual void							EnableSpecularLight(Bool bEnable) = 0;

		//
		virtual Bool							EnableTransmissionLight() = 0;

		//
		virtual void							EnableTransmissionLight(Bool bEnable) = 0;

		//
		virtual Bool							EnableDetailLayer() = 0;

		//
		virtual void							EnableDetailLayer(Bool bEnable) = 0;

		//
		virtual Bool							EnableDetailNormalMap() = 0;

		//
		virtual void							EnableDetailNormalMap(Bool bEnable) = 0;

		//
		virtual Bool							EnableAmbientContrast() = 0;

		//
		virtual void							EnableAmbientContrast(Bool bEnable) = 0;

		virtual void							setGrassLod(Flt fStartFade, Flt fEndFade) = 0;

		virtual void							getGrassLod(Flt& fStartFade, Flt& fEndFade) = 0;
	};
}
#endif